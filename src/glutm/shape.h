#ifndef GLUTM_SHAPE_H
#define GLUTM_SHAPE_H

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
    \brief   GLUT Geometric Object Classes
    \ingroup GlutMaster
*/

#include <glutm/config.h>

#include <node/shape.h>

/////////////

/*! \class   GlutSphere
    \brief   GLUT sphere scene-graph node
    \ingroup GlutMaster
    \note    See GltShape for further information
*/

class GlutSphere : public GltShape
{
public:
    /*!
        \brief      Constructor
        \param      solid   Display as solid or wireframe
        \param      radius  Radius of sphere
        \param      slices  Number of slices around the equator
        \param      stacks  Number of stacks from pole to pole
    */
    GlutSphere(const bool solid = true,const GLdouble radius = 1.0,const GLint slices = 15,const GLint stacks = 15);
    /// Destructor
    ~GlutSphere();

    //

    virtual void     draw() const;
    virtual GLdouble volume() const;
    virtual bool     inside(const Vector &pos) const;
    virtual void     boundingBox(BoundingBox &box) const;
    virtual bool     povrayExport(std::ostream &os) const;

    //
    // Position
    //

    /*!
        \brief      Position the sphere
        \param      pos     Position of sphere center
        \param      radius  Radius of sphere
    */
    void position(const Vector &pos,const double radius);

    //
    // Get/set
    //

    /// Sphere radius
    GLdouble &radius();
    /// Sphere slices around the equator
    GLint    &slices();
    /// Sphere stacks from pole to pole
    GLint    &stacks();

    /// Sphere radius
    const GLdouble &radius() const;
    /// Sphere slices around the equator
    const GLint    &slices() const;
    /// Sphere stacks from pole to pole
    const GLint    &stacks() const;

private:

    GLdouble _radius;
    GLint    _slices;
    GLint    _stacks;
};

/////////////

/*! \class   GlutCube
    \brief   GLUT sphere scene-graph node
    \ingroup GlutMaster
    \note    See GltShape for further information
*/

class GlutCube : public GltShape
{
public:
    /*!
        \brief      Constructor
        \param      solid   Display as solid or wireframe
        \param      size    Width, height and depth of box
    */
    GlutCube(const bool solid = true,const GLdouble size = 2.0);
    /*!
        \brief      Constructor
        \param      solid   Display as solid or wireframe
        \param      min     Near bottom left corner of box
        \param      max     Far top right corner of box
    */
    GlutCube(const bool solid       ,const Vector &min,const Vector &max);
    /// Destructor
    ~GlutCube();

    virtual void     draw() const;
    virtual GLdouble volume() const;
    virtual void     boundingBox(BoundingBox &box) const;
    virtual bool     povrayExport(std::ostream &os) const;

    //
    // Position
    //

    /*!
        \brief      Position the box
        \param      min     Near bottom left corner of box
        \param      max     Far top right corner of box
    */
    void position(const Vector &min,const Vector &max);
    /*!
        \brief      Position the box
        \param      pos     Near bottom left corner of box
        \param      width   Width of box in x
        \param      height  Height of box in y
        \param      depth   Depth of box in z
    */
    void position(const Vector &pos,const real width,const real height,const real depth);

    //
    // Get/set
    //

    /// Box width, height and depth
          GLdouble &size();
    /// Box width, height and depth
    const GLdouble &size() const;

private:

    GLdouble    _size;
};

/////////////

/*! \class   GlutCylinder
    \brief   GLUT cylinder scene-graph node
    \ingroup GlutMaster
    \note    See GltShape for further information
*/

class GlutCylinder : public GltShape
{
public:
    /*!
        \brief      Constructor
        \param      solid   Display as solid or wireframe
        \param      radius  Radius of cylinder
        \param      height  Height of cylinder
        \param      slices  Slices
        \param      stacks  Stacks
        \param      loops   Loops
    */
    GlutCylinder(const bool solid = true,const GLdouble radius = 1.0,const GLdouble height = 1.0,const GLint slices = 15,const GLint stacks = 10,const GLint loops = 5);
    /// Destructor
    ~GlutCylinder();

    virtual void     draw() const;
    virtual GLdouble volume() const;
    virtual void     boundingBox(BoundingBox &box) const;
    virtual bool     povrayExport(std::ostream &os) const;

    //
    // Position
    //

    /*!
        \brief      Position the cylinder
        \param      begin   First end-point of cylinder
        \param      end     Second end-point of cylinder
        \param      radius  Radius of cylinder
    */
    void position(const Vector &begin,const Vector &end,const double radius);

    //
    // Get/Set
    //

    /// Cylinder radius
    GLdouble &radius();
    /// Cylinder length/height
    GLdouble &height();
    /// Cylinder slices
    GLint    &slices();
    /// Cylinder stacks
    GLint    &stacks();
    /// Cylinder loops
    GLint    &loops();

    /// Cylinder radius
    const GLdouble &radius() const;
    /// Cylinder length/height
    const GLdouble &height() const;
    /// Cylinder slices
    const GLint    &slices() const;
    /// Cylinder stacks
    const GLint    &stacks() const;
    /// Cylinder loops
    const GLint    &loops()  const;

private:

    GLdouble _radius;
    GLdouble _height;
    GLint    _slices;
    GLint    _stacks;
    GLint    _loops;
};

/////////////

