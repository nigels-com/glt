#ifndef MESH_QUAD_H
#define MESH_QUAD_H

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
    \brief   Mesh Quadrilateral
    \ingroup Mesh

    $Id: quad.h,v 1.2 2004/02/08 14:13:21 jgasseli Exp $

    $Log: quad.h,v $
    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.7  2003/05/10 17:01:35  nigels
    Tidy and document

    Revision 1.6  2003/03/06 12:31:14  nigels
    *** empty log message ***

*/

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include <iosfwd>

#include <math/point.h>
#include <math/plane.h>

///////////////////////////// Quad ///////////////////////////////////////

/*! \class Quad
    \brief Mesh Quadrilateral
    \ingroup Mesh
    \todo Implement writePOV
*/

class Quad
{
public:


    Quad();                                     ///< Construct undefined quad
    Quad(Point *a,Point *b,Point *c,Point *d);  ///< Construct quad from four points

          Point *operator[](int);               ///< Access points 0,1,2 or 3
    const Point *operator[](int) const;         ///< Access points 0,1,2 or 3

          Vector &normal();                     ///< Normal of quad face
    const Vector &normal() const;               ///< Normal of quad face

    Plane   plane() const;                      ///< Tangent plane of quad

    bool operator==(const Quad &quad) const;    ///< Are quads the same?
    bool operator!=(const Quad &quad) const;    ///< Are quads different?

    void glDraw() const;                        ///< Render quad with OpenGL

    std::ostream &writePOV(std::ostream &os) const;  ///< Write quad to POV format

private:


    Point *_vertex[4];          ///< Vertecies of quad
    Vector _normal;             ///< Normal of quad face
};

#endif
