#ifndef MATH_RANDOM_H
#define MATH_RANDOM_H

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
    \brief   Random Number Classes
    \ingroup Math
*/

#include <iosfwd>
#include <cassert>
#include <cmath>

#include <glt/config.h>

#include <math/real.h>
#include <math/vector3.h>
#include <math/matrix4.h>
#include <math/round.h>

/*! \class   GltRandomLCG
    \brief   The Park and Miller "Minimal Standard" LCG generator
    \ingroup Math

    X[n+1] = (X[n]*a)%m

    Adapted from Numerical Recipies in C, 2nd Ed

    Similar to FreeBSD random number generator
*/

class GltRandomLCG
{
public:
    GltRandomLCG(const uint32 seed = 199125);   ///< Construct with non-zero seed
    GltRandomLCG(const GltRandomLCG &rng);      ///< Copy constructor
    ~GltRandomLCG();                            ///< Destructor

    uint32 rand() const;                        ///< Random number in [0,max()]
    uint32 max()  const;                        ///< Maximum random number

    void seed(const uint32 seed = 199125);      ///< Seed the random number generator

          GltRandomLCG &base();                 ///< Base random number generator
    const GltRandomLCG &base() const;           ///< Base random number generator

    static GltRandomLCG rng;                    ///< Global LCG RNG for convenience

private:

    mutable uint32 _idum;

    const static int32 a;
    const static int32 m;
    const static int32 q;
    const static int32 r;
};

/*! \class   GltRandomLFSRMix
    \brief   Multiple LFSR (Linear Feedback Shift Register) generator
    \ingroup Math
    \author  Larry Smith
    \author  Nigel Stewart, RMIT (nigels@nigels.com)
    \note    Original Pascal implementation from unknown source

    This random number generator uses three LFSRs (Linear Feedback Shift Registers)
    to create long sequences of random bits.  Each bit is equally randomised.
    The origins of this exact algorithm is unknown.  This implementation is
    based on the ctools module rndnums by Larry Smith, used with permission.

    It is not really known how good this method is for random number generation -
    but it has the advantage of generating 32 random bits.  Probably not recommended
    for crypto applications....

    Further information about LFSRs:

    B. Schneier, Applied Cryptography, 2nd Ed, Johyn Wiley & Sons
*/

class GltRandomLFSRMix
{
public:
    /// Constructor
    GltRandomLFSRMix(
        const uint32 seed1 = 199125,
        const uint32 seed2 = 90618,
        const uint32 seed3 = 189419);


    GltRandomLFSRMix(const GltRandomLFSRMix &rng);  ///< Copy constructor
    ~GltRandomLFSRMix();                            ///< Destructor

    uint32 rand() const;                            ///< 32-bit random number
    uint32 max()  const;                            ///< Maximum random number

    /// Seed the random number generator
    void seed(
        const uint32 seed1 = 199125,
        const uint32 seed2 = 90618,
        const uint32 seed3 = 189419);

          GltRandomLFSRMix &base();                 ///< Base random number generator
    const GltRandomLFSRMix &base() const;           ///< Base random number generator

    static GltRandomLFSRMix rng;                    ///< Global LFSRMix RNG for convenience

private:

    mutable uint32 _regA, _regB, _regC;
};

/*! \class   GltRandomDouble
    \brief   Adaptor for random float or double numbers
    \ingroup Math
*/

template<class R = GltRandomLFSRMix,class F = real>
class GltRandomDouble
{
public:

    /// Constructor
    GltRandomDouble(R &random,const F min = 0.0,const F max = 1.0)
    : _random(random),
      _min(min),
      _max(max),
      _mult(max-min)
    {
    }

    /// Constructor using default RNG
    GltRandomDouble(const F min = 0.0,const F max = 1.0)
    : _random(R::rng),
      _min(min),
      _max(max),
      _mult(max-min)
    {
    }

    /// Copy constructor
    GltRandomDouble(const GltRandomDouble<F,R> &gen)
    : _random(gen._random),
      _min(gen._min),
      _max(gen._max),
      _mult(gen._mult)
    {
    }

    /// Destructor
    ~GltRandomDouble()
    {
    }

    /// Random number in the range [min,max]
    F rand() const
    {
        return lerp(_min,_max,_random.rand()<<1);
//        F r;
//        fraction(r,_random.rand()<<1);
//        return _min + _mult*r;
    }

    /// Base random number generator
          R &base()       { return _random; }
    /// Base random number generator
    const R &base() const { return _random; }

private:

    R       &_random;
    const F  _min;
    const F  _max;
    const F  _mult;
};

/*! \class   GltRandomInteger
    \brief   Adaptor for random numbers in integer domain
    \ingroup Math
*/

template<class R = GltRandomLFSRMix>
class GltRandomInteger
{
public:

    /// Constructor
    GltRandomInteger(R &random,const uint32 min,const uint32 max)
    : _random(random),
      _min(min),
      _mod(max-min+1)
    {
        assert(min<max);
    }

