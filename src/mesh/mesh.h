#ifndef MESH_MESH_H
#define MESH_MESH_H

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
    \brief   Mesh
    \ingroup Mesh

    $Id: mesh.h,v 2.1 2004/02/16 14:23:38 nigels Exp $

    $Log: mesh.h,v $
    Revision 2.1  2004/02/16 14:23:38  nigels
    Mesh shapes always control GL_CULL_FACE

    Revision 1.16  2003/05/31 13:31:15  nigels
    3DS now loaded as GltShapes rather than via Mesh

    Revision 1.15  2003/03/06 12:31:14  nigels
    *** empty log message ***

*/

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include <glt/config.h>

#include <node/shape.h>
#include <math/point.h>
#include <mesh/triangle.h>
#include <mesh/quad.h>

#include <iosfwd>
#include <deque>
#include <string>

/** \brief Supported file types for import and/or export
 *  \ingroup Mesh
 */
typedef enum
{
    MESH_VRML = 0,          /*!< VRML 97 */
    MESH_OFF,               /*!< OFF */
    MESH_AUTO
} MeshFileType;

///////////////////////////// Mesh ///////////////////////////////////////

/*! \class   Mesh
    \brief   Triangle and Quadrilateral Mesh
    \ingroup Mesh
    \todo  Quad support not yet complete
*/

class Mesh : public GltShape
{
public:

    Mesh();                                                             ///< Constructor
    Mesh(const Mesh &mesh);                                             ///< Copy constructor
    Mesh(const std::string &filename,MeshFileType type = MESH_AUTO);    ///< Read from file
    virtual ~Mesh();                                                    ///< Destructor

    Mesh &operator=(const Mesh &mesh);                                  ///< Assignment operator

    // GltShape interface

    virtual void draw() const;
    virtual void boundingBox(BoundingBox &box) const;
    virtual std::string description() const;
    virtual bool povrayExport(std::ostream &os) const;

    // Get/Set

          std::deque<Point> &point();                        ///< Mesh points
    const std::deque<Point> &point() const;                  ///< Mesh points


          std::deque<Triangle> &triangle();                  ///< Mesh triangles
    const std::deque<Triangle> &triangle() const;            ///< Mesh triangles

          std::deque<Quad> &quad();                          ///< Mesh quads
    const std::deque<Quad> &quad() const;                    ///< Mesh quads

          bool &cullFace();                                  ///< Back-face culling mode
    const bool &cullFace() const;                            ///< Back-face culling mode

    /*!
        \brief      Is a point inside the mesh?
        \note       Works only for convex polyhedra
    */
    bool inside(const Vector &pos) const;

    std::ostream &writeDebugInfo(std::ostream &os) const;   ///< Output debugging information
    std::ostream &writeAOff(std::ostream &os) const;        ///< Output OFF file to stream

private:


    std::deque<Point>    _point;                ///< Mesh points
    std::deque<Triangle> _triangle;             ///< Mesh triangles
    std::deque<Quad>     _quad;                 ///< Mesh quads

    bool                 _cullFace;             ///< Back-face culling mode


    void readOff(std::istream &is);             ///< Read from OFF stream

    int index(const Point *point) const;        ///< Find point index (position in container)
};

#endif
