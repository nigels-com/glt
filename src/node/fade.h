#ifndef NODE_FADE_H
#define NODE_FADE_H

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
    \brief   OpenGL Viewport Fade Node
    \ingroup Node
*/

#include <glt/viewport.h>
#include <glt/color.h>

#include <node/shapes.h>

///////////////////////////// GltFadeViewport ///////////////////////////////////////

/*! \class   GltFadeViewport
    \brief   OpenGL Viewport Fade Node
    \ingroup Node
*/

class GltFadeViewport : public GltShape
{
public:
             GltFadeViewport();             ///< Constructor
    virtual ~GltFadeViewport();             ///< Destructor

    virtual void draw() const;

    // Get/Set

          bool &border();                   ///< Draw border
    const bool &border() const;             ///< Draw border

          GltColor &borderColor();          ///< Border color
    const GltColor &borderColor() const;    ///< Border color

private:

    bool               _border;
    GltColor           _borderColor;
};

#endif
