#ifndef GLT_GLUT_H
#define GLT_GLUT_H

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
    \brief   GLUT (proxy) header file
    \ingroup GlutMaster

    #include <GL/glut.h> proxy header
*/

#include <glt/gl.h>
#include <glutm/config.h>

/* Use FreeGLUT */

#if  defined(GLUTM_FREEGLUT)

#   ifndef FREEGLUT_STATIC
#   define FREEGLUT_STATIC
#   endif

#   include <GL/freeglut.h>
#   include <GL/freeglut_ext.h>

#elif defined(GLUTM_OPENGLUT)

#   ifndef OPENGLUT_STATIC
#   define OPENGLUT_STATIC
#   endif

#   include <GL/openglut.h>
#   include <GL/openglut_ext.h>

#else

/* Use GLUT */

#   include <GL/glut.h>

#endif

#endif
