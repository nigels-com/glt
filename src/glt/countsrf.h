#ifndef GLT_COUNTSRF_H
#define GLT_COUNTSRF_H

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

/* $Id: countsrf.h,v 2.2 2007/05/06 16:46:24 nigels Exp $ */

/*! \file
    \brief   Surface Counting Interface
    \ingroup GLT
*/

#include <glt/config.h>
#include <glt/gl.h>

class GltShape;

typedef enum
{
    COUNT_SURFACES_ALL,             /*!< Count the maximum number of surfaces exactly. */
    COUNT_SURFACES_99TH_PERCENTILE  /*!< Take the maximum of the 99th percentile, ignoring outliers. */
} countSurfacesMode;

/*! \brief Use the stencil buffer to count the number of surfaces drawn at each pixel
    \ingroup GLT
    \param shape Shapes
    \warning Uses the current culling configuration
*/

void countSurfaces(const GltShape &shape);

/*! \brief Use the stencil buffer to count the number of surfaces drawn at each pixel
    \ingroup GLT
    \param shape Shapes
    \param mode  Count Mode
    \return Maximum number of surfaces covering a pixel
    \warning Uses the current culling configuration
*/

GLubyte countSurfaces(const GltShape &shape,const countSurfacesMode mode);

/*! \brief Visualise the number of rendered surfaces at each pixel
    \ingroup GLT
    \param shape Shapes
    \return Maximum number of surfaces covering a pixel
    \warning Uses the current culling configuration
*/

GLubyte countSurfacesVisualise(const GltShape &shape);


/*! \brief Extract a stencil buffer histogram for the current viewport
    \ingroup GLT
    \param  histogram  Array of GLuint histogram entries
    \return Number of pixels in the current viewport
*/

GLuint  stencilHistogram(GLuint histogram[256]);

#endif
