#include "draw.h"

/*

  GltLife
  C++ OpenGL Implementation of Conways Game of Life
  http://www.nigels.com/glt/gltlife/

  Based on CAEL 1.5 by Abraham Egnor
  http://www.ugcs.caltech.edu/~abe/cael.html

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2000 Nigel Stewart
  Email: nigels@nigels.com   WWW: http://www.nigels.com/glt/

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

#include "world.h"

#include <glutm/glut.h>
#include <glt/rgb.h>

#include <iostream>
#include <cmath>
using namespace std;

GltLifeDraw::GltLifeDraw(const GltLifeWorld &arena,const GltViewport &viewport)
:
    _arena(arena),
    _viewport(viewport),
    _mode(DRAW_LIFE_BLEND),
    _interp(color())
{
    setMode(DRAW_LIFE_BLEND);

    _interp.colorMap().addEntry( 0.0,red);
    _interp.colorMap().addEntry( 1.0,orange);
    _interp.colorMap().addEntry( 2.0,yellow);
    _interp.colorMap().addEntry( 3.0,green);
    _interp.colorMap().addEntry( 4.0,purple);
    _interp.colorMap().addEntry( 5.0,blue);
    _interp.colorMap().addEntry( 6.0,lightSteelBlue);
    _interp.colorMap().addEntry( 7.0,white);
    _interp.colorMap().addEntry( 8.0,red);

    _interp.colorMap() *= 300.0;    // Scale the domain of the colour map
}

GltLifeDraw::~GltLifeDraw()
{
}

void
GltLifeDraw::setMode(const DrawMode mode)
{
    _mode = mode;

    switch (_mode)
    {
    case DRAW_LIFE_PIXELS:
        color() = lightSteelBlue;
        _background = GltColor(0.3,0.3,0.5);
        _interp.stop();
        break;

    case DRAW_LIFE_CAEL:
        color() = lightSteelBlue;
        _background = black;
        _interp.stop();
        break;

    case DRAW_LIFE_BLEND:
        _background = black;
        _interp.start(true);
        _fadeView.color() = black;
        _fadeView.color().alpha() = 0.1;
        break;
    }
}

void
GltLifeDraw::drawBorder() const
{
    glBegin(GL_LINE_LOOP);
        glVertex2i(           -1,               0);
        glVertex2i(           -1,_arena._height+1);
        glVertex2i(_arena._width,_arena._height+1);
        glVertex2i(_arena._width,               0);
    glEnd();
}

void
GltLifeDraw::drawSquares() const
{
    unsigned short *j = _arena.getCells();

    glBegin(GL_QUADS);
    for (GLshort y=0; y<_arena._height; y++)
        for (GLshort x=0; x<_arena._width; x++)
            if (*(j++)>0)
            {
                glVertex2i(x  ,y  );
                glVertex2i(x  ,y+1);
                glVertex2i(x+1,y+1);
                glVertex2i(x+1,y  );
            }
    glEnd();
}

void
GltLifeDraw::drawBlend() const
{
    const int n = _arena.population();
    const int s = n<<1;

    GLshort *vertex = new GLshort[s];

    {
        GLshort        *i = vertex;
        unsigned short *j = _arena.getCells();
        for (GLshort y=_arena._height-1; y>=0; y--)
            for (GLshort x=0; x<_arena._width; x++)
                if (*(j++)>0)
                {
                    *(i++) = x;
                    *(i++) = y;
                }
    }

    // Use OpenGL 1.1 Vertex Array Extension
    //
    // Perhaps use bitmap instead?

    glVertexPointer(2,GL_SHORT,0,vertex);
    glEnableClientState(GL_VERTEX_ARRAY);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0,_viewport.width(),0.0,_viewport.height(),-1.0,1.0);

        glMatrixMode(GL_MODELVIEW);

        for (int x=0; x<_viewport.width()+_arena._width; x += _arena._width)
            for (int y=0; y<_viewport.height()+_arena._height; y += _arena._height)
            {
                glLoadIdentity();
                glTranslated(x,y,0.0);
                glDrawArrays(GL_POINTS,0,n);
            }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    delete [] vertex;
}

void
GltLifeDraw::drawCAEL() const
{
    for (int y=1; y<_arena._height-1; y++)
        for (int x=1; x<_arena._width-1; x++)
            if (_arena.cell(x,y)>0)
            {
                bool pattern[8];

                  /* 0 1 2
                     3   4
                     5 6 7 */

                pattern[0] = _arena.cell(x-1,y-1)>0;
                pattern[1] = _arena.cell(x  ,y-1)>0;
                pattern[2] = _arena.cell(x+1,y-1)>0;
                pattern[3] = _arena.cell(x-1,y  )>0;
                pattern[4] = _arena.cell(x+1,y  )>0;
                pattern[5] = _arena.cell(x-1,y+1)>0;
                pattern[6] = _arena.cell(x  ,y+1)>0;
                pattern[7] = _arena.cell(x+1,y+1)>0;

                bool quads[4] = { false,false,false,false };

                if (pattern[1] || (pattern[0] && pattern[2])) quads[0] = true; // north
                if (pattern[4] || (pattern[2] && pattern[7])) quads[1] = true; // east
                if (pattern[6] || (pattern[5] && pattern[7])) quads[2] = true; // south
                if (pattern[3] || (pattern[0] && pattern[5])) quads[3] = true; // west

                if ((quads[1] && (pattern[0] || pattern[1])) ||
                    (quads[3] && (pattern[1] || pattern[2])))
                    quads[0] = 1;

                if ((quads[0] && (pattern[4] || pattern[7])) ||
                    (quads[2] && (pattern[2] || pattern[4])))
                    quads[1] = 1;

                if ((quads[1] && (pattern[5] || pattern[6])) ||
                    (quads[3] && (pattern[6] || pattern[7])))
                    quads[2] = 1;

                if ((quads[0] && (pattern[3] || pattern[5])) ||
                    (quads[2] && (pattern[0] || pattern[3])))
                    quads[3] = 1;

                if (quads[0] && quads[2]) quads[1] = quads[3] = 1;
                if (quads[1] && quads[3]) quads[0] = quads[2] = 1;

                if (!quads[0] && !quads[1] && !quads[2] && !quads[3])
                {
                    quads[0] = 1;
                    quads[1] = 1;
                    quads[2] = 1;
                    quads[3] = 1;
                }

                // Draw

                const Vector v0(x    ,y    ,0.0);
                const Vector v1(x+1.0,y    ,0.0);
                const Vector v2(x    ,y+1.0,0.0);
                const Vector v3(x+1.0,y+1.0,0.0);
                const Vector v4(x+0.5,y+0.5,0.0);

                GltColor col0;

                switch (_arena.cell(x,y))
                {
                    case 1: col0 = GltColor(0.5,0.0,0.0); break;
                    case 2: col0 = GltColor(1.0,0.0,0.0); break;
                    case 3: col0 = GltColor(0.0,0.5,0.0); break;
                    case 4: col0 = GltColor(0.0,1.0,0.0); break;
                    case 5: col0 = GltColor(0.0,0.0,0.5); break;
                    case 6: col0 = GltColor(0.0,0.0,1.0); break;
                };

                GltColor col1 = col0*0.5;

                glBegin(GL_TRIANGLES);

                    if (quads[0])
                    {
                        col0.glColor();
                        v0.glVertex();
                        v1.glVertex();
                        col1.glColor();
                        v4.glVertex();
                    }

                    if (quads[1])
                    {
                        col0.glColor();
                        v1.glVertex();
                        v3.glVertex();
                        col1.glColor();
                        v4.glVertex();
                    }

                    if (quads[2])
                    {
                        col0.glColor();
                        v2.glVertex();
                        v3.glVertex();
                        col1.glColor();
                        v4.glVertex();
                    }

                    if (quads[3])
                    {
                        col0.glColor();
                        v0.glVertex();
                        v2.glVertex();
                        col1.glColor();
                        v4.glVertex();
                    }

                glEnd();
            }
}

void
GltLifeDraw::draw() const
{
    switch (_mode)
    {
    case DRAW_LIFE_PIXELS:
        _background.glClearColor();
        glClear(GL_COLOR_BUFFER_BIT);
        color().glColor();
        drawBorder();
        drawSquares();
        break;

    case DRAW_LIFE_CAEL:
        _background.glClearColor();
        glClear(GL_COLOR_BUFFER_BIT);
        color().glColor();
        drawBorder();
        drawCAEL();
        break;

    case DRAW_LIFE_BLEND:
        _background.glClearColor();
        _fadeView.draw();
        _interp.draw();
        color().glColor();
        drawBlend();
        break;
    }
}

const GltColor &GltLifeDraw::background() const
{
    return _background;
}

const GltLifeDraw::DrawMode &GltLifeDraw::mode() const
{
    return _mode;
}
