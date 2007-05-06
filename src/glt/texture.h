#ifndef GLT_TEXTURE_H
#define GLT_TEXTURE_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2004 Nigel Stewart


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
    \brief OpenGL Texture Class
    \ingroup GLT

    $Id: texture.h,v 2.4 2007/05/06 03:03:32 nigels Exp $
*/

#include <glt/config.h>
#include <glt/gl.h>

#include <misc/refcount.h>

#include <iosfwd>
#include <string>

/*! \class   GltTexture
    \brief   OpenGL Texture Class
    \ingroup GLT
*/

class GltTexture;
typedef ReferenceCountPtr<GltTexture> GltTexturePtr;

class GltTexture
{
public:

    //
    // Constructor/Destructor
    //

    GltTexture(const GLenum target = GL_TEXTURE_2D); ///< Constructor
    ~GltTexture();                                   ///< Destructor

    //
    // Textures can't be copied
    //

private:

    GltTexture(const GltTexture &);              ///< Copy constructor is private to prevent copying
    GltTexture &operator=(const GltTexture &);   ///< Assignment operator is private to prevent copying

public:

    /// Initialise from PPM, PNG or TGA file
    bool 
    init
    (
        const std::string &filename,
        const bool         mipmap   = true,
        const GLenum       target   = GL_TEXTURE_2D
    );

    /// Initialise from compressed GLT format
    bool 
    init
    (
        const void  *buffer,
        const bool   mipmap = true,
        const GLenum target = GL_TEXTURE_2D
    );

    /// Initialise from raw string buffer
    bool
    init
    (
        const GLsizei      width,
        const GLsizei      height,
        const std::string &image,
        const bool         mipmap = true,
        const GLenum       target = GL_TEXTURE_2D
    );

    /// Initialise from raw memory buffer
    bool
    init
    (
        const GLsizei  width,
        const GLsizei  height,
        const byte    *image,
        const GLsizei  channels,
        const bool     mipmap = true,
        const GLenum   target = GL_TEXTURE_2D
    );

    void clear();           /// Reset texture and release OpenGL resources

    void set() const;       ///< Set the current OpenGL texture
    bool defined() const;   ///< Is the texture object defined?

    /*!
        \brief      Set wrapping of OpenGL texture coordinates
        \param      s    Horizontal mapping mode
        \param      t    Vertical mapping mode

        Wrapping mode can be either of
        <table>
        <tr><td><b>GL_CLAMP    </b></td><td> Clamp coordinate to [0,1].</td></tr>
        <tr><td><b>GL_REPEAT   </b></td><td> Ignore integer part of coordinate.</td></tr>
        </table>
    */
    void setWrap(const GLenum s,const GLenum t,const GLenum r = GL_REPEAT);

    /*!
        \brief      Set filtering of OpenGL texture
        \param      min  Texture minification function
        \param      mag  Texture magnification  function

        Wrapping mode is one of
        <table>
        <tr><td><b>GL_NEAREST               </b></td><td>Nearest texel.</td></tr>
        <tr><td><b>GL_LINEAR                </b></td><td>Linearly interpolate.</td></tr>
        <tr><td><b>GL_NEAREST_MIPMAP_NEAREST</b></td><td>Nearest texel in nearest mipmap.</td></tr>
        <tr><td><b>GL_NEAREST_MIPMAP_LINEAR </b></td><td>Linearly interpolate nearest texel from closest two mipmaps.</td></tr>
        <tr><td><b>GL_LINEAR_MIPMAP_NEAREST </b></td><td>Linearly interpolate from nearest mipmap.</td></tr>
        <tr><td><b>GL_LINEAR_MIPMAP_LINEAR  </b></td><td>Linearly interpolate interpolated texel from closest two mipmaps.</td></tr>
        </table>
    */
    void setFilter(const GLenum min,const GLenum mag);

    ///
    void setRowLength(const GLint rowLength);

    /// Gamma adjustment of OpenGL texture
    void setGamma(const real gamma);

    /// Hue-saturation-value adjustment of OpenGL texture
    void setHSVAdjust(const real hue,const real saturation,const real value);

    //
    //
    //

    const GLsizei width()  const;      ///< Texture width
    const GLsizei height() const;      ///< Texture height
    const GLuint  id()     const;      ///< OpenGL texture identifier

    // Serialisation

    /*!
        \brief GLT texture types
        \ingroup GLT
    */

    typedef enum
    {
        TEXTURE_TYPE_RGB = 0,           /*!< RGB              */
        TEXTURE_TYPE_RGBA,              /*!< RGBA             */
        TEXTURE_TYPE_GREY,              /*!< Greyscale        */
        TEXTURE_TYPE_GREYA,             /*!< Greyscale, Alpha */
        TEXTURE_TYPE_ALPHA,             /*!< Alpha            */
        TEXTURE_TYPE_BITMAP,            /*!< Bitmap           */
        TEXTURE_TYPE_INDEXED_RGB,       /*!< Indexed RGB      */
        TEXTURE_TYPE_INDEXED_RGBA       /*!< Indexed RGBA     */

        // Add new types to the end, for compatibility

    } GltTextureType;

    /// Encode GLT Texture header
    static bool makeHeader(
        std::string &header,
        const uint32 type,
        const uint32 width,
        const uint32 height,
        const uint32 alignment,
        const uint32 compressed,
        const uint32 bytes
    );

    /// Extract GLT Texture header
    static void *getHeader(
        const void * const h,
        uint32 &type,
        uint32 &width,
        uint32 &height,
        uint32 &alignment,
        uint32 &compressed,
        uint32 &bytes
    );

    static bool decodeImage(
        const void  *buffer,
        uint32      &format,
        uint32      &components,
        uint32      &width,
        uint32      &height,
        std::string &image
    );

private:

    GLenum  _target;

    GLint   _components;
    GLsizei _width;
    GLsizei _height;
    GLint   _border;
    GLenum  _format;
    GLenum  _type;
    GLint   _alignment;

    GLint   _rowLength;
    GLenum  _wrapS;
    GLenum  _wrapT;
    GLenum  _wrapR;
    GLenum  _filterMin;
    GLenum  _filterMag;

    real _gamma;
    real _hue,_saturation,_value;

    GLuint  _name;          ///< OpenGL texture name

    //

    void genTexture();        ///< Generate texture name using glGenTextures, if necessary
    void bindTexture() const; ///< Bind texture using glBindTexture
    void deleteTexture();     ///< Delete texture name and resources using glDeleteTextures

    static bool targetIs2D       (const GLenum target);  
    static bool targetIs2DCubeMap(const GLenum target);

    static GLenum textureBinding (const GLenum target);
};

#endif
