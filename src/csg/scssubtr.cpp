#include "scssubtr.h"

//
// OpenGL CSG Rendering
//
// Nigel Stewart (nigels@nigels.com)
// RMIT Department of Mechanical and Manufacturing Engineering
//
// Fast CSG Intersection of Convex Objects
//

/** \file
 * CSG Subtraction of Convex Objects Implementation
 *
 * \author  Nigel Stewart (nigels@nigels.com)
 * \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 */

#include <csg/element.h>
#include <csg/scs.h>
#include <csg/options.h>
#include <csg/info.h>

#include <node/shape.h>

#include <glt/gl.h>
#include <glt/zplane.h>
#include <glt/error.h>

#include <cassert>
#include <iostream>
using namespace std;

//#define DEBUG_SAMPLES 1

void csgRenderConvexSubtraction
(
    const CsgProduct             &product,      // CSG Product
    const CsgSubtractionSequence &sequence,     // Subtraction Sequence
    const CsgOptions             &options,      // Runtime Options
          CsgInfo                &information   // Runtime Info
)
{
    GLERROR                                     // Check for OpenGL errors

    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT |
                 GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Enable writes to depth and stencil buffers only

        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
        glDepthMask(GL_TRUE);
        glStencilMask(~0);

        // Enable stencil and depth testing, disable normalisation

        glEnable(GL_STENCIL_TEST);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_NORMALIZE);

        // Culling mode is optional (perhaps faster)

        if (options.cullFaces)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);

        // Disable lighting, unless using NVIDIA hardware

        if (options.nvidiaHardware)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        // Determine the number of stencil buffer bits

        GLint stencilBits = 0;
        glGetIntegerv(GL_STENCIL_BITS,&stencilBits);
        assert(stencilBits>0);

        information.stencilBits = GLuint(stencilBits);

        const GLuint stencilMask = (1<<stencilBits)-1;
              GLuint stencilCode = 0;

        //

        #ifdef DEBUG_SAMPLES
        GLuint *samples = new GLuint[sequence.size()];
        glGenQueriesARB(sequence.size(),samples);
        #endif

        // Subtract each object in the sequence...

        for (GLuint i=0; i<sequence.size(); i++)
        {
            // Clear stencil buffer when necessary

            if (++stencilCode>stencilMask)
            {
                stencilCode = 1;
                glClear(GL_STENCIL_BUFFER_BIT);
                information.stencilClears++;
            }

            // Get the i'th entry in the sequence

            const GLuint j = sequence[i];
            assert(!product.positive(j));

            const GltShapePtr &shape = product.shape(j);
            assert(shape.get());

            // Set stencil flag for front facing surfaces
            // closer or equal to the z-buffer

            glCullFace(GL_BACK);
            glDepthFunc(GL_LEQUAL);
            glDepthMask(GL_FALSE);
            glStencilFunc(GL_ALWAYS,stencilCode,stencilMask);
            glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

            shape->draw();

            // Replace z-buffer with back facing surface
            // iff greater than z-buffer and stencil flag is true

            glCullFace(GL_FRONT);
            glDepthFunc(GL_GEQUAL);
            glDepthMask(GL_TRUE);
            glStencilFunc(GL_EQUAL,stencilCode,stencilMask);
            glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);

            #ifdef DEBUG_SAMPLES
            glBeginQueryARB(GL_SAMPLES_PASSED_ARB,samples[i]);
            #endif

            shape->draw();

            #ifdef DEBUG_SAMPLES
            glEndQueryARB(GL_SAMPLES_PASSED_ARB);
            #endif
        }

    glPopAttrib();                                // Restore OpenGL state

    GLERROR;                                      // Check for OpenGL errors

    information.subtractions += sequence.size();  // Collect subtraction statistics

    #ifdef DEBUG_SAMPLES
    for (GLuint i=0; i<sequence.size(); i++)
    {
        GLuint count;
        glGetQueryObjectuivARB(samples[i],GL_QUERY_RESULT_ARB,&count);
        cout << i << " " << sequence[i] << " " << count << endl;
    }

    glDeleteQueriesARB(sequence.size(),samples);
    delete [] samples;
    #endif
}
