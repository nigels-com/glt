#include "matrix.h"

/*! \file
    \ingroup GLT

    $Id: matrix.cpp,v 2.0 2004/02/08 19:44:11 nigels Exp $

    $Log: matrix.cpp,v $
    Revision 2.0  2004/02/08 19:44:11  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.7  2002/11/27 00:57:28  nigels
    expand

    Revision 1.6  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.5  2002/10/09 15:09:38  nigels
    Added RCS Id and Log tags


*/

#include <glt/error.h>

GltPushMatrix::GltPushMatrix(const bool enable)
: _enable(enable)
{
    GLERROR

    if (_enable)
        glPushMatrix();

    GLERROR
}

GltPushMatrix::~GltPushMatrix()
{
    GLERROR

    if (_enable)
        glPopMatrix();

    GLERROR
}
