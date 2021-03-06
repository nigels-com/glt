#ifndef MESH_SWEEP_H
#define MESH_SWEEP_H

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

/*! \file
    \brief   Sweeping
    \ingroup Mesh

    $Id: sweep.h,v 2.2 2004/08/11 05:20:19 nigels Exp $

    $Log: sweep.h,v $
    Revision 2.2  2004/08/11 05:20:19  nigels
    Updated copyright and removed email address from headers

    Revision 2.1  2004/02/16 14:28:20  nigels
    Whitespace differences

    Revision 1.5  2003/03/06 12:31:14  nigels
    *** empty log message ***

*/

#include <glt/config.h>

class GltPath3D;
class GltShape;

GltShape *MeshSweep(const GltPath3D &f,const double radius,const int slices,const int stacks,const bool convex = false);

#endif
