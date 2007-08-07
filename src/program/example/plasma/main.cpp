/*

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2001-2002 Nigel Stewart
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
#include <glutm/winexam.h>
#include <glutm/shape.h>
#include <glutm/robot.h>

#include <glt/gl.h>
#include <glt/error.h>
#include <glt/rgb.h>
#include <glt/light.h>
#include <glt/lightm.h>
#include <glt/material.h>
#include <glt/fontasci.h>

#include <node/line.h>
#include <node/text.h>
#include <node/fade.h>
#include <node/interp.h>
#include <node/blend.h>
#include <node/shapes.h>
#include <node/starfld.h>

#include <math/random.h>
#include <misc/timer.h>

#include <iostream>
#include <cmath>
using namespace std;

class GltPlasmaWindow : public GlutWindowExaminer
{
public:
    GltPlasmaWindow
    (
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault
    );

   ~GltPlasmaWindow();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnKeyboard(unsigned char key, int x, int y);

private:

    static void makeSparks   (GltShapes &shapes,GltRandomLCG &random,const int n,const double alpha,const double width,const bool lineSmooth);
    static void makeShell    (GltShapes &shapes);
    static void plasmaLineSubdivide(vector<Vector> &line,GltRandomLCG &random,const real mag);
    static void plasmaLineCreate   (vector<Vector> &line,GltRandomLCG &random,const real mag,const real mult,const int n);

    GltShapes      _shapes;

    GltShapes       _lines;
    vector<Matrix> _transform;

    GltFadeViewport *_fade;
};

GltPlasmaWindow::GltPlasmaWindow(int width,int height,int x,int y)
: GlutWindowExaminer("GLT Plasma Demo",width,height,x,y,GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH)
{
}

GltPlasmaWindow::~GltPlasmaWindow()
{
}

void
GltPlasmaWindow::OnOpen()
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

    black.glClearColor();

    GltLight light0(GL_LIGHT0);
    light0.ambient()  = GltColor(0.1, 0.1, 0.1, 1.0);
    light0.specular() = GltColor(1.0, 1.0, 1.0, 0.0);
    light0.position() = Vector(8.0, 2.0, 8.0);
    light0.attenutationLinear() = 0.05;
    light0.enabled()  = true;
    light0.set();

    GltLight light1(GL_LIGHT1);
    light1.ambient()  = GltColor(0.1, 0.1, 0.1, 1.0);
    light1.specular() = GltColor(1.0, 1.0, 1.0, 0.0);
    light1.position() = Vector(-8.0, 2.0, 8.0);
    light1.attenutationLinear() = 0.05;
    light1.enabled()  = true;
    light1.set();

    GltMaterial material(GL_FRONT_AND_BACK);
    material.ambient()   = GltColor(0.1,0.1,0.1);
    material.diffuse()   = GltColor(0.9,0.9,0.9);
    material.specular()  = GltColor(0.6,0.6,0.6);
    material.shininess() = 40.0;
    material.set();

    GltLightModel lightModel;
    lightModel.setAmbient(0.2, 0.2, 0.2, 0.0);
    lightModel.setLocalViewer(GL_FALSE);
    lightModel.setTwoSide(GL_TRUE);

    GLERROR

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

//  glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LIGHTING);

    glDepthFunc(GL_LEQUAL);

    // Make sure draw() is called so that interpolators get a chance
    setTick(20);

    // Setup viewing so the front half of starfield is out of sight
    _ortho.zNear() =  1.1;
    _ortho.zFar()  = -4.0;
    _ortho.set();

    // Leave a little space around sphere
    _viewMatrix = matrixScale(0.95);

    //

    const int n = 30;

    {
        GltRandomOrientation<> randMatrix;
        for (int i=0; i<n; i++)
            _transform.push_back(randMatrix.rand());
    }

    makeSparks(_lines,GltRandomLCG::rng,n,1.0,1.0,false);
    _shapes.insert(_shapes.end(),_lines.begin(),_lines.end());

    _shapes.push_back(new GltStarField(150,5));
    makeShell(_shapes);

    {
        _fade = new GltFadeViewport();
        GltInterpolatorColor *interp = new GltInterpolatorColor(_fade->color());
        interp->colorMap().addEntry(0.0,GltColor(0,0,0,1));
        interp->colorMap().addEntry(1.0,GltColor(0,0,0,0));
        interp->start(1.0);
        _shapes.push_back(interp);
        _shapes.push_back(_fade);
    }
}

void
GltPlasmaWindow::OnClose()
{
    _transform.clear();
    _lines.clear();
    _shapes.clear();
    _fade = NULL;
}

void
GltPlasmaWindow::OnDisplay()
{
    for (uint32 i=0; i<_lines.size(); i++)
    {
        int j = rand()%_transform.size();
        _lines[i]->transformation() = _lines[i]->transformation() * _transform[j];
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _shapes.draw();
    _shapes.flushExpired();

    GLERROR;
}

void
GltPlasmaWindow::OnKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 27:
                if (_fade)
                {
                    GltInterpolatorColor *interp = new GltInterpolatorColor(_fade->color());
                    interp->colorMap().addEntry(0.0,GltColor(0,0,0,0));
                    interp->colorMap().addEntry(1.0,GltColor(0,0,0,1));
                    interp->start(1.0);
                    _shapes.push_back(interp);
                    _shapes.push_back(new GlutRobot(_shapes.back(),*this,MENU_CLOSE));
                }
                break;
    default:
                GlutWindowExaminer::OnKeyboard(key,x,y);
    }
}

void
GltPlasmaWindow::makeSparks(GltShapes &shapes,GltRandomLCG &rand,const int n,const double alpha,const double width,const bool lineSmooth)
{
    for (int i=0; i<n; i++)
    {
        GltLine *line = new GltLine();
        plasmaLineCreate(line->points(),rand,0.1,1.2,4);
        line->color() = GltColor(white,alpha);
        line->width() = width;
        shapes.push_back(line);
    }
}

void
GltPlasmaWindow::makeShell(GltShapes &shapes)
{
    {
        GlutCylinder *cyl = new GlutCylinder();
        cyl->color() = grey;
        cyl->position(Vector0,-VectorY,0.02);
        shapes.push_back(cyl);
    }

    {
        GlutSphere *ball = new GlutSphere();
        ball->color() = grey;
        ball->position(Vector0,0.04);
        shapes.push_back(ball);
    }

    {
        GltBlend *blend = new GltBlend(GL_SRC_ALPHA,GL_ONE);
        GlutSphere *sphere = new GlutSphere(true,1.01,40,40);
        blend->push_back(sphere);

        GltInterpolatorColor *interp = new GltInterpolatorColor(sphere->color());
        const GLdouble alpha = 0.5;
        interp->colorMap().addEntry(0.0,GltColor(blue  ,alpha));
        interp->colorMap().addEntry(0.9,GltColor(blue  ,alpha));
        interp->colorMap().addEntry(1.0,GltColor(red   ,alpha));
        interp->colorMap().addEntry(1.9,GltColor(red   ,alpha));
        interp->colorMap().addEntry(2.0,GltColor(green ,alpha));
        interp->colorMap().addEntry(2.9,GltColor(green ,alpha));
        interp->colorMap().addEntry(3.0,GltColor(orange,alpha));
        interp->colorMap().addEntry(3.9,GltColor(orange,alpha));
        interp->colorMap().addEntry(4.0,GltColor(pink  ,alpha));
        interp->colorMap().addEntry(4.9,GltColor(pink  ,alpha));
        interp->colorMap().addEntry(5.0,GltColor(blue  ,alpha));
        interp->start(60.0,true);

        shapes.push_back(interp);
        shapes.push_back(blend);
    }
}

void
GltPlasmaWindow::plasmaLineSubdivide(vector<Vector> &line,GltRandomLCG &rand,const real mag)
{
    vector<Vector> tmp;
    tmp.reserve(line.size()*2);

    for (uint32 i=0; i<line.size()-1; i++)
    {
        tmp.push_back(line[i]);

        Vector dir =  line[i+1] - line[i];
        const real r = dir.length();
        if (r<1.e-3)
            continue;

        real pos = GltRandomDouble<GltRandomLCG>(0.0,1.0).rand();
        const Vector mid = line[i] + dir*pos;

        if (pos>0.5)
            pos = (1.0-pos);
        pos *= 2.0;

        Vector x,y;
        orthogonalSystem(dir,x,y);

        const real xp = GltRandomDouble<GltRandomLCG>(-1.0,1.0).rand();
        const real yp = GltRandomDouble<GltRandomLCG>(-1.0,1.0).rand();

        tmp.push_back(mid+(x*xp+y*yp)*(r*mag*pos));
    }

    tmp.push_back(line.back());
    line = tmp;
}

void
GltPlasmaWindow::plasmaLineCreate(vector<Vector> &line,GltRandomLCG &random,const real mag,const real mult,const int n)
{
    line.clear();
    line.push_back(Vector0);
    line.push_back(VectorX);

    real m = mag;
    for (int i=0; i<n; i++,m*=mult)
        plasmaLineSubdivide(line,random,m);
}

#include <glutm/main.h>

bool GlutMain(const std::vector<std::string> &arg)
{
    GlutWindow *main = new GltPlasmaWindow(400,400,20,20);
    main->open();

    return true;
}
