#include "random.h"

/*! \file
    \ingroup Math

    $Id: random.cpp,v 2.0 2004/02/08 19:44:12 nigels Exp $

    $Log: random.cpp,v $
    Revision 2.0  2004/02/08 19:44:12  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.12  2003/07/22 03:58:05  nigels
    Vector -> Vector3
    CLAMP -> clamp
    LERP -> lerp

    Revision 1.11  2003/05/10 17:00:56  nigels
    Last tweaks for 0.8

    Revision 1.10  2003/04/07 19:45:21  nigels
    *** empty log message ***

    Revision 1.9  2003/03/06 12:29:59  nigels
    *** empty log message ***

*/

#include <cassert>

//////////////////////////////////////////////////////////////////////

GltRandomLCG GltRandomLCG::rng;

const int32 GltRandomLCG::a = 16807;
const int32 GltRandomLCG::m = 2147483647;
const int32 GltRandomLCG::q = 127773;
const int32 GltRandomLCG::r = 2836;

GltRandomLCG::GltRandomLCG(const uint32 seed)
: _idum(0)
{
    GltRandomLCG::seed(seed);
    assert(_idum!=0);
}

GltRandomLCG::GltRandomLCG(const GltRandomLCG &rng)
{
    _idum = rng._idum;
}

GltRandomLCG::~GltRandomLCG()
{
}

uint32
GltRandomLCG::rand() const
{
    //
    // Based on Numerical Recipes in C
    // and FreeBSD implementation of libkern/random.c
    //
    // See also:
    //   http://minnie.cs.adfa.edu.au/FreeBSD-srctree/newsrc/libkern/random.c.html
    //   http://www.scd.ucar.edu/zine/96/spring/articles/3.random-6.html
    //   http://www.mactech.com/articles/mactech/Vol.08/08.03/RandomNumbers/
    //   http://wad.www.media.mit.edu/people/wad/mas864/psrc/random.c.txt
    //   http://prog.cz/swag/swag/numbers/0081.htm
    //   http://www.dcs.gla.ac.uk/mail-www/glasgow-haskell-users/msg00158.html

    int32 t = a*(_idum%q) - r*(_idum/q);
    if (t <= 0)
       t += m;
    _idum = t;

    return _idum;
}

void
GltRandomLCG::seed(const uint32 seed)
{
    if (seed)
        _idum = seed;
    else
        _idum = 25101974;

    assert(_idum!=0);
}

             uint32 GltRandomLCG::max()  const { return m-1;   }
      GltRandomLCG &GltRandomLCG::base()       { return *this; }
const GltRandomLCG &GltRandomLCG::base() const { return *this; }

//////////////////////////////////////////////////////////////////////

GltRandomLFSRMix GltRandomLFSRMix::rng;

GltRandomLFSRMix::GltRandomLFSRMix(const uint32 seed1,const uint32 seed2,const uint32 seed3)
{
    seed(seed1,seed2,seed3);
}

GltRandomLFSRMix::GltRandomLFSRMix(const GltRandomLFSRMix &rng)
{
    seed(rng._regA,rng._regB,rng._regC);
}

GltRandomLFSRMix::~GltRandomLFSRMix()
{
}

uint32
GltRandomLFSRMix::rand() const
{
    uint32 result = 0;

    for (int j=0; j<32; j++)
    {
        _regA = ((( (_regA >> 31) ^ (_regA >> 6) ^ (_regA >> 4) ^ (_regA >> 2) ^ (_regA << 1) ^ _regA) & 0x00000001) << 31) | (_regA >> 1);
        _regB = ((( (_regB >> 30) ^ (_regB >> 2)) & 0x00000001) << 30) | (_regB >> 1);
        _regC = ((( (_regC >> 28) ^ (_regC >> 1)) & 0x00000001) << 28) | (_regC >> 1);
        result = (result << 1) ^ (((_regA & _regB) | (~_regA & _regC)) & 0x00000001);
    }

    return result;
}

void
GltRandomLFSRMix::seed(const uint32 seed1,const uint32 seed2,const uint32 seed3)
{
    _regA = seed1;
    _regB = seed2;
    _regC = seed3;
}

                uint32  GltRandomLFSRMix::max()  const { return 0xffffffff; }
      GltRandomLFSRMix &GltRandomLFSRMix::base()       { return *this;      }
const GltRandomLFSRMix &GltRandomLFSRMix::base() const { return *this;      }

