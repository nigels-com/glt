#include <glutm/master.h>
#include <glutm/window.h>
#include <glutm/main.h>

#include <glt/error.h>
#include <glt/texture.h>
#include <node/fade.h>
#include <node/interp.h>

#include <math/real.h>
#include <misc/timer.h>

#include <iostream>
#include <cmath>
using namespace std;

#include "roller.h"
#include "poteau.h"

#include "textures.h"

///////////

class RollerCoasterWindow : public GlutWindow
{
public:
    RollerCoasterWindow
    (
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault
    );

   ~RollerCoasterWindow();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnReshape(int width,int height);
    void OnKeyboard(unsigned char key, int x, int y);

private:

    RollerCoaster _coaster;

    GltTexture _grass;
    GltTexture _panneau;
    GltTexture _metal;
    GltTexture _tree;

    int        _scene;
    GLfloat    _aperture;
    GLfloat    _nearClip,_farClip;

    GltFadeViewport      _fade;
    GltInterpolatorColor _fadeInterp;

    Timer           _timer;

    void setFade(const float duration,const float transitiion);

    void drawGround()  const;
    void drawSky()     const;
    void drawTree()    const;
    void drawPoteau()  const;
    void drawMetal()   const;
    void drawPanneau() const;

    void setScene(int scene);
    void drawScene();
};

RollerCoasterWindow::RollerCoasterWindow(int width,int height,int x,int y)
: GlutWindow("Roller Coaster",width,height,x,y,GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH),
  _scene(0),
  _aperture(60.0f),
  _nearClip(0.01f),
  _farClip(60.0f),
  _fadeInterp(_fade.color())
{
    setTick(1000/100);  // 100 FPS max
}

RollerCoasterWindow::~RollerCoasterWindow()
{
}

void
RollerCoasterWindow::OnOpen()
{
    _coaster.ParseRollerFile("rc2k.trk");
    _coaster.InitializeRoller(getWidth(),getHeight(),0,60.0f,0.005f,0.05f);

    _grass.setWrap(GL_REPEAT,GL_REPEAT);
    _grass.setFilter(GL_LINEAR_MIPMAP_NEAREST,GL_LINEAR);
    _grass.init(grassTexture);

    _panneau.setWrap(GL_CLAMP,GL_CLAMP);
    _panneau.setFilter(GL_LINEAR,GL_LINEAR);
    _panneau.init(panneauTexture);

    _metal.setWrap(GL_REPEAT,GL_REPEAT);
    _metal.setFilter(GL_LINEAR_MIPMAP_NEAREST,GL_LINEAR);
    _metal.init(metalTexture);

    _tree.setWrap(GL_CLAMP,GL_CLAMP);
    _tree.setFilter(GL_LINEAR,GL_LINEAR);
    _tree.init(treeTexture);

    setScene(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.3f, 0.3f, 0.7f, 0.0f); /* This will clear the background color to "la couleur du ciel" */
    glClearDepth(1.0);                    /* Enables clearing of the depth buffer */
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
    glShadeModel(GL_SMOOTH);              /* Enables Gouraud shading */
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_STENCIL_TEST);

/*  glDisable(GL_DITHER); */
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT,GL_FILL);
    glFrontFace(GL_CCW);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void
RollerCoasterWindow::OnClose()
{
    _grass.clear();
    _panneau.clear();
    _metal.clear();
    _tree.clear();
//  ExitRoller();
}

void
RollerCoasterWindow::OnReshape(int width,int height)
{
    GlutWindow::OnReshape(width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    const float ratio = float(width)/float(height);
    const float wd2 = _nearClip * tan(0.5f * M_PI * _aperture / 180.0f);

    glFrustum(-ratio*wd2,  /* left   */
              ratio*wd2,   /* right  */
              -wd2,        /* bottom */
              wd2,         /* top    */
              _nearClip, _farClip);

    glMatrixMode(GL_MODELVIEW);
}

void
RollerCoasterWindow::OnKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    default:
        GlutWindow::OnKeyboard(key,x,y);
    }
}

