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

#include <vector>
#include <list>
#include <iostream>
#include <iomanip>
#include <algorithm>
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

#include <node/shapes.h>
#include <node/dlist.h>

struct SortGrey
{
	SortGrey(const GltColor rgbValue[])
	: _rgbValue(rgbValue)
	{
	}

	bool operator()(const int i,const int j)
	{
		return _rgbValue[i]<_rgbValue[j];
	}

	const GltColor *_rgbValue;
};

// By default the colours are sorted by name.
// We try here to sort them into a reasonable
// progression of colours, for display.

vector<int> 
sortColors(const int rgbSize, const char *rgbName[], const GltColor rgbValue[])
{
	vector<int> out;
	vector<int> todo;
	
	out.reserve(rgbSize);
	todo.reserve(rgbSize);

	// Put black, grey and white colors in output
	// vector, we'll sort these later

	{
		for (int i=0; i<rgbSize; i++)
			if (rgbValue[i].isGrey())
				out.push_back(i);
			else
				todo.push_back(i);
	}

	// Sort grey

	sort(out.begin(),out.end(),SortGrey(rgbValue));

	//

	{
		list<int> chain;
		
		for (int k=0; k<todo.size(); k++)
		{
			const GltColor &color = rgbValue[todo[k]];

			if (chain.size()==0)
				chain.push_back(todo[k]);
			else
			{
				list<int>::iterator i = chain.begin();
				list<int>::iterator j = i;
				j++;

				double best = (rgbValue[*i]-color).norm()*2.0;
				list<int>::iterator pos = chain.begin();

				while (i!=chain.end())
				{
					// Use this metric to find the "best" location
					// to insert the color

					const double d = 
						j==chain.end() ?
						(rgbValue[*i]-color).norm()*2.0 :
						(rgbValue[*i]-color).norm() + (rgbValue[*j]-color).norm();


					if (d<best)
					{
						best = d;
						pos = j;
					}

					i++;
					j++;
				}

				chain.insert(pos,todo[k]);		
			}
		}

		for (list<int>::iterator i = chain.begin(); i!=chain.end(); i++)
			out.push_back(*i);
	}

	return out;
}

/////////////////

class GltColorWindow : public GlutWindowExaminer
{
public:
	GltColorWindow
	(
		int width                = widthDefault, 
		int height               = heightDefault,
		int x                    = xDefault, 
		int y                    = yDefault
	);

	~GltColorWindow();

	void OnOpen();
	void OnClose();
	void OnDisplay();
	void OnKeyboard(unsigned char ch,int x,int y);

private:
	void arrangeGrid();
	void arrangeRGB();
	void arrangeHSV();

	GltDisplayList   _sphere;
	vector<GltColor> _color;
	vector<Vector>   _pos;
	GltShapes        _shapes;
};

GltColorWindow::GltColorWindow(int width,int height,int x,int y)
: GlutWindowExaminer("GLT Colors",width,height,x,y,GLUT_DOUBLE|GLUT_RGBA)
{
}

GltColorWindow::~GltColorWindow()
{
}

void 
GltColorWindow::arrangeGrid()
{
	_shapes.clear();
	_color.clear();
	_color.reserve(rgbSize);
	_pos.clear();
	_pos.reserve(rgbSize);

	//

	vector<int> tmp = sortColors(rgbSize,rgbName,rgbValue);

	const int columns = 23;
	const int rows    = (tmp.size()/columns)+1;

	int i=0;
	
	real x = -columns+1;
	real y =  rows-1;

	while (i<tmp.size())
	{
		x = -columns+1;

		for (int j=0; j<columns && i<tmp.size(); i++,j++)
		{
			_color.push_back(rgbValue[tmp[i]]);
			_pos  .push_back(Vector(x,y,0.0));
				
			x += 2.0; 
		}

		y -= 2.0;
	}
}

