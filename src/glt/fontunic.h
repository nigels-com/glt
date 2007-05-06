#ifndef GLT_FONTUNIC_H
#define GLT_FONTUNIC_H

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

/* $Id: fontunic.h,v 2.2 2007/05/06 16:46:24 nigels Exp $ */

/*! \file
    \brief OpenGL Unicode Font Class
    \ingroup GLT
*/

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <glt/config.h>
#include <glt/font.h>
#include <glt/dlcache.h>

/*! \class GltFontUnicode
    \brief OpenGL Unicode Font Class
    \ingroup GLT

    \todo Display lists are never recycled because DisplayListCache age is not ticking
*/

typedef GltDisplayListCache<GltChar> GltFontUnicodeCache;

class GltFontUnicode : public GltFont, private GltFontUnicodeCache
{
public:
    /// Constructor
    GltFontUnicode(void *data = NULL);
    /// Destructor
    ~GltFontUnicode();

    void init(void *);
    void clear();

    bool print(const GltChar    ch ) const;
    bool print(const GltString &str) const;
    int  width(const GltChar    ch ) const;

    //
    // Convert between raw font data and a GLTU buffer
    //

    static bool  makeHeader(std::string &header,const int compressed);
    static void *getHeader(const void * const h,int &compressed);

private:

    void OnDraw(const uint32 seed) const;

    //

    unsigned char *_data;
    unsigned int   _index[0x10001];
};

#endif
