#include "round.h"

/*! \file
    \ingroup Math
*/

#include <math/real.h>

#include <cmath>
#include <cassert>

//////////////////////////////////////////////////////////////////////////////

float precision(const float value, const int prec)
{
    return (float) precision(double(value),prec);
}

//////////////////////////////////////////////////////////////////////////////

double precision(const double value, const int prec)
{
    if (prec>=0)
    {
        // Prevent excessive precision

        const int p = clamp(prec,-15,15);

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

