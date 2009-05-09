//
// Demonstration of glCopyPixels roundoff problem.
//
// Nigel Stewart, RMIT University, 1996-2003
// nigels@nigels.com
//

#include <glt/gl.h>
#include <glt/color.h>
#include <glt/fontasci.h>
#include <glt/info.h>
#include <glt/rgb.h>

#include <node/text.h>

#include <fonts/fonts.h>

#include <glutm/main.h>
#include <glutm/window.h>
#include <glutm/glut.h>

#include <string>
#include <iostream>
using namespace std;

static GltString banner =
        "OpenGL Z-Buffer Copying Diagnostic\n" \
        "(C) 2001-2005 Nigel Stewart       \n" \
        "http://www.nigels.com/research/   \n" \
        "\n\n"                                 \
        "Viewport top is zFar              \n" \
        "Viewport bottom is zNear          \n" \
        "\n"                                   \
        "Green pixels - correct copying    \n" \
        "Red pixels - failed copying       \n";

class OpenGLCopyZBuffer : public GlutWindow
{
public:
    OpenGLCopyZBuffer();
   ~OpenGLCopyZBuffer();

   void OnOpen();
   void OnClose();
   void OnDisplay();

protected:

    GltFontAscii   _font;
    GltTextOverlay _info;
    Vector         _quad[4];
};

OpenGLCopyZBuffer::OpenGLCopyZBuffer()
: GlutWindow("OpenGL Z-Buffer Copying Diagnostic"),
  _info(_font,_viewport)
{
    cout << banner;
}

OpenGLCopyZBuffer::~OpenGLCopyZBuffer()
{
}

void
OpenGLCopyZBuffer::OnOpen()
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
    glDisable(GL_LIGHTING);

    // Setup geometry

    _quad[0] = Vector( 1.0, 1.0,-1.0);
    _quad[1] = Vector(-1.0, 1.0,-1.0);
    _quad[2] = Vector(-1.0,-1.0, 1.0);
    _quad[3] = Vector( 1.0,-1.0, 1.0);
}

void
OpenGLCopyZBuffer::OnClose()
{
}

void
OpenGLCopyZBuffer::OnDisplay()
{
    cout << getWidth() << "x" << getHeight() << endl;

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);

        GltViewport viewport(true);
        viewport.width() >>= 1;
        viewport.set();

        glDepthFunc(GL_ALWAYS);

        // Draw grey quad in left half

        grey.glColor();
        glBegin(GL_POLYGON);
            _quad[0].glVertex();
            _quad[1].glVertex();
            _quad[2].glVertex();
            _quad[3].glVertex();
        glEnd();

    glPopAttrib();

    glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);

        // Copy left z-buffer to right-hand side in red

        red.glColor();

        glDepthFunc(GL_NOTEQUAL);
        glPushMatrix();
            glLoadIdentity();
            glRasterPos2d(0,-1);
        glPopMatrix();

        glCopyPixels(0,0,viewport.width(),viewport.height(),GL_DEPTH);

        // Draw quad on right side with z-equal test in green

        viewport.x() = viewport.width();
        viewport.set();

        green.glColor();
        glDepthFunc(GL_EQUAL);

        glBegin(GL_POLYGON);
            _quad[0].glVertex();
            _quad[1].glVertex();
            _quad[2].glVertex();
            _quad[3].glVertex();
        glEnd();

    glPopAttrib();

    _info.draw();
}

bool GlutMain(const vector<string> &arg)
{
    GlutWindow *main = new OpenGLCopyZBuffer();
    main->open();
    return true;
}
