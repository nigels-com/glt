#ifndef GLT_FONTUNIC_H
#define GLT_FONTUNIC_H

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
    \brief OpenGL Unicode Font Class
    \ingroup GLT

    $Id: fontunic.h,v 2.0 2004/02/08 19:44:11 nigels Exp $

    $Log: fontunic.h,v $
    Revision 2.0  2004/02/08 19:44:11  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.21  2003/08/05 08:03:49  nigels
    *** empty log message ***

    Revision 1.19  2003/06/26 09:58:08  nigels
    *** empty log message ***

    Revision 1.18  2003/06/02 07:05:12  nigels
    Tweak things for gcc 3.0.1

    Revision 1.17  2003/03/06 12:18:51  nigels
    *** empty log message ***

    Revision 1.16  2002/11/27 00:57:28  nigels
    expand

    Revision 1.15  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.14  2002/10/07 16:27:46  nigels
    Added CVS version control info


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
