#ifndef MESH_READ3DSB_H
#define MESH_READ3DSB_H

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
    \brief   3D Studio 3DS File Loader
    \ingroup Mesh

    Resources:
        - http://www.the-labs.com/Blender/3DS-details.html
        -

    $Id: read3dsb.h,v 2.2 2004/08/11 05:20:19 nigels Exp $

    $Log: read3dsb.h,v $
    Revision 2.2  2004/08/11 05:20:19  nigels
    Updated copyright and removed email address from headers

    Revision 2.1  2004/02/16 14:22:01  nigels
    Added debug diagnostics

    Revision 1.7  2003/05/31 12:53:41  nigels
    Cleanup of Binary 3DS Reader

    Revision 1.6  2003/05/31 11:38:02  nigels
    Some changes to 3DS support

    Revision 1.5  2003/03/06 12:31:14  nigels
    *** empty log message ***

*/

#include <node/shapes.h>

/// Read from 3D Studio binary file
GltShapes read3DS(const byte *buffer,const uint32 size);

#endif

