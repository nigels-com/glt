#ifndef MATH_RAY_H
#define MATH_RAY_H

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
    \brief   3D Ray Class
    \ingroup Math
*/

#include <math/vector3.h>

////////////////////////// Ray /////////////////////////////////

/*! \class   Ray
    \brief   3D Ray Class
    \ingroup Math

    Ray/Ray intersection based on code by Seth Teller
    http://graphics.lcs.mit.edu/~seth/geomlib/linelinecp.c
*/

class Ray
{
    /// Output Ray to stream
    friend std::ostream &operator<<(std::ostream &os, const Ray &r);

    /// Intersection of two Rays
    friend bool intersection(Vector &pos,const Ray &a,const Ray &b);

public:

    Ray();                                                  ///< Default constructor
    Ray(const Vector &origin,const Vector &direction);      ///< Constructor
    Ray(const Ray &ray);                                    ///< Copy Constructor
    ~Ray();                                                 ///< Destructor

    //
    // Get/Set
    //

          Vector &origin();                                 ///< Origin
    const Vector &origin() const;                           ///< Origin

          Vector &direction();                              ///< Direction
    const Vector &direction() const;                        ///< Direction

    bool operator==(const Ray &r) const;                    ///< Equality operator

protected:

    Vector _origin;                                         ///< Ray origin
    Vector _direction;                                      ///< Box direction
};

#endif
