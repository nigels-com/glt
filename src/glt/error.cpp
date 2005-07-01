/* $Id: error.cpp,v 2.3 2005/07/01 03:17:34 nigels Exp $ */

#include "error.h"

#include <string>
#include <iostream>
using namespace std;

#ifdef GLT_WIN32
#include <windows.h>
#endif

/*! \file
    \ingroup GLT
*/

#include <misc/string.h>

#include <cstdarg>

#ifdef GLT_UNIX
#include <GL/glx.h>
#endif

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

bool
gltCurrentContext()
{
    #ifdef GLT_WIN32
    return wglGetCurrentContext()!=NULL;
    #endif

    #ifdef GLT_UNIX
    return glXGetCurrentContext()!=NULL;
    #endif

    return false;
}
