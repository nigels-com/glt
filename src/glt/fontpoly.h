#ifndef GLT_FONTPOLY_H
#define GLT_FONTPOLY_H

#if 0  // Experimental, at this stage

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
    \brief   Polyfont OpenGL Font
    \ingroup GLT

    $Id: fontpoly.h,v 2.2 2004/02/16 01:26:18 nigels Exp $

    $Log: fontpoly.h,v $
    Revision 2.2  2004/02/16 01:26:18  nigels
    Whitespace differences

    Revision 2.1  2004/02/12 13:48:56  nigels
    no message

    Revision 1.1  2003/12/11 23:46:48  nigels
    Added PolyFont library

*/

#include <glt/config.h>
#include <glt/font.h>

#include <polyfonts/polyfonts.h>

/*! \class GltFontPolygon
    \brief Polyfont font class
    \ingroup GLT

    http://www.gameprogrammer.com/polyfonts/polyfonts.html
*/

class GltFontPolygon : public GltFont
{
public:

    GltFontPolygon(void *data = NULL);              ///< Constructor
    ~GltFontPolygon();                              ///< Destructor

    void init(void *);
    void clear();

    bool print(const GltChar ch)     const;
    bool print(const GltString &str) const;
    int  width(const GltChar    ch ) const;

private:

    pffont *_font;

    float pfGetCharDescent(wchar_t c) const;

    const pfglyph *getGlyph(const wchar_t c) const;
    static int     comp(const void *key, const void *target);

    float skew(float x, float y)       const;

    bool  _center;
    int   _weight;
    real  _skew;
};

#endif

#endif
