#ifndef NODE_TEXT_H
#define NODE_TEXT_H

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
    \brief   Text Overlay Node
    \ingroup Node
*/

#include <iosfwd>
#include <string>

#include <glt/viewport.h>
#include <glt/color.h>
#include <glt/font.h>

#include <node/shapes.h>
#include <node/fade.h>

///////////////////////////// GltTextOverlay ///////////////////////////////////////

/*! \class   GltTextOverlay
    \brief   Text Overlay Node
    \ingroup Node

    Overlay will be constrained to _window viewport
    and positioned according to horizontal and
    vertical alignment.

*/

class GltTextOverlay : public GltShape
{
public:
             GltTextOverlay(const GltFont &font,const GltViewport &window); ///< Constructor
             GltTextOverlay(const GltTextOverlay &overlay);                 ///< Constructor
    virtual ~GltTextOverlay();                                              ///< Destructor

    virtual void draw() const;

                 GltString &text();             ///< Current overlay text
           const GltString &text() const;       ///< Current overlay text

                  GltColor &fadeColor();        ///< Fade colour of overlay viewport

                      bool &border();           ///< Draw overlay border
                  GltColor &borderColor();      ///< Overlay border color

                      bool &shadow();           ///< Draw text shadow
                  GltColor &shadowColor();      ///< Text shadow color

                       int &spacing();          ///< Spacing between overlay border and text
                       int &margin();           ///< Spacing between overlay and window

    GltHorizontalAlignment &alignHorizontal();  ///< Horizontal alignment
    GltVerticalAlignment   &alignVertical();    ///< Vertical alignment

private:

    const GltFont          &_font;
    const GltViewport      &_window;

    GltString              _text;
    GltFadeViewport        _textFade;
    bool                   _textShadow;
    GltColor               _textShadowColor;
    GltHorizontalAlignment _textAlignHorizontal;
    GltVerticalAlignment   _textAlignVertical;

    int                    _spacing;
    int                    _margin;
};

#endif
