#include "buffer.h"

/*! \file
    \ingroup GLT

    $Id: buffer.cpp,v 1.2 2004/02/08 14:13:18 jgasseli Exp $

    $Log: buffer.cpp,v $
    Revision 1.2  2004/02/08 14:13:18  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.16  2003/05/10 16:58:11  nigels
    Last tweaks for 0.8

    Revision 1.15  2003/01/22 08:12:50  nigels
    Added JPEG support

    Revision 1.14  2002/11/27 00:57:28  nigels
    expand

    Revision 1.13  2002/11/07 15:40:44  nigels
    *** empty log message ***

    Revision 1.12  2002/10/09 15:09:38  nigels
    Added RCS Id and Log tags


*/

#include <cassert>
#include <cstring>
#include <cstdio>
using namespace std;

GltFrameBuffer::GltFrameBuffer()
: _viewport(true)
{
}

GltFrameBuffer::GltFrameBuffer(const GltViewport &viewport)
: _viewport(viewport)
{
}

GltFrameBuffer::~GltFrameBuffer()
{
}

GLuint GltFrameBuffer::x() const        { return _viewport.x(); }
GLuint GltFrameBuffer::y() const        { return _viewport.y(); }
GLuint GltFrameBuffer::width() const    { return _viewport.width();  }
GLuint GltFrameBuffer::height() const   { return _viewport.height(); }
GLuint GltFrameBuffer::size() const     { return _viewport.pixels(); }

////////////////////////////////////////////////////////////////////////////////////

GltFrameBufferRGB::GltFrameBufferRGB()
: GltFrameBuffer()
{
    _image.resize(size()*3);
    read();
}

/*
GltFrameBufferRGB::GltFrameBufferRGB(GLubyte *pixels)
: GltFrameBuffer()
{
}
*/

GltFrameBufferRGB::GltFrameBufferRGB(const GltFrameBufferRGB &a,const GltFrameBufferRGB &b,const GLdouble alpha)
{
    if (a.width()!=b.width())
        return;

    if (a.height()!=b.height())
        return;

    _viewport = a._viewport;
    _image.resize(size()*3);

    for (GLuint i=0; i<size()*3; i++)
        _image[i] = GLubyte((1.0-alpha)*a._image[i] + alpha*b._image[i]);
}

GltFrameBufferRGB::~GltFrameBufferRGB()
{
}

void
GltFrameBufferRGB::read()
{
    //
    // Check that viewport has not changed since
    // construction.
    //

    GltViewport viewport(true);
    if (_viewport!=viewport || !_image.size())
    {
        _viewport = viewport;
        _image.resize(size()*3);
    }

    //
    // Read the depth buffer
    //

    glPixelStorei(GL_PACK_ALIGNMENT,sizeof(GLubyte));
    glReadPixels(x(),y(),width(),height(),GL_RGB,GL_UNSIGNED_BYTE,(GLvoid *) _image.data());
}

void
GltFrameBufferRGB::write() const
{
    glPixelStorei(GL_UNPACK_ALIGNMENT,sizeof(GLubyte));

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1.0,1.0,-1.0,1.0,0.0,100.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(-1.0F,-1.0F);
    glDrawPixels(width(),height(),GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) _image.data());
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}

void
GltFrameBufferRGB::writePPM(ostream &os) const
{
    string data;
    if (encodePPM(data,width(),height(),_image))
        writeStream(os,data);
}

void
GltFrameBufferRGB::writeTGA(ostream &os) const
{
    string data;
    if (encodeTGA(data,width(),height(),_image))
        writeStream(os,data);
}

#ifdef GLT_PNG
void
GltFrameBufferRGB::writePNG(ostream &os) const
{
    string data;
    if (encodePNG(data,width(),height(),_image))
        writeStream(os,data);
}
#endif

#ifdef GLT_JPEG
void
GltFrameBufferRGB::writeJPG(ostream &os) const
{
    string data;
    if (encodeJPG(data,width(),height(),_image))
        writeStream(os,data);
}
#endif

