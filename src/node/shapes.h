#ifndef NODE_SHAPES_H
#define NODE_SHAPES_H

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
    \brief   Scenegraph Parent Node Base-Class
    \author  Nigel Stewart, RMIT (nigels@nigels.com)
    \ingroup Node
*/

#include <node/shape.h>

#include <string>
#include <vector>

///////////////////////////// GltShapes ///////////////////////////////////////

/*! \class   GltShapes
    \brief   Scenegraph Parent Node Base-Class
    \ingroup Node
    \note    Child nodes must be allocated dynamically (via new)
*/

class GltShapes : public GltShape, public std::vector<GltShapePtr>
{
public:
             GltShapes();       ///< Constructor
    virtual ~GltShapes();       ///< Destructor

    virtual void draw() const;
    virtual void boundingBox(BoundingBox &box) const;
    virtual std::string description() const;
    virtual bool povrayExport(std::ostream &os) const;

    virtual void flushExpired();
};

#endif