void
RollerCoasterWindow::OnDisplay()
{
//  DrawRoller();
    drawScene();
    drawPoteau();
    drawGround();
    drawSky();
    _fadeInterp.draw();
    _fade.draw();
    GLERROR;
}

bool GlutMain(const std::vector<std::string> &arg)
{
    static GlutWindow *main = new RollerCoasterWindow(400,400,20,20);
    main->open();

    return true;
}

//////////////////////////////////////

void
RollerCoasterWindow::setFade(const float total,const float delta)
{
    const GltColor out(0,0,0,1);
    const GltColor in (0,0,0,0);

    _fadeInterp.colorMap() = GltColorMap();
    _fadeInterp.colorMap().addEntry(0.0,out);
    _fadeInterp.colorMap().addEntry(delta,in);
    _fadeInterp.colorMap().addEntry(total-delta,in);
    _fadeInterp.colorMap().addEntry(total,out);
    _fadeInterp.colorMap() /= _fadeInterp.colorMap().duration();

    _fadeInterp.start(total,false);
}

//  drawSkyAndGround(8,50.0f,60.0f,0.0f,10.0f);
// void drawSkyAndGround(int nbCote, float size, float texsize,float bas, float haut)

void
RollerCoasterWindow::drawGround() const
{
    const int   nbCote = 8;
    const float size = 50.0f;
    const float texsize = 60.f;
    const float bas = 0.0f;
//    const float haut = 0.0f;

    glPushAttrib(GL_ENABLE_BIT);

        glEnable(GL_TEXTURE_2D);
        _grass.set();
        glColor3f(1.0f,1.0f,1.0f);

        glBegin(GL_TRIANGLE_FAN);

            glTexCoord2f(0.0f,0.0f);
            glVertex3f(0.0f,0.0f,bas);

            for(int i=0 ; i<nbCote ; i++)
            {
                float c = cos((float)i*2.0f*M_PI/(float)nbCote);
                float s = sin((float)i*2.0f*M_PI/(float)nbCote);
                glTexCoord2f(texsize*c,texsize*s);
                glVertex3f(size*c,size*s,bas);
            }
            glTexCoord2f(texsize,0.0f);
            glVertex3f(size,0.0f,bas);

        glEnd();

    glPopAttrib();
}

void
RollerCoasterWindow::drawSky() const
{
    const int   nbCote = 8;
    const float size = 50.0f;
//    const float texsize = 60.0f;
    const float bas = 0.0f;
    const float haut = 0.0;

    glBegin(GL_QUAD_STRIP);
        glColor3f(0.5f,0.5f,0.7f);  glVertex3f(size,0.0f,bas);
        glColor3f(0.3f,0.3f,0.7f);  glVertex3f(size,0.0f,haut);

        for(int i=1 ; i<nbCote ; i++)
        {
            float x = size * cos((float)i*2.0f*M_PI/(float)nbCote);
            float y = size * sin((float)i*2.0f*M_PI/(float)nbCote);
            glColor3f(0.5f,0.5f,0.7f); glVertex3f(x,y,bas);
            glColor3f(0.3f,0.3f,0.7f); glVertex3f(x,y,haut);
        }
        glColor3f(0.5f,0.5f,0.7f);  glVertex3f(size,0.0f,bas);
        glColor3f(0.3f,0.3f,0.7f);  glVertex3f(size,0.0f,haut);
    glEnd();
}

