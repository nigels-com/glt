#include "round.h"

/*! \file
    \ingroup Math

    $Id: round.cpp,v 1.2 2004/02/08 14:13:21 jgasseli Exp $

    $Log: round.cpp,v $
    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.9  2003/07/22 03:58:05  nigels
    Vector -> Vector3
    CLAMP -> clamp
    LERP -> lerp

    Revision 1.8  2003/05/10 17:01:03  nigels
    *** empty log message ***

    Revision 1.6  2003/03/06 12:29:59  nigels
    *** empty log message ***

*/

#include <math/real.h>

#include <cmath>
#include <cassert>

//////////////////////////////////////////////////////////////////////////////

float round(const float value, const int precision)
{
    return (float) round(double(value),precision);
}

//////////////////////////////////////////////////////////////////////////////

double round(const double value, const int precision)
{
    if (precision>=0)
    {
        // Prevent excessive precision

        const int p = clamp(precision,-15,15);

        // Lookup table for pwr(10.0,i)

        const static double pwr[] = {
                1e0,  1e1,  1e2,  1e3,  1e4,
                1e5,  1e6,  1e7,  1e8,  1e9,
                1e10, 1e11, 1e12, 1e13, 1e14 };

        // Table of inverses
        const static double invpwr[] = {
                1e0,   1e-1,  1e-2,  1e-3,  1e-4,
                1e-5,  1e-6,  1e-7,  1e-8,  1e-9,
                1e-10, 1e-11, 1e-12, 1e-13, 1e-14 };

        //

        double val = value;

        //

        if (value<0.0)
            val = ceil(val*pwr[p]-0.5);

        if (value>0.0)
            val = floor(val*pwr[p]+0.5);

        return val*invpwr[p];
    }

    // TODO - Precision is negative

    return value;
}

