#ifndef NODE_SPRITE_H
#define NODE_SPRITE_H

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
    \brief   Sprite Image Node
    \author  Nigel Stewart, RMIT (nigels@nigels.com)
    \ingroup Node
*/

#include <glt/texture.h>

#include <node/shapes.h>

#include <vector>

///////////////////////////// GltSprite ///////////////////////////////////////

/*! \class   GltSprite
    \brief   Sprite Image Node
    \ingroup Node
*/

class GltSprite : public GltShape
{
public:
             GltSprite();               ///< Constructor
    virtual ~GltSprite();               ///< Destructor

    // Initialisation

    bool init(                          ///< Initialise from PPM, PNG or TGA file
        const std::string &filename,
        const bool mipmap = true);

    bool init(                          ///< Initialise from compressed GLT format
        const void *,
        const bool mipmap = true);

    bool init(                          ///< Initialise from raw string buffer
        const GLsizei width,
        const GLsizei height,
        const std::string &image,
        const bool mipmap = true);

    bool init(                          ///< Initialise from raw memory buffer
        const GLsizei width,
        const GLsizei height,
        const byte *image,
        const GLsizei channels,
        const bool mipmap = true);

    virtual void draw() const;


    void clear();                       ///< Reset sprite and release OpenGL resources

    // Query

    bool   empty()  const;              ///< Is the sprite defined?
    uint32 width()  const;              ///< Sprite width
    uint32 height() const;              ///< Sprite height

          bool &blend();                 ///<
    const bool &blend() const;           ///<

    GltFieldPtr settings();

private:

    std::vector<GltTexturePtr> _texture;

    uint32                     _nx;
    uint32                     _ny;

    uint32                     _width;
    uint32                     _height;

    bool                       _blend;
    bool                       _stretch;
};

#endif