void
RollerCoasterWindow::drawTree() const
{
    glPushAttrib(GL_ENABLE_BIT);
        glEnable(GL_TEXTURE_2D);
        _tree.set();
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_NOTEQUAL,0.0f);
        glColor3f(1.0f,1.0f,1.0f);
            glBegin(GL_QUADS);
                glTexCoord2f(1.0f, 1.0f);   glVertex3f(-0.5f, 0.0f, 1.5f);
                glTexCoord2f(0.0f, 1.0f);   glVertex3f( 0.5f, 0.0f, 1.5f);
                glTexCoord2f(0.0f, 0.0f);   glVertex3f( 0.5f, 0.0f, 0.0f);
                glTexCoord2f(1.0f, 0.0f);   glVertex3f(-0.5f, 0.0f, 0.0f);

                glTexCoord2f(1.0f, 0.0f);   glVertex3f(-0.5f, 0.0f, 0.0f);
                glTexCoord2f(0.0f, 0.0f);   glVertex3f( 0.5f, 0.0f, 0.0f);
                glTexCoord2f(0.0f, 1.0f);   glVertex3f( 0.5f, 0.0f, 1.5f);
                glTexCoord2f(1.0f, 1.0f);   glVertex3f(-0.5f, 0.0f, 1.5f);

                glTexCoord2f(1.0f, 1.0f);   glVertex3f(0.0f, -0.5f, 1.5f);
                glTexCoord2f(0.0f, 1.0f);   glVertex3f(0.0f,  0.5f, 1.5f);
                glTexCoord2f(0.0f, 0.0f);   glVertex3f(0.0f,  0.5f, 0.0f);
                glTexCoord2f(1.0f, 0.0f);   glVertex3f(0.0f, -0.5f, 0.0f);

                glTexCoord2f(1.0f, 0.0f);   glVertex3f(0.0f, -0.5f, 0.0f);
                glTexCoord2f(0.0f, 0.0f);   glVertex3f(0.0f, 0.5f, 0.0f);
                glTexCoord2f(0.0f, 1.0f);   glVertex3f(0.0f, 0.5f, 1.5f);
                glTexCoord2f(1.0f, 1.0f);   glVertex3f(0.0f, -0.5f, 1.5f);
            glEnd();
    glPopAttrib();
}

//extern point *ptree;
//extern int nbTree;

void
RollerCoasterWindow::drawPoteau() const
{
    point v;
    v.x = v.y = v.z = 0.0f;

    glPushMatrix();
    for(int i=0 ; i<nbTree ; i++)
    {
        glTranslatef(ptree[i].x - v.x,ptree[i].y - v.y,ptree[i].z - v.z);
        v = ptree[i];
        drawTree();
    }
    glPopMatrix();

    drawPanneau();
    drawMetal();
    poteau_draw();
}

float metalLength = 2.0f;
float metalAngle = 0.0f;
point metalPosition = {-1.0f,-1.0f,0.5f};

