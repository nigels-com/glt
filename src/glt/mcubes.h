#ifndef GLT_MCUBES_H
#define GLT_MCUBES_H

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
    \brief   Marching Cubes Interface
    \ingroup GLT
    \author  Steve Anger (70714.3113@compuserve.com)

    $Id: mcubes.h,v 1.2 2004/02/08 14:13:21 jgasseli Exp $

    $Log: mcubes.h,v $
    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.9  2003/03/06 12:21:33  nigels
    *** empty log message ***

    Revision 1.8  2002/11/27 00:57:28  nigels
    expand

    Revision 1.7  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.6  2002/10/07 16:33:35  nigels
    Added CVS info


*/

/*! \brief Marching Cubes Function Type
*/

typedef float (*GltFunc3d)(float x, float y, float z);

extern float sphere(float,float,float);
extern float heart (float,float,float);
extern float klein (float,float,float);
extern float wave  (float,float,float);
extern float sss   (float,float,float);

/*! \brief Marching Cubes Algorithm
    \ingroup GLT

    A simple implementation of the marching cubes algorithm for tesselating
    a 3d function. The function is tesselated into triangle faces and drawn
    using OpenGL. You are free to use all or part of this code in your own
    programs as long as proper credit is given.

    \param func    Function to evaluate
    \param minx    Minimum X of bounding box
    \param miny    Minimum Y of bounding box
    \param minz    Minimum Z of bounding box
    \param maxx    Maximum X of bounding box
    \param maxy    Maximum Y of bounding box
    \param maxz    Maximum Z of bounding box
    \param xsteps  Level of detail in x direction
    \param ysteps  Level of detail in y direction
    \param zsteps  Level of detail in z direction
    \return        1 on success, 0 on failure

    \note The bounding box is axis aligned.

    \author  Steve Anger (70714.3113@compuserve.com)
*/

int GltMarchingCubes(
        GltFunc3d func,
        float minx, float miny, float minz,
        float maxx, float maxy, float maxz,
        int xsteps, int ysteps, int zsteps);

#endif
