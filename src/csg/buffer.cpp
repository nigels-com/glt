#include "buffer.h"

#include <glt/zplane.h>
#include <glt/error.h>

////////////////////////////////////////////////

CsgDepthBufferHelper::CsgDepthBufferHelper(const bool useCopy)
: _useCopy(useCopy), _viewport(true), _buffer(NULL)
{
    if (_useCopy)
        glViewport(0,0,_viewport.width()>>1,_viewport.height());
}

CsgDepthBufferHelper::~CsgDepthBufferHelper()
{
    if (_buffer)
        delete _buffer;
    _buffer = NULL;
}

bool
CsgDepthBufferHelper::empty() const
{
    return _buffer==NULL;
}

void
CsgDepthBufferHelper::read()
{
    GLERROR

    if (_useCopy)
    {
        glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            _viewport.set();

            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0,_viewport.width(),0,_viewport.height(),0.0,1.0);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glRasterPos2f(_viewport.width()>>1,0.0F);

            glDisable(GL_STENCIL_TEST);
            glEnable(GL_DEPTH_TEST);
            glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
            glDepthMask(GL_TRUE);
            glDepthFunc(GL_ALWAYS);
            glDisable(GL_CULL_FACE);

            glCopyPixels(0,0,_viewport.width()>>1,_viewport.height(),GL_DEPTH);

            glPopMatrix();
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);

        glPopAttrib();
    }
    else
    {
        if (!_buffer)
            _buffer = new depthBuffer();
        else
            _buffer->read();
    }

    GLERROR
}

void
CsgDepthBufferHelper::write(const bool merge)
{
    GLERROR

    glDisable(GL_STENCIL_TEST);
    glDisable(GL_CULL_FACE);
    glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    if (merge)
        glDepthFunc(GL_LESS);
    else
        glDepthFunc(GL_ALWAYS);

    if (_useCopy)
    {
        glPushAttrib(GL_VIEWPORT_BIT);

            _viewport.set();

            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0,_viewport.width(),0,_viewport.height(),0.0,1.0);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glRasterPos2f(0.0f,0.0f);

            glCopyPixels(_viewport.width()>>1,0,_viewport.width()>>1,_viewport.height(),GL_DEPTH);

            glPopMatrix();
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);

        glPopAttrib();
    }
    else
        if (_buffer)
            _buffer->write();

    GLERROR
}


