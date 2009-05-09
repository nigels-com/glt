#include <glutm/main.h>
#include <glutm/window.h>
#include <glutm/winexam.h>
#include <glutm/glut.h>
#include <glutm/shape.h>

#include <glt/gl.h>
#include <glt/buffer.h>
#include <glt/light.h>
#include <glt/material.h>
#include <glt/lightm.h>
#include <glt/info.h>
#include <glt/rgb.h>

#include <misc/string.h>
#include <misc/timer.h>

#include <csg/element.h>
#include <csg/scsinter.h>
#include <csg/scs.h>
#include <csg/options.h>
#include <csg/info.h>

#include <node/blend.h>

#include <iostream>
using namespace std;

class GlutWindowCSGBubbles : public GlutWindow
{
public:
    GlutWindowCSGBubbles();
    ~GlutWindowCSGBubbles();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnKeyboard(unsigned char key, int x, int y);
    void OnMenu(int value);

private:

    GltLight      _light0;
    GltLight      _light1;
    GltMaterial   _material;
    GltLightModel _lightModel;

    GltShapePtr _sphere1;
    GltShapePtr _sphere2;
    GltShapePtr _sphere3;

    CsgProduct  _csg;

    GltBlend    _blend;
    Timer       _timer;

    typedef enum
    {
        PREVIEW = 0,
        INTERSECTED,
        BLENDED,
        MAX
    } Mode;

    Mode        _mode;
};

GlutWindowCSGBubbles::GlutWindowCSGBubbles()
: GlutWindow("CSG Bubbles Demo"),
  _light0(GL_LIGHT0),
  _light1(GL_LIGHT1),
  _mode(BLENDED)
{
    _material.ambient()   = black;
    _material.diffuse()   = black;
    _material.specular()  = white;
    _material.shininess() = 40.0;

    _light0.position() = Vector( 2.2, 0.5, 5.0);
    _light1.position() = Vector(-3.8, 0.8, 4.0);

    _light0.ambient()  = _light1.ambient()  = GltColor(0.1, 0.1, 0.1, 1.0);
    _light0.specular() = _light1.specular() = GltColor(0.5, 0.5, 0.5, 0.0);
    _light0.enabled()  = _light1.enabled()  = true;
}

void
GlutWindowCSGBubbles::OnOpen()
{
    //

    GlutMenu &mode = _leftButtonMenu.subMenu();
    mode.addEntry("Preview",PREVIEW);
    mode.addEntry("Intersect",INTERSECTED);
    mode.addEntry("Blend",BLENDED);

    GlutMenu &save = _leftButtonMenu.subMenu();
    save.addEntry("RGB"     ,MENU_CAPTURE_RGB);
    save.addEntry("stencil" ,MENU_CAPTURE_STENCIL);
    save.addEntry("z-buffer",MENU_CAPTURE_ZBUFFER);

    _leftButtonMenu.addEntry("Mode",mode);
    _leftButtonMenu.addEntry("Save",save);
    _leftButtonMenu.addEntry("Close" ,MENU_CLOSE);
    _leftButtonMenu.attach();

    //

    _sphere1 = new GlutSphere(true,1.0,32,16);
    _sphere2 = new GlutSphere(true,1.0,32,16);
    _sphere3 = new GlutSphere(true,1.0,32,16);

    _sphere1->color() = red;
    _sphere2->color() = green;
    _sphere3->color() = blue;

    _csg.push_back(CsgElement(_sphere1,true));
    _csg.push_back(CsgElement(_sphere2,true));
    _csg.push_back(CsgElement(_sphere3,true));

    _sphere1->color().alpha() = 0.2;
    _sphere2->color().alpha() = 0.2;
    _sphere3->color().alpha() = 0.2;

    _blend.push_back(_sphere1);
    _blend.push_back(_sphere2);
    _blend.push_back(_sphere3);


    //

    _light0.set();
    _light1.set();

    _material.set();

    _lightModel.setAmbient(0.0, 0.0, 0.0, 0.0);
    _lightModel.setLocalViewer(GL_FALSE);
    _lightModel.setTwoSide(GL_TRUE);

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearDepth(1.0);
    glDepthRange(0.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(0.8f,0.8f,0.8f);

    GltOrtho ortho;
    ortho.set(getWidth(),getHeight());

    white.glClearColor();
}

void
GlutWindowCSGBubbles::OnClose()
{
    _leftButtonMenu.reset();
}

GlutWindowCSGBubbles::~GlutWindowCSGBubbles()
{
}

void
GlutWindowCSGBubbles::OnDisplay()
{
    const double t = _timer.elapsed();

    _sphere1->transformation() = matrixScale(0.7+sin(t*0.11)*0.3) * matrixTranslate(VectorZ*-0.1);
    _sphere2->transformation() = matrixTranslate(VectorX*(sin(t*0.3)));
    _sphere3->transformation() = matrixTranslate(VectorY*(sin(t*0.5)));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CsgOptions options;
    CsgInfo    info;

    switch (_mode)
    {
        default:
        case PREVIEW:
            glDepthFunc(GL_LESS);
            _sphere1->draw();
            _sphere2->draw();
            _sphere3->draw();
            break;

        case INTERSECTED:
            csgRenderConvexIntersectionRGB(_csg,options,info);
            break;

        case BLENDED:
            glDepthFunc(GL_ALWAYS);
            _blend.draw();
            csgRenderConvexIntersectionRGB(_csg,options,info);
            break;
    }

    postRedisplay();
}

void
GlutWindowCSGBubbles::OnKeyboard(unsigned char key, int x, int y)
{
    if (key==13)
        _mode = Mode((_mode+1)%MAX);
    else
        GlutWindow::OnKeyboard(key,x,y);
}

void
GlutWindowCSGBubbles::OnMenu(int value)
{
    switch (value)
    {
    case PREVIEW:     _mode = PREVIEW;     break;
    case INTERSECTED: _mode = INTERSECTED; break;
    case BLENDED:     _mode = BLENDED;     break;
    default:
        GlutWindow::OnMenu(value);
    }

    postRedisplay();
}

bool GlutMain(const std::vector<std::string> &arg)
{
    GlutWindow *main = new GlutWindowCSGBubbles();
    main->open();
    return true;
}

