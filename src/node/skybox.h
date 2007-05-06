#ifndef NODE_SKYBOX_H
#define NODE_SKYBOX_H

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
    \brief   OpenGL Sky Box Node
    \ingroup Node
*/

#include <node/shapes.h>
#include <glt/texture.h>

///////////////////////////// GltSkyBox ///////////////////////////////////////

/*! \class   GltSkyBox
    \brief   OpenGL Sky Box
    \ingroup GLT

    \todo Make use of GltSprite -> large textures
*/

class GltSkyBox : public GltShape
{
public:

             GltSkyBox();   ///< Constructor
    virtual ~GltSkyBox();   ///< Destructor

    /// Draw sky-box
    virtual void draw() const;

    /// Reset textures
    void clear();

    //
    // Access textures
    //

    /// Right-hand texture
    GltTexture &positiveX();
    /// Left-hand texture
    GltTexture &negativeX();
    /// Ceiling texture
    GltTexture &positiveY();
    /// Floor texture
    GltTexture &negativeY();
    /// Back texture
    GltTexture &positiveZ();
    /// Front texture
    GltTexture &negativeZ();

    /// Field of view
          GLdouble &fov();
    /// Field of view
    const GLdouble  fov() const;

    enum Mode
    {
        MODE_OPENGL = 0,
        MODE_VRML,
        MODE_DIRECTX,
        MODE_DARKBASIC,
        MODE_UNREAL
    };

          Mode &mode();
    const Mode &mode() const;

private:

    GltTexture _positiveX;
    GltTexture _negativeX;
    GltTexture _positiveY;
    GltTexture _negativeY;
    GltTexture _positiveZ;
    GltTexture _negativeZ;

    GLdouble   _fov;
    Mode       _mode;
};

#endif
