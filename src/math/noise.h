#ifndef MATH_NOISE_H
#define MATH_NOISE_H

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
    \brief   Perlin Noise Functions
    \ingroup Math
*/

#include <glt/config.h>

#include <math/real.h>
#include <math/hash.h>
#include <math/vector3.h>

#include <cassert>

////////////////////////// GltNoisePerlin /////////////////////////////////

/*! \class   GltNoisePerlin
    \brief   Perlin Noise Generator with support for FBM or Turbulence
    \ingroup Math

    Adapted from Ray++, with permission.
    Ray++ - Object-oriented ray tracing library
    Copyright (C) 1998-2000 Martin Reinecke and others.
    http://www.mpa-garching.mpg.de/~martin/ray++/

    This implementation incorporates the modifications proposed
    by Ken Perlin:

    Ken Perlin, Improving noise                                   <br>
    ACM Transactions on Graphics (TOG)                            <br>
    Proceedings of the 29th annual conference on Computer         <br>
    graphics and interactive techniques                           <br>
    July 2002 Volume 21 Issue 3

    Other sources of information

    Perlin Noise and FBM talk by Ken Perlin
    http://www.noisemachine.com/talk1/

    Perlin Noise and Turbulence summary by Paul Bourke
    http://astronomy.swin.edu.au/~pbourke/texture/perlin/

    The Perlin Noise Math FAQ by Matt Zucker
    http://students.vassar.edu/mazucker/code/perlin-noise-math-faq.html

    Perlin Noise by Hugo Elias
    http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
*/

class GltNoisePerlin
{
public:

    GltNoisePerlin(const uint32 seed = 0);          ///< Constructor
    GltNoisePerlin(const GltNoisePerlin &noise);    ///< Copy constructor
    ~GltNoisePerlin();                              ///< Destructor

    //
    // Noise in floating point domain
    //

    real val(const real x) const;                           ///< 1d noise field
    real val(const real x,const real y) const;              ///< 2d noise field
    real val(const real x,const real y,const real z) const; ///< 3d noise field
    real val(const Vector &pos) const;                      ///< 3d noise field

    //
    // Noise in integer domain
    //

    /*!
        \brief 1D noise field on tiled integer lattice
        \param x                Integer lattice position in x
        \param fractionalBits   Number of least significant bits used for fraction
        \param fx               Floating-point fraction in x
    */
    real
    val
    (
        const uint32 x,
        const uint32 fractionalBits,
        const real   fx = 0.0
    ) const;

    /*!
        \brief 2D noise field on tiled integer lattice
        \param x                Integer lattice position in x
        \param y                Integer lattice position in y
        \param fractionalBits   Number of least significant bits used for fraction
        \param fx               Floating-point fraction in x
        \param fy               Floating-point fraction in y
    */
    real
    val
    (
        const uint32 x,
        const uint32 y,
        const uint32 fractionalBits,
        const real   fx = 0.0,
        const real   fy = 0.0
    ) const;

    /*!
        \brief 3D noise field on tiled integer lattice
        \param x                Integer lattice position in x
        \param y                Integer lattice position in y
        \param z                Integer lattice position in z
        \param fractionalBits   Number of least significant bits used for fraction
        \param fx               Floating-point fraction in x
        \param fy               Floating-point fraction in y
        \param fz               Floating-point fraction in z
    */
    real
    val
    (
        const uint32 x,
        const uint32 y,
        const uint32 z,
        const uint32 fractionalBits,
        const real   fx = 0.0,
        const real   fy = 0.0,
        const real   fz = 0.0
    ) const;

    //
    // Configuration
    //

    typedef enum
    {
        NOISE_PERLIN =0,
        NOISE_FBM,
        NOISE_TURBULENCE
    } NoiseType;

       NoiseType &type();            ///< Noise type
          uint32 &seed();            ///< Unique seed for noise field
          uint32 &octaves();         ///< Number of harmonics
          uint32 &lambda();          ///< Domain scale factor for subsequent harmonics
          real   &omega();           ///< Range scale factor for subsequent harmonics

   const NoiseType &type()    const; ///< Noise type
   const uint32    &seed()    const; ///< Unique seed for noise field
   const uint32    &octaves() const; ///< Number of harmonics
   const uint32    &lambda()  const; ///< Domain scale factor for subsequent harmonics
   const real      &omega()   const; ///< Range scale factor for subsequent harmonics

private:

    NoiseType  _type;                   ///< Noise type
    uint32     _seed;                   ///< Unique seed for noise field

    uint32     _octaves;                ///< Number of harmonics
    uint32     _lambda;                 ///< Domain scale factor for subsequent harmonics
    real       _omega;                  ///< Range scale factor for subsequent harmonics

    const static Vector _vector[16];    ///< Fixed set of possible gradients

    /*!
        \brief 1D Perlin noise field
        \param x                Integer lattice position in x
        \param y                Integer lattice position in y
        \param fractionalBits   Number of least significant bits used for fraction
        \param fx               Floating-point fraction in x
        \param fy               Floating-point fraction in y
    */
    static real
    perlinNoise
    (
        const uint32 seed,
        const uint32 x,
        const uint32 fractionalBits,
        const real   fx = 0.0
    );

    /*!
        \brief 2D Perlin noise field
        \param x                Integer lattice position in x
        \param y                Integer lattice position in y
        \param fractionalBits   Number of least significant bits used for fraction
        \param fx               Floating-point fraction in x
        \param fy               Floating-point fraction in y
    */
    static real
    perlinNoise
    (
        const uint32 seed,
        const uint32 x,
        const uint32 y,
        const uint32 fractionalBits,
        const real   fx = 0.0,
        const real   fy = 0.0
    );

    /*!
        \brief 3D Perlin noise field
        \param x                Integer lattice position in x
        \param y                Integer lattice position in y
        \param z                Integer lattice position in z
        \param fractionalBits   Number of least significant bits used for fraction
        \param fx               Floating-point fraction in x
        \param fy               Floating-point fraction in y
        \param fz               Floating-point fraction in z
    */
    static real
    perlinNoise
    (
        const uint32 seed,
        const uint32 x,
        const uint32 y,
        const uint32 z,
        const uint32 fractionalBits,
        const real   fx = 0.0,
        const real   fy = 0.0,
        const real   fz = 0.0
    );

    /// 1D integer lattice gradient index
    static inline uint32 hash(const uint32 seed,const uint32 x)
    {
        return hashWang32(x^seed)%16;
    }

    /// 2D integer lattice gradient index
    static inline uint32 hash(const uint32 seed,const uint32 x,const uint32 y)
    {
        return hashWang32(x^hashWang32(y^seed))%16;
    }

    /// 3D integer lattice gradient index
    static inline uint32 hash(const uint32 seed,const uint32 x,const uint32 y,const uint32 z)
    {
        return hashWang32(x^hashWang32(y^hashWang32(z^seed)))%16;
    }

    /// Ease in-out curve for interpolation
    inline static real scurve(real t)
    {
        const real t3 = t*t*t;
        const real t4 = t3*t;
        const real t5 = t4*t;

        return 6*t5 - 15*t4 + 10*t3;
    }
};

#endif
