#ifndef GLT_ERROR_H
#define GLT_ERROR_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2003 Nigel Stewart

  Email:  nigels@nigels.com
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

/*! \file
    \brief   OpenGL Debugging Tools
    \ingroup GLT

    $Id: error.h,v 2.1 2004/02/12 13:48:56 nigels Exp $

    $Log: error.h,v $
    Revision 2.1  2004/02/12 13:48:56  nigels
    no message

    Revision 1.14  2003/12/11 23:48:57  nigels
    Fix potential buffer overflow
    Check for current OpenGL context in GLERROR

    Revision 1.12  2003/03/06 12:18:15  nigels
    Documentation refinements

    Revision 1.11  2002/11/27 00:57:28  nigels
    expand

    Revision 1.10  2002/11/07 15:40:44  nigels
    *** empty log message ***

    Revision 1.9  2002/10/07 16:27:46  nigels
    Added CVS version control info


*/

#include <string>

void gltError  (const char *format, ...);    ///< Display error
void gltWarning(const char *format, ...);    ///< Display warning

/*! \def     GLERROR
    \brief   Check OpenGL error state
    \ingroup GLT
    \note    Does nothing if NDEBUG is defined
*/

#if defined(NDEBUG)
    #define GLERROR
#else
    #include <glt/config.h>
    #include <glt/gl.h>
    #include <glt/glu.h>

    #include <iostream>

#if defined(WIN32)
    #define GLERROR                                          \
    {                                                        \
		if (!wglGetCurrentContext())						 \
			gltError("No OpenGL rendering context.");		 \
		else												 \
		{													 \
			GLenum code = glGetError();                      \
	        while (code!=GL_NO_ERROR)                        \
		    {                                                \
			    gltError("glGetError %s:%d %s",              \
                    __FILE__,__LINE__,gluErrorString(code)); \
				code = glGetError();                         \
			}                                                \
		}													 \
    }
#else
    #define GLERROR                                          \
    {                                                        \
		if (0)  /* TODO - GLX rendering context check */     \
			gltError("No OpenGL rendering context.");		 \
		else												 \
		{													 \
        GLenum code = glGetError();                          \
        while (code!=GL_NO_ERROR)                            \
        {                                                    \
			    gltError("glGetError %s:%d %s",              \
                    __FILE__,__LINE__,gluErrorString(code)); \
            code = glGetError();                             \
        }                                                    \
		}													 \
    }
#endif
#endif

#endif