    /// Constructor using default RNG
    GltRandomInteger(const uint32 min,const uint32 max)
    : _random(R::rng),
      _min(min),
      _mod(max-min+1)
    {
        assert(min<max);
    }

    /// Copy constructor
    GltRandomInteger(const GltRandomInteger<R> &gen)
    : _random(gen._random),
      _min(gen._min),
      _mod(gen._mod)
    {
    }

    /// Destructor
    ~GltRandomInteger()
    {
    }

    /// Random number in the range [min,max]
    uint32 rand() const
    {
        return _min + _random.rand()%_mod;
    }

    /// Base random number generator
          R &base()       { return _random; }
    /// Base random number generator
    const R &base() const { return _random; }

private:

    R            &_random;
    const uint32  _min;
    const uint32  _mod;
};

/*! \class   GltRandomSphere
    \brief   Random points on the unit sphere
    \ingroup Math
    \author  Nigel Stewart, RMIT (nigels@nigels.com)

      http://www.math.niu.edu/~rusin/known-math/96/sph.rand

      The trig method.  This method works only in 3-space, but it is
      very fast.  It depends on the slightly counterintuitive fact
      that each of the three coordinates of a uniformly
      distributed point on S^2 is uniformly distributed on [-1,1] (but
      the three are not independent, obviously).  Therefore, it
      suffices to choose one axis (Z, say) and generate a uniformly
      distributed value on that axis.  This constrains the chosen point
      to lie on a circle parallel to the X-Y plane, and the obvious
      trig method may be used to obtain the remaining coordinates.

    <ul>
    <li>Choose z uniformly distributed in [-1,1].</li>
    <li>Choose t uniformly distributed on [0, 2*pi).</li>
    <li>Let r = sqrt(1-z^2).</li>
    <li>Let x = r * cos(t).</li>
    <li>Let y = r * sin(t).</li>
    </ul>
*/

template<class R = GltRandomLFSRMix>
class GltRandomSphere
{
public:

    /// Constructor
    GltRandomSphere(R &random,const double radius = 1.0)
    : _z(random,-1.0,1.0),
      _t(random,0,2*M_PI),
      _radius(radius)
    {
    }

    /// Constructor using default RNG
    GltRandomSphere(const double radius = 1.0)
    : _z(R::rng,-1.0,1.0),
      _t(R::rng, 0.0,2*M_PI),
      _radius(radius)
    {
    }

    /// Copy constructor
    GltRandomSphere(const GltRandomSphere<R> &gen)
    : _z(gen._z._random),
      _t(gen._t._random),
      _radius(gen._radius)
    {
    }

    /// Destructor
    ~GltRandomSphere()
    {
    }

    /// Random point on sphere surface
    Vector rand() const
    {
        const double z = _z.rand();
        const double t = _t.rand();
        const double r = _radius*sqrt(1.0-z*z);
        return Vector(r*cos(t),r*sin(t),_radius*z);
    }

    /// Base random number generator
          R &base()       { return _z.base(); }
    /// Base random number generator
    const R &base() const { return _z.base(); }

private:

    GltRandomDouble<R> _z,_t;
    const double    _radius;
};

/*! \class   GltRandomOrientation
    \brief   Random orientation matricies in 3D
    \ingroup Math
    \author  Nigel Stewart, RMIT (nigels@nigels.com)
*/

template<class R = GltRandomLFSRMix>
class GltRandomOrientation
{
public:

    /// Constructor
    GltRandomOrientation(R &random)
    : _s(random), _a(random,0.0,2*M_PI)
    {
    }

    /// Constructor using default RNG
    GltRandomOrientation()
    : _s(R::rng), _a(R::rng,0.0,2*M_PI)
    {
    }

    /// Copy constructor
    GltRandomOrientation(const GltRandomOrientation<R> &gen)
    : _s(gen._s), _a(gen._a)
    {
    }

    /// Destructor
    ~GltRandomOrientation()
    {
    }

    /// Random orientation matrix
    Matrix rand() const
    {
        // A is a vector distributed
        // randomly on the unit sphere

        const Vector a(_s.rand());

        // B is orthogonal to A

        Vector b;

        switch (a.dominant())
        {
        case 0: b = xProduct(a,VectorZ); break; // a in x direction
        case 1: b = xProduct(a,VectorZ); break; // a in y direction
        case 2: b = xProduct(a,VectorX); break; // a in z direction
        }

        // C is orthogonal to both A and B

        Vector c(xProduct(b,a));

        // TODO - Possible to avoid this step?
        b.normalize();
        c.normalize();

        // Choose an angle in the AB plane

        const real angle = _a.rand();
        const real sina  = sin(angle);
        const real cosa  = cos(angle);

        return matrixOrient
            (
                a,
                sina*b +  cosa*c,
                cosa*b -  sina*c
            );
    }

    /// Base random number generator
          R &base()       { return _s.base(); }
    /// Base random number generator
    const R &base() const { return _s.base(); }

private:
    GltRandomSphere<R> _s;
    GltRandomDouble<R> _a;
};

#endif
