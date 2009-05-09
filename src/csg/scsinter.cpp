#include "scsinter.h"

//
// OpenGL CSG Rendering
//
// Nigel Stewart (nigels@nigels.com)
// RMIT Department of Mechanical and Manufacturing Engineering
//
// Fast CSG Intersection of Convex Objects
//

/** \file
 * Fast CSG Intersection of Convex Objects Implementation
 *
 * \author  Nigel Stewart (nigels@nigels.com)
 * \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 */

#include <csg/element.h>
#include <csg/options.h>
#include <csg/info.h>

#include <node/shape.h>

#include <glt/gl.h>
#include <glt/zplane.h>
#include <glt/error.h>

#include <cassert>
using namespace std;

void csgRenderConvexIntersection
(
    const CsgProduct &product,          // CSG Product
    const CsgOptions &options,          // Runtime Options
          CsgInfo    &information       // Runtime Info
)
{
    GLERROR                             // Check for OpenGL errors

    CsgProduct intersect,subtract;      // Partition CSG product into
    product.split(intersect,subtract);  // intersected and subtracted

    // Preserve OpenGL state

    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT |
                 GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Enable writes to depth and stencil buffers only

        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
        glDepthMask(GL_TRUE);
        glStencilMask(~0);

        // Disable stencil testing and normalisation

        glDisable(GL_STENCIL_TEST);
        glDisable(GL_NORMALIZE);

        // Disable lighting, unless using NVIDIA hardware

        if (options.nvidiaHardware)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        // Draw the furthest front facing surface into z-buffer.

        const int n = intersect.size();

        glClearStencil(0);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Clear depth buffer, as necessary

        if (n>1)
        {
            glClearDepth(0.0);
            glDepthFunc(GL_GREATER);
            glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            information.depthClears++;
            information.stencilClears++;
        }
        else
        {
            glDepthFunc(GL_ALWAYS);
            glClear(GL_STENCIL_BUFFER_BIT);

            information.stencilClears++;
        }

        // Draw all intersected objects

        int i;
        for (i=0; i<n; i++)
            intersect.shape(i)->draw();

        // If there is more than one intersected object,
        // perform image-space clipping

        if (n>1)
        {
            // Count the number of back-facing surfaces behind each pixel.

            glEnable(GL_STENCIL_TEST);
            glStencilFunc(GL_ALWAYS,0,~0);
            glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);
            glCullFace(GL_FRONT);
            glDepthMask(GL_FALSE);

            for (i=0; i<n; i++)
                intersect.shape(i)->draw();

            // Reset the z-buffer for pixels where stencil != n
            // Also, reset stencil to zero

            glStencilFunc(GL_NOTEQUAL,n,~0);
            glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);
            glDepthFunc(GL_ALWAYS);
            glDepthMask(GL_TRUE);
            glDisable(GL_CULL_FACE);

            // Draw viewport covering polygon at zFar
            drawZfar();

            information.intersections += n;
        }

    glPopAttrib();                      // Restore OpenGL state
    GLERROR                             // Check for OpenGL errors
}

void csgRenderConvexIntersectionRGB
(
    const CsgProduct &product,
    const CsgOptions &options,
          CsgInfo    &info
)
{
    csgRenderConvexIntersection(product,options,info);

    //
    // Z-Buffer now contains the result of intersection.
    // Draw the result into colour buffer.
    //

    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glDepthFunc(GL_EQUAL);
    glDepthMask(GL_FALSE);
    glDisable(GL_STENCIL_TEST);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    for (GLuint i=0; i<product.size(); i++)
        if (product.positive(i))
            product.shape(i)->draw();

    glPopAttrib();
}
