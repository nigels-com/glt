#ifndef GLT_FONTTEX_H
#define GLT_FONTTEX_H

/*
  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2007 Nigel Stewart

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

/* $Id: fonttex.h,v 2.3 2007/05/06 16:46:24 nigels Exp $ */

/*! \file
    \brief   Textured OpenGL Font
    \ingroup GLT
*/

#include <glt/config.h>

#include <glt/font.h>
#include <glt/texture.h>

/*! \class GltFontTexture
    \brief GLT Textured font class
    \ingroup GLT

    Based on Mark Kilgard's article and code:

    A Simple OpenGL-based API for Texture Mapped Text
    http://www.opengl.org/resources/code/rendering/mjktips/TexFont/TexFont.html
*/

class GltFontTexture : public GltFont
{
public:
    /// Constructor
    GltFontTexture(void *data = NULL);
    /// Destructor
    ~GltFontTexture();

    void init(void *);
    void clear();

    bool print(const GltChar ch) const;
    bool print(const GltString &str) const;
    int  width(const GltChar ch) const;

    //
    // Convert between raw font data and a GLTF buffer
    //

    static bool  makeHeader(std::string &header,const int width,const int height);
    static void *getHeader(const void * const h,int &width,int &height);

private:

    typedef struct
    {
        uint16 glyph;
        byte   width;
        byte   height;
        char   xoffset;
        char   yoffset;
        char   advance;
        char   dummy;           // Ensure 32-bit alignment
        int16  x;
        int16  y;
    }
    GlyphInfo;

    typedef struct
    {
        GLfloat t0[2];
        GLshort v0[2];
        GLfloat t1[2];
        GLshort v1[2];
        GLfloat t2[2];
        GLshort v2[2];
        GLfloat t3[2];
        GLshort v3[2];
        byte    width;
        byte    advance;
    }
    GlyphVertexInfo;

    //

//    bool print(const char ch) const;
//    bool print(const std::string &str) const;

    void compileLists(void *);

    GltTexture _texture;
    int32      _maxAscent;
    int32      _maxDescent;
    uint32     _numGlyphs;
    uint32     _minGlyph;
    uint32     _range;

    GlyphInfo         *_glyph;
    GlyphVertexInfo   *_glyphVertex;
    GlyphVertexInfo  **_glyphLut;

//  int   _width;
//  int   _height;
//  int   _listBase;
};

#endif
