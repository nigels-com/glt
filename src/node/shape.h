#ifndef NODE_SHAPE_H
#define NODE_SHAPE_H

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
    \brief   Scenegraph Leaf Node Base-Class
    \author  Nigel Stewart, RMIT (nigels.com@gmail.com)
    \ingroup Node
*/

#include <glt/color.h>

#include <math/vector3.h>
#include <math/matrix4.h>
#include <math/bbox.h>

#include <misc/refcount.h>

#include <node/fields.h>

#include <string>
#include <vector>

///////////////////////////// GltShape ///////////////////////////////////////

/*! \class   GltShape
    \brief   Scenegraph Node Base-Class
    \ingroup Node
    \author  Nigel Stewart (nigels.com@gmail.com)
*/

class GltShape;
typedef ReferenceCountPtr<GltShape> GltShapePtr;

class GltShape
{
public:

    /// Destructor
    virtual ~GltShape();

    /// Derived classes should supply this
    virtual void draw() const = 0;

    /// Get the volume of the shape
    virtual GLdouble volume() const;

    /// Inside/Outside test
    virtual bool inside(const Vector &pos) const;

    /// Get an axis aligned bounding box, unavailable by default
    virtual void boundingBox(BoundingBox &box) const;

    /// Check for intersection with another object
    virtual bool intersects(const GltShape &shape) const;

    /// Brief description of the shape
    virtual std::string description() const;

    /// Settings
    virtual GltFieldPtr settings();

    /// Export to POV format
    virtual bool povrayExport(std::ostream &os) const;

    /// Remove expired shapes
    virtual void flushExpired();

                                                /// Transformation matrix
    Matrix      &transformation();
                                                /// Color
    GltColor    &color();
                                                /// Draw as solid or wireframe
    bool        &solid();
                                                /// Enable visibility
    bool        &visible();
                                                /// Name
    std::string &name();
                                                /// Depth complexity
    uint32      &convexity();
                                                /// Use current OpenGL color
    bool        &inheritColor();
                                                /// Use current polygon mode
    bool        &inheritSolid();
                                                /// Ready to be removed from scene
    bool        &expired();

                                                /// Transformation matrix
    const Matrix      &transformation() const;
                                                /// Color
    const GltColor    &color()          const;
                                                /// Draw as solid or wireframe
    const bool        &solid()          const;
                                                /// Enable visibility
    const bool        &visible()        const;
                                                /// Name
    const std::string &name()           const;
                                                /// Depth complexity
    const uint32      &convexity()      const;
                                                /// Use current OpenGL color
    const bool        &inheritColor()   const;
                                                /// Use current polygon mode
    const bool        &inheritSolid()   const;
                                                /// Ready to be removed from scene
    const bool        &expired()        const;

protected:

    /// Constructor is protected since GltShape is abstract base class
    GltShape(const bool solid = true);

    /// Apply current transformation to co-ordinates
    void transformPoints(std::vector<Vector> &v) const;

    /// Apply current color, unless inherited
    void glColor() const;

private:

    Matrix      _transformation;
    GltColor    _color;
    bool        _solid;
    bool        _visible;
    std::string _name;
    uint32      _convexity;
    bool        _inheritColor;
    bool        _inheritSolid;
    bool        _expired;
};

#endif
