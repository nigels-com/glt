#ifndef GLT_FONTTEX_H
#define GLT_FONTTEX_H

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
    \brief   Textured OpenGL Font
    \ingroup GLT

    $Id: fonttex.h,v 2.1 2004/02/16 01:09:31 nigels Exp $

    $Log: fonttex.h,v $
    Revision 2.1  2004/02/16 01:09:31  nigels
    Tweak the horizontal spacing of characters
    Tweak the GREY_ALPHA texture to improve appearance

    Revision 1.7  2003/03/06 12:18:45  nigels
    *** empty log message ***

    Revision 1.6  2003/02/07 09:57:10  nigels
    Added GltChar and GltString

    Revision 1.5  2002/11/27 00:57:28  nigels
    expand

    Revision 1.4  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.3  2002/11/06 15:27:23  nigels
    gcc 3.2 -Wall noise

    Revision 1.2  2002/10/07 16:27:46  nigels
    Added CVS version control info

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