void 
GltColorWindow::arrangeRGB()
{
	const real scale = 30.0;

	_shapes.clear();
	_color.clear();
	_color.reserve(rgbSize);
	_pos.clear();
	_pos.reserve(rgbSize);

	//

	for (int i=0; i<rgbSize; i++)
	{
		_color.push_back(rgbValue[i]);
		_pos.push_back(rgbValue[i]*scale);
	}

	//

	GlutCube *box = new GlutCube();
	box->solid() = false;
	box->position(Vector0,Vector1*scale);
	box->color() = white;
	_shapes.push_back(box);
}

void 
GltColorWindow::arrangeHSV()
{
	const real scale = 30.0;

	//

	_shapes.clear();
	_color.clear();
	_color.reserve(rgbSize);
	_pos.clear();
	_pos.reserve(rgbSize);

	//

	for (int i=0; i<rgbSize; i++)
	{
		_color.push_back(rgbValue[i]);
		real h,s,v;
		rgbValue[i].toHSV(h,s,v);
		const real a = h*M_PI_DEG;
		_pos.push_back(Vector(cos(a)*s,sin(a)*s,v*2.0)*scale);
	}

	//

	GlutCylinder *cyl = new GlutCylinder();
	cyl->solid() = false;
	cyl->position(Vector0,VectorZ*2.0*scale,scale);
	cyl->color() = white;
	_shapes.push_back(cyl);
}

void 
GltColorWindow::OnOpen()
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
	light0.specular() = GltColor(0.5, 0.5, 0.5, 0.0);
	light0.position() = Vector(0.2, 0.5, 5.0);
	light0.enabled()  = true;
	light0.set();

	GltMaterial material(GL_FRONT_AND_BACK);
	material.ambient()   = black;
	material.diffuse()   = black;
	material.specular()  = white;
	material.shininess() = 40.0;
	material.set();

	GltLightModel lightModel;
	lightModel.setAmbient(0.0, 0.0, 0.0, 0.0);
	lightModel.setLocalViewer(GL_FALSE);
	lightModel.setTwoSide(GL_TRUE);

	GLERROR

	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	//

	GlutSphere sphere;
	sphere.inheritColor() = true;

	_sphere.newList();
	sphere.draw();
	_sphere.endList();
	
	//

	arrangeRGB();

	//

	_viewMatrix = matrixScale(0.06) * matrixTranslate(-1.0,-1.0,0.0);
}

void 
GltColorWindow::OnClose()
{
	_sphere.reset();
}

void 
GltColorWindow::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i=0; i<_color.size() && i<_pos.size(); i++)
	{
		glPushMatrix();
			glTranslate(_pos[i]);
			_color[i].glColor();
			_sphere.draw();
		glPopMatrix();
	}

	glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		_shapes.draw();
	glPopAttrib();
}

void 
GltColorWindow::OnKeyboard(unsigned char ch,int x,int y)
{
	switch (ch)
	{
	case '1':	arrangeGrid(); break;
	case '2':	arrangeRGB();  break;
	case '3':	arrangeHSV();  break;
	default:
		GlutWindowExaminer::OnKeyboard(ch,x,y);
		return;
	}

	postRedisplay();
}

bool GlutMain(const std::vector<std::string> &arg)
{
	cout << endl;
	cout << "color" << endl;
	cout << endl;
	cout << "(C) 2001-2002 Nigel Stewart (nigels@nigels.com)" << endl;
	cout << "Source code available under terms of LGPL." << endl;
	cout << "For updates, source code and information:" << endl;
	cout << "http://www.nigels.com/glt/" << endl;
	cout << endl;
	cout << "Usage: color" << endl;
	cout << endl;
	cout << "Keys:" << endl;
	cout << "  1  Grid display" << endl;
	cout << "  2  RGB-space"    << endl;
	cout << "  3  HSV-space"    << endl;
	cout << endl;

	static GlutWindow *main = new GltColorWindow(400,400,20,20);
	main->open();

	return true;
}

