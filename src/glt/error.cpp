#include "error.h"

#include <string>
#include <iostream>
using namespace std;

#ifdef GLT_WIN32
#include <windows.h>
#endif

/*! \file
    \ingroup GLT

    $Id: error.cpp,v 2.1 2004/02/12 13:48:56 nigels Exp $

    $Log: error.cpp,v $
    Revision 2.1  2004/02/12 13:48:56  nigels
    no message

    Revision 1.8  2003/12/11 23:48:57  nigels
    Fix potential buffer overflow
    Check for current OpenGL context in GLERROR

    Revision 1.6  2003/05/10 16:58:11  nigels
    Last tweaks for 0.8

    Revision 1.4  2002/11/27 00:57:28  nigels
    expand

    Revision 1.3  2002/11/07 15:40:44  nigels
    *** empty log message ***

    Revision 1.2  2002/10/09 15:09:38  nigels
    Added RCS Id and Log tags


*/

#include <misc/string.h>

#include <cstdarg>

void
gltError(const char *format, ...)
{
    va_list argp;
    va_start(argp, format);
    
    fprintf (stderr, "GLT error: ");
    vfprintf(stderr, format, argp);
    fprintf (stderr, "\n");

    va_end(argp);
}

void
gltWarning(const char *format, ...)
{
    va_list argp;
    va_start(argp, format);
    
    fprintf (stderr, "GLT warning: ");
    vfprintf(stderr, format, argp);
    fprintf (stderr, "\n");

    va_end(argp);
}
