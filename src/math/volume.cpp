#include "volume.h"

/*! \file
    \ingroup Math

    $Id: volume.cpp,v 2.0 2004/02/08 19:44:13 nigels Exp $

    $Log: volume.cpp,v $
    Revision 2.0  2004/02/08 19:44:13  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.6  2003/03/06 12:30:51  nigels
    *** empty log message ***

*/

#include <math/real.h>

double sphereVolume(const double radius)
{
    return (4.0/3.0)*M_PI*radius*radius*radius;
}

double cylinderVolume(const double radius,const double height)
{
    return M_PI*radius*radius*height;
}

double coneVolume(const double radius,const double height)
{
    return (1.0/3.0)*M_PI*radius*radius*height;
}

double boxVolume(const double width,const double height,const double depth)
{
    return width*height*depth;
}
