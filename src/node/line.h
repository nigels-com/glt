#ifndef NODE_LINE_H
#define NODE_LINE_H

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
    \brief   Line Node
    \ingroup Node
*/

#include <node/shape.h>
#include <math/vector3.h>
#include <glt/gl.h>

#include <vector>

///////////////////////////// GltLine ///////////////////////////////////////

/*! \class   GltLine
    \brief   Line Node
    \ingroup Node
*/

class GltLine : public GltShape
{
public:
             GltLine();                         ///< Constructor
    virtual ~GltLine();                         ///< Destructor

    virtual void draw() const;
    virtual void boundingBox(BoundingBox &box) const;
    virtual std::string description() const;

    //
    // Get/set
    //

          std::vector<Vector> &points();        ///< Polyline vertecies
    const std::vector<Vector> &points()  const; ///< Polyline vertecies

          std::vector<Vector> &normals();       ///< Polyline normals
    const std::vector<Vector> &normals() const; ///< Polyline normals

          GLfloat &width();                     ///< Width of polyline
    const GLfloat &width() const;               ///< Width of polyline

private:

    std::vector<Vector> _points;
    std::vector<Vector> _normals;

    GLfloat             _width;
};

#endif
