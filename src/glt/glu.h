#ifndef GLT_GLU_H
#define GLT_GLU_H

/*
  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2007 Nigel Stewart

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

/* $Id: glu.h,v 2.3 2009/06/22 05:03:21 nigels Exp $ */

/*! \file
    \brief   GLU (proxy) header file
    \ingroup GLT

    #include <GL/glu.h> proxy header
*/

#include <glt/config.h>
#include <glt/gl.h>

#if defined(__APPLE__)
#include <OpenGL/GLU.h>
#else
#include <GL/glu.h>
#endif

#endif
