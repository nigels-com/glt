#ifndef MATH_BBOX_H
#define MATH_BBOX_H

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
    \brief   Axis-Aligned 3D Bounding Box Class
    \ingroup Math
*/

#include <vector>

#include <math/vector3.h>

/*! \class   BoundingBox
    \brief   Axis-Aligned 3D Bounding Box Class
    \ingroup Math
*/

class Matrix;
class GltViewport;

class BoundingBox
{
    /// Output AAB to stream
    friend std::ostream &operator<<(std::ostream &os, const BoundingBox &b);

    /// Union of two axis aligned bounding boxes
    friend BoundingBox sum         (const BoundingBox &a,const BoundingBox &b);

    /// Intersection of two axis aligned bounding boxes
    friend BoundingBox intersection(const BoundingBox &a,const BoundingBox &b);

public:

    BoundingBox();                                      ///< Default constructor
    BoundingBox(const Vector &min,const Vector &max);   ///< Constructor
    ~BoundingBox();                                     ///< Destructor

    //
    // Get/Set
    //

          bool &defined();                              ///< Defined?
    const bool  defined() const;                        ///< Defined?

          Vector &min();                                ///< Minimum x,y,z
    const Vector &min() const;                          ///< Minimum x,y,z

          Vector &max();                                ///< Maximum x,y,z
    const Vector &max() const;                          ///< Maximum x,y,z

    Vector center() const;                              ///< Box center

    real width() const;                                 ///< Box width (Xmax - Xmin)
    real height() const;                                ///< Box height (Ymax - Ymin)
    real depth() const;                                 ///< Box depth (Zmax - Zmin)

    void points(std::vector<Vector> &p) const;          ///< Extract the 8 corners of the box

    //
    // Set operations
    //

    void reset();                                               ///< Empty set (undefined)

    BoundingBox &operator+=(const Vector &p);                   ///< Boolean union
    BoundingBox &operator+=(const std::vector<Vector> &p);      ///< Boolean union
    BoundingBox &operator+=(const BoundingBox &box);            ///< Boolean union
    BoundingBox &operator*=(const BoundingBox &box);            ///< Boolean intersection

    bool operator==(const BoundingBox &box) const;              ///< Box equality operator

//  Real   dist(const Vector &pos) const;                       ///< Closest distance to box

    bool inside(const Vector &pos) const;                       ///< Volumetric classification
    bool intersects(const BoundingBox &box) const;              ///< Intersection between boxes

    /// Map object co-ordinates to window co-ordinates
    bool project(const Matrix &model,const Matrix &proj,const GltViewport &view);

//  Real   intersect        (const Vector &p0,const Vector &p1) const;  ///< Intersect ray
//  Vector intersectPosition(const Vector &p0,const Vector &p1) const;  ///< Intersect ray

protected:

    bool   _defined;        ///< Is the bounding box defined?
    Vector _min;            ///< Box minimum
    Vector _max;            ///< Box maximum
};

#endif
