#ifndef MATH_VECTOR4_H
#define MATH_VECTOR4_H

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

/* $Id: vector4.h,v 2.3 2007/05/06 16:47:28 nigels Exp $ */

/*! \file
    \brief   4D Vector
    \ingroup Math
*/

#include <iosfwd>
#include <string>

#include <glt/config.h>
#include <math/real.h>

class Vector2;
class Vector3;

////////////////////////// Vector4 /////////////////////////////////

/*! \class   Vector4
    \brief   4D Vector
    \ingroup Math
*/

class Vector4
{
    friend std::ostream &operator<<(std::ostream &os, const Vector4 &x);
    friend std::istream &operator>>(std::istream &is,       Vector4 &x);

public:

    Vector4();                                  ///< Default constructor
    Vector4(const Vector2 &v);                  ///< Copy constructor
    Vector4(const Vector3 &v,const real w = 0.0); ///< Copy constructor
    Vector4(const Vector4 &v);                  ///< Copy constructor

    /// Constructor
    Vector4(const real x, const real y,const real z,const real w = 0.0);

    Vector4(const float  *v);                   ///< Constructor
    Vector4(const double *v);                   ///< Constructor
    Vector4(const std::string &str);            ///< Construct from string

          real &x();                            ///< x co-ordinate
          real &y();                            ///< y co-ordinate
          real &z();                            ///< z co-ordinate
          real &w();                            ///< w co-ordinate

    const real &x() const;                      ///< x co-ordinate
    const real &y() const;                      ///< y co-ordinate
    const real &z() const;                      ///< z co-ordinate
    const real &w() const;                      ///< w co-ordinate

          real &operator[](const int i);        ///< i'th co-ordinate
    const real &operator[](const int i) const;  ///< i'th co-ordinate

    operator       real *();                    ///< Access as array
    operator const real *() const;              ///< Access as array

    real operator*(const Vector4 &v) const;     ///< Vector dot product (aka scalar product)

    void glVertex()   const;                    ///< Draw OpenGL vertex
    void glNormal()   const;                    ///< Draw OpenGL normal
    void glColor()    const;                    ///< Draw OpenGL color
    void glTexCoord() const;                    ///< Draw OpenGL texture co-ordinate

    /// Write vector in Povray format
    std::ostream &writePov(std::ostream &os) const;

protected:

    real _vector[4];                    ///< Storage for x, y and z components
};

#endif
