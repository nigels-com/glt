#include "rasterb.h"

#include <glt/gl.h>

GltRasterBar::GltRasterBar(const GltColor &edge,const GltColor &middle)
: _edge(edge), _middle(middle), _height(1.0), _pos(0.0)
{
}

void
GltRasterBar::draw()
{
    glBegin(GL_QUADS);

        _edge  .glColor();  glVertex2d( 1.0,-_height+_pos);
        _edge  .glColor();  glVertex2d(-1.0,-_height+_pos);
        _middle.glColor();  glVertex2d(-1.0,         _pos);
        _middle.glColor();  glVertex2d( 1.0,         _pos);

        _middle.glColor();  glVertex2d( 1.0,         _pos);
        _middle.glColor();  glVertex2d(-1.0,         _pos);
        _edge  .glColor();  glVertex2d(-1.0, _height+_pos);
        _edge  .glColor();  glVertex2d( 1.0, _height+_pos);

    glEnd();
}

double &GltRasterBar::height() { return _height; }
double &GltRasterBar::pos()    { return _pos;    }
