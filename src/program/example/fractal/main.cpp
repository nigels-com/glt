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

#include <glutm/master.h>
#include <glutm/main.h>
#include <glutm/winexam.h>

#include <glt/gl.h>
#include <glt/error.h>
#include <glt/light.h>
#include <glt/lightm.h>
#include <glt/material.h>
#include <glt/color.h>
#include <glt/rgb.h>

#include <node/shapes.h>

#include <iostream>
#include <cmath>
using namespace std;

#include "sierpink.h"

class GltFractalWindow : public GlutWindowExaminer
{
public:
    GltFractalWindow
    (
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault
    );

   ~GltFractalWindow();

    void OnOpen();
    void OnClose();
    void OnDisplay();

private:

    GltShapes _shapes;
};

GltFractalWindow::GltFractalWindow(int width,int height,int x,int y)
: GlutWindowExaminer("GLT Fractal Demo",width,height,x,y,GLUT_DOUBLE|GLUT_RGBA)
{
    _ortho.zNear() = -10.0;
    _ortho.zFar()  =  10.0;
}

GltFractalWindow::~GltFractalWindow()
{
}

void
GltFractalWindow::OnOpen()
{
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

    dodgerBlue4.glClearColor();

    GltLight light0(GL_LIGHT0);
    light0.ambient()  = GltColor(0.1, 0.1, 0.1, 1.0);
    light0.specular() = GltColor(0.5, 0.5, 0.5, 0.0);
    light0.position() = Vector(0.2, 0.5, 5.0);
    light0.enabled()  = true;
    light0.set();

    polishedBronzeMaterial.set();

    GltLightModel lightModel;
    lightModel.setAmbient(0.0, 0.0, 0.0, 0.0);
    lightModel.setLocalViewer(GL_FALSE);
    lightModel.setTwoSide(GL_TRUE);

    GLERROR

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    //

    sierpinskiSponge(_shapes,2,-Vector1,Vector1,yellow);
//  sierpinskiFlake(_shapes,4,-Vector1,Vector1,yellow);
}

void
GltFractalWindow::OnClose()
{
    _shapes.clear();
}

void
GltFractalWindow::OnDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _shapes.draw();
}

bool GlutMain(const std::vector<std::string> &arg)
{
    GlutWindow *main = new GltFractalWindow(400,400,20,20);
    main->open();

    return true;
}

