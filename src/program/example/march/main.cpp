/*

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

#include <glutm/main.h>
#include <glutm/winexam.h>
#include <glutm/glut.h>

#include <glt/gl.h>
#include <glt/rgb.h>
#include <glt/info.h>
#include <glt/color.h>
#include <glt/error.h>
#include <glt/light.h>
#include <glt/lightm.h>
#include <glt/mcubes.h>
#include <glt/material.h>
#include <glt/fontasci.h>

#include <math/matrix4.h>
#include <math/vector3.h>

#include <node/text.h>
#include <node/dlist.h>

#include <fonts/fonts.h>

#include <string>
#include <cmath>
#include <iostream>
#include <iostream>
using namespace std;

////

class MarchingCubesDemo : public GlutWindowExaminer
{
public:
    MarchingCubesDemo();
   ~MarchingCubesDemo();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnTick();
    void OnKeyboard(unsigned char key, int x, int y);
    void OnMenu(int value);

   static const string _message;

protected:

    GltDisplayList _list;
    void generateDisplayList(GltFunc3d func);

    GltFontAscii             _font;
    GltTextOverlay           _info;

    typedef enum
    {
        MCUBES_SPHERE,
        MCUBES_HEART,
        MCUBES_KLEIN,
        MCUBES_SSS,
        MCUBES_WAVE
    } MenuCallbacks;
};

////

const string MarchingCubesDemo::_message =
    "GLT Marching Cubes Demo\n" \
    "\n" \
    "        Left  Button    Menu\n" \
    "        Right Button    Rotate\n" \
    "Shift + Right Button    Pan\n" \
    "Ctrl  + Right Button    Zoom\n" \
    "\n" \
    "               Space    Toggle animation\n" \
    "           1,2,3,4,5    Set isosurface";

MarchingCubesDemo::MarchingCubesDemo()
: GlutWindowExaminer("GLT Marching Cubes Demo"),
  _info(_font,_viewport)
{
    mouseMode() = MODE_MOUSE_RIGHT;
}

MarchingCubesDemo::~MarchingCubesDemo()
{
}

void
MarchingCubesDemo::OnOpen()
{
    _font.init(vga8Font);

    _info.border() = true;
    _info.text() = _message;

    GLERROR

    GlutMenu &func = _leftButtonMenu.subMenu();
    func.addEntry("Sphere",MCUBES_SPHERE);
    func.addEntry("Heart" ,MCUBES_HEART);
    func.addEntry("Klein" ,MCUBES_KLEIN);
    func.addEntry("Sss"   ,MCUBES_SSS);
    func.addEntry("Wave"  ,MCUBES_WAVE);

    _leftButtonMenu.addEntry("Function",func);
    _leftButtonMenu.addEntry("Close" ,MENU_CLOSE);
    _leftButtonMenu.attach();

    GLERROR

    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glDisable(GL_DITHER);
    glCullFace(GL_BACK);
    glClearDepth(1.0);
    glDepthRange(0.0,1.0);
    glLoadIdentity();

    GLERROR

    steelBlue4.glClearColor();

    GltLight light0(GL_LIGHT0);
    light0.ambient()  = GltColor(0.2, 0.2, 0.2, 1.0);
    light0.specular() = GltColor(0.5, 0.5, 0.5, 0.0);
    light0.position() = Vector(1.5, 1.5, 5.0);
    light0.enabled()  = true;
    light0.set();

    chromeMaterial.set();

    GltLightModel lightModel;
    lightModel.setAmbient(0.0, 0.0, 0.0, 0.0);
    lightModel.setLocalViewer(GL_TRUE);
    lightModel.setTwoSide(GL_TRUE);

    GLERROR

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    GLERROR

    generateDisplayList(sphere);

    cout << GltInfo() << endl;
}

void
MarchingCubesDemo::OnClose()
{
    _font.init(NULL);
    _list.reset();
}

void
MarchingCubesDemo::OnDisplay()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    _list.draw();
    _info.draw();
}

void
MarchingCubesDemo::OnTick()
{
    _viewMatrix = matrixRotate(Vector1,1.0)*_viewMatrix;
    postRedisplay();
}

void
MarchingCubesDemo::OnKeyboard(unsigned char key, int x, int y)
{
    GlutWindowExaminer::OnKeyboard(key,x,y);

    switch (key)
    {

    case '1':   generateDisplayList(sphere); break;
    case '2':   generateDisplayList(heart);  break;
    case '3':   generateDisplayList(klein);  break;
    case '4':   generateDisplayList(sss);    break;
    case '5':   generateDisplayList(wave);   break;

    case ' ':   setTick(getTick() ? 0 : 1000/60); break;
    }

    postRedisplay();
}

void
MarchingCubesDemo::OnMenu(int value)
{
    GlutWindowExaminer::OnMenu(value);

    switch (value)
    {
    case MCUBES_SPHERE: generateDisplayList(sphere); break;
    case MCUBES_HEART:  generateDisplayList(heart);  break;
    case MCUBES_KLEIN:  generateDisplayList(klein);  break;
    case MCUBES_SSS:    generateDisplayList(sss);    break;
    case MCUBES_WAVE:   generateDisplayList(wave);   break;
    }

    postRedisplay();
}

////

void
MarchingCubesDemo::generateDisplayList(GltFunc3d func)
{
    _list.newList();
    if (func)
        GltMarchingCubes(func,-1,-1,-1,1,1,1,300,300,300);
    _list.endList();
}


bool GlutMain(const std::vector<std::string> &arg)
{
    cout << MarchingCubesDemo::_message << endl << endl;

    GlutWindow *main = new MarchingCubesDemo();
    main->open();

    return true;
}

