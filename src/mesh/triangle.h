#ifndef MESH_TRIANGLE_H
#define MESH_TRIANGLE_H

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
    \brief   Mesh Triangle
    \ingroup Mesh

    $Id: triangle.h,v 1.2 2004/02/08 14:13:21 jgasseli Exp $

    $Log: triangle.h,v $
    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.8  2003/03/06 12:31:14  nigels
    *** empty log message ***

*/

#include <iosfwd>

#include <math/point.h>
#include <math/plane.h>

///////////////////////////// Triangle ///////////////////////////////////////

/*! \class   Triangle
    \brief   Triangle
    \ingroup Mesh
*/

class Triangle
{
public:

    Triangle();                                 ///< Construct undefined triangle
    Triangle(Point *a,Point *b,Point *c);       ///< Construct triangle from three points

    Point *operator[](int);                     ///< Access points 0,1 and 2
    const Point *operator[](int) const;         ///< Access points 0,1 and 2

          Vector &normal();                     ///< Normal of triangle face
    const Vector &normal() const;               ///< Normal of triangle face

    Plane plane() const;                        ///< Tangent plane of triangle


    bool operator==(const Triangle &tri) const; ///< Are triangles the same?
    bool operator!=(const Triangle &tri) const; ///< Are triangles different?

    void glDraw() const;                        ///< Render triangle with OpenGL

    std::ostream &writePOV(std::ostream &os) const;     ///< Write triangle to POV format

private:

    Point *_vertex[3];      ///> Vertecies of triangle
    Vector _normal;         ///> Normal of triangle face
};

#endif
