#include "goldlay2.h"

/** \file
 *  \brief   Improved Layered Goldfeather CSG Rendering Algorithm
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 */

#include <csg/element.h>
#include <csg/buffer.h>
#include <csg/parity.h>
#include <csg/options.h>
#include <csg/util.h>
#include <csg/info.h>

#include <node/shape.h>
#include <node/shapes.h>

#include <glt/zplane.h>
#include <glt/countsrf.h>
#include <glt/buffer.h>
#include <glt/error.h>

#include <list>
using namespace std;

void csgRenderGoldfeatherLayeredImproved
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

        // Process each CSG product, in turn

        // For products of size greater than one, each layer
        // of each primitive needs to be clipped individually

        GLuint p;
        for (p=0; p<sumOfProducts.size(); p++)
            if (sumOfProducts[p].size()>1)
            {
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

                glDepthFunc(GL_ALWAYS);
                glDepthMask(GL_TRUE);

                // Copy OpenGL depth buffer to the 2nd buffer,
                // for merging back in later

                if (useSecondZbuffer)
                {
                    zBuffer2.read();
                    information.depthReads++;
                }

                //

                const CsgProduct &product = sumOfProducts[p];

                // Seperate elements into front (intersected) and
                // back (subtracted).  Front or back face culling is
                // used, depending on whether the element is subtracted.

                GltShapes front,back;
                product.split(front,back);

                // Find the depth complexity of front-facing and
                // back-facing surfaces seperately.

                const GLuint frontK = countSurfaces(front,COUNT_SURFACES_ALL);
                const GLuint backK  = countSurfaces(back ,COUNT_SURFACES_ALL);

                //

                const GLuint maxK   = std::max(frontK,backK);
                const GLuint totalK = frontK+backK;

                // Determine the number of bits required for
                // layer counting.

                GLuint lowerBits = 0;
                for (GLuint kTmp = maxK; kTmp>0; lowerBits++,kTmp>>=1);

                // Mask the lowest lowerBits bits in the stencil buffer
                // for layer counting and parity testing.  The other
                // stencil bits are reserved for layer parity masks.

                const GLuint lowerMask = (1<<lowerBits)-1;

                // Collect statistics
                information.depthComplexityFront += frontK;
                information.depthComplexityBack  += backK;
                information.depthComplexity      += totalK;
                information.stencilBufferKBits    = lowerBits;

                // Check that we have enough stencil bits to
                // do layer counting upto maxK

                assert(maxK <(1<<stencilBits));
                assert(maxK <(1<<lowerBits));

                // layerBit is the current stencil bit for layer parity mask

                GLuint layerBit = lowerBits;

                // Layer parity masks that don't fit into
                // stencil planes must be copied into memory

                list<GltFrameBufferStencilUbyte *> stencilBuffers;

                // Find the stencil mask for each layer

                GLuint k;
                for (k=0; k<totalK; k++)
                {
                    // Clear layer counting planes of
                    // stencil buffer in preparation
                    // for layer counting

                    glStencilMask(lowerMask);
                    glClear(GL_STENCIL_BUFFER_BIT);
                    information.stencilClears++;

                    // Setup depth testing to draw all
                    // fragments that pass the stencil test.

                    glDepthFunc(GL_ALWAYS);
                    glDepthMask(GL_TRUE);
                    glEnable(GL_CULL_FACE);

                    // Draw k'th layer into z-buffer

                    glEnable(GL_STENCIL_TEST);
                    glStencilOp(GL_INCR,GL_INCR,GL_INCR);
                    glStencilMask(lowerMask);

                    if (k<frontK)
                    {
                        glCullFace(GL_BACK);
                        glStencilFunc(GL_EQUAL,k,lowerMask);
                        front.draw();
                    }
                    else
                    {
                        glCullFace(GL_FRONT);
                        glStencilFunc(GL_EQUAL,k-frontK,lowerMask);
                        back.draw();
                    }

                    //
                    // Parity test layer against all primitives
                    //

                    // parityBit is the current stencil parity bit
                    // parityMask is the combined stencil parity mask

                    // Parity information is using the same bitplanes
                    // as layer counting.

                    GLuint parityBit = 0;
                    GLuint parityMask = 0;

                    // Clear lower bit-planes in preparation for parity testing

                    glStencilMask(lowerMask);
                    glClear(GL_STENCIL_BUFFER_BIT);
                    information.stencilClears++;

                    // Do parity testing

                    for (GLuint j=0; j<product.size(); j++)
                    {
                        if (product.positive(j))
                            parityIntersect(*product.shape(j),parityBit,parityMask,GL_LEQUAL);
                        else
                            paritySubtract (*product.shape(j),parityBit,parityMask,GL_LEQUAL);

                        // Use the next available stencil bit
                        parityBit++;

                        // If we've run out of stencil bits, or
                        // we're finished with parity testing, it's
                        // time to apply the parity mask

                        if ( (parityBit==lowerBits || j==product.size()-1) && parityBit )
                        {
                            // Reset pixels that fail parity test

                            parityApply(parityMask,lowerMask);

                            // Clear parity testing stencil planes

                            glStencilMask(lowerMask);
                            glClear(GL_STENCIL_BUFFER_BIT);
                            information.stencilClears++;

                            // Reset mask and current bit

                            parityMask = 0;
                            parityBit = 0;
                        }
                    }

                    // Now that parity clipping is complete, create a binary mask
                    // for pixels with z<zFar.  We'll use this flag later to
                    // merge all the clipped surfaces into the final image.

                    const GLuint layerMask = (1<<layerBit);

                    glStencilMask(layerMask);
                    glStencilFunc(GL_ALWAYS,layerMask,layerMask);
                    glStencilOp(GL_ZERO,GL_ZERO,GL_REPLACE);

                    glDepthMask(GL_FALSE);
                    glDepthFunc(GL_GREATER);
                    glDisable(GL_CULL_FACE);

                    drawZfar();

                    // Select the next stencil buffer bit for layer
                    // mask

                    layerBit++;

                    // If we've run out of stencil buffer bits, it's time
                    // to read the stencil buffer into main memory

                    if (layerBit==GLuint(stencilBits) && k+1<totalK)
                    {
                        layerBit = lowerBits;

                        stencilBuffers.push_back(new GltFrameBufferStencilUbyte());
                        information.stencilReads++;
                    }
                }

                // Replace saved zBuffer if possible, otherwise
                // clear depth buffer to z-far

                if (useSecondZbuffer)
                {
                    zBuffer2.write(false);
                    information.depthWrites++;
                }
                else
                {
                    // Preserve OpenGL z-buffer next time
                    useSecondZbuffer = true;

                    glDepthMask(GL_TRUE);
                    glClear(GL_DEPTH_BUFFER_BIT);
                    information.depthClears++;
                }

                // Use the stencil masks to mask each layer and merge the final
                // result.  Work in reverse order, since there may be masks in
                // the stencil buffer before we start copying stencil buffers
                // from memory.

                for (k=totalK-1; k<totalK; k--)
                {
                    // Select the previous stencil buffer bit for layer
                    // mask

                    layerBit--;

                    // If we've run out of stencil buffer bits, it's time
                    // to copy the next memory buffer into the stencil

                    if (layerBit<lowerBits)
                    {
                        layerBit = stencilBits-1;

                        stencilBuffers.back()->write();
                        delete stencilBuffers.back();
                        stencilBuffers.pop_back();
                        information.stencilWrites++;
                    }

                    // Clear layer counting planes of
                    // stencil buffer in preparation
                    // for layer counting

                    glStencilMask(lowerMask);
                    glClear(GL_STENCIL_BUFFER_BIT);
                    information.stencilClears++;

                    // Draw k'th layer into z-buffer

                    glDepthFunc(GL_LESS);
                    glDepthMask(GL_TRUE);
                    glEnable(GL_CULL_FACE);

                    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
                    glEnable(GL_NORMALIZE);
                    glEnable(GL_LIGHTING);

                    const GLuint layerMask = (1<<layerBit);

                    glEnable(GL_STENCIL_TEST);
                    glStencilOp(GL_INCR,GL_INCR,GL_INCR);
                    glStencilMask(lowerMask);

                    if (k<frontK)
                    {
                        glCullFace(GL_BACK);
                        glStencilFunc(GL_EQUAL,k|layerMask,lowerMask|layerMask);
                        front.draw();
                    }
                    else
                    {
                        glCullFace(GL_FRONT);
                        glStencilFunc(GL_EQUAL,(k-frontK)|layerMask,lowerMask|layerMask);
                        back.draw();
                    }
                }

                // Hopefully, no memory leaks!
                assert(stencilBuffers.size()==0);
            }
            else
            {
                // For CSG products of size one, simply
                // draw with z-less depth test

                glDepthFunc(GL_LESS);
                glDepthMask(GL_TRUE);

                glEnable(GL_DEPTH_TEST);
                glDisable(GL_STENCIL_TEST);

                glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
                glEnable(GL_NORMALIZE);
                glEnable(GL_LIGHTING);

                for (p=0; p<sumOfProducts.size(); p++)
                    if (sumOfProducts[p].size()==1)
                        sumOfProducts[p].front().drawFront();
            }

    glPopAttrib();                         // Restore OpenGL state
    GLERROR                                // Check for errors

    glFinish();                            // Wait for OpenGL to finish
    information.drawTime += timer.clock(); // Collect elapsed time for analysis
}

