#ifndef MESH_MD3_H
#define MESH_MD3_H

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
    \brief   Quake3 MD3 File Loader
    \ingroup Mesh
    \todo    Animation support
    \todo    MD3 Documentation

    $Id: md3.h,v 1.1 2004/02/08 11:54:21 jgasseli Exp $

    $Log: md3.h,v $
    Revision 1.1  2004/02/08 11:54:21  jgasseli
    Initial revision

    Revision 1.8  2003/07/29 08:21:54  nigels
    *** empty log message ***

    Revision 1.5  2003/06/02 03:15:56  nigels
    MD3 Tweaks

    Revision 1.4  2003/05/10 17:01:15  nigels
    Tidy and document

    Revision 1.3  2003/03/06 12:31:14  nigels
    *** empty log message ***

*/

#include <mesh/mesh.h>
#include <node/shapes.h>
#include <glt/texture.h>

#include <string>

class MD3Object;

///////////////////////////// MD3Surface //////////////////////////////

/*! \class   MD3Surface
    \brief   Quake3 MD3 Surface
    \ingroup Mesh
*/

class MD3Surface : public GltShape
{
    friend class MD3Object;

public:
    MD3Surface();                               ///< Constructor
    virtual ~MD3Surface();                      ///< Destructor

    void draw() const;
    void boundingBox(BoundingBox &box) const;

private:
    std::vector<Mesh> _frame;                   ///< Keyframes
    uint32            _current;                 ///< Current keyframe

    GltTexturePtr     _texture;                 ///< Texture
    std::string       _textureName;             ///< Texture name
};

///////////////////////////// MD3Object //////////////////////////////

/*! \class   MD3Object
    \brief   Quake3 MD3 Object
    \ingroup Mesh
*/

class MD3Object : public GltShape
{
public:
    MD3Object();                                            ///< Constructor
    virtual ~MD3Object();                                   ///< Destructor

    void draw() const;
    void boundingBox(BoundingBox &box) const;

    bool loadModel(const std::string &filename);            ///< Load model from file
    bool loadModel(const void *buffer,const uint32 size);   ///< Load model from memory

    bool loadSkin(const std::string &filename);             ///< Load skin from file
    bool loadSkin(const void *buffer,const uint32 size);    ///< Load skin from memory

    bool link(GltShapePtr object,const std::string &tag);   ///< Link surfaces via tag

private:
    std::vector<std::string> _tag;                          ///< Tag names
    std::vector<Matrix>      _tagFrame;                     ///< Tag reference frames

    std::vector<MD3Surface>  _surface;                      ///< MD3 surfaces
    std::vector<GltShapePtr> _link;                         ///< Links
};

////////////////////////////////////////////////////////////////////////

GltShapes readMD3(const std::string &basename);

#endif
