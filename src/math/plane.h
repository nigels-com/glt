#ifndef MATH_PLANE_H
#define MATH_PLANE_H

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
    \brief   3D Plane Equation
    \ingroup Math
*/

#include <math/vector3.h>

/*! \class   Plane
    \brief   3D Plane Equation
    \ingroup Math
    \todo    Nice illustrations and explanation.
*/

class BoundingBox;
class Matrix;

class Plane
{
public:
    /// Default constructor
    Plane();
    /// Constructor
    Plane(const Vector &pos,const Vector &dir);

    /// Plane normal vector
          Vector &direction();
    /// Plane normal vector
    const Vector &direction() const;

    /// d
          double  d()         const;
    /// d
          double  &d();

    /// Plane equality operator
    bool operator==(const Plane &plane) const;

    /// Transform plane by a 4x4 matrix
    void transform(const Matrix &trans);
    /// Toggle the orienation of the plane
    void flip();

    /// Evaluate plane equation
    real   dist(const Vector &pos) const;
    /// Evaluate sign of plane equation
    bool inside(const Vector &pos) const;

    /// Classify axis-aligned box w.r.t plane
    real dist(const BoundingBox &box) const;

    /// Intersect ray
    real   intersect        (const Vector &p0,const Vector &p1) const;
    /// Intersect ray
    Vector intersectPosition(const Vector &p0,const Vector &p1) const;

protected:

    /// Point on plane
    Vector _pos;
    /// Direction of plane normal
    Vector _direction;
    /// Plane equation 'd'
    double _d;
};

#endif