/*! \class   GlutCone
    \brief   GLUT cone scene-graph node
    \ingroup GlutMaster
    \note    See GltShape for further information
*/

class GlutCone : public GltShape
{
public:
    /*!
        \brief      Constructor
        \param      solid   Display as solid or wireframe
        \param      base    Radius of cone base
        \param      height  Height of cone
        \param      slices  Slices
        \param      stacks  Stacks
        \param      closed  Closed at base

        \note   FreeGLUT cones are always closed
    */
    GlutCone(const bool solid = true,const GLdouble base = 1.0,const GLdouble height = 1.0,const GLint slices = 15,const GLint stacks = 10,const bool closed = false);
    /// Destructor
    ~GlutCone();

    virtual void     draw() const;
    virtual GLdouble volume() const;
    virtual void     boundingBox(BoundingBox &box) const;

    /// Cone base radius
    GLdouble &base();
    /// Cone height/length
    GLdouble &height();
    /// Cone slices
    GLint    &slices();
    /// Cone stacks
    GLint    &stacks();
    /// Closed at base
    bool     &closed();

    /// Cone base radius
    const GLdouble &base()   const;
    /// Cone height/length
    const GLdouble &height() const;
    /// Cone slices
    const GLint    &slices() const;
    /// Cone stacks
    const GLint    &stacks() const;
    /// Closed at base
    const bool     &closed() const;

private:

    GLdouble _base;
    GLdouble _height;
    GLint    _slices;
    GLint    _stacks;
    bool     _closed;
};

/////////////

/*! \class   GlutTorus
    \brief   GLUT torus scene-graph node
    \ingroup GlutMaster
    \note    See GltShape for further information
*/

class GlutTorus : public GltShape
{
public:
    /*!
        \brief      Constructor
        \param      solid       Display as solid or wireframe
        \param      innerRadius Inner radius of torus
        \param      outerRadius Outer radius of torus
        \param      nsides      Number of edges on each ring
        \param      rings       Number of rings around the torus
    */
    GlutTorus(const bool solid = true,const GLdouble innerRadius = 0.5,const GLdouble outerRadius = 1.0,const GLint nsides = 10,const GLint rings = 16);
    /// Destructor
    ~GlutTorus();

    virtual void draw() const;

    /// Torus inner radius
    GLdouble &innerRadius();
    /// Torus outer radius
    GLdouble &outerRadius();
    /// Number of edges on each torus ring
    GLint    &nsides();
    /// Number of rings around torus
    GLint    &rings();

    /// Torus inner radius
    const GLdouble &innerRadius() const;
    /// Torus outer radius
    const GLdouble &outerRadius() const;
    /// Number of edges on each torus ring
    const GLint    &nsides() const;
    /// Number of rings around torus
    const GLint    &rings() const;

private:

    GLdouble _innerRadius;
    GLdouble _outerRadius;
    GLint    _nsides;
    GLint    _rings;
};

/////////////

/*! \class   GlutDodecahedron
    \brief   GLUT dodecahedron scene-graph node
    \ingroup GlutMaster
    \note    See GltShape for further information
*/

class GlutDodecahedron : public GltShape
{
public:
    /*!
        \brief      Constructor
        \param      solid       Display as solid or wireframe
    */
    GlutDodecahedron(const bool solid = true);
    /// Destructor
    ~GlutDodecahedron();

    virtual void draw() const;
};

/////////////

/*! \class   GlutOctahedron
    \brief   GLUT octahedron scene-graph node
    \ingroup GlutMaster
    \note    See GltShape for further information
*/

class GlutOctahedron : public GltShape
{
public:
    /*!
        \brief      Constructor
        \param      solid       Display as solid or wireframe
    */
    GlutOctahedron(const bool solid = true);
    /// Destructor
    ~GlutOctahedron();

    virtual void draw() const;
};

/////////////

/*! \class   GlutTetrahedron
    \brief   GLUT tetrahedron scene-graph node
    \ingroup GlutMaster
    \note    See GltShape for further information
*/

class GlutTetrahedron : public GltShape
{
public:
    /*!
        \brief      Constructor
        \param      solid       Display as solid or wireframe
    */
    GlutTetrahedron(const bool solid = true);
    /// Destructor
    ~GlutTetrahedron();

    virtual void draw() const;
};

/////////////

/*! \class   GlutIcosahedron
    \brief   GLUT icosahedron scene-graph node
    \ingroup GlutMaster
    \note    See GltShape for further information
*/

class GlutIcosahedron : public GltShape
{
public:
    /*!
        \brief      Constructor
        \param      solid       Display as solid or wireframe
    */
    GlutIcosahedron(const bool solid = true);
    /// Destructor
    ~GlutIcosahedron();

    virtual void draw() const;
};

/////////////

/*! \class   GlutTeapot
    \brief   GLUT teapot scene-graph node
    \ingroup GlutMaster
    \note    See GltShape for further information
*/

class GlutTeapot : public GltShape
{
public:
    /*!
        \brief      Constructor
        \param      solid       Display as solid or wireframe
        \param      size        Teapot size
    */
    GlutTeapot(const bool solid = true,const GLdouble size = 1.0);
    /// Destructor
    ~GlutTeapot();

    virtual void draw() const;

    /// Size of the teapot
          GLdouble &size();
    /// Size of the teapot
    const GLdouble &size() const;

private:

    GLdouble    _size;
};

#endif
