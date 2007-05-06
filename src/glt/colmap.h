#ifndef GLT_COLMAP_H
#define GLT_COLMAP_H

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

/* $Id: colmap.h,v 2.2 2007/05/06 16:46:23 nigels Exp $ */

/*! \file
    \brief   One Dimensional Color-Mapping Class
    \ingroup GLT
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
