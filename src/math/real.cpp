#include "real.h"

/*! \file
    \ingroup Math

    $Id: real.cpp,v 2.0 2004/02/08 19:44:12 nigels Exp $

    $Log: real.cpp,v $
    Revision 2.0  2004/02/08 19:44:12  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.2  2003/08/05 08:06:16  nigels
    *** empty log message ***


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
