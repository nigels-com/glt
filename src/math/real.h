#ifndef MATH_REAL_H
#define MATH_REAL_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2004 Nigel Stewart


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
    \brief   Numerical constants and basic math functions
    \ingroup Math
*/

#include <glt/config.h>

#include <cfloat>
#include <cmath>

//
// Basic types, constants
// and functions
//

// Constants borrowed from PHP

#define M_PI        3.14159265358979323846
#define M_E         2.7182818284590452354
#define M_LOG2E     1.4426950408889634074
#define M_LOG10E    0.43429448190325182765
#define M_LN2       0.69314718055994530942
#define M_LN10      2.30258509299404568402
#define M_PI_2      1.57079632679489661923
#define M_PI_4      0.78539816339744830962
#define M_1_PI      0.31830988618379067154
#define M_2_PI      0.63661977236758134308

#ifndef M_SQRTPI
#define M_SQRTPI    1.77245385090551602729
#endif

#define M_2_SQRTPI  1.12837916709551257390
#define M_SQRT2     1.41421356237309504880

#ifndef M_SQRT3
#define M_SQRT3     1.73205080756887729352
#endif

#define M_SQRT1_2   0.70710678118654752440
#define M_LNPI      1.14472988584940017414
#define M_EULER     0.57721566490153286061

// Other useful constants

#define M_PI_DEG    (M_PI/180.0)
#define M_DEG_PI    (180.0/M_PI)
#define M_2PI       (2.0*M_PI)

#ifdef _MSC_VER
namespace std
{
    template<typename T> const T &min(const T &a,const T &b) { return a<b ? a : b }
    template<typename T> const T &max(const T &a,const T &b) { return a>b ? a : b }
}
#endif

//#define MAX(x,y) (((x)>(y)) ? (x) : (y))
//#define MIN(x,y) (((x)<(y)) ? (x) : (y))

/*!
    \brief   Square of two numbers: x^2
    \ingroup Math
*/
template <class T>
T sqr(const T &x)
{
    return x*x;
}

/*!
    \brief   Determine highest n, given 2^n <= x
    \ingroup Math
*/

template<class T>
T lowerPowerOf2(const T x)
{
    uint32 tmp = 1<<(sizeof(T)*8-1);
    while ((tmp&x)==0 && tmp)
        tmp >>= 1;
    return tmp;
}

/*!
    \brief   Determine lowest n, given 2^n >= x
    \ingroup Math
*/

template<class T>
T upperPowerOf2(const T x)
{
    uint32 tmp = 1<<(sizeof(T)*8-1);
    while ((tmp&x)==0 && tmp)
        tmp >>= 1;
    return x==tmp ? tmp : tmp<<1;
}

/*!
    \brief   Test if two numbers have same sign
    \ingroup Math
*/

template <class T>
bool sameSign(const T &a, const T &b)
{
    return (a<0 && b<0) || (a>0 && b>0);
}

/*!
    \brief   Clamp a number to [min,max] range
    \ingroup Math
*/

template <class T>
T clamp(const T x, const T &min, const T &max)
{
    return x<min ?  min : (x>max ? max: x);
}

/*
template <class A>
A LERP(const A &a,const A &b,const real t)
{
    return a*(1.0-t) + b*t;
}
*/

/*!
    \brief   Convert an integer to a float between 0 and 1
    \ingroup Math
    \param   frac      Output fraction
    \param   bits      Input integer

    <pre>
    IEEE 4 byte real

        31 30    23 22                0
        |-------------------------------------.
        |s| 8 bits |msb   23 bit mantissa  lsb|
        `-------------------------------------'
         |  |        `----------------  mantissa
         |  `--------------------------------  biased exponent (7fh)
         `-------------------------------------  sign bit
    </pre>
*/

void fraction(float &frac,const uint32 bits);

/*!
    \brief   Convert an integer to a double between 0 and 1
    \ingroup Math
    \param   frac      Output fraction
    \param   bits      Input integer

    <pre>
    IEEE 8 byte real

    63 62      52 51                  0
    |-------------------------------------------------.
    |s|  11 bits |msb    52 bit mantissa       lsb|
    `-------------------------------------------------'
     |  |        `----------------  mantissa
     |  `--------------------------------  biased exponent (3FFh)
     `-------------------------------------  sign bit

    </pre>
*/

void fraction(double &frac,const uint32 bits);

/*!
    \brief   Linear interpolation between two values
    \ingroup Math
    \param   t         Fraction from a to b [0.0,1.0]
    \param   a         Start value
    \param   b         End value
*/

template<class T>
inline T lerp(const T &a,const T &b,const real t)
{
    return a*(1.0-t) + b*t;
}

/*!
    \brief   Linear interpolation between two values
    \ingroup Math
    \param   t         Fraction from a to b [0,~0]
    \param   a         Start value
    \param   b         End value
*/

template<class T>
inline T lerp(const T &a,const T &b,const uint32 t)
{
    real rt;
    fraction(rt,t);
    return lerp(a,b,rt);
}

#endif
