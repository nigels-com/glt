#ifndef MATH_PATH_H
#define MATH_PATH_H

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

/* $Id: path.h,v 2.2 2007/05/06 16:47:28 nigels Exp $ */

/*! \file
    \brief   Parametric 3D Curves
    \ingroup Math
*/

#include <math/vector3.h>
#include <math/matrix4.h>

/*! \class   GltPath3D
    \brief   Abstract base class for parametric 3D paths
    \ingroup Math
*/

class GltPath3D
{
public:

    /// Constructor
    GltPath3D();
    /// Destructor
    virtual ~GltPath3D();

    /// f(t) - position in 3D space as a function of time
    virtual Vector f(const real t) const = 0;
    /// f'(t) - first derivative as a function of time
    virtual Vector df(const real t) const = 0;
    /// f''(t) - second derivative as a function of time
    virtual Vector ddf(const real t) const = 0;
};

/*! \class   GltPath3DLine
    \brief   Linear 3D path
    \ingroup Math
*/

class GltPath3DLine : public GltPath3D
{
public:
    /// Constructor
    GltPath3DLine(const Vector &origin,const Vector &direction);

    Vector f(const real t) const;
    Vector df(const real t) const;
    Vector ddf(const real t) const;

private:
    const Vector _origin;
    const Vector _direction;
};

/*! \class   GltPath3DHelix
    \brief   Helical 3D path
    \ingroup Math
    \todo    Make _trans const.
*/

class GltPath3DHelix : public GltPath3D
{
public:
    /// Constructor
    GltPath3DHelix(const Vector &origin,const Vector &direction,const real radius,const real freq,const real phase);

    Vector f(const real t) const;
    Vector df(const real t) const;
    Vector ddf(const real t) const;

private:
    Matrix _trans;
    const Vector _origin;
    const Vector _direction;
    const real _radius;
    const real _freq;
    const real _phase;
};


/*! \class   GltPath3DSegment
    \brief   3D path segment
    \ingroup Math

    An adaptor object for making a parametric path
    from the specified domain of another parametric path.
*/

class GltPath3DSegment : public GltPath3D
{
public:
    /// Constructor
    GltPath3DSegment(const GltPath3D &f,const real begin,const real end);

    Vector f(const real t) const;
    Vector df(const real t) const;
    Vector ddf(const real t) const;

private:

    real segT(const real t) const;

    const GltPath3D &_func;
    const real     _begin;
    const real     _end;
};

#endif

