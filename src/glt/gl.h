#ifndef GLT_GL_H
#define GLT_GL_H

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
    \brief   OpenGL (proxy) header file
    \ingroup GLT

    #include <GL/gl.h> proxy header

    This header can be used instead of GL/gl.h.
    Other necessary dependencies such as windows.h
    are handled here.

    $Id: gl.h,v 1.1 2004/02/08 11:45:45 jgasseli Exp $

    $Log: gl.h,v $
    Revision 1.1  2004/02/08 11:45:45  jgasseli
    Initial revision

    Revision 1.13  2003/03/06 12:19:05  nigels
    *** empty log message ***

    Revision 1.12  2002/11/27 00:57:28  nigels
    expand

    Revision 1.11  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.10  2002/10/09 15:18:17  nigels
    Tidy

    Revision 1.9  2002/10/07 16:27:46  nigels
    Added CVS version control info

*/

#include <glt/config.h>

#ifdef GLT_WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include <GL/gl.h>

#endif
