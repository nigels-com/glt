#ifndef GLT_MATERIAL_H
#define GLT_MATERIAL_H

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
    \brief OpenGL Material Class
    \ingroup GLT

    $Id: material.h,v 2.1 2004/08/11 05:20:18 nigels Exp $

    $Log: material.h,v $
    Revision 2.1  2004/08/11 05:20:18  nigels
    Updated copyright and removed email address from headers

    Revision 2.0  2004/02/08 19:44:11  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.16  2003/03/06 12:21:17  nigels
    Documentation refinements

    Revision 1.15  2002/11/27 00:57:28  nigels
    expand

    Revision 1.14  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.13  2002/10/07 16:33:35  nigels
    Added CVS info


*/

#include <glt/gl.h>
#include <glt/color.h>

#include <iosfwd>

/////////////////////////// GltMaterial ////////////////////////////////////

/*! \class GltMaterial
    \brief OpenGL Material Class
    \ingroup GLT

    OpenGL material settings object
*/

class GltMaterial
{
public:

    /// Constructor
    GltMaterial(const GLenum face = GL_FRONT_AND_BACK,const bool getIt = false);

    /// Full constructor
    GltMaterial
    (
        const GltColor &ambient,
        const GltColor &diffuse,
        const GltColor &specular,
        const GltColor &emission,
        const GLfloat   shininess,
        const GLenum face  = GL_FRONT_AND_BACK
    );

    /// Construct by name
    GltMaterial(const std::string &name,const GLenum face  = GL_FRONT_AND_BACK);

    /// Destructor
    ~GltMaterial();

    //

    void get();             ///< Get the current OpenGL material settings
    void set() const;       ///< Set the current OpenGL material settings

    //


    GLenum   &face();       ///< Front and/or back face
    GltColor &ambient();    ///< Ambient color
    GltColor &diffuse();    ///< Diffuse color
    GltColor &specular();   ///< Specular color
    GltColor &emission();   ///< Emissive color
    GLfloat  &shininess();  ///< Shininess coefficient
    GLint    *colorIndex(); ///< Color Index


    const GLenum   &face()       const; ///< Front and/or back face
    const GltColor &ambient()    const; ///< Ambient color
    const GltColor &diffuse()    const; ///< Diffuse color
    const GltColor &specular()   const; ///< Specular color
    const GltColor &emission()   const; ///< Emissive color
    const GLfloat  &shininess()  const; ///< Shininess coefficient
    const GLint    *colorIndex() const; ///< Color Index

private:

    GLenum  _face;

    GltColor _ambient;
    GltColor _diffuse;
    GltColor _specular;
    GltColor _emission;
    GLfloat _shininess;

    GLint   _colorIndex[4];

    //

    static const int          _matSize;
    static const char        *_matName [];
    static const GltMaterial *_matValue[];
};

//

extern const GltMaterial blackPlasticMaterial;
extern const GltMaterial blackRubberMaterial;
extern const GltMaterial brassMaterial;
extern const GltMaterial bronzeMaterial;
extern const GltMaterial chromeMaterial;
extern const GltMaterial copperMaterial;
extern const GltMaterial emeraldMaterial;
extern const GltMaterial goldMaterial;
extern const GltMaterial jadeMaterial;
extern const GltMaterial obsidianMaterial;
extern const GltMaterial pearlMaterial;
extern const GltMaterial pewterMaterial;
extern const GltMaterial polishedBronzeMaterial;
extern const GltMaterial polishedCopperMaterial;
extern const GltMaterial polishedGoldMaterial;
extern const GltMaterial polishedSilverMaterial;
extern const GltMaterial rubyMaterial;
extern const GltMaterial silverMaterial;
extern const GltMaterial turquoiseMaterial;
extern const GltMaterial whitePlasticMaterial;

#endif
