#ifndef GLT_BUFFER_H
#define GLT_BUFFER_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2003 Nigel Stewart

  Email:  nigels@nigels.com
  WWW:    http://www.nigels.com/glt/
  Forums: http://sourceforge.net/forum/?group_id=36869

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*! \file
    \brief   OpenGL Framebuffer Classes
    \ingroup GLT

    $Id: buffer.h,v 2.0 2004/02/08 19:44:11 nigels Exp $

    $Log: buffer.h,v $
    Revision 2.0  2004/02/08 19:44:11  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.28  2003/05/10 16:58:11  nigels
    Last tweaks for 0.8

    Revision 1.27  2003/03/06 12:15:54  nigels
    Documentation refinements

    Revision 1.26  2003/01/22 08:38:21  nigels
    *** empty log message ***

    Revision 1.25  2003/01/22 08:12:50  nigels
    Added JPEG support

    Revision 1.24  2002/11/27 00:57:28  nigels
    expand

    Revision 1.23  2002/11/07 15:40:44  nigels
    *** empty log message ***

    Revision 1.22  2002/10/11 08:32:05  nigels
    Added operator[] to stencil buffer

    Revision 1.21  2002/10/07 16:27:46  nigels
    Added CVS version control info


*/

#include <glt/config.h>
#include <glt/gl.h>
#include <glt/viewport.h>
#include <glt/error.h>

#include <misc/image.h>
#include <misc/string.h>

#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <cstring>

/////////////////////////// OpenGLbuffer ////////////////////////////

/*! \class   GltFrameBuffer
    \brief   Base class for framebuffer interfaces
    \ingroup GLT
 */

class GltFrameBuffer
{
public:

    /// Update from frame buffer
    virtual void read() = 0;
    /// Write to frame buffer
    virtual void write() const = 0;

    /// Viewport x
    GLuint x() const;
    /// Viewport y
    GLuint y() const;
    /// Viewport width
    GLuint width() const;
    /// Viewport height
    GLuint height() const;
    /// Viewport size in pixels
    GLuint size() const;

    /// Write to PPM file from memory
    virtual void writePPM(std::ostream &os) const = 0;
    /// Write to TGA file from memory
    virtual void writeTGA(std::ostream &os) const = 0;

    #ifdef GLT_PNG
    virtual void writePNG(std::ostream &os) const = 0;
    #endif

    #ifdef GLT_JPEG
    virtual void writeJPG(std::ostream &os) const = 0;
    #endif

protected:

    /// Constructor
    GltFrameBuffer();
    /// Constructor
    GltFrameBuffer(const GltViewport &viewport);

    /// Destructor
    virtual ~GltFrameBuffer();

    GltViewport _viewport;
};

/////////////////////////// GltFrameBufferRGB ////////////////////////////

/*! \class   GltFrameBufferRGB
    \brief   RGB frame buffer interface
    \ingroup GLT
 */

class GltFrameBufferRGB : public GltFrameBuffer
{
public:

    /// Constructor
    GltFrameBufferRGB();
//  /// Construct from memory buffer
//  GltFrameBufferRGB(GLubyte *pixels);
    /// Construct by blending between two other buffers
    GltFrameBufferRGB(const GltFrameBufferRGB &a,const GltFrameBufferRGB &b,const GLdouble alpha);
    /// Destructor
    ~GltFrameBufferRGB();

          GLubyte *operator[](const uint32 n)       { assert(n<size()); return (      GLubyte *) _image.data() + n*3; }
    const GLubyte *operator[](const uint32 n) const { assert(n<size()); return (const GLubyte *) _image.data() + n*3; }

    void read();
    void write() const;

    void writePPM(std::ostream &os) const;
    void writeTGA(std::ostream &os) const;

    #ifdef GLT_PNG
    virtual void writePNG(std::ostream &os) const;
    #endif

    #ifdef GLT_JPEG
    virtual void writeJPG(std::ostream &os) const;
    #endif

protected:

    std::string _image;         ///< Pixel storage
};

/////////////////////////// GltFrameBufferZ ////////////////////////////

/*! \class   GltFrameBufferZ
    \brief   Z-buffer interface
    \ingroup GLT
 */

template< class DepthType , GLenum GlDepthType >
class GltFrameBufferZ : public GltFrameBuffer
{
protected:

    std::string _image;         ///< Pixel storage
    GLint      _depthBits;

public:

    /// Constructor
    GltFrameBufferZ()
    : GltFrameBuffer()
    {
        glGetIntegerv(GL_DEPTH_BITS,&_depthBits);
        _image.resize(size()*sizeof(DepthType));
        read();
    };

    /// Destructor
    ~GltFrameBufferZ()
    {
    };

