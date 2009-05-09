#include "scs.h"

/*!
    \file
    \brief   Sequenced Convex Subtraction (SCS) CSG Rendering Algorithm
    \ingroup CSG

    The Sequenced Convex Subtraction CSG Rendering Algorithm is
    described in the following papers:

    "A CSG Rendering Algorithm for Convex Objects"
    N. Stewart, G. Leach, S. John,
    The 8-th International Conference in Central Europe on Computer Graphics,
    Visualisation and Interactive Digital Media '2000 - WSCG 2000,
    Volume II, pp. 369-372

    "Linear-Time CSG Rendering of Intersected Convex Objects"
    N. Stewart, G. Leach, S. John,
    The 10-th International Conference in Central Europe on
    Computer Graphics, Visualization and Computer Vision'2002 - WSCG 2002,
    Volume II, pp. 437-444

   \author  Nigel Stewart (nigels@nigels.com)

    \note SGI ONYX2 requires a hack:

    // ONYX2 Hack
    #if 0
    glColor3f(0,0,0);
    glDisable(GL_LIGHTING);
    drawZfar();
    #endif
*/

#include <csg/scsk.h>
#include <csg/scsseq.h>
#include <csg/scsclip.h>
#include <csg/scsinter.h>
#include <csg/scssubtr.h>
#include <csg/shadez.h>
#include <csg/buffer.h>
#include <csg/element.h>
#include <csg/options.h>
#include <csg/info.h>
#include <csg/util.h>

#include <glt/zplane.h>
#include <glt/error.h>
#include <glt/gl.h>

#include <math/real.h>
#include <misc/timer.h>

#include <vector>
#include <list>
#include <string>
#include <iosfwd>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

// Define this for info
//#define DEBUG_SCS

// Define this to print subtraction sequences
//#define DEBUG_SCS_SEQUENCE

//

#if defined(NDEBUG) && defined(DEBUG_SCS)
#undef DEBUG_SCS
#endif

#if defined(NDEBUG) && defined(DEBUG_SCS_SEQUENCE)
#undef DEBUG_SCS_SEQUENCE
#endif

void
csgRenderSequencedConvexSubtraction
(
    const CsgSumOfProducts &sumOfProducts,
    const CsgOptions       &options,
          CsgInfo          &information
)
{
    GLERROR             // Check for OpenGL errors

    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT | GL_VIEWPORT_BIT);

        CsgDepthBufferHelper zBuffer2(options.zBufferCopy);

        if (options.msDriver)
            massageOpenGLMatrices();

        // NVIDIA hardware generates different fragments depending
        // on the lighting mode

        if (options.nvidiaHardware)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        glDisable(GL_NORMALIZE);
        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_TRUE);

        glDisable(GL_STENCIL_TEST);
        glStencilMask(~0);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // For each product

        GLuint p;
        for (p=0; p<sumOfProducts.size();)
        {
            GLERROR

            // Current CSG product
            const CsgProduct &product = sumOfProducts[p];

            // Determine the subtraction sequence
            CsgSubtractionSequence sequence;
            csgRenderSubtractionSequence(product,options,sequence,information);

            #ifdef DEBUG_SCS_SEQUENCE
            cout << seqenceString(sequence) << endl;
            #endif

            Timer timer;        // Track elapsed time

            // Do CSG intersection
            csgRenderConvexIntersection(product,options,information);

            // Do CSG subtraction and z-buffer clipping
            if (sequence.size() && options.scsSubtraction)
            {
                csgRenderConvexSubtraction(product,sequence,options,information);

                if (options.scsZBufferClip)
                    csgRenderClipZBuffer(product);
            }

            /* If doing products sorted from back to front,
               we want to shade each product, rather than the
               combined z-buffer */

//          csgRenderLightShadeZBuffer(sumOfProducts[p],options);

            // (OPTIMISATION)
            //
            // CSG products of size one can be merged directly
            // using normal rasterisation, rather than z-buffer
            // merging.  This only works because no subtractions
            // need to be applied to products of size one.

            p++;
            while (p<sumOfProducts.size() && sumOfProducts[p].size()==1)
            {
                glDepthFunc(GL_LESS);
                sumOfProducts[p].front().drawFront();
                p++;
            }

            GLERROR

            // Merge with current saved z-buffer, if available

            if (!zBuffer2.empty())
            {
                zBuffer2.write(true);
                information.depthWrites++;
            }

            // Copy z-buffer to a safe place, if there are more
            // products to be processed

            if (p<sumOfProducts.size())
            {
                zBuffer2.read();
                information.depthReads++;
            }

            information.drawTime += timer.clock(); // Collect elapsed time for analysis

        }

        GLERROR

        Timer timer;        // Track elapsed time

        // Now that depth buffer contains CSG result,
        // the lit and shaded RGB result can be drawn.

        csgRenderLightShadeZBuffer(sumOfProducts,options);

    glPopAttrib();                         // Restore OpenGL state
    GLERROR                                // Check for errors
    glFinish();                            // Wait for OpenGL to finish


    information.drawTime += timer.clock(); // Collect elapsed time for analysis
}

/////////////////////////////////////////////////////////////

void csgRenderSubtractionSequence
(
    const CsgProduct             &product,
    const CsgOptions             &options,
          CsgSubtractionSequence &sequence,
          CsgInfo                &information
)
{
    // Collect sequence encoding time
    Timer timer;

    // Split product into intersected, and subtracted

    CsgProduct intersect,subtract;
    product.split(intersect,subtract);

    #ifdef DEBUG_SCS
    cout << "CSG Product: ";
    cout << intersect.size() << " intersected, ";
    cout << subtract.size()  << " subtracted." << endl;
    #endif

    // Use object-space overlap graph for sequence encoding

    if (options.overlapGraph)
    {
        information.encodeTime += timer.clock();

        sequence = gscsSequence(product,options,information);

        timer.start();
    }
    else

    // Use view independent or view dependent sequence
    // encoding without overlap graph information.

    {
        // Determine number of objects n
        const int n = subtract.size();

        // Determine depth complexity k
        int k = subtract.size();
        if (options.sampleDepthComplexity)
        {
            information.encodeTime += timer.clock();

            k = csgSampleK(subtract,options,information);
            k = clamp<int>(k,0,subtract.size());

            // Collect depth complexity for analysis
            information.depthComplexity = (CsgInfo::intType) k;

            timer.start();
        }

        #ifdef DEBUG_SCS
        cout << "k=" << k << endl;
        #endif

        // Find the subtraction sequence for n and k
        sequence = gscsSequence(n,k);

        // Adjust indecies
        gscsRemapSequence(sequence,product);
    }

    // Record the total encoding time
    information.encodeTime += timer.clock();
}

