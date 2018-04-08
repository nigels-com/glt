#ifndef CHAOS_H
#define CHAOS_H

/*

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2001-2018 Nigel Stewart
  Email: nigel@nigels.com
  WWW: http://www.nigels.com/glt/gltchaos/

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

#include <vector>

#include <math/random.h>

class ChaosSystem
{
public:
    ChaosSystem();

    void draw(const uint32 n);

    void set(const uint32 seed = 0);    // Random number seed
    void set(const std::string &id);    // String style co-efficients

    void mutate(const double m);        // Randomly change coefficients

    void interpolate(const ChaosSystem & other, const double t); // Interpolate between a pair of systems

    void advancexy(const double x, const double y, double &xn, double &yn) const;

    void findSize();

    ChaosSystem & operator=(const ChaosSystem & sys);

    uint32 lastSeed() const;

    void draw
    (
        unsigned int * image,
        const int      width,
        const int      height,
        const double   minx,
        const double   miny,
        const double   maxx,
        const double   maxy,
        const std::size_t n
    );

    void size
    (
        double & minx,
        double & miny,
        double & maxx,
        double & maxy
    );

protected:

    double  _x,_y;   // Current position
    double  _a[12];  // Quadratic Co-efficients

    uint32 _lastSeed; // Last seed used for searching

    // The LCG random number generator has the
    // convenient property that it can be seeded
    // with a single integer.

    static GltRandomDouble<GltRandomLCG> _random;   // Co-efficient randomisation
    static GltRandomDouble<GltRandomLCG> _mutate;   // Co-efficient mutation
};

#endif