    /// Clear z-buffer to a particular value
    GltFrameBufferZ &
    operator=(const DepthType &value)
    {
        // Check that viewport has not changed since
        // construction.

        GLuint viewport[4];
        glGetIntegerv(GL_VIEWPORT,(GLint *) viewport);

        if (_width!=viewport[2] || _height!=viewport[3] || _pixels==NULL)
        {
            _x = viewport[0];
            _y = viewport[1];
            _width = viewport[2];
            _height = viewport[3];
            _size = _width*_height;

            if (_pixels)
                delete [] _pixels;

            _pixels = new DepthType[_size];
        }

        for (uint32 n=0; n<_size; n++)
            _pixels[n] = value;

        return *this;
    }

          DepthType &operator[](const uint32 n)       { return *((      DepthType *) _image.data() + n); }
    const DepthType &operator[](const uint32 n) const { return *((const DepthType *) _image.data() + n); }

    /// Read z-buffer from OpenGL frame buffer
    void
    read()
    {
        GLERROR

        //
        // Check that viewport has not changed since
        // construction.
        //

        GltViewport viewport(true);
        if (_viewport!=viewport || !_image.size())
        {
            _viewport = viewport;
            _image.resize(size()*sizeof(DepthType));
        }

        //

        glPixelStorei(GL_PACK_ALIGNMENT,sizeof(DepthType));
        glReadPixels(x(),y(),width(),height(),GL_DEPTH_COMPONENT,GlDepthType,(GLvoid *) _image.data());

        GLERROR
    }

    /// Read z-buffer to OpenGL frame buffer
    void
    write() const
    {
        GLERROR

        glPixelStorei(GL_UNPACK_ALIGNMENT,sizeof(DepthType));

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        glLoadIdentity();
        glOrtho(-1.0,1.0,-1.0,1.0,0.0,100.0);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glRasterPos2f(-1.0F,-1.0F);
        glDrawPixels(width(),height(),GL_DEPTH_COMPONENT,GlDepthType,(GLvoid *) _image.data());

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        GLERROR
    }

    /// Write z-buffer to PPM image
    void
    writePPM(std::ostream &os) const
    {
        std::string tmp;
        toGreyscale(tmp);

        std::string data;
        if (encodePPM(data,width(),height(),tmp))
            writeStream(os,data);
    }

    /// Write z-buffer to TGA image
    void
    writeTGA(std::ostream &os) const
    {
        std::string tmp;
        toHeightfield(tmp);

        std::string data;
        if (encodeTGA(data,width(),height(),tmp))
            writeStream(os,data);
    }

    #ifdef GLT_PNG
    /// Write z-buffer to PNG image
    void
    writePNG(std::ostream &os) const
    {
        std::string tmp;
        toGreyscale(tmp);

        std::string data;
        if (encodePNG(data,width(),height(),tmp))
            writeStream(os,data);

    }
    #endif

    #ifdef GLT_JPEG
    /// Write z-buffer to JPG image
    void
    writeJPG(std::ostream &os) const
    {
        std::string tmp;
        toGreyscale(tmp);

        std::string data;
        if (encodeJPG(data,width(),height(),tmp))
            writeStream(os,data);

    }
    #endif

    /// Maximum possible z value
    DepthType
    maxPossible() const
    {
        switch (GlDepthType)
        {
        case GL_UNSIGNED_SHORT:
            return DepthType(0xffff);
        case GL_UNSIGNED_INT:
            #ifdef GLT_WIN32
            return DepthType(0xffffffff - 6911);
            #else
            return DepthType(0xffffffff);
            #endif
        case GL_FLOAT:
            return DepthType(1.0);
        default:
            assert(0);
            return DepthType();
        }
    };

    /// Minimum possible z value
    DepthType
    minPossible() const
    {
        switch (GlDepthType)
        {
        case GL_UNSIGNED_SHORT: return 0x0;
        case GL_UNSIGNED_INT:   return 0x0;
        case GL_FLOAT:          return (DepthType) 0.0;
        default:
            assert(0);
            return DepthType();
        }
    };

    /// Obtain z-buffer histogram
    bool
    histogram(GLuint freq[64]) const
    {
        // Set all the counts to zero
        memset(freq,0,64*sizeof(GLuint));

        uint32 i;

        // For each pixel in buffer...
        switch (GlDepthType)
        {
        case GL_UNSIGNED_SHORT:
        case GL_UNSIGNED_INT:
            for (i=0; i<size(); i++)
            {
                const int index = (*this)[i]>>(_depthBits-5);
                assert(index>=0 && index<=63);
                freq[index]++;
            }
            break;
        default:
            assert(0);
            return DepthType();
        }

        return true;
    }

protected:

