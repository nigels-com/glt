#include "scsclip.h"

#include "element.h"

#include <node/shape.h>

#include <glt/zplane.h>
#include <glt/error.h>
#include <glt/gl.h>

//
// Reset pixels that have any backfacing surface
// in front of the z-buffer
//

void csgRenderClipZBuffer(const CsgProduct &prod)
{
    GLERROR                             // Check for OpenGL errors

    glPushAttrib(GL_ENABLE_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Clear the stencil buffer
        glClear(GL_STENCIL_BUFFER_BIT);

        // Cull front facing polygons
        glCullFace(GL_FRONT);
        glEnable(GL_CULL_FACE);

        // Configure z-less depth test with
        // no updates to depth buffer
        glDepthFunc(GL_LESS);
        glDepthMask(GL_FALSE);

        // Configure stencil test to set pixels
        // to one which pass the depth test
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS,1,~0);
        glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

        // Draw all intersected objects in the CSG product
        for (GLuint i=0; i<prod.size(); i++)
            if (prod.positive(i))
                prod.shape(i)->draw();

        // Configure OpenGL for second pass, using
        // a stencil test to reset pixels with stencil
        // equal to one
        glDisable(GL_CULL_FACE);
        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_TRUE);
        glStencilFunc(GL_EQUAL,1,0xffff);
        glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);

        // Draw viewport covering polygon at zFar
        drawZfar();

    glPopAttrib();                      // Restore OpenGL state
    GLERROR                             // Check for OpenGL errors
}


