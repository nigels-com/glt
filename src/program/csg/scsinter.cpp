#include <glutm/main.h>
#include <glutm/window.h>
#include <glutm/shape.h>

#include <glt/gl.h>
#include <glt/light.h>
#include <glt/material.h>
#include <glt/lightm.h>
#include <glt/project.h>
#include <glt/zplane.h>
#include <glt/info.h>
#include <glt/rgb.h>
#include <glt/fontasci.h>
#include <glt/frame.h>

#include <node/text.h>
#include <fonts/fonts.h>

#include <misc/timer.h>
#include <misc/string.h>

#include <iostream>
#include <cstdio>
using namespace std;

class GlutWindowSCSIntersect : public GlutWindow
{
public:
    GlutWindowSCSIntersect();
    ~GlutWindowSCSIntersect();

    void OnOpen();
    void OnDisplay();
    void OnKeyboard(unsigned char key, int x, int y);

private:

    GltLight       _light0;
    GltLight       _light1;
    GltMaterial    _material;
    GltLightModel  _lightModel;

    GltFontAscii   _font;
    GltTextOverlay _info;
    GltFrameRate   _frameRate;

    int            _n;
    Timer          _timer;
    GlutCylinder   _cylinder;

    void drawCylinder(const int i);
};

GlutWindowSCSIntersect::GlutWindowSCSIntersect()
: GlutWindow("SCS-Intersect Demo",640,480),
  _light0(GL_LIGHT0),
  _light1(GL_LIGHT1),
  _info(_font,_viewport),
  _frameRate(29),
  _n(3),
  _cylinder(true)
{
    _info.fadeColor().alpha() = 0.5;

    //

    _cylinder.transformation() = matrixScale(Vector(1,1,2)) * matrixTranslate(-VectorZ);
    _cylinder.color() = orange;

    //

    _light0.position() = Vector( 5.0, 3.5, 6.0);
    _light1.position() = Vector(-5.0, 3.5, 7.0);

    _light0.ambient()  = _light1.ambient()  = GltColor(0.1, 0.1, 0.1, 1.0);
    _light0.specular() = _light1.specular() = GltColor(0.5, 0.5, 0.5, 0.0);
    _light0.enabled()  = _light1.enabled()  = true;

    _material.ambient()   = black;
    _material.diffuse()   = black;
    _material.specular()  = white;
    _material.shininess() = 40.0;
}

GlutWindowSCSIntersect::~GlutWindowSCSIntersect()
{
}

void
GlutWindowSCSIntersect::drawCylinder(const int i)
{
    glPushMatrix();

        glRotated(double(i)/_n*180.0,0,1,0);

        #if defined(WIN32) || defined(linux)

        // A fakey trick that shouldn't be necessary
        //
        // WindowsNT software OpenGL seems to lose
        // precision on transformation matricies when
        // they are pushed/popped.
        //

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glPopMatrix();

        #endif

        _cylinder.draw();

    glPopMatrix();
}

void
GlutWindowSCSIntersect::OnOpen()
{
    _font.init(iso14Font);

    _lightModel.setAmbient(0.0, 0.0, 0.0, 0.0);
    _lightModel.setLocalViewer(GL_FALSE);
    _lightModel.setTwoSide(GL_TRUE);

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glDepthRange(0.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(0.7,0.7,0.7);
    glRotatef(30,1,0,0);

    GltOrtho ortho;
    ortho.set(getWidth(),getHeight());

    _light0.set();
    _light1.set();
    _material.set();

    //

    cout << GltInfo() << endl;

    cout << endl << "Use +/- to adjust number of cylinders." << endl;
}

void
GlutWindowSCSIntersect::OnDisplay()
{
    int i;
    int n = _n;

    glPushMatrix();
        glRotated(_timer.elapsed()*20.0,0,1,0);

        /* Clear frame-buffer */

        glClearDepth(0.0);
        glDepthMask(GL_TRUE);
        glClearStencil(0);
        glStencilMask(~0);
        glClearColor(1,1,1,0);
        glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        /* Find furthest front face */

        glDisable(GL_STENCIL_TEST);

        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GREATER);
        glDepthMask(GL_TRUE);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        for (i=0; i<n; i++)
            drawCylinder(i);

        /* Count back-facing surfaces behind */

        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS,0,~0);
        glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);

        glCullFace(GL_FRONT);

        glDepthMask(GL_FALSE);

        for (i=0; i<n; i++)
            drawCylinder(i);

        /* Reset pixels where n != stencil */

        glStencilFunc(GL_NOTEQUAL,n,~0);
        glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);

        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_TRUE);

        glDisable(GL_CULL_FACE);

        drawZfar();

        /* Draw RGB image */

        glDisable(GL_STENCIL_TEST);

        glDepthFunc(GL_EQUAL);
        glDepthMask(GL_FALSE);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

        for (i=0; i<n; i++)
            drawCylinder(i);

    glPopMatrix();

    sprintf(_info.text(),"%5.1f\nn=%d",_frameRate.frameRate(),n);
    _info.draw();

    postRedisplay();

    ++((GlutWindowSCSIntersect *) this)->_frameRate;
}

void GlutWindowSCSIntersect::OnKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '+': if (_n<256) _n++; break;
    case '-': if (_n>1)   _n--; break;

    default:
        GlutWindow::OnKeyboard(key,x,y);
        return;
    }

    postRedisplay();
}

bool GlutMain(const std::vector<std::string> &arg)
{
    static GlutWindow *main = new GlutWindowSCSIntersect();
    main->open();
    return true;
}
