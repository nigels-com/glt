#ifndef MATH_UMATRIX_H
#define MATH_UMATRIX_H

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

/* $Id: umatrix.h,v 2.3 2010/06/19 17:18:41 nigels Exp $ */

/*! \file
    \brief   4x4 UnMatrix
    \ingroup Math
*/

#include <iosfwd>

#include <math/real.h>
#include <math/vector3.h>

class Matrix;

////////////////////////// UnMatrix /////////////////////////////////

/*! \enum    UnMatrixField
    \brief   4x4 UnMatrix Field
    \ingroup Math
    \author  Nigel Stewart, RMIT (nigels.com@gmail.com)
    \author  Spencer W. Thomas, University of Michigan
    \todo    Replace enums with descriptive class interface.
*/

typedef enum
{
    U_SCALEX = 0,
    U_SCALEY,
    U_SCALEZ,
    U_SHEARXY,
    U_SHEARXZ,
    U_SHEARYZ,
    U_ROTATEX,
    U_ROTATEY,
    U_ROTATEZ,
    U_TRANSX,
    U_TRANSY,
    U_TRANSZ,
    U_PERSPX,
    U_PERSPY,
    U_PERSPZ,
    U_PERSPW,
    U_MAX
} UnMatrixField;

/*! \class   UnMatrix
    \brief   4x4 UnMatrix
    \ingroup Math
    \author  Nigel Stewart, RMIT (nigels.com@gmail.com)
    \author  Spencer W. Thomas, University of Michigan

    Graphics Gems II - Decomposing a matrix into simple transformations. Pg. 320

    The unmatrix subroutine fills in a vector of floating point
    values.  These symbols make it easier to get the data back out.
*/

class UnMatrix
{
    friend class Matrix;

    friend std::ostream &operator<<(std::ostream &os,const UnMatrixField &field);
    friend std::ostream &operator<<(std::ostream &os,const UnMatrix &unMatrix);

    friend std::istream &operator>>(std::istream &is,UnMatrixField &field);
    friend std::istream &operator>>(std::istream &is,UnMatrix &unMatrix);

    friend UnMatrix operator-(const UnMatrix &b,const UnMatrix &a);
    friend UnMatrix operator*(const UnMatrix &a,const double scaleFactor);
    friend UnMatrix operator+(const UnMatrix &a,const UnMatrix &b);

public:
    /// Constructor
    UnMatrix();
    /// Copy Constructor
    UnMatrix(const UnMatrix &);

    /// Construct from 4x4 matrix
    UnMatrix(const Matrix &matrix);

    /// Destructor
    ~UnMatrix();

    /// Is the scale uniform?
    bool uniformScale (const double tol = 1.0e-4) const;
    /// Is there no rotation transformation?
    bool noRotation   (const double tol = 1.0e-4) const;
    /// Is there no shear transformation?
    bool noShear      (const double tol = 1.0e-4) const;
    /// Is there no perspective transformation?
    bool noPerspective(const double tol = 1.0e-4) const;

    /// Access UnMatrix fields
    double &operator[](const UnMatrixField field) { return _tran[field]; };

private:
    double _tran[16];
};

#endif
