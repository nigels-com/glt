/* $Id: error.cpp,v 2.6 2010/06/11 18:26:59 nigels Exp $ */

#include "error.h"

#include <glt/config.h>

#include <cstdio>
#include <cstring>

#include <string>
#include <iostream>
using namespace std;

#ifdef GLT_WIN32
#include <windows.h>
#include <wingdi.h>
#endif

/*! \file
    \ingroup GLT
*/

#include <misc/string.h>

#include <cstdarg>

#if defined(GLT_UNIX) && !defined(__APPLE__)
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
    #ifdef __APPLE__
    return true;
    #else
    return glXGetCurrentContext()!=NULL;
    #endif
    #endif

    return false;
}
