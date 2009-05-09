#include "util.h"

#include <glt/gl.h>

void massageOpenGLMatrices()
{
    // Windows NT OpenGL seems to lose precision
    // when transform matricies are pushed and popped.
    // Here we force a push and pop so that it will
    // work better next time..

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPopMatrix();
}