void
RollerCoasterWindow::drawMetal() const
{
    typedef struct
    {
        float x,y;
    } coord2d;
    static coord2d tabt[12];
    static point tabc[] = {
        {-1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f}
    };
    static point tab1v[] = {
        {-0.25f, 0.0f, -0.02f},
        {-0.25f, 0.0f, 0.04f},
        {-0.5f, 0.0f, 0.04f},
        {-0.5f, 0.0f, 0.0f},
        {0.25f, 0.0f, 0.0f},
        {0.25f, 0.0f, -0.02f}
    };
    static coord2d tab1t[6];
    static point tab1c = {0.0f, -1.0f, 0.0f};
    static point tab2v[6];
    static coord2d tab2t[6];
    static point tab2c = {0.0f, 1.0f, 0.0f};
    int i;
    static int first = 1;
    point p;
    point z = {0.0f, 0.0f, 1.0f};

    if(metalLength == 0.0f) return;
    if(first)
    {
        point lightAmbient = {0.4f,0.4f,0.4f};
        point lightDiffuse = {1.0f,1.0f,1.0f};
        point light = {1.0f,1.0f,1.0f};
        float angle = metalAngle * M_PI / 180;

        for(i=0 ; i<6 ; i++)
        {
            tab1t[i].x = tab1v[i].x * 20.0f;
            tab1t[i].y = (tab1v[i].z + (i!=3 && i!=4 ? metalPosition.z : 0.0f)) * 20.0f;
            tabt[i*2].x = tabt[i*2+1].x = (tab1v[(9-i)%6].x + tab1v[(9-i)%6].z + (i!=0 && i!=5 ? metalPosition.z : 0.0f)) * 20.0f;
            tabt[i*2].y = 0.0f;
            tabt[i*2+1].y = metalLength * 20.0f;
        }
        tab2t[0] = tab1t[0];
        for(i=1 ; i<6 ; i++) tab2t[i] = tab1t[6-i];
        tab2v[0] = tab1v[0];
        for(i=1 ; i<6 ; i++) tab2v[i] = tab1v[6-i];
        for(i=0 ; i<6 ; i++)
        {
            tab1v[i].y -= metalLength / 2.0f;
            rotate(&p,&z,angle,&tab1v[i]);
            add(&tab1v[i],&metalPosition,&p);
            tab2v[i].y += metalLength / 2.0f;
            rotate(&p,&z,angle,&tab2v[i]);
            add(&tab2v[i],&metalPosition,&p);
        }
        tab1v[3].z = tab1v[4].z = 0.0f;
        tab2v[2].z = tab2v[3].z = 0.0f;
        rotate(&p,&z,angle,&tab1c);
        tab1c = p;
        rotate(&p,&z,angle,&tab2c);
        tab2c = p;
        for(i=0 ; i<5 ; i++)
        {
            rotate(&p,&z,angle,&tabc[i]);
            tabc[i] = p;
        }
        calc_coul(5,tabc,&lightAmbient,&lightDiffuse,&light,tabc);
        calc_coul(1,&tab1c,&lightAmbient,&lightDiffuse,&light,&tab1c);
        calc_coul(1,&tab2c,&lightAmbient,&lightDiffuse,&light,&tab2c);
        first = 0;
    }
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
    _metal.set();
    glBegin(GL_QUAD_STRIP);
    for(i=0 ; i<6 ; i++)
    {
        glColor3fv((float*)&tabc[(i+4)%5]);
        glTexCoord2fv((float*)&tabt[2*i]);
        glVertex3fv((float*)&tab2v[(3+i)%6]);
        glTexCoord2fv((float*)&tabt[2*i+1]);
        glVertex3fv((float*)&tab1v[(9-i)%6]);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3fv((float*)&tab1c);
    for(i=0 ; i < int(sizeof(tab1v)/sizeof(point)) ; i++)
    {
        glTexCoord2fv((float*)&tab1t[i]);
        glVertex3fv((float*)&tab1v[i]);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3fv((float*)&tab2c);
    for(i=0 ; i < int(sizeof(tab2v)/sizeof(point)) ; i++)
    {
        glTexCoord2fv((float*)&tab2t[i]);
        glVertex3fv((float*)&tab2v[i]);
    }
    glEnd();
    glShadeModel(GL_SMOOTH);
    glDisable(GL_TEXTURE_2D);
}

point panneauPosition = {0.0f,0.0f,0.0f};
point panneauDirection;

void
RollerCoasterWindow::drawPanneau() const
{
    typedef struct{
        float x,y;
    } coord2d;
    static point tabv[] = {
        {-0.4f, -0.03f, -0.1f},
        { 0.4f, -0.03f, -0.1f},
        {-0.4f,  0.03f, -0.1f},
        { 0.4f,  0.03f, -0.1f},
        {-0.4f,  0.03f, -0.6f},
        { 0.4f,  0.03f, -0.6f},
        {-0.4f, -0.03f, -0.6f},
        { 0.4f, -0.03f, -0.6f}
    };
    static coord2d tabt[] = {
        {0.0f, 0.0f},
        {16.0f, 0.0f},
        {0.0f, 1.2f},
        {16.0f, 1.2f},
        {0.0f, 11.2f},
        {16.0f, 11.2f},
        {0.0f, 12.4f},
        {16.0f, 12.4f}
    };
    static point tabc[] = {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, -1.0f},
        {1.0f, 0.0f, 0.0f},
        {-1.0f, 0.0f, 0.0f},
        {0.0f, -1.0f, 0.0f}
    };
    static int first_call = 1;
    int i;

    if(panneauPosition.z == 0.0f) return;

    if( first_call )
    {
        point lightAmbient = {0.4f,0.4f,0.4f};
        point lightDiffuse = {1.0f,1.0f,1.0f};
        point light = {1.0f,1.0f,1.0f};
        point a, z={0.0f,0.0f,1.0f};

        normalize(&panneauDirection);
        a = panneauDirection;
        if(a.x*a.x>0.0001f){
            a.x = -a.y / a.x;
            a.y = 1.0f;
        }
        else{
            a.y = -a.x / a.y;
            a.x = 1.0f;
        }
        if(panneauDirection.x * a.y - panneauDirection.y * a.x > 0.0f)
        {
            a.x = -a.x; a.y = -a.y; a.z = -a.z;
        }
        for(i=0 ; i<6 ; i++)
        {
            point v = tabc[i];
            tabc[i].x = a.x * v.x + panneauDirection.x * v.y + z.x * v.z;
            tabc[i].y = a.y * v.x + panneauDirection.y * v.y + z.y * v.z;
            tabc[i].z = a.z * v.x + panneauDirection.z * v.y + z.z * v.z;
        }
        for(i=0 ; i<8 ; i++)
        {
            point v = tabv[i];
            tabv[i].x = a.x * v.x + panneauDirection.x * v.y + z.x * v.z;
            tabv[i].y = a.y * v.x + panneauDirection.y * v.y + z.y * v.z;
            tabv[i].z = a.z * v.x + panneauDirection.z * v.y + z.z * v.z;
            add(&tabv[i],&panneauPosition,&tabv[i]);
        }
        calc_coul(sizeof(tabc)/sizeof(point),tabc,&lightAmbient,&lightDiffuse,&light,tabc);
        first_call = 0;
    }
    glShadeModel(GL_FLAT);
    glEnable(GL_TEXTURE_2D);
    _panneau.set();
    glBegin(GL_QUADS);
        glColor3fv((float*)&tabc[5]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv((float*)&tabv[1]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv((float*)&tabv[0]);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv((float*)&tabv[6]);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv((float*)&tabv[7]);
    glEnd();
    _metal.set();
    glBegin(GL_QUAD_STRIP);
        for(i=0 ; i < int(sizeof(tabv)/sizeof(point)) ; i++)
        {
            glColor3fv((float*)&tabc[i>1?(i-2)/2:0]);
            glTexCoord2fv((float*)&tabt[i]);
            glVertex3fv((float*)&tabv[i]);
        }
    glEnd();
    glBegin(GL_QUADS);
        glColor3fv((float*)&tabc[3]);
        glTexCoord2f(0.0f, 0.0f);  glVertex3fv((float*)&tabv[1]);
        glTexCoord2f(0.0f, 10.0f); glVertex3fv((float*)&tabv[7]);
        glTexCoord2f(1.2f, 10.0f); glVertex3fv((float*)&tabv[5]);
        glTexCoord2f(1.2f, 0.0f);  glVertex3fv((float*)&tabv[3]);
        glColor3fv((float*)&tabc[4]);
        glTexCoord2f(0.0f, 0.0f);  glVertex3fv((float*)&tabv[0]);
        glTexCoord2f(1.2f, 0.0f);  glVertex3fv((float*)&tabv[2]);
        glTexCoord2f(1.2f, 10.0f); glVertex3fv((float*)&tabv[4]);
        glTexCoord2f(0.0f, 10.0f); glVertex3fv((float*)&tabv[6]);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
}


void
RollerCoasterWindow::setScene(int scene)
{
    _scene = scene%2;

    switch (_scene)
    {
    case 0: setFade(36.0,1.5); break;
    case 1: setFade(60.0,1.5); break;
    }

    _timer.start();
}

void
RollerCoasterWindow::drawScene()
{
    const double t = _timer.elapsed();
    const double d = _fadeInterp.duration();
    const double f = t/d;

    switch (_scene)
    {
    case 0: if (_coaster.DrawGLScene0(f)) setScene(1); return;
    case 1: if (_coaster.DrawGLScene(t))  setScene(0); return;
    }
}

