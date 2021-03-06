#include "texture.h"

/*! \file
    \ingroup GLT

    $Id: texture.cpp,v 2.6 2010/06/11 18:26:59 nigels Exp $
*/

#include <glt/gl.h>
#include <glt/glu.h>
#include <glt/error.h>

#include <misc/compress.h>
#include <misc/image.h>
#include <misc/string.h>

#include <iostream>
#include <fstream>
#include <string>

#include <cassert>
#include <cstring>
#include <cstdio>

using namespace std;

//#define DEBUG_THIS 0

//////////////////////////////////////////////////////////////////////////

GltTexture::GltTexture(const GLenum target)
:
    _target(target),
    _components(0),
    _width(0),
    _height(0),
    _border(0),
    _format(0),
    _type(0),
    _alignment(0),
    _rowLength(0),
    _wrapS(GL_REPEAT),
    _wrapT(GL_REPEAT),
    _wrapR(GL_REPEAT),
    _filterMin(GL_NEAREST_MIPMAP_LINEAR),
    _filterMag(GL_LINEAR),
    _gamma(1.0),
    _hue(0.0),
    _saturation(0.0),
    _value(0.0),

    _name(0)
{
    #ifdef DEBUG_THIS
    cout << "GltTexture::GltTexture" << endl;
    #endif
}

GltTexture::GltTexture(const GltTexture &)
{
    // Can't copy textures
    assert(0);
}

GltTexture::~GltTexture()
{
    #ifdef DEBUG_THIS
    cout << "GltTexture::~GltTexture" << endl;
    #endif

    #if !defined(NDEBUG)
    if (_name)
        cerr << "WARNING: Potential OpenGL texture leak (" << this << ")" << endl;
    #endif

    clear();
}

GltTexture &
GltTexture::operator=(const GltTexture &)
{
    // Can't copy textures
    assert(0);
    return *this;
}

void
GltTexture::setWrap(const GLenum s,const GLenum t,const GLenum r)
{
    _wrapS = s;
    _wrapT = t;
    _wrapR = r;

    if (_name)
    {
        GLint name;
        glGetIntegerv(textureBinding(_target),&name);
        if (name!=_name)
            glBindTexture(_target,_name);

            set();
            glTexParameteri(_target,GL_TEXTURE_WRAP_S,_wrapS);
            glTexParameteri(_target,GL_TEXTURE_WRAP_T,_wrapT);
            glTexParameteri(_target,GL_TEXTURE_WRAP_R,_wrapR);


        if (name!=_name)
            glBindTexture(_target,name);
    }
}

void
GltTexture::setFilter(const GLenum min,const GLenum mag)
{
    _filterMin = min;
    _filterMag = mag;

    if (_name)
    {
        GLint name;
        glGetIntegerv(textureBinding(_target),&name);
        if (name!=_name)
            glBindTexture(_target,_name);

        glTexParameteri(_target,GL_TEXTURE_MIN_FILTER,_filterMin);
        glTexParameteri(_target,GL_TEXTURE_MAG_FILTER,_filterMag);

        if (name!=_name)
            glBindTexture(_target,name);
    }
}

void
GltTexture::setRowLength(const GLint rowLength)
{
    _rowLength = rowLength;
}

void
GltTexture::setGamma(const real gamma)
{
    _gamma = gamma;
}

void
GltTexture::setHSVAdjust(const real hue,const real saturation,const real value)
{
    _hue = hue;
    _saturation = saturation;
    _value = value;
}

bool
GltTexture::init(const std::string &filename,const bool mipmap,const GLenum target)
{
    if (!filename.size())
        return false;

    #ifdef DEBUG_THIS
    cout << "GltTexture::init filename=" << filename << endl;
    #endif

    uint32 width;
    uint32 height;
    string data;

    ifstream is(filename.c_str(),ios::binary);
    readStream(is,data);

    string image;
    if (decode(width,height,image,data))
        return init(width,height,image,mipmap,target);

    return false;
}

