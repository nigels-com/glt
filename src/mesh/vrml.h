#ifndef MESH_VRML_H
#define MESH_VRML_H

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
    \brief   VRML Data Types
    \ingroup Mesh
    \todo Vector2 for SFVec2f

    $Id: vrml.h,v 1.2 2004/02/08 14:13:21 jgasseli Exp $

    $Log: vrml.h,v $
    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.6  2003/05/10 17:02:08  nigels
    Tidy and document

    Revision 1.5  2003/03/06 12:31:14  nigels
    *** empty log message ***

*/

#include <vector>

#include <glt/color.h>
#include <math/vector3.h>
#include <math/vector4.h>
#include <misc/refcount.h>
#include <node/shape.h>
#include <node/shapes.h>

typedef bool     SFBool;
typedef int32    SFInt32;
typedef real     SFFloat;
typedef real     SFTime;
typedef Vector   SFVec3f;
typedef Vector4  SFRotation;
typedef GltColor SFColor;

typedef std::vector<SFBool>  MFBool;
typedef std::vector<SFInt32> MFInt32;
typedef std::vector<SFFloat> MFFloat;
typedef std::vector<SFVec3f> MFVec3f;
typedef std::vector<SFColor> MFColor;

typedef GltShape Node;
typedef ReferenceCountPtr<Node> NodePtr;

typedef GltShapes Nodes;
typedef ReferenceCountPtr<Nodes> NodesPtr;

///////////////////////////// IndexedFaceSet //////////////////////////////

/*! \class   IndexedFaceSet
    \brief   VRML97 Indexed Face Set
    \ingroup Mesh

    http://www.web3d.org/Specifications/VRML97/part1/nodesRef.html#IndexedFaceSet

    <pre>
    IndexedFaceSet
    {
      eventIn       MFInt32 set_colorIndex
      eventIn       MFInt32 set_coordIndex
      eventIn       MFInt32 set_normalIndex
      eventIn       MFInt32 set_texCoordIndex
      exposedField  SFNode  color             NULL
      exposedField  SFNode  coord             NULL
      exposedField  SFNode  normal            NULL
      exposedField  SFNode  texCoord          NULL
      field         SFBool  ccw               TRUE
      field         MFInt32 colorIndex        []        # [-1,infinity)
      field         SFBool  colorPerVertex    TRUE
      field         SFBool  convex            TRUE
      field         MFInt32 coordIndex        []        # [-1,infinity)
      field         SFFloat creaseAngle       0         # [0,infinity)
      field         MFInt32 normalIndex       []        # [-1,infinity)
      field         SFBool  normalPerVertex   TRUE
      field         SFBool  solid             TRUE
      field         MFInt32 texCoordIndex     []        # [-1,infinity)
    }
    </pre>
*/

class IndexedFaceSet;
typedef ReferenceCountPtr<IndexedFaceSet> IndexedFaceSetPtr;

class IndexedFaceSet : public Node
{
public:

    IndexedFaceSet();
    ~IndexedFaceSet();

    MFVec3f coord;
    MFInt32 coordIndex;

    MFVec3f normal;
    MFInt32 normalIndex;
    SFBool  normalPerVertex;

    MFColor color;
    MFInt32 colorIndex;
    SFBool  colorPerVertex;

    MFVec3f texCoord;
    MFInt32 texCoordIndex;

    SFBool  ccw;
    SFBool  convex;
    SFBool  solid;
    SFFloat creaseAngle;

    virtual void draw() const;
};

///////////////////////////// Material //////////////////////////////

/*! \class   Material
    \brief   VRML97 Material
    \ingroup Mesh

    http://www.web3d.org/Specifications/VRML97/part1/nodesRef.html#Material

    <pre>
    Material
    {
      exposedField SFFloat ambientIntensity  0.2         # [0,1]
      exposedField SFColor diffuseColor      0.8 0.8 0.8 # [0,1]
      exposedField SFColor emissiveColor     0 0 0       # [0,1]
      exposedField SFFloat shininess         0.2         # [0,1]
      exposedField SFColor specularColor     0 0 0       # [0,1]
      exposedField SFFloat transparency      0           # [0,1]
    }
    </pre>
*/

class Material;
typedef ReferenceCountPtr<Material> MaterialPtr;

class Material : public Node
{
public:

    Material();
    ~Material();

    SFFloat ambientIntensity;
    SFColor diffuseColor;
    SFColor emissiveColor;
    SFFloat shininess;
    SFColor specularColor;
    SFFloat transparency;

    virtual void draw() const;
};

///////////////////////////// Shape //////////////////////////////

/*! \class   Shape
    \brief   VRML97 Shape
    \ingroup Mesh

    <pre>
    Shape
    {
        exposedField SFNode appearance NULL
        exposedField SFNode geometry   NULL
    }
    </pre>
*/

class Shape;
typedef ReferenceCountPtr<Shape> ShapePtr;

class Shape : public Node
{
public:
    Shape();
    ~Shape();

    virtual void draw() const;
    virtual void boundingBox(BoundingBox &box) const;

    MaterialPtr       material;
    IndexedFaceSetPtr faces;
};

///////////////////////////// Transform //////////////////////////////

/*! \class   Transform
    \brief   VRML97 Transform
    \ingroup Mesh

    <pre>
    Transform
    {
        eventIn      MFNode      addChildren
        eventIn      MFNode      removeChildren
        exposedField SFVec3f     center           0 0 0    # (-,)
        exposedField MFNode      children         []
        exposedField SFRotation  rotation         0 0 1 0  # [-1,1],(-,)
        exposedField SFVec3f     scale            1 1 1    # (0,)
        exposedField SFRotation  scaleOrientation 0 0 1 0  # [-1,1],(-,)
        exposedField SFVec3f     translation      0 0 0    # (-,)
        field        SFVec3f     bboxCenter       0 0 0    # (-,)
        field        SFVec3f     bboxSize         -1 -1 -1 # (0,) or -1,-1,-1
    }
    </pre>
*/

class Transform;
typedef ReferenceCountPtr<Transform> TransformPtr;

class Transform : public Node
{
public:

    Transform();
    ~Transform();

    GltShapePtr children;

    SFVec3f     center;
    SFRotation  rotation;
    SFVec3f     scale;
    SFRotation  scaleOrientation;
    SFVec3f     translation;
    SFVec3f     bboxCenter;
    SFVec3f     bboxSize;

    virtual void draw() const;
};

#endif
