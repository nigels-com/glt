#include "terminal.h"

#include <glt/color.h>
#include <glt/viewport.h>
#include <glt/cursor.h>
#include <glt/raster.h>
#include <glt/rgb.h>

#include <glutm/glut.h>

#include <cassert>
using namespace std;

GltNoteTerminal::GltNoteTerminal(GltFont &font)
:
  _pos(_buffer),
  _textColor(lightGrey),
  _cursorColor(lightGrey),
  _currentLineFrontColor(white),
  _currentLineBackColor(dimGrey),
  _font(font)
{
    clear();
}

void
GltNoteTerminal::clear()
{
    _buffer.clear();
    _pos.reset();
}

GltNoteTerminal::~GltNoteTerminal()
{
}

void
GltNoteTerminal::draw(const GltViewport &viewport)
{
    GltTextBuffer::iterator tmp = _pos.line();

    const int maxlines = viewport.height()/_font.vStep();

    int i;
    for (i=0; i<maxlines-1 && tmp!=_pos.begin(); i++)
        tmp--;

    _textColor.glColor();
    GltCursor cursor(_font,viewport);

    for (i=0; i<maxlines && tmp!=_pos.end(); i++,tmp++)
    {
        const int w = _font.hStep();
        const int h = _font.vStep();
        const GltRasterPos rpos(true);

        // If on current line

        if (tmp==_pos.line())
        {
            glPushMatrix();

                // Draw background

                glTranslatef(0.0,viewport.height()-rpos.y()+4,0.0);
                _currentLineBackColor.glColor();
                glBegin(GL_POLYGON);
                    glVertex2i(0               ,0);
                    glVertex2i(viewport.width(),0);
                    glVertex2i(viewport.width(),h+1);
                    glVertex2i(0               ,h+1);
                glEnd();

                // Draw cursor

                _cursorColor.glColor();
                glTranslatef(_pos.x()*w,0.0,0.0);
                if (_pos.modeInsert())
                    drawCursor(CURSOR_OUTLINE,w,h);
                else
                    drawCursor(CURSOR_SOLID,w,h);

            glPopMatrix();

            // Text is this color
            _currentLineFrontColor.glColor();
        }
        else
            _textColor.glColor();

        cursor.print(*tmp);
    }
}

void
GltNoteTerminal::drawCursor(const CursorStyle cursor,const int w,const int h)
{
    switch (cursor)
    {
    case CURSOR_OUTLINE:
        glBegin(GL_LINE_LOOP);
            glVertex2i(0,0);
            glVertex2i(w,0);
            glVertex2i(w,h);
            glVertex2i(0,h);
        glEnd();
        break;

    case CURSOR_SOLID:
        glBegin(GL_POLYGON);
            glVertex2i(0,0);
            glVertex2i(w,0);
            glVertex2i(w,h);
            glVertex2i(0,h);
        glEnd();
        break;

    case CURSOR_UNDERLINE:
        glBegin(GL_LINES);
            glVertex2i(0,h);
            glVertex2i(w,h);
        glEnd();
        break;

    default:
        assert(0);
        break;
    }
}

void
GltNoteTerminal::OnKeyboard(unsigned char key, int x, int y)
{
    _pos.insert(key);
}

void
GltNoteTerminal::OnSpecial(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_DOWN:   _pos.goDown();                          break;
        case GLUT_KEY_UP:     _pos.goUp();                            break;
        case GLUT_KEY_LEFT:   _pos.goLeft();                          break;
        case GLUT_KEY_RIGHT:  _pos.goRight();                         break;
        case GLUT_KEY_INSERT: _pos.modeInsert() = !_pos.modeInsert(); break;
    }
}

