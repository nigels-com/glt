/*
 * Copyright (C) 2002  Terence M. Welsh
 *
 * Plasma is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Plasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <glt/fontasci.h>
#include <glt/rgb.h>

#include <glutm/main.h>
#include <glutm/window.h>
#include <glutm/glut.h>

#include <node/fields.h>
#include <node/registry.h>
#include <node/fieldmen.h>
#include <node/text.h>

#include <fonts/fonts.h>

#include "plasma.h"

#include <string>
#include <iostream>

class PlasmaScreenSaver : public GlutWindow
{
public:
    PlasmaScreenSaver();
    ~PlasmaScreenSaver();

    void OnOpen();
    void OnClose();
    void OnReshape(int width,int height);
    void OnDisplay();
    void OnTick();
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);

private:

    Plasma           _plasma;

    GltRegistry      _settings;
    GltRegistryMenu  _menu;
    GltTextOverlay   _overlay;
    GltFontAscii     _font;

    static const std::string _registryKey;
};

const std::string PlasmaScreenSaver::_registryKey("Software\\GltPlasma");

PlasmaScreenSaver::PlasmaScreenSaver()
: GlutWindow("GltPlasma",500,400,0,0,GLUT_RGBA|GLUT_DOUBLE),
  _menu(_settings),
  _overlay(_font,_viewport)
{
    _settings.set(_plasma.settings());

    _overlay.color() = white;
    _overlay.fadeColor() = black;
    _overlay.fadeColor().alpha() = 0.3;
    _overlay.shadow() = true;
    _overlay.alignHorizontal() = GLT_ALIGN_LEFT;
    _overlay.alignVertical()   = GLT_ALIGN_TOP;

    #ifdef GLT_WIN32
    _settings.readRegistry(_registryKey);
    #endif
}

PlasmaScreenSaver::~PlasmaScreenSaver()
{
    #ifdef GLT_WIN32
    _settings.writeRegistry(_registryKey);
    #endif
}

void
PlasmaScreenSaver::OnOpen()
{
    ignoreKeyRepeat(true);
    _font.init(vga14Font);
    _menu.reset();

    setTick(1000/30); // 30 fps max
}

void
PlasmaScreenSaver::OnClose()
{
    _font.init(NULL);
}

void
PlasmaScreenSaver::OnReshape(int width,int height)
{
    GlutWindow::OnReshape(width,height);
    _plasma.init(width,height);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0,width,0,height,-1,1);

    glMatrixMode(GL_MODELVIEW);
}

void
PlasmaScreenSaver::OnDisplay()
{
    _plasma.draw();

    if (_menu.active())
    {
        _overlay.text() = _menu.menu();
        _overlay.draw();
    }
}

void
PlasmaScreenSaver::OnTick()
{
    _plasma.update();
    postRedisplay();
}

void
PlasmaScreenSaver::OnKeyboard(unsigned char key, int x, int y)
{
    if (_menu.OnKeyboard(key,x,y))
    {
        postRedisplay();
        return;
    }

    GlutWindow::OnKeyboard(key,x,y);
}

void
PlasmaScreenSaver::OnSpecial(int key, int x, int y)
{
    if (_menu.OnSpecial(key,x,y))
    {
        postRedisplay();
        return;
    }

    GlutWindow::OnSpecial(key,x,y);
}

bool GlutMain(const std::vector<std::string> &arg)
{
    static GlutWindow *main = new PlasmaScreenSaver();
    main->open();

    return true;
}

