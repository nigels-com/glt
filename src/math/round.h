#ifndef MATH_ROUND_H
#define MATH_ROUND_H

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

/* $Id: round.h,v 2.2 2007/05/06 16:47:28 nigels Exp $ */

/*! \file
    \brief   Numerical Rounding Routines
    \ingroup Math
*/

#include <glt/config.h>

/*!
    \brief   rounds value to a specified precision
    \ingroup Math
    \author  Stefan Greuter
    \param   value          float to be rounded
    \param   precision      desired precision
    \return  rounded float value
    \note    precision must be non-negative

    Returns the rounded value of 'value' to the specified 'precision'
    (number of digits after the decimal point). The value must be
    a positive integer.
*/

float precision(const float value, const int precision = 0);

/*!
    \brief   rounds value to a specified precision
    \ingroup Math
    \author  Stefan Greuter
    \param   value          float to be rounded
    \param   precision      desired precision
    \return  rounded float value
    \note    precision must be non-negative

    Returns the rounded value of 'value' to the specified 'precision'
    (number of digits after the decimal point). The must be a positive integer
    value.
*/

double precision(const double value, const int precision = 0);

#endif
