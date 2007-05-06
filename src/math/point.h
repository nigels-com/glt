#ifndef MATH_POINT_H
#define MATH_POINT_H

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

/* $Id: point.h,v 2.2 2007/05/06 16:47:28 nigels Exp $ */

/*! \file
    \brief   3D Position and Normal Class
    \ingroup Math
*/

#include <math/vector3.h>

/*! \class   Point
    \brief   3D Position and Normal Class
    \ingroup Math
*/

class Matrix;

class Point : public Vector
{
public:

    /// Default constructor
    Point();
    /*!
        \brief Constructor
        \param pos  Position of point
        \param normal   Surface normal of point
    */
    Point(const Vector &pos,const Vector &normal);
    /*!
        \brief Constructor
        \param pos  Position of point
        \param normal   Surface normal of point
        \param texture  Texture coordinate
    */
    Point(const Vector &pos,const Vector &normal,const Vector &texture);
    /*!
        \brief Constructor
        \param x        x position
        \param y        y position
        \param z        z position
    */
    Point(const double &x,const double &y,const double &z);

                    /// Position of point
          Vector &position();
                    /// Position of point
    const Vector &position() const;

                    /// Surface normal of point
          Vector &normal();
                    /// Surface normal of point
    const Vector &normal() const;

                    /// Texture co-ordinate
          Vector &texture();
                    /// Texture co-ordinate
    const Vector &texture() const;

    /// Equality operator
    bool operator==(const Point &vector) const;
    /// Inequality operator
    bool operator!=(const Point &vector) const;

    /// Transform point by 4x4 matrix
    void transform(const Matrix &trans);

private:

    Vector _normal;
    Vector _texture;
};

#endif
