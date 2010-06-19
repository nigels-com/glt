#ifndef GLT_LIFE_DRAW
#define GLT_LIFE_DRAW

/*

  GltLife
  C++ OpenGL Implementation of Conways Game of Life
  http://www.nigels.com/glt/gltlife/

  Based on CAEL 1.5 by Abraham Egnor
  http://www.ugcs.caltech.edu/~abe/cael.html

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2000 Nigel Stewart
  Email: nigels.com@gmail.com   WWW: http://www.nigels.com/glt/

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

#include <glt/color.h>

#include <node/shape.h>
#include <node/fade.h>
#include <node/interp.h>

#include <vector>

class GltLifeWorld;
class GltViewport;

class GltLifeDraw : public GltShape
{
public:
    GltLifeDraw(const GltLifeWorld &,const GltViewport &);
    ~GltLifeDraw();

    virtual void draw() const;

    typedef enum
    {
        DRAW_LIFE_PIXELS,
        DRAW_LIFE_CAEL,
        DRAW_LIFE_BLEND
    } DrawMode;

    const GltColor  &background() const;
    const DrawMode  &mode() const;

    void setMode(const DrawMode mode);

protected:
    const GltLifeWorld          &_arena;
    const GltViewport           &_viewport;

    DrawMode              _mode;
    GltColor              _background;
    GltFadeViewport       _fadeView;
    GltInterpolatorColor  _interp;

    void drawBorder() const;
    void drawSquares() const;
    void drawCAEL() const;
    void drawBlend() const;
};

#endif