bool
GltTexture::init(const void *data,const bool mipmap,const GLenum target)
{
    GLERROR

    #ifdef DEBUG_THIS
    cout << "GltTexture::init data=" << data << endl;
    #endif

    if (!targetIs2DCubeMap(target))
        clear();

#if 1
    uint32 format,components,width,height;
    string image;

    if (decodeImage(data,format,components,width,height,image))
    {
        if (_gamma!=1.0)
            adjustGamma(image,_gamma);

        if (_hue!=0.0 || _saturation!=0.0 || _value!=0.0)
            adjustHSV(image,width,height,_hue,_saturation,_value);

        _width      = width;
        _height     = height;
        _format     = format;
        _components = components;
        _type       = GL_UNSIGNED_BYTE;

        assert(image.size() && _components!=0);

        if (image.size() && _components!=0)
        {
            GLERROR

            if (targetIs2D(_target))
            {
                genTexture();
                set();
                glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
//              glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
                glTexParameteri(_target, GL_TEXTURE_MIN_FILTER,_filterMin);
                glTexParameteri(_target, GL_TEXTURE_MAG_FILTER,_filterMag);
                glTexParameteri(_target, GL_TEXTURE_WRAP_S, _wrapS);
                glTexParameteri(_target, GL_TEXTURE_WRAP_T, _wrapT);
                glTexParameteri(_target, GL_TEXTURE_WRAP_R, _wrapR);
            }

            glPixelStorei(GL_UNPACK_ROW_LENGTH,_rowLength);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            if (mipmap)
                gluBuild2DMipmaps(target,_components,_width,_height,_format,_type,&image[0]);
            else
            {
                cout << _components << endl;
                cout << _width << endl;
                cout << _height << endl;
                cout << _border << endl;

                glTexImage2D(target,0,_components,_width,_height,_border,_format,_type,&image[0]);
            }

            GLERROR

            return true;
        }

    }

    return false;
#else
    if (!data)
        return true;

    // Extract the header

    int type,width,height,alignment,compressed;
    void *pixels = getHeader((const byte *) data,type,width,height,alignment,compressed);
    bool deletePixels = false;

    // If the header is valid, initialise texture

    assert(pixels);

    if (pixels)
    {
        switch (type)
        {
        case TEXTURE_TYPE_RGB:          _components = 3; _format = GL_RGB;             break;
        case TEXTURE_TYPE_RGBA:         _components = 4; _format = GL_RGBA;            break;
        case TEXTURE_TYPE_GREY:         _components = 1; _format = GL_LUMINANCE;       break;
        case TEXTURE_TYPE_GREYA:        _components = 2; _format = GL_LUMINANCE_ALPHA; break;
        case TEXTURE_TYPE_ALPHA:        _components = 1; _format = GL_ALPHA;           break;
        case TEXTURE_TYPE_BITMAP:       _components = 1; _format = TEXTURE_TYPE_BITMAP;break;
        case TEXTURE_TYPE_INDEXED_RGB:  _components = 3; _format = GL_RGB;             break;
        case TEXTURE_TYPE_INDEXED_RGBA: _components = 4; _format = GL_RGBA;            break;
        default: assert(0); break;
        }

        if (compressed)
        {
            string tmp;
            bool ok;

            #ifdef GLT_JPEG
            if (compressed==3)
            {
                char *data = reinterpret_cast<char *>(pixels) + sizeof(uint32);
                uint32 size = *reinterpret_cast<uint32 *>(pixels);

                string buffer(data,data+size);

                uint32 w,h;
                ok = ::decodeJPG(w,h,tmp,buffer);

                assert(w==width);
                assert(h=height);
                ok = ok && (w==width) && (h==height);
            }
            else
            #endif
                ok = ::decompress(tmp,pixels);

            assert(ok);
            assert(tmp.size());

            if (ok && tmp.size())
            {
                const int n = width*height*_components;
                pixels = new unsigned char[n];
                deletePixels = true;

                if (type==TEXTURE_TYPE_INDEXED_RGB)
                {
                    string rgb;
                    indexed2rgb(rgb,tmp);

                    if (_gamma!=1.0)
                        adjustGamma(rgb,_gamma);

                    if (_hue!=0.0 || _saturation!=0.0 || _value!=0.0)
                        adjustHSV(rgb,width,height,_hue,_saturation,_value);

                    memcpy(pixels,rgb.c_str(),n);

                    /* TODO - Deal with indexed data */
                }
                else
                {
                    if (_gamma!=1.0)
                        adjustGamma(tmp,_gamma);

                    if (_hue!=0.0 || _saturation!=0.0 || _value!=0.0)
                        adjustHSV(tmp,width,height,_hue,_saturation,_value);

                    memcpy(pixels,tmp.c_str(),n);
                }
            }
            else
                pixels = NULL;
        }

        /* TODO - Deal with uncompressed indexed data */

        _width = width;
        _height = height;

        _type = GL_UNSIGNED_BYTE;
    }

    assert(pixels && _components!=0);

    if (pixels && _components!=0)
    {
        GLERROR

        if (_target==GL_TEXTURE_2D)
        {
            genTexture();
            set();
            glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,_filterMin);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,_filterMag);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapS);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, _wrapR);
        }

        glPixelStorei(GL_UNPACK_ROW_LENGTH,_rowLength);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        if (mipmap)
            gluBuild2DMipmaps(_target,_components,_width,_height,_format,_type,pixels);
        else
            glTexImage2D(_target,0,_components,_width,_height,_border,_format,_type,pixels);

        if (deletePixels)
            delete [] (unsigned char *) pixels;

        GLERROR

        return true;
    }

    GLERROR

    return false;
