/*
  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2007 Nigel Stewart

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

#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include <glt/rgb.h>
#include <glt/color.h>
#include <glt/error.h>
#include <glt/light.h>
#include <glt/material.h>
#include <glt/lightm.h>
#include <glt/matrix.h>

#include <glutm/main.h>
#include <glutm/shape.h>
#include <glutm/winexam.h>

#include <node/dlist.h>

#include <math/vector3.h>
#include <math/random.h>

/////////////////

class GlutRandomSpherePointsWindow : public GlutWindowExaminer
{
public:
	GlutRandomSpherePointsWindow
	(
		int width                = widthDefault, 
		int height               = heightDefault,
		int x                    = xDefault, 
		int y                    = yDefault
	);

	~GlutRandomSpherePointsWindow();

	void OnOpen();
	void OnClose();
	void OnDisplay();
	void OnKeyboard(unsigned char ch,int x,int y);

private:
	void arrangeGrid();
	void arrangeRGB();
	void arrangeHSV();

	GltDisplayList   _sphere;
	GlutSphere       _world;
	vector<Vector>   _point;
	int              _n;
};

GlutRandomSpherePointsWindow::GlutRandomSpherePointsWindow(int width,int height,int x,int y)
: GlutWindowExaminer("Random Points on Sphere",width,height,x,y,GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH)
{
}

GlutRandomSpherePointsWindow::~GlutRandomSpherePointsWindow()
{
}

void
GlutRandomSpherePointsWindow::OnOpen()
{
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glDisable(GL_DITHER);
	glCullFace(GL_BACK);
	glClearDepth(1.0);
	glDepthRange(1.0,0.0);
	glLoadIdentity();

	GLERROR

	black.glClearColor();
	
	GltLight light0(GL_LIGHT0);
	light0.ambient()  = GltColor(0.1, 0.1, 0.1, 1.0);
	light0.specular() = GltColor(0.5, 0.5, 0.5, 0.0);
	light0.position() = Vector(1.5, 4.0, 8.0);
	light0.enabled()  = true;
	light0.set();

	bronzeMaterial.set();

	GltLightModel lightModel;
	lightModel.setAmbient(0.0, 0.0, 0.0, 0.0);
	lightModel.setLocalViewer(GL_FALSE);
	lightModel.setTwoSide(GL_TRUE);

	GLERROR

	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	// World

	_world.color() = orange;

	// Sphere display list

	GlutSphere sphere;
	sphere.inheritColor() = true;
	sphere.transformation() = matrixScale(0.025);

	_sphere.newList();
	sphere.draw();
	_sphere.endList();

	// Random points on sphere

	_n = 500;
	_point.clear();
	_point.reserve(_n);

	GltRandomSphere<> random;
	for (int i=0; i<_n; i++)
		_point.push_back(random.rand());

	//

	_viewMatrix = matrixScale(0.9);
}

void 
GlutRandomSpherePointsWindow::OnClose()
{
	_sphere.reset();
	_point.clear();
}

void 
GlutRandomSpherePointsWindow::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_world.draw();

	white.glColor();
	for (int i=0; i<_point.size(); i++)
	{
		glPushMatrix();
			glTranslate(_point[i]);
			_sphere.draw();
		glPopMatrix();
	}
}

void 
GlutRandomSpherePointsWindow::OnKeyboard(unsigned char ch,int x,int y)
{
	switch (ch)
	{
	case ' ':
		OnOpen();
		break;
	default:
		GlutWindowExaminer::OnKeyboard(ch,x,y);
		return;
	}

	postRedisplay();
}

bool GlutMain(const std::vector<std::string> &arg)
{
	cout << "Space key to randomise" << endl;
	cout << endl;

	GlutWindow *main = new GlutRandomSpherePointsWindow(600,600,20,20);
	main->open();

	return true;
}

