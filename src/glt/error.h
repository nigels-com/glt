#ifndef GLT_ERROR_H
#define GLT_ERROR_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2004 Nigel Stewart

  WWW:    http://www.nigels.com/glt/
  Forums: http://sourceforge.net/forum/?group_id=36869

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/* $Id: error.h,v 2.4 2005/07/01 03:17:35 nigels Exp $ */

/*! \file
    \brief   OpenGL Debugging Tools
    \ingroup GLT
*/

#include <string>

extern void gltError  (const char *format, ...);    ///< Display error
extern void gltWarning(const char *format, ...);    ///< Display warning

extern bool gltCurrentContext();                    ///< Check for OpenGL context

/*! \def     GLERROR
    \brief   Check OpenGL error state
    \ingroup GLT
    \note    Does nothing if NDEBUG is defined
*/

#if defined(NDEBUG)
    #define GLERROR
#else
    #include <glt/gl.h>
    #include <glt/glu.h>

    #define GLERROR                                          \
    {                                                        \
        if (!gltCurrentContext())                            \
            gltError("No OpenGL rendering context.");        \
        else                                                 \
        {                                                    \
            GLenum code = glGetError();                      \
            while (code!=GL_NO_ERROR)                        \
            {                                                \
                gltError("glGetError %s:%d %s",              \
                    __FILE__,__LINE__,gluErrorString(code)); \
                code = glGetError();                         \
            }                                                \
        }                                                    \
    }
#endif

#endif