#endif
}

bool
GltTexture::init(const GLsizei width,const GLsizei height,const std::string &image,const bool mipmap,const GLenum target)
{
    #ifdef DEBUG_THIS
    cout << "GltTexture::init width=" << width << " height=" << height << " mipmap=" << mipmap << endl;
    #endif

    if (!targetIs2DCubeMap(target))
        clear();

    GLenum mode = 0;
    int    channels = 0;

    if (width*height  == (GLsizei)image.size()) { mode = GL_LUMINANCE;       channels = 1; }
    if (width*height*2== (GLsizei)image.size()) { mode = GL_LUMINANCE_ALPHA; channels = 2; }
    if (width*height*3== (GLsizei)image.size()) { mode = GL_RGB;             channels = 3; }
    if (width*height*4== (GLsizei)image.size()) { mode = GL_RGBA;            channels = 3; }

    if (!mode || !channels)
        return false;

    if (targetIs2D(_target))
    {
        genTexture();
        set();
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        glTexParameteri(_target, GL_TEXTURE_MIN_FILTER,_filterMin);
        glTexParameteri(_target, GL_TEXTURE_MAG_FILTER,_filterMag);
        glTexParameteri(_target, GL_TEXTURE_WRAP_S, _wrapS);
        glTexParameteri(_target, GL_TEXTURE_WRAP_T, _wrapT);
        glTexParameteri(_target, GL_TEXTURE_WRAP_R, _wrapR);
    }

    glPixelStorei(GL_UNPACK_ROW_LENGTH,_rowLength);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (mipmap)
        gluBuild2DMipmaps(target,channels,width,height,mode,GL_UNSIGNED_BYTE,image.data());
    else
        glTexImage2D(target,0,channels,width,height,0,mode,GL_UNSIGNED_BYTE,image.data());

    _width = width;
    _height = height;

    return true;
}

