#ifndef GLT_COLMAP_H
#define GLT_COLMAP_H

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
    \brief   One Dimensional Color-Mapping Class
    \ingroup GLT

    $Id: colmap.h,v 1.1 2004/02/08 11:46:10 jgasseli Exp $

    $Log: colmap.h,v $
    Revision 1.1  2004/02/08 11:46:10  jgasseli
    Initial revision

    Revision 1.15  2003/05/10 16:58:11  nigels
    Last tweaks for 0.8

    Revision 1.14  2003/03/06 12:16:05  nigels
    *** empty log message ***

    Revision 1.13  2002/11/27 00:57:28  nigels
    expand

    Revision 1.12  2002/11/07 15:40:44  nigels
    *** empty log message ***

    Revision 1.11  2002/10/07 16:27:46  nigels
    Added CVS version control info


*/

#include <glt/color.h>

#include <list>

/*! \class   GltColorMap
    \brief   One Dimensional Color-Mapping Class
    \ingroup GLT
 */

class GltColorMap
{
public:
    /// Constructor
    GltColorMap();
    /// Destructor
    ~GltColorMap();

    /// Add an entry to the color map
    void addEntry(const real t,const GltColor &color);
    /// Add an entry to the color map, with alpha
    void addEntry(const real t,const GltColor &color,const real alpha);

    /// Clear
    void clear();

    /// Lookup a color map value, using interpolation
    GltColor  lookup(const real t) const;
    /// Lookup the i'th entry of the color map
    double    lookup(const int  i) const;

    /// Number of entries
    const int    size()     const;
    /// Beginning of domain
    const real start()    const;
    /// Ending of domain
    const real end()      const;
    /// Duration of domain
    const real duration() const;

    /// Adjust color map domain
    GltColorMap &operator+=(const real x);
    /// Adjust color map domain
    GltColorMap &operator-=(const real x);
    /// Adjust color map domain
    GltColorMap &operator*=(const real x);
    /// Adjust color map domain
    GltColorMap &operator/=(const real x);

private:

    typedef std::list< std::pair<real,GltColor> >    map;
    typedef GltColorMap::map::iterator               iterator;
    typedef GltColorMap::map::const_iterator         const_iterator;

    map _map;
};

#endif
