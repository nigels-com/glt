#ifndef MATH_VECTOR3_H
#define MATH_VECTOR3_H

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
    \brief   3D Vector
    \ingroup Math
*/

#include <iosfwd>
#include <string>

#include <glt/config.h>
#include <math/real.h>

class Matrix;
class GltViewport;
class Vector2;
class Vector4;

////////////////////////// Vector3 /////////////////////////////////

/*! \class   Vector3
    \brief   3D Vector
    \ingroup Math
    \todo    Nice pictures and explanation. Dot product, Cross product, etc.
*/

class Vector3
{
    friend std::ostream &operator<<(std::ostream &os, const Vector3 &x);
    friend std::istream &operator>>(std::istream &is,       Vector3 &x);

    friend Vector3 operator*(const Vector3  &v, const real x);
    friend Vector3 operator/(const Vector3  &v, const real x);
    friend Vector3 operator*(const real     x,  const Vector3 &v);
    friend Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
    friend Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
    friend Vector3 xProduct (const Vector3 &v1, const Vector3 &v2);

    friend Vector3 planeNormal(const Vector3 &v1, const Vector3 &v2,const Vector3 &v3);

    friend Vector3 polar(const real lat,const real longitude);

    friend void orthogonalSystem(Vector3 &a,Vector3 &b,Vector3 &c);

public:

    Vector3();                                          ///< Default constructor
    Vector3(const Vector2 &v);                          ///< Copy constructor
    Vector3(const Vector3 &v);                          ///< Copy constructor
    Vector3(const Vector4 &v);                          ///< Copy constructor
    Vector3(const real x, const real y,const real z);   ///< Constructor
    Vector3(const float  *v);                           ///< Constructor
    Vector3(const double *v);                           ///< Constructor
    Vector3(const std::string &str);                    ///< Construct from string

          real &x();                                    ///< x co-ordinate
    const real &x() const;                              ///< x co-ordinate

          real &y();                                    ///< y co-ordinate
    const real &y() const;                              ///< y co-ordinate

          real &z();                                    ///< z co-ordinate
    const real &z() const;                              ///< z co-ordinate

          real &operator[](const int i);                ///< i'th co-ordinate
    const real &operator[](const int i) const;          ///< i'th co-ordinate

    operator       real *();                            ///< Access as array
    operator const real *() const;                      ///< Access as array

    bool operator==(const Vector3 &v) const;            ///< Equality operator
    bool operator!=(const Vector3 &v) const;            ///< Inequality operator
    bool operator==(const real &a) const;               ///< Equality operator: x==a && y==a && z==a

    bool operator< (const Vector3 &c) const;            ///< less-than comparison
    bool operator> (const Vector3 &c) const;            ///< greater-than comparison

    Vector3 &operator= (const Vector3 &v);              ///< Assignment operator
    Vector3 &operator= (const float *);                 ///< Assignment operator
    Vector3 &operator= (const double *);                ///< Assignment operator

    Vector3 &operator+=(const Vector3 &v);              ///< Addition
    Vector3 &operator-=(const Vector3 &v);              ///< Subtraction

    real operator*(const Vector3 &v) const;             ///< Vector dot product (aka scalar product)

    Vector3 &operator*=(const real &x);                 ///< Multiply
    Vector3 &operator*=(const Matrix &m);               ///< Matrix Transformation
    Vector3 operator-() const;                          ///< Negative

    void scale(const real &x);                          ///< Scale
    void scale(const Vector3 &x);                       ///< Scale

    void normalize();                   ///< Normalise the vector: |x| = 1.0
    void abs();                         ///< Make x, y and z positive
    int  dominant() const;              ///< Find the dominant component: x, y or z

    real norm() const;                  ///< Squared length of vector
    real dist(const Vector3 &x) const;  ///< Squared distance between vectors
    real length() const;                ///< Length of vector

    Vector3 &vmin(const Vector3 &v);    ///< Replace with minimum x, y and z
    Vector3 &vmax(const Vector3 &v);    ///< Replace with maximum x, y and z

    void glVertex()   const;            ///< Draw OpenGL vertex
    void glNormal()   const;            ///< Draw OpenGL normal
    void glColor()    const;            ///< Draw OpenGL color
    void glTexCoord() const;            ///< Draw OpenGL texture co-ordinate

    /// Map object co-ordinates to window co-ordinates
    bool project(const Matrix &model,const Matrix &proj,const GltViewport &view);

    /// Write vector in Povray format
    std::ostream &writePov(std::ostream &os) const;

protected:
    /// Storage for x, y and z components
    real _vector[3];
};

typedef Vector3 Vector;

extern const Vector3 VectorX;           ///< (1,0,0)
extern const Vector3 VectorY;           ///< (0,1,0)
extern const Vector3 VectorZ;           ///< (0,0,1)
extern const Vector3 Vector0;           ///< (0,0,0)
extern const Vector3 Vector1;           ///< (1,1,1)

#endif
