#include "goldlayr.h"

/** \file
 *  \brief   Layered Goldfeather CSG Rendering Algorithm
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 *
 *  This algorithm is documented in detail in the
 *  following paper:
 *
 *  "An Improved CSG Rendering Algorithm"
 *  N. Stewart, G. Leach, S. John
 *  1998 Eurographics/Siggraph Graphics Hardware Workshop
 *  Lisbon, Portugal.
 *
 * The idea here is to clip more surfaces at once by
 * advantage of depth-complexity in the scene.
 * For front and back facing surfaces, we clip each 'layer'
 * rather than each primitive.  The assumption is that
 * the degree of overlap is less than n^2.
 * If depth-complexity is denoted 'k', this is O(kn)
 * rather than O(n^2).
 *
 */

#include <csg/element.h>
#include <csg/buffer.h>
#include <csg/parity.h>
#include <csg/shadez.h>
#include <csg/options.h>
#include <csg/util.h>
#include <csg/info.h>

#include <node/shape.h>
#include <node/shapes.h>

#include <glt/zplane.h>
#include <glt/countsrf.h>

#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif

void csgRenderGoldfeatherLayered
(
    const CsgSumOfProducts &sumOfProducts,
    const CsgOptions       &options,
          CsgInfo          &information
)
{
    Timer timer;        // Track elapsed time

    GLERROR             // Check for OpenGL errors

    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT |
                 GL_POLYGON_BIT | GL_VIEWPORT_BIT);

        // Simulated second OpenGL depth buffer
        CsgDepthBufferHelper zBuffer2(options.zBufferCopy);
        bool useSecondZbuffer = false;

        // Massage OpenGL transformation matricies, if necessary
        if (options.msDriver)
            massageOpenGLMatrices();

        // Query OpenGL for number of stencil bit-planes
        GLint stencilBits = 0;
        glGetIntegerv(GL_STENCIL_BITS,&stencilBits);
        information.stencilBits = GLuint(stencilBits);

        // Do not draw into RGBA, or do expensive
        // things like lighting or normalisation

        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
        glDisable(GL_NORMALIZE);

        // NVIDIA hardware generates different fragments depending
        // on the lighting mode

        if (options.nvidiaHardware)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        // Process each CSG product, in turn

        GLuint p;

        // For products of size greater than one, each layer
        // of each primitive needs to be clipped individually

        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_TRUE);

        for (p=0; p<sumOfProducts.size(); p++)
            if (sumOfProducts[p].size()>1)
            {
                const CsgProduct &product = sumOfProducts[p];

                // Here's the variation on Goldfeather.
                // Start with front facing surfaces of non-inverted
                // primitives.  Extract the 0 to kth layer and
                // clip against _all_ primitives.

                // Seperate elements into front (intersected) and
                // back (subtracted).  Front or back face culling is
                // used, depending on whether the element is subtracted.

                GltShapes front,back;
                product.split(front,back);

                //

                const GLint frontK = countSurfaces(front,COUNT_SURFACES_ALL);
                const GLint backK  = countSurfaces(back ,COUNT_SURFACES_ALL);
                const GLint kMax = frontK + backK;

                // Collect statistics
                information.depthComplexityFront += frontK;
                information.depthComplexityBack  += backK;
                information.depthComplexity      += kMax;

                assert(kMax<(1<<stencilBits));

                // For debugging, limit processing to one particular layer
                const bool oneLayerOnly = options.layer>=0;

                for (GLint k=0; k<kMax; k++)
                {
                    if (oneLayerOnly) k = options.layer;

                    // Copy OpenGL depth buffer to the 2nd buffer,
                    // for merging back in later

                    if (useSecondZbuffer)
                    {
                        zBuffer2.read();
                        information.depthReads++;
                    }

                    // Stencil needs to be cleared for layer counting
                    glClear(GL_STENCIL_BUFFER_BIT);
                    information.stencilClears++;

                    // Draw k'th layer into z-buffer

                    glDepthFunc(GL_ALWAYS);
                    glDepthMask(GL_TRUE);
                    glEnable(GL_CULL_FACE);

                    glEnable(GL_STENCIL_TEST);
                    glStencilOp(GL_INCR,GL_INCR,GL_INCR);
                    glStencilMask(~0);

                    if (k<frontK)
                    {
                        glCullFace(GL_BACK);
                        glStencilFunc(GL_EQUAL,k,~0);
                        front.draw();
                    }
                    else
                    {
                        glCullFace(GL_FRONT);
                        glStencilFunc(GL_EQUAL,k-frontK,~0);
                        back.draw();
                    }

                    // Clip depth buffer against all primitives
                    // in the CSG product.

                    GLint bit = 0;
                    GLuint mask = 0;

                    // Stencil needs to be cleared for parity clipping
                    glClear(GL_STENCIL_BUFFER_BIT);
                    information.stencilClears++;

                    for (GLuint j=0; j<product.size(); j++)
                    {
                        // The parity test is inverted depending on
                        // whether we're intersecting or subtracting.

                        if (product.positive(j))
                            parityIntersect(*product.shape(j),bit,mask,GL_LEQUAL);
                        else
                            paritySubtract(*product.shape(j),bit,mask,GL_LEQUAL);

                        bit++;

                        // Apply parity mask as soon as stencil bit planes
                        // have been exhausted, or finished with clipping

                        if ( (bit==stencilBits || j==product.size()-1 || oneLayerOnly) && bit )
                        {
                            // Pixels that don't match the parity mask
                            // are reset to zFar

                            parityApply(mask,~0);
                            glClear(GL_STENCIL_BUFFER_BIT);
                            information.stencilClears++;

                            mask = 0;
                            bit = 0;
                        }
                    }

                    // Merge with 2nd z-buffer, if available

                    if (useSecondZbuffer)
                    {
                        zBuffer2.write(true);
                        information.depthWrites++;
                    }

                    // Preserve 1st z-buffer next time
                    useSecondZbuffer = true;

                    // Exit loop if in one-layer debugging mode
                    if (oneLayerOnly) break;
                }
            }

        // (OPTIMISATION)
        //
        // For products of size one, no clipping is necessary
        // Simply draw front surfaces with z-less test

        glDisable(GL_STENCIL_TEST);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

        for (p=0; p<sumOfProducts.size(); p++)
            if (sumOfProducts[p].size()==1)
                sumOfProducts[p].front().drawFront();

        // Now that depth buffer contains CSG result,
        // the lit and shaded RGB result can be drawn.

        csgRenderLightShadeZBuffer(sumOfProducts,options);

    glPopAttrib();                         // Restore OpenGL state
    GLERROR                                // Check for errors
    glFinish();                            // Wait for OpenGL to finish

    information.drawTime += timer.clock(); // Collect elapsed time for analysis
}

