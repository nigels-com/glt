#ifndef MATH_VECTOR2_H
#define MATH_VECTOR2_H

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
    \brief   2D Vector
    \ingroup Math
*/

#include <iosfwd>
#include <string>

#include <glt/config.h>
#include <math/real.h>

class Matrix;
class GltViewport;
class Vector3;
class Vector4;

////////////////////////// Vector2 /////////////////////////////////

/*! \class   Vector2
    \brief   2D Vector
    \ingroup Math
*/

class Vector2
{
    friend std::ostream &operator<<(std::ostream &os, const Vector2 &x);
    friend std::istream &operator>>(std::istream &is,       Vector2 &x);

    friend Vector2 operator*(const Vector2  &v, const real x);
    friend Vector2 operator/(const Vector2  &v, const real x);
    friend Vector2 operator*(const real     x,  const Vector2 &v);
    friend Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
    friend Vector2 operator-(const Vector2 &v1, const Vector2 &v2);

public:
    Vector2();                                   ///< Default constructor
    Vector2(const Vector2 &v);                   ///< Copy constructor
    Vector2(const Vector3 &v);                   ///< Copy constructor
    Vector2(const Vector4 &v);                   ///< Copy constructor
    Vector2(const real x, const real y);         ///< Constructor
    Vector2(const float  *v);                    ///< Constructor
    Vector2(const double *v);                    ///< Constructor
    Vector2(const std::string &str);             ///< Construct from string

    // xy plane interpretation

          real &x();                             ///< x co-ordinate
    const real &x() const;                       ///< x co-ordinate

          real &y();                             ///< y co-ordinate
    const real &y() const;                       ///< y co-ordinate

    // st texturing interpretation

          real &s();                             ///< s co-ordinate
    const real &s() const;                       ///< s co-ordinate

          real &t();                             ///< t co-ordinate
    const real &t() const;                       ///< t co-ordinate

          real &operator[](const int i);         ///< i'th co-ordinate
    const real &operator[](const int i) const;   ///< i'th co-ordinate

    operator       real *();                     ///< Access as array
    operator const real *() const;               ///< Access as array


    bool operator==(const Vector2 &v) const;     ///< Equality operator
    bool operator!=(const Vector2 &v) const;     ///< Inequality operator
    bool operator==(const real &a) const;        ///< Equality operator: x==a && y==a


    bool operator< (const Vector2 &c) const;     ///< less-than comparison
    bool operator> (const Vector2 &c) const;     ///< greater-than comparison


    Vector2 &operator= (const Vector2 &v);       ///< Assignment operator
    Vector2 &operator= (const float *);          ///< Assignment operator
    Vector2 &operator= (const double *);         ///< Assignment operator
    Vector2 &operator+=(const Vector2 &v);       ///< Addition
    Vector2 &operator-=(const Vector2 &v);       ///< Subtraction

    real     operator* (const Vector2 &v) const; ///< Vector dot product (aka scalar product)
    Vector2 &operator*=(const real &x);          ///< Multiply
    Vector2 &operator*=(const Matrix &m);        ///< Matrix Transformation

    Vector2 operator-() const;                   ///< Negative


    void scale(const real &x);                   ///< Scale
    void scale(const Vector2 &x);                ///< Scale


    void normalize();           ///< Normalise the vector: |x| = 1.0
    void abs();                 ///< Make x and y non-negative
    int  dominant() const;      ///< Find the dominant component: x or y


    real norm() const;                  ///< Squared length of vector
    real dist(const Vector2 &x) const;  ///< Squared distance between vectors

    real length() const;                ///< Length of vector

    Vector2 &vmin(const Vector2 &v);    ///< Replace with minimum of x and y
    Vector2 &vmax(const Vector2 &v);    ///< Replace with maximum of x and y

    void glVertex() const;              ///< Draw OpenGL vertex
    void glTexCoord() const;            ///< Set OpenGL texture co-ordinate

    /// Output in Povray format
    std::ostream &writePov(std::ostream &os) const;

    /// Map object co-ordinates to window co-ordinates
    bool project(const Matrix &model,const Matrix &proj,const GltViewport &view);

protected:
    /// Storage for x and y components
    real _vector[2];
};

#endif
