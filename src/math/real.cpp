#include "real.h"

/* $Id: real.cpp,v 2.2 2007/05/07 03:38:49 nigels Exp $ */

/*! \file
    \ingroup Math
*/

#include <cmath>
#include <cassert>

//////////////////////////////////////////////////////////////////////////////

void fraction(float &frac,const uint32 bits)
{
    assert(sizeof(float)==4 && sizeof(float)==sizeof(uint32));
    union { float f; uint32 i; } tmp;

    // Place fractional bits in mantissa
    tmp.i = (0x7f<<23) | (bits>>9);

    // Adjust to [0,1) range
    frac = tmp.f-1.0f;
}

void fraction(double &frac,const uint32 bits)
{
    assert(sizeof(double)==8 && sizeof(double)==sizeof(uint32)*2);
    union { double f; uint32 i[2]; } tmp;

    // Place fractional bits in mantissa
    tmp.i[1] = (0x3FF<<20) | (bits>>12);
    tmp.i[0] = (bits<<12);

    // Adjust to [0,1) range
    frac = tmp.f-1.0;
}
