#include "parity.h"

#include <node/shape.h>

#include <glt/zplane.h>
#include <glt/error.h>

void parityTest(const GltShape &shape,const GLuint bit,const GLenum depthFunction)
{
    GLERROR

    const GLuint mask = 1<<bit;

    glPushAttrib(GL_ENABLE_BIT       | GL_DEPTH_BUFFER_BIT  |
                 GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glEnable(GL_STENCIL_TEST);              // Configure stencil test to toggle
        glStencilFunc(GL_ALWAYS,~0,~0);         // the mask bit for each pixel for
        glStencilOp(GL_KEEP,GL_KEEP,GL_INVERT); // each fragment.

        glEnable(GL_DEPTH_TEST);                // Configure the depth test
        glDepthFunc(depthFunction);             // (usually GL_LESS), and
        glDisable(GL_CULL_FACE);                // disable back-face culling

        glStencilMask(mask);
        glDepthMask(GL_FALSE);
        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

        shape.draw();

    glPopAttrib();

    GLERROR
}

void parityIntersect(const GltShape &shape,const GLuint bit,GLuint &mask,const GLenum depthFunction)
{
    parityTest(shape,bit,depthFunction);
    mask |= (1<<bit); // Set parity mask bit
}

void paritySubtract(const GltShape &shape,const GLuint bit,GLuint &mask,const GLenum depthFunction)
{
    parityTest(shape,bit,depthFunction);
    mask &= ~(1<<bit); // Clear parity mask bit
}

void parityApply(const GLuint parityMask,const GLuint stencilMask)
{
    GLERROR

    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glEnable(GL_STENCIL_TEST);                          // Use stencil testing to
        glStencilFunc(GL_NOTEQUAL,parityMask,stencilMask);  // restrict fragments to pixels
        glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);               // not satisfying the parity mask

        glEnable(GL_DEPTH_TEST);                            // Enable depth testing
        glDepthFunc(GL_ALWAYS);                             // Depth depth always passes
        glDisable(GL_CULL_FACE);                            // Disable face culling

        glStencilMask(0);                                   // Disable stencil updates
        glDepthMask(GL_TRUE);                               // Enable depth updates

        drawZfar();                                         // Draw viewport size polygon

    glPopAttrib();

    GLERROR
}
