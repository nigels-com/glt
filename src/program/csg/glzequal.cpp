#include <glt/gl.h>
#include <glt/color.h>
#include <glt/rgb.h>
#include <glt/fontasci.h>
#include <glt/info.h>
#include <glt/matrix.h>

#include <node/text.h>

#include <fonts/fonts.h>

#include <glutm/main.h>
#include <glutm/window.h>

#include <string>
#include <iostream>
using namespace std;

static GltString banner =
        "OpenGL Z-Equal Diagnostic      \n" \
        "(C) 2002-2003 Nigel Stewart    \n" \
        "http://www.nigels.com/research/\n";

class GlutWindowZEqual : public GlutWindow
{
public:
    GlutWindowZEqual();
   ~GlutWindowZEqual();

   void OnOpen();
   void OnClose();
   void OnDisplay();

protected:

    GltFontAscii   _font;
    GltTextOverlay _info;
    Vector         _triangle[3];
};

GlutWindowZEqual::GlutWindowZEqual()
: GlutWindow("OpenGL Z-Equal Diagnostic"),
  _info(_font,_viewport)
{
    cout << banner;
}

GlutWindowZEqual::~GlutWindowZEqual()
{
}

void
GlutWindowZEqual::OnOpen()
{
    // Setup overlay information

    _font.init(vga8Font);

    _info.text() = banner + "\n\n" + GltInfo() + "\n\n" + GltDate();
    _info.shadow() = true;
    _info.fadeColor().alpha() = 0.30;

    // Setup GLUT menu

    GlutMenu &save = _leftButtonMenu.subMenu();
    save.addEntry("RGB"     ,MENU_CAPTURE_RGB);
    save.addEntry("z-buffer",MENU_CAPTURE_ZBUFFER);

    _leftButtonMenu.addEntry("Save PPM",save);
    _leftButtonMenu.addEntry("Close" ,MENU_CLOSE);
    _leftButtonMenu.attach();

    // Setup OpenGL

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearDepth(1.0);
    glDepthRange(0.0,1.0);
    glLoadIdentity();

    // Setup geometry

    _triangle[0] = Vector(-0.8, 0.0,0.0);
    _triangle[1] = Vector( 0.8, 0.8,0.0);
    _triangle[2] = Vector( 0.8,-0.8,0.0);
}

void
GlutWindowZEqual::OnClose()
{
    _font.clear();
    _leftButtonMenu.reset();
}

void
GlutWindowZEqual::OnDisplay()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glPushMatrix();

        // Draw in one direction in red

        glDepthFunc(GL_ALWAYS);
        glFrontFace(GL_CW);
        red.glColor();

        glBegin(GL_TRIANGLES);
            _triangle[0].glVertex();
            _triangle[1].glVertex();
            _triangle[2].glVertex();
        glEnd();

        // Draw in other direction with z-equal test in blue

        glDepthFunc(GL_EQUAL);
        glFrontFace(GL_CCW);
        blue.glColor();

        glBegin(GL_TRIANGLES);
            _triangle[2].glVertex();
            _triangle[1].glVertex();
            _triangle[0].glVertex();
        glEnd();

    glPopMatrix();

    glRotateX(1);
    glRotateZ(1);

    _info.draw();

    postRedisplay();
}

bool GlutMain(const vector<string> &arg)
{
    static GlutWindow *main = new GlutWindowZEqual();
    main->open();
    return true;
}