    /// Convert z-buffer to 8-bit greyscale
    void
    toGreyscale(std::string &image) const
    {
        image.resize(size());

        byte      *i = (byte *)       image.data();
        DepthType *j = (DepthType *) _image.data();

        const double min = minPossible();
        const double range = maxPossible()-min;

        for (uint32 k=0; k<size(); k++)
            *(i++) = (byte) ((*(j++)-min)/range*255.0);
    }

    /// Convert z-buffer to 24-bit heightfield
    void
    toHeightfield(std::string &image) const
    {
        image.resize(size()*3);

        byte      *i = (byte *)       image.data();
        DepthType *j = (DepthType *) _image.data();

        const double min = minPossible();
        const double range = maxPossible()-min;

        for (uint32 k=0; k<size(); k++)
        {
            double v = (*(j++)-min)/range;
            *(i++) = (byte) floor(v = v*255.0);
            *(i++) = (byte) floor(v = fmod(v,1.0)*255.0);
            *(i++) = (byte) floor(    fmod(v,1.0)*255.0);
        }
    }
};

/*! \typedef GltFrameBufferZFloat
    \brief   Floating point z-buffer
    \ingroup GLT
 */

 /*! \typedef GltFrameBufferZShort
     \brief   Unsigned short z-buffer
     \ingroup GLT
 */

 /*! \typedef GltFrameBufferZUint
     \brief   Unsigned integer z-buffer
     \ingroup GLT
 */

typedef GltFrameBufferZ<GLfloat,GL_FLOAT>           GltFrameBufferZFloat;
typedef GltFrameBufferZ<GLushort,GL_UNSIGNED_SHORT> GltFrameBufferZShort;
typedef GltFrameBufferZ<GLuint,GL_UNSIGNED_INT>     GltFrameBufferZUint;


/////////////////////////// GltFrameBufferStencil ////////////////////////////

/*! \class   GltFrameBufferStencil
    \brief   Stencil buffer interface
    \ingroup GLT
 */

template<class StencilType,GLenum GlStencilType>
class GltFrameBufferStencil : public GltFrameBuffer
{
protected:
    std::string _image;         ///< Pixel storage

public:

    GltFrameBufferStencil()
    : GltFrameBuffer()
    {
        _image.resize(size()*sizeof(StencilType));
        read();
    }

    ~GltFrameBufferStencil()
    {
    }

    void
    read()
    {
        GLERROR

        //
        // Check that viewport has not changed since
        // construction.
        //

        GltViewport viewport(true);
        if (_viewport!=viewport || !_image.size())
        {
            _viewport = viewport;
            _image.resize(size()*sizeof(StencilType));
        }

        //

        glPixelStorei(GL_PACK_ALIGNMENT,sizeof(StencilType));
        glReadPixels(x(),y(),width(),height(),GL_STENCIL_INDEX,GlStencilType,(GLvoid *) _image.data());

        GLERROR
    }

    void
    write() const
    {
        GLERROR

        glPixelStorei(GL_UNPACK_ALIGNMENT,sizeof(StencilType));

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(-1.0,1.0,-1.0,1.0,0.0,100.0);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glRasterPos2f(-1.0F,-1.0F);
        glStencilMask(~0);
        glDrawPixels(width(),height(),GL_STENCIL_INDEX,GlStencilType,(GLvoid *) _image.data());
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW);

        GLERROR
    }

          StencilType &operator[](const int i)       { return ((      StencilType *) _image.data())[i]; }
    const StencilType &operator[](const int i) const { return ((const StencilType *) _image.data())[i]; }

    void
    writePPM(std::ostream &os) const
    {
        // TODO - stencil depth != 8 ??

        std::string data;
        if (encodePPM(data,width(),height(),_image))
            writeStream(os,data);
    }

    void
    writeTGA(std::ostream &os) const
    {
        std::string data;
        if (encodeTGA(data,width(),height(),_image))
            writeStream(os,data);
    }

    #ifdef GLT_PNG
    void
    writePNG(std::ostream &os) const
    {
        std::string data;
        if (encodePNG(data,width(),height(),_image))
            writeStream(os,data);
    }
    #endif

    #ifdef GLT_JPEG
    void
    writeJPG(std::ostream &os) const
    {
        std::string data;
        if (encodeJPG(data,width(),height(),_image))
            writeStream(os,data);
    }
    #endif
};

/*! \typedef GltFrameBufferStencilUbyte
    \brief   Unsigned byte stencil buffer
    \ingroup GLT
 */

typedef GltFrameBufferStencil<GLubyte,GL_UNSIGNED_BYTE> GltFrameBufferStencilUbyte;


#endif