bool
GltTexture::init(const GLsizei width,const GLsizei height,const byte *image,const GLsizei channels,const bool mipmap,const GLenum target)
{
    #ifdef DEBUG_THIS
    cout << "GltTexture::init width=" << width << " height=" << height << " mipmap=" << mipmap << endl;
    #endif

    if (!targetIs2DCubeMap(target))
        clear();

    GLenum mode = 0;

    switch (channels)
    {
        case 1: mode = GL_LUMINANCE;       break;
        case 2: mode = GL_LUMINANCE_ALPHA; break;
        case 3: mode = GL_RGB;             break;
        case 4: mode = GL_RGBA;            break;
        default: return false;
    }

    if (targetIs2D(_target))
    {
        genTexture();
        set();
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        glTexParameteri(_target, GL_TEXTURE_MIN_FILTER,_filterMin);
        glTexParameteri(_target, GL_TEXTURE_MAG_FILTER,_filterMag);
        glTexParameteri(_target, GL_TEXTURE_WRAP_S, _wrapS);
        glTexParameteri(_target, GL_TEXTURE_WRAP_T, _wrapT);
        glTexParameteri(_target, GL_TEXTURE_WRAP_R, _wrapR);
    }

    #ifdef DEBUG_THIS
    cout << "GltTexture::init rowLength=" << _rowLength << endl;
    #endif

    glPixelStorei(GL_UNPACK_ROW_LENGTH,_rowLength);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (mipmap)
        gluBuild2DMipmaps(target,channels,width,height,mode,GL_UNSIGNED_BYTE,image);
    else
        glTexImage2D(target,0,channels,width,height,0,mode,GL_UNSIGNED_BYTE,image);

    _width = width;
    _height = height;

    return true;
}

void
GltTexture::clear()
{
    deleteTexture();

    _components = 0;
    _width = 0;
    _height = 0;
    _border = 0;
    _format = 0;
    _type = 0;
    _alignment = 0;
}

void
GltTexture::set() const
{
    bindTexture();
}

bool
GltTexture::defined() const
{
    return _name!=0;
}

const GLsizei GltTexture::width()  const { return _width;  }
const GLsizei GltTexture::height() const { return _height; }
const GLuint  GltTexture::id()     const { return _name;   }

////////////////////////////////////////////////////////////////////////////

// Create variable-length header for texture data

bool GltTexture::makeHeader
(
    string       &header,
    const uint32  type,
    const uint32  width,
    const uint32  height,
    const uint32  alignment,
    const uint32  compressed,
    const uint32  bytes
)
{
    sprintf(header,"GLTT %u %u %u %u %u %u",type,width,height,alignment,compressed,bytes);
    header += '\0';
    return true;
}

// Decode variable-length header for texture data

void *
GltTexture::getHeader
(
    const void * const data,
    uint32            &type,
    uint32            &width,
    uint32            &height,
    uint32            &alignment,
    uint32            &compressed,
    uint32            &bytes
)
{
    const char * const h = (const char * const) data;

    if (h[0]=='G' && h[1]=='L' && h[2]=='T' && h[3]=='T' && h[4]==' ')
    {
        if (sscanf(h+5,"%u %u %u %u %u %u",&type,&width,&height,&alignment,&compressed,&bytes)==6)
            return (void *) (h + strlen(h) + 1);
    }

    return NULL;
}

