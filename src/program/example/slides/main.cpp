/*

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2000-2001 Nigel Stewart
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

#include <node/slides.h>

#include <glt/error.h>
#include <glt/rgb.h>

#include <glutm/master.h>
#include <glutm/window.h>

using namespace std;

//////////////////////////////////////////

class SlidesDemo : public GlutWindow
{
public:
    SlidesDemo
    (
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault
    );

   ~SlidesDemo();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnTick();
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);

    void add(const string &filename);

private:

    GltSlides               _slides;
    bool                    _auto;

    void setAuto(const bool a);
};

SlidesDemo::SlidesDemo(int width,int height,int x,int y)
: GlutWindow("Slides",width,height,x,y,GLUT_DOUBLE|GLUT_RGBA), _auto(false)
{
}

SlidesDemo::~SlidesDemo()
{
}


void
SlidesDemo::OnOpen()
{
    glDisable(GL_NORMALIZE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DITHER);
    glLoadIdentity();

    GLERROR

    black.glClearColor();

    GLERROR

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    setAuto(false);
    enterGameMode();
    setCursor(GLUT_CURSOR_NONE);
    _slides.init();

}

void
SlidesDemo::OnClose()
{
    _slides.clear();
}

void
SlidesDemo::OnTick()
{
    if (_auto)
        _slides.next();

    postRedisplay();
}

void
SlidesDemo::OnKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
    case 13:
        setAuto(!_auto);
        break;

    case 'q':
    case 27:
        close();
        break;

    default:
                GlutWindow::OnKeyboard(key,x,y);
    }

    postRedisplay();
}

void
SlidesDemo::OnSpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_LEFT:  _slides.prev(); break;

    case GLUT_KEY_DOWN:
    case GLUT_KEY_RIGHT: _slides.next(); break;

    default:
                GlutWindow::OnSpecial(key,x,y);
    }

    postRedisplay();
}

void
SlidesDemo::OnDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    _slides.draw();
   GLERROR;
}

void
SlidesDemo::add(const string &filename)
{
    _slides.push_back(filename);
}

void
SlidesDemo::setAuto(const bool a)
{
    _auto = a;
    setTick(_auto ? 3000 : 0);
}

#include <glutm/main.h>

bool GlutMain(const std::vector<std::string> &arg)
{
    SlidesDemo *main = new SlidesDemo(640,480,20,20);
    for (uint32 i=1; i<arg.size(); i++)
        main->add(arg[i]);
    main->open();
    return true;
}
