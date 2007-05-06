#ifndef GLT_MCUBES_H
#define GLT_MCUBES_H

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

/* $Id: mcubes.h,v 2.3 2007/05/06 16:46:24 nigels Exp $ */

/*! \file
    \brief   Marching Cubes Interface
    \ingroup GLT
    \author  Steve Anger (70714.3113@compuserve.com)
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

    A simple implementation of the marching cubes algorithm for producing
    a tesselated isosurface from a 3d scalar field.   An isosurface is the
    set of points equal to the isovalue.

    The algorithms draws triangles directly using OpenGL.

    You are free to use all or part of this code in your own
    programs as long as proper credit is given.

    \param func    Function to evaluate
    \param minx    Minimum X of bounding box
    \param miny    Minimum Y of bounding box
    \param minz    Minimum Z of bounding box
    \param maxx    Maximum X of bounding box
    \param maxy    Maximum Y of bounding box
    \param maxz    Maximum Z of bounding box
    \param xsteps  Number of steps in x axis
    \param ysteps  Number of steps in y axis
    \param zsteps  Number of steps in z axis
    \return        true on success

    \note The bounding box is axis aligned.

    \author  Steve Anger (70714.3113@compuserve.com)
    \author  Adapted by Nigel Stewart for GLT
*/

bool GltMarchingCubes(
        GltFunc3d func,
        float minx, float miny, float minz,
        float maxx, float maxy, float maxz,
        int xsteps, int ysteps, int zsteps);

#endif
