#include "goldfeat.h"

//
// OpenGL CSG Rendering
//
// Nigel Stewart (nigels@nigels.com)
// RMIT Department of Mechanical and Manufacturing Engineering
// 14th February 2001
//
// Goldfeather CSG Rendering Algorithm
//
// This module is an OpenGL/C++ implementation
// of the following journal article:
//
// "Near Real-Time CSG Rendering Using Tree Normalisation
// "and Geometric Pruning", Jack Goldfeather, et. al.
// IEEE Computer Graphics and Applications, May 1989, pp 20-28
//
// TODO: Test and Doxygenate

#include <csg/element.h>
#include <csg/buffer.h>
#include <csg/parity.h>
#include <csg/shadez.h>
#include <csg/options.h>
#include <csg/info.h>
#include <csg/util.h>

#include <node/shape.h>

#include <glt/zplane.h>
#include <glt/buffer.h>
#include <glt/countsrf.h>

#include <iostream>
using namespace std;

void csgRenderGoldfeather
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

        // Massage OpenGL transformation matricies, if necessary
        if (options.msDriver)
            massageOpenGLMatrices();

        // Query OpenGL for number of stencil bit-planes,
        // usually eight

        GLint stencilBits = 0;
        glGetIntegerv(GL_STENCIL_BITS,&stencilBits);
        information.stencilBits = GLuint(stencilBits);

        // Do not draw into RGBA, or do expensive
        // things like lighting or normalisation

        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
        glDisable(GL_NORMALIZE);

        // Nvidia hardware generates different fragments depending
        // on the lighting mode.  The depth will need to match
        // when csgRenderLightShadeZBuffer is called.

        if (options.nvidiaHardware)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        // Process each CSG product, in turn

        bool useSecondZbuffer = false;
        GLuint p;

        // For products of size greater than one, each layer
        // of each primitive needs to be clipped individually

        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_TRUE);

        for (p=0; p<sumOfProducts.size(); p++)
            if (sumOfProducts[p].size()>1)
            {
                const CsgProduct &product = sumOfProducts[p];

                // Non-trivial products are clipped,
                // each layer of each primitive at a time.

                for (GLuint i=0; i<product.size(); i++)
                {
                    // Determine depth complexity of the shape,
                    // each layer will be clipped in turn

                    glEnable(GL_CULL_FACE);
                    glCullFace(GL_BACK);
                    const GLuint maxK = countSurfaces(*product.shape(i),COUNT_SURFACES_ALL);

                    for (GLuint k=0; k<maxK; k++)
                    {
                        information.layerClips++;

                        // Copy OpenGL depth buffer to the 2nd buffer,
                        // for merging back in later

                        if (useSecondZbuffer)
                        {
                            zBuffer2.read();
                            information.depthReads++;
                        }

                        // In the convex case, only one layer to be
                        // processed for this primitive.

                        if (maxK==1)
                        {
                            glDisable(GL_STENCIL_TEST);

                            // Draw front or back surface into z-buffer
                            if (product.positive(i))
                                product[i].drawFront();
                            else
                                product[i].drawBack();
                        }
                        else
                        {
                            glClear(GL_STENCIL_BUFFER_BIT);
                            information.stencilClears++;

                            glEnable(GL_STENCIL_TEST);
                            glStencilOp(GL_INCR,GL_INCR,GL_INCR);
                            glStencilFunc(GL_EQUAL,k,~0);
                            glStencilMask(~0);

                            if (product.positive(i))
                                product[i].drawFront();
                            else
                                product[i].drawBack();

                            glClear(GL_STENCIL_BUFFER_BIT);
                            information.stencilClears++;
                        }

                        // Clip depth buffer against other primitives
                        // in the CSG product.

                        GLuint bit  = 0;
                        GLuint mask = 0;

                        for (GLuint j=0; j<product.size(); j++)
                        {
                            // Only clip against other shapes

                            if (j!=i)
                            {
                                // The parity test is inverted depending on
                                // whether we're intersecting or subtracting.

                                if (product.positive(j))
                                    parityIntersect(*product.shape(j),bit,mask);
                                else
                                    paritySubtract(*product.shape(j),bit,mask);

                                bit++;
                            }

                            // Apply parity mask as soon as stencil bit planes
                            // have been exhausted, or finished with clipping

                            if ( (bit==GLuint(stencilBits) || j==product.size()-1) && bit )
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
                    }
                }
            }

        // Optimisation
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
