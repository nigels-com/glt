#ifndef GLT_ZPLANE_H
#define GLT_ZPLANE_H

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
    \brief   Z-Plane Drawing
    \ingroup GLT

    $Id: zplane.h,v 1.1 2004/02/08 11:46:10 jgasseli Exp $

    $Log: zplane.h,v $
    Revision 1.1  2004/02/08 11:46:10  jgasseli
    Initial revision

    Revision 1.9  2003/03/06 12:23:15  nigels
    *** empty log message ***

    Revision 1.8  2002/11/27 00:57:28  nigels
    expand

    Revision 1.7  2002/10/07 16:33:35  nigels
    Added CVS info


*/

#include <glt/gl.h>

/*! \brief   Draw an OpenGL polygon at Z-near, covering the viewport
    \ingroup GLT
*/
void drawZnear();

/*! \brief   Draw an OpenGL polygon at Z-far, covering the viewport
    \ingroup GLT
*/
void drawZfar();

/*! \brief   Draw an OpenGL polygon at a z-position, covering the viewport
    \ingroup GLT
*/
void drawZat(const GLdouble z);

#endif
