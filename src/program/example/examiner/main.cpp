/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2003 Nigel Stewart

  Email:  nigels@nigels.com
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

////////////////////////////////////////////////////////////////////////////////////////////

#include <glt/rgb.h>        // Built-in GLT colours: black, white, red, etc

#include <fonts/fonts.h>    // Built-in GLT ASCII fonts
#include <glt/fontasci.h>   // GLT ASCII font support

#include <node/text.h>      // GLT text overlay support

#include <glutm/main.h>     // GlutMain() support
#include <glutm/shape.h>    // GLUT shapes such as sphere, cylinder, etc
#include <glutm/winexam.h>  // GLUT examiner viewer

#include <iostream>         // std::cout
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////

class ExaminerDemo : public GlutWindowExaminer
{
public:
    ExaminerDemo(
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault
    );
   ~ExaminerDemo();

   void OnOpen();
   void OnClose();
   void OnDisplay();
   void OnTick();
   void OnKeyboard(unsigned char key, int x, int y);

   static const string _message;

protected:

    GltFontAscii    _font;                              // Font used for overlay text
    GltTextOverlay  _info;                              // Text overlay object
    GltShapePtr     _shape;                             // Current shape to be drawn
};

////////////////////////////////////////////////////////////////////////////////////////////

const string ExaminerDemo::_message =

    "GlutMaster Examiner Demo.           \n" \
    "\n"\
    "Use mouse buttons to rotate, zoom and pan. \n" \
    "Keys 0 to 9 select different objects.      \n";


ExaminerDemo::ExaminerDemo(int width,int height,int x,int y)
: GlutWindowExaminer("GlutMaster Examiner Demo",width,height,x,y),
  _info(_font,_viewport)
{
    _ortho.zNear() = -2.0;
    _ortho.zFar()  =  2.0;
}

ExaminerDemo::~ExaminerDemo()
{
}

//////////////////////////////////////////////////////////////////////////
//
// Called once when GLUT window is opened

void ExaminerDemo::OnOpen()
{
    _font.init(vga8Font);               // Initialise font
    _info.text() = _message;            // Initialise overlay text
    glEnable(GL_DEPTH_TEST);            // Use OpenGL depth testing

    // Initialise viewing direction
    _viewMatrix = matrixRotate(Vector1,60.0)*_viewMatrix;

    OnKeyboard('1',0,0);                // Select 1st shape
    setTick(1000/60);                   // Set 60 frames per second
}

//////////////////////////////////////////////////////////////////////////
//
// Called once when GLUT window is closed

void ExaminerDemo::OnClose()
{
    _font.init(NULL);                   // Release font resources
}

//////////////////////////////////////////////////////////////////////////
//
// Called for each required re-draw

void ExaminerDemo::OnDisplay()
{
   // Clear OpenGL color and depth buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Draw current shape
   if (_shape.get())
       _shape->draw();

   // Draw text overlay
   _info.draw();
}

//////////////////////////////////////////////////////////////////////////
//
// Called periodically to update state

void ExaminerDemo::OnTick()
{
    // Rotate viewing position unless mouse pressed
    if (!mousePressed())
        _viewMatrix = matrixRotate(Vector1,0.2)*_viewMatrix;

    // Trigger redraw
    postRedisplay();
}

//////////////////////////////////////////////////////////////////////////
//
// Called each time a key is pressed

void ExaminerDemo::OnKeyboard(unsigned char key, int x, int y)
{
    // Pass keys to parent class
    GlutWindowExaminer::OnKeyboard(key,x,y);

    // Create a new shape, according to the pressed key
    switch (key)
    {
    case '1': _shape = new GlutSphere(false);        break;
    case '2': _shape = new GlutCube(false);          break;
    case '3': _shape = new GlutCylinder(false);      break;
    case '4': _shape = new GlutCone(false);          break;
    case '5': _shape = new GlutTorus(false);         break;
    case '6': _shape = new GlutDodecahedron(false);  break;
    case '7': _shape = new GlutOctahedron(false);    break;
    case '8': _shape = new GlutTetrahedron(false);   break;
    case '9': _shape = new GlutIcosahedron(false);   break;
    case '0': _shape = new GlutTeapot(false);        break;
    }

    // Configure shape
    if (_shape.get())
    {
        _shape->color() = red;
        _shape->solid() = false;
    }

    // Trigger redraw
    postRedisplay();
}

//////////////////////////////////////////////////////////////////////////
//
// Called by GlutMaster instead of main()

bool GlutMain(const std::vector<std::string> &arg)
{
    // Print welcome message
    cout << ExaminerDemo::_message << endl;

    // Create GlutMaster window
    GlutWindow *main = new ExaminerDemo(400,400,20,20);
    main->open();

    // Finished GlutMain(), now ready to enter GlutMaster loop.
    // If we return false here, GlutMaster simply exits with EXIT_FAILURE

    return true;
}