bool
GltTexture::decodeImage
(
    const void  *buffer,
    uint32      &format,
    uint32      &components,
    uint32      &width,
    uint32      &height,
    std::string &image
)
{
    if (!buffer)
        return false;

    // Extract the header

    uint32 type,alignment,compressed,bytes;
    void *pixels = getHeader((const byte *) buffer,type,width,height,alignment,compressed,bytes);
//    bool deletePixels = false;

    // If the header is valid, initialise texture

    assert(pixels);

    if (pixels)
    {
        switch (type)
        {
            case TEXTURE_TYPE_RGB:          components = 3; format = GL_RGB;             break;
            case TEXTURE_TYPE_RGBA:         components = 4; format = GL_RGBA;            break;
            case TEXTURE_TYPE_GREY:         components = 1; format = GL_LUMINANCE;       break;
            case TEXTURE_TYPE_GREYA:        components = 2; format = GL_LUMINANCE_ALPHA; break;
            case TEXTURE_TYPE_ALPHA:        components = 1; format = GL_ALPHA;           break;
            case TEXTURE_TYPE_BITMAP:       components = 1; format = TEXTURE_TYPE_BITMAP;break;
            case TEXTURE_TYPE_INDEXED_RGB:  components = 3; format = GL_RGB;             break;
            case TEXTURE_TYPE_INDEXED_RGBA: components = 4; format = GL_RGBA;            break;
            default:                        assert(0);                                   break;
        }

        if (compressed)
        {
            bool ok;

            #ifdef GLT_JPEG
            if (compressed==3)
            {
                const char *data = reinterpret_cast<const char *>(pixels);
                string buffer(data,data+bytes);

                uint32 w,h;
                ok = ::decodeJPG(w,h,image,buffer);

                assert(w==width);
                assert(h=height);
                ok = ok && (w==width) && (h==height);

/*
                char *data = reinterpret_cast<char *>(pixels) + sizeof(uint32);
                uint32 size = *reinterpret_cast<uint32 *>(pixels);

                string buffer(data,data+size);

                uint32 w,h;
                ok = ::decodeJPG(w,h,image,buffer);

                assert(w==width);
                assert(h=height);
                ok = ok && (w==width) && (h==height);
*/
            }
            else
            #endif
                ok = ::decompress(image,pixels);

            assert(ok);
            assert(image.size());

            if (ok && image.size() && type==TEXTURE_TYPE_INDEXED_RGB)
            {
                string rgb;
                indexed2rgb(rgb,image);
                image = rgb;
            }

            if (!ok)
                return false;
        }
        else
        {
            // Simply copy uncompressed data
            const char *buffer = reinterpret_cast<const char *>(pixels);
            image = string(buffer,buffer+width*height*components);
        }

        return true;
    }

    return false;
}

void
GltTexture::genTexture()
{
    if (!_name)
        glGenTextures(1,&_name);
    assert(_name);
}

void 
GltTexture::bindTexture() const
{
    if (_name)
        glBindTexture(_target,_name);
}

void
GltTexture::deleteTexture()
{
    if (_name)
        glDeleteTextures(1,&_name);
    _name = 0;
}

bool 
GltTexture::targetIs2D(const GLenum target)
{
    return 
        targetIs2DCubeMap(target)              ||
        target==GL_TEXTURE_2D                  ||
        target==GL_PROXY_TEXTURE_2D            ||
        target==GL_PROXY_TEXTURE_CUBE_MAP;
}

bool
GltTexture::targetIs2DCubeMap(const GLenum target)
{
    return
        target==GL_TEXTURE_CUBE_MAP_POSITIVE_X ||
        target==GL_TEXTURE_CUBE_MAP_NEGATIVE_X ||
        target==GL_TEXTURE_CUBE_MAP_POSITIVE_Y ||
        target==GL_TEXTURE_CUBE_MAP_NEGATIVE_Y ||
        target==GL_TEXTURE_CUBE_MAP_POSITIVE_Z ||
        target==GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
}

GLenum
GltTexture::textureBinding(const GLenum target)
{
    switch (target)
    {
        case GL_TEXTURE_1D:       return GL_TEXTURE_BINDING_1D;
        case GL_TEXTURE_2D:       return GL_TEXTURE_BINDING_2D;
        case GL_TEXTURE_3D:       return GL_TEXTURE_BINDING_3D;
        case GL_TEXTURE_CUBE_MAP: return GL_TEXTURE_BINDING_CUBE_MAP;
        default:
            return 0;
    }
}
