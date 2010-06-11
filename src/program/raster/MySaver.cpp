#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>

#include <glutm/window.h>
#include <glutm/main.h>

#include <misc/compress.h>

#include "MySaver.h"

#include "media.h"

#ifdef  _MSC_VER
#pragma warning (disable:4305 4244)
#endif

//-----------------------------------------------------------------------------

// Various constants that control the screen saver effects

const real RasterSaver::jitterAmp       = 0.1;
const real RasterSaver::jitterRate      = 100.0;
const real RasterSaver::jitterRotation  = 0.5;

const real RasterSaver::fadeAmp         = 0.05;
const real RasterSaver::fadeRate        = 0.5;

RasterSaver::RasterSaver()
:
    _bRasters(true),
    _bSnow(true),
    _scene(0),
    _done(true),
    _rng(0.0,1.0)
{
}

RasterSaver::~RasterSaver()
{
}

void
RasterSaver::OnOpen()
{
    // 60Hz refresh rate, maximum
    setTick(1000/60);

    // Load textures and models
    SetupTextures();
    SetupModels();

    // Setup OpenGL state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
}

void
RasterSaver::OnClose()
{
    // Textures

    _crt.clear();
    _kana.clear();
    _code.clear();
    _numbers.clear();
    _snow.clear();
    _raster.clear();

    // Display Lists

    {
        for (unsigned int i=0; i<_sphere.size(); i++)
            _sphere[i].reset();
    }

    {
        for (unsigned int i=0; i<_building.size(); i++)
            _building[i].Reset();
    }
}

void
RasterSaver::OnDisplay()
{
    // Switch scenes as required

    if (_done)
    {
        _timer.start();
        _scene++;
        _done = false;
    }

    // Draw the current scene

    switch (_scene%3)
    {
        case 0: _done = drawScene1(); break;
        case 1: _done = drawScene2(); break;
        case 2: _done = drawScene3(); break;
        // add groovy new scenes here :)
    }
}

//-----------------------------------------------------------------------------

// Draw a bar at (x,y) of size (w x h)

void
RasterSaver::drawBar(float x, float y, float w, float h)
{
    glRectf(x,y,x+w,y+h);
}

//-----------------------------------------------------------------------------

// Draw a sphere with specified Radius, Slices and Stacks. The Wire parameter
// can be used to draw a wireframe sphere

void
RasterSaver::drawSphere(float Radius, int Slices, int Stacks, bool Wire)
{
    // something changed, create on display list
    GLUquadricObj *q = gluNewQuadric();
        if (Wire) gluQuadricDrawStyle(q, GLU_LINE);
        gluSphere(q,Radius,Slices,Stacks);
    gluDeleteQuadric(q);
}

//-----------------------------------------------------------------------------

// Draw numeric string, using blurry number font
// Appears at (x,y), with specified size 's', valid chars are: '0123456789:'
void
RasterSaver::myNumString (const char *str, float x, float y, float s) const
{
    const float ts=1.0/11.0;    // 11 chars across texture w
    float w=s*0.9f, h=s;
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        _numbers.set();
        for (int n=0; str[n]; n++) {
            // idx= 0..9 for digit, 10 for colon, -1 for anything else
            int idx = isdigit(str[n])?str[n]-48:(str[n]==':')?10:-1;
            if (idx >= 0) { // is it a drawable char?
                float l,r;
                l=ts*idx;
                r=l+ts-0.008f;
                glPushMatrix();
                    glTranslatef(x+n*w*1.1f,y,0);
                    glBegin(GL_QUADS);
                        glTexCoord2f(r,0);
                        glVertex2f(w,0);
                        glTexCoord2f(r,1);
                        glVertex2f(w,h);
                        glTexCoord2f(l,1);
                        glVertex2f(0,h);
                        glTexCoord2f(l,0);
                        glVertex2f(0,0);
                    glEnd();
                glPopMatrix();
            }
        }
    glPopAttrib();
}

//---------------------------------------------------------------------------

// Draw a block of 'code' at (x,y), with size (w*h) that can be scrolled
// vertically according to the 'scroll' parameter

void
RasterSaver::drawCode(float x, float y, float w, float h, float scroll)
{
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        _code.set();

        glPushMatrix();
            glTranslatef(x,y,0);
            glBegin(GL_QUADS);
                glTexCoord2f(1,0+scroll);
                glVertex2f(w,0);
                glTexCoord2f(1,1+scroll);
                glVertex2f(w,h);
                glTexCoord2f(0,1+scroll);
                glVertex2f(0,h);
                glTexCoord2f(0,0+scroll);
                glVertex2f(0,0);
            glEnd();
        glPopMatrix();
    glPopAttrib();
}

//---------------------------------------------------------------------------

// Draw kana string (kana) at (x,y), with h (h) - w scaled to
// match aspect.
//
void
RasterSaver::drawKana(float x, float y, float h, int kana)
{
    const int numKana=4;
    kana%=numKana;  // take modulo no.of kana strings available
    float
        w  =h  *(float)numKana,
        vs =1.0f/(float)numKana,
        u  =vs*kana,
        v  =u+vs;
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        _kana.set();

        glPushMatrix();
            glTranslatef(x,y,0);
            glBegin(GL_QUADS);
                glTexCoord2f(1,u);
                glVertex2f(w,0);
                glTexCoord2f(1,v);
                glVertex2f(w,h);
                glTexCoord2f(0,v);
                glVertex2f(0,h);
                glTexCoord2f(0,u);
                glVertex2f(0,0);
            glEnd();
        glPopMatrix();
    glPopAttrib();
}

//---------------------------------------------------------------------------

// Draw (num) horizontal Bar Graphs at (x,y) with bar dimensions (w,h)

void
RasterSaver::drawBars(float time, float x, float y, float w, float h, int num)
{
    float a = 2.0f*time;

    for (int n=0; n<num; n++)
    {
        const float len = float(w*(0.8*(1.0+sin(a+0.3*n))*(1.0+cos(2.0*a+3.7*n))/2.0 + 0.2));
        const float y1  = y+h*n;
        const float y2  = y1+h*0.8f;
        glRectf(x,y1,x+len,y2);
    }
}

//---------------------------------------------------------------------------

void
RasterSaver::drawTimecode(float time, int w, int h) const
{
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);

        {
            int ms = (int) floor(time*1000);
            int mn=(ms/60000)%60,se=(ms/1000)%60,fr=(ms/20)%50;
            char str[64];
            float cw=32.0f*w/800.0f, space=0.2f*cw;
            sprintf(str,"%02d:%02d:%02d", mn,se,fr);
            myNumString(str, w-strlen(str)*cw-space,space,cw);
        }
    glPopAttrib();
}

void
RasterSaver::drawRasters(float Time, int w, int h) const
{
    // the '_bRasters' flag can be used to disable rasters effect
    if (!_bRasters) return;

    float angle = 1000.0*Time/20.0;
    // texture scale
    float ts=400.0/5.0;
    // vertical jitter
    float vs = jitterAmp*sin(jitterRate*M_PI_DEG*angle);
    // Draw Rasters
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        glEnable(GL_TEXTURE_2D);
        _raster.set();
        // cyclic fading to vary brightness across rasters
        float
            k = 1.0-fadeAmp,
            a = k+fadeAmp*sin(fadeRate*M_PI_DEG*11.5*angle),
            b = k+fadeAmp*sin(fadeRate*M_PI_DEG*12.0*angle),
            c = k+fadeAmp*sin(fadeRate*M_PI_DEG*11.3*angle),
            d = k+fadeAmp*sin(fadeRate*M_PI_DEG*11.7*angle);
        // slight rotational jitter
        glRotatef(jitterRotation*vs,0,0,1);
        // draw the rasters
        glBegin(GL_QUADS);
            glColor4f(a,a,a,1);
            glTexCoord2f(ts,vs);
            glVertex2f(w,0);

            glColor4f(b,b,b,1);
            glTexCoord2f(ts,ts+vs);
            glVertex2f(w,h);

            glColor4f(c,c,c,1);
            glTexCoord2f(0,ts+vs);
            glVertex2f(0,h);

            glColor4f(d,d,d,1);
            glTexCoord2f(0,vs);
            glVertex2f(0,0);
        glEnd();
    glPopAttrib();
}

//---------------------------------------------------------------------------

void
RasterSaver::drawSnow(float time, float x, float y, int w, int h, bool loseSync, int Image) const
{
    // the '_bSnow' flag can be used to disable snow effect
    if (!_bSnow) return;

    float border=w/20, shade=w/10;

    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        glDisable(GL_DEPTH_TEST);
        glTranslatef(x,y,0);

        glColor4f(0,0,0, 0.2);
        // draw drop shadow
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glRectf(w,-shade,w+shade,h-shade);
        glRectf(shade,-shade,w,0);
        glDisable(GL_BLEND);

        // draw black border frame
        glRectf(0,0,w,border);
        glRectf(w-border,border,w,h-border);
        glRectf(0,h-border,w,h);
        glRectf(0,border,border,h-border);

        glColor3f(0,1,0);

        glDisable(GL_DEPTH_TEST);

        // draw snow
        glEnable(GL_TEXTURE_2D);
        _snow.set();

        float u = _rng.rand();
        float v = _rng.rand();

        glBegin(GL_QUADS);
            glTexCoord2f(1+u,0+v);
            glVertex2f(w-border,border);

            glTexCoord2f(1+u,1+v);
            glVertex2f(w-border,h-border);

            glTexCoord2f(0+u,1+v);
            glVertex2f(border,h-border);

            glTexCoord2f(0+u,0+v);
            glVertex2f(border,border);
        glEnd();

        float angle = 1000.0*time/10.0;

        // draw blurry crt image
        _crt.set();  // glCallList(TEX_CRTSNAP);
        glEnable(GL_BLEND);
        // use alpha to fade image in/out of snow background
        glColor4f(0,1,0, 0.7+0.2*sin(M_PI_DEG*angle));
        // crt image jitters according to texture coords. from
        // above, and will intermittently synchronise to make
        // the picture visible briefly
        if ((((int)(time+sin(M_PI_DEG*angle)*6)%6)<2) || (!loseSync))
        {
            u=0;
            v=0;
        }
        float
            l= (float)(Image%4)/4.0,
            r= l+0.25,
            t= (float)(Image/4)/2.0,
            b= t+0.5;
        glBegin(GL_QUADS);
            glTexCoord2f(r+u,t+v);
            glVertex2f(w-border,border);

            glTexCoord2f(r+u,b+v);
            glVertex2f(w-border,h-border);

            glTexCoord2f(l+u,b+v);
            glVertex2f(border,h-border);

            glTexCoord2f(l+u,t+v);
            glVertex2f(border,border);
        glEnd();

        // could also blend scrolling code?
        //DrawCode(0,0,w,h,-Time/4.0);

        drawTimecode(time,w,h);
    glPopMatrix();
    glPopAttrib();
}

//---------------------------------------------------------------------------

// Scene 1: Spinning spheres, rasters, scrolling code & timecode

bool
RasterSaver::drawScene1()
{
    // w and h of OpenGL window
    // Avoid zero w or h

    const int h  = std::max(1,getHeight());
    const int w = std::max(1,getWidth());

    const float time = _timer.elapsed();


    const float angle = 1000.0*time/20.0;

    glClearColor(0.4,0.4,0.4,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup 3D Perspective View
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/(float)h, 0.1, 10.0);
    gluLookAt(0,0,3, 0,0,0, 0,1,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Tumble Scene
    glRotatef(angle,     0,1,0);
    glRotatef(angle*0.5, 1,0,0);
    glRotatef(angle*0.1, 0,0,1);

    // Draw Scene
    glPushAttrib(GL_ENABLE_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (int n=0;n<3;n++)
        {
            float alpha=0.5+0.5*sin(M_PI_DEG*angle);

            switch (n)
            {
            case 0:
                // 1st pass: black outlines
                glDisable(GL_LIGHTING);
                glColor3f(0,0,0);
                glDisable(GL_DEPTH_TEST);
                glEnable(GL_CULL_FACE);
                break;
            case 1:
                // 2nd pass: green wireframe
                glColor3f(0,1,0);
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_CULL_FACE);
                break;
            case 2:
                // 3rd pass: lit shaded spheres
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_CULL_FACE);
                break;
            }

            glPushMatrix();
                glTranslatef(0,0.4,0);
                if (n==2)
                    glColor4f(1,0.2,0.2,alpha);
                _sphere[n].draw();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-0.4,-0.3,0);
                if (n==2)
                    glColor4f(0.2,1,0.2,alpha);
                _sphere[n].draw();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0.4,-0.3,0);
                if (n==2)
                    glColor4f(0.2,0.2,1,alpha);
                _sphere[n].draw();
            glPopMatrix();
        }
    glPopAttrib();

    // Setup 2D Ortho View
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,w,0,h,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw Scrolling Code
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        // left hand layer
        glColor4f(0,1,0, 0.5 +0.5*sin(0.01*angle)*cos(0.02*angle));
        drawCode(0,0,h,h,-angle/100.0);
        // right hand layer
        glColor4f(1,1,0, 0.5 +0.5*cos(0.03*angle)*sin(0.07*angle));
        drawCode(w-0.5*h,0.05*h,h,h,-2.0*angle/100.0);
    glPopAttrib();

    // Draw bar graph
    {
        float vs=h/20.0;
        glColor3f(1,1,0);
        drawBars(time,4,h-vs*4,w/10.0,vs,3);
    }

    // Draw Kana Script
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        float size=h;
        float x=(time-5)*w/8.0;
        float y=h-size;
        // draw shadow
        glColor3f(.2,.2,.2);
        glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
        drawKana(x+size/20,y-size/20, size,3);
        // draw script
        glColor3f(0,0,1);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        drawKana(x,y, size,3);
    glPopAttrib();

    // Draw Timecode
    glColor4f(0.7,0.7,0.6, 1);
    drawTimecode(time,w,h);

    // Draw Rasters
    drawRasters(time,w,h);

    return time>=5.0;
}

//---------------------------------------------------------------------------

// Scene 2: Snowy CRTs and twisty bendy timecodes :)

bool
RasterSaver::drawScene2()
{
    // w and h of OpenGL window
    // Avoid zero w or h

    const int w = std::max(1,getWidth());
    const int h = std::max(1,getHeight());

    const float time = _timer.elapsed();

    float angle = 1000.0*time/20.0;

    glClearColor(0.4,0.4,0.4,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup 3D Perspective View
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/(float)h, 1.0, 1000.0);
    glTranslatef(0,0,-400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Tumble Scene
    glRotatef(angle,     0,1,0);
    glRotatef(angle*0.5, 1,0,0);
    glRotatef(angle*0.1, 0,0,1);

    // Draw Object
    glColor3f(0,1,0);
    glPushAttrib(GL_LINE_BIT);
        glLineWidth(3.0f);
        _building[0].DrawWire();
        glScalef(0.7,0.7,0.7);
        glRotatef(90, 0,1,0);
        _building[0].DrawWire();
    glPopAttrib();

    // Setup 2D Ortho View
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,w,0,h,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw twisty bendy timecodes
    for (int n=0;n<90;n+=3) {
        float i=n/60.0;
        glColor4f(0.2*i,i,i, 1);
        glPushMatrix();
            glRotatef(n,0,0,1);
            glTranslatef(30.0*sin(0.1*n+M_PI_DEG*angle),0,0);
            drawTimecode(time,w,h);
        glPopMatrix();
    }

    // Draw Scrolling Code
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        // left hand layer
        glColor4f(0,1,0, 0.5 +0.5*sin(0.01*angle)*cos(0.02*angle));
        drawCode(0,0,h,h,-angle/100.0);
        // middle layer
        glColor4f(0,1,0, 0.5 +0.5*cos(0.03*angle)*sin(0.07*angle));
        drawCode(w/2,0,h,h,-1.5*angle/100.0);
    glPopAttrib();

    // Draw Snowy CRTs
    drawSnow(time,30,50,h/3,h/3);
    glPushMatrix();
        //glRotatef(5.0*sin(M_PI_DEG*angle), 0,0,1);
        //glTranslatef(w*Time/10.0, 0,0);
        drawSnow(
            time,w/4+w/5*sin(M_PI_DEG*angle/3),h/3,h/2,h/2,
            false,              // don't lose sync on this display
            (int)(0.9*time)%8   // image changes periodically
        );
    glPopMatrix();

    // Draw Timecode
    glColor4f(0.7,0.7,0.6, 1);
    drawTimecode(time,w,h);

    // Draw Rasters
    drawRasters(time, w, h);

    return time>=5.0f;
}

//---------------------------------------------------------------------------

// Scene 3: Building zoom and snowy CRTs

bool
RasterSaver::drawScene3()
{
    // w and h of OpenGL window
    // Avoid zero w or h

    const int w = std::max(1,getWidth());
    const int h = std::max(1,getHeight());

    const float time = _timer.elapsed();

    float angle = 1000.0*time/20.0;

    glClearColor(0.4,0.4,0.4,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup 2D Ortho View
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,w,0,h,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw Scrolling Code
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        // left hand layer
        glColor4f(0,1,0, 0.3 +0.3*sin(0.01*angle)*cos(0.02*angle));
        drawCode(0,0,h,h,-angle/100.0);
        // middle layer
        glColor4f(0,1,0, 0.3 +0.3*cos(0.03*angle)*sin(0.07*angle));
        drawCode(w/2,0,h,h,-1.5*angle/100.0);
    glPopAttrib();

    // Setup 3D View
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/(float)h, 250.0, 1000.0);
    gluLookAt(
        0,400,600,
        0,0,0,
        0,1,0
    );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int pass=0;pass<4;pass++) {
        bool wire=false;
        glPushMatrix();
        glPushAttrib(GL_LINE_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT);
            switch (pass) {
            case 0: { //-- background mask
                glColor3f(0.4,0.4,0.4);
                glDisable(GL_LIGHTING);
                glDisable(GL_DEPTH_TEST);
              } break;
            case 1: { //-- outline
                wire=true;
                glColor3f(0,0,0);
                glDisable(GL_LIGHTING);
                glDisable(GL_DEPTH_TEST);
                glLineWidth(8.0);
              } break;
            case 2: { //-- shaded model
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_BLEND);
                float alpha = (time<2.0)?1.0 : 0.5+0.5*sin(M_PI_DEG*angle);
                glColor4f(0.8,0.8,0.8,alpha);
              } break;
            case 3: { //-- wireframe
                wire=true;
                glDisable(GL_LIGHTING);
                glLineWidth(2.0);
                glEnable(GL_LINE_SMOOTH);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glDisable(GL_DEPTH_TEST);
                float alpha = (time<2.0)?0.0:0.5-0.5*cos(time-2.0);
                glColor4f(0,1,0,alpha);
              } break;
            }//switch(pass)

            float sub=(time<4.0)?0:time<7.0?(time-4.0):3.0;
            int levels=(time<4.0)?6:6-int(sub);

            glPushMatrix();
                if (time>4.0) {
                    // zoom in..
                    float s=(time<6.0)?(1.0+(time-4.0)/4.0):1.5;
                    glScalef(s,s,s);
                }
                // spin about vertical axis
                glRotatef(-angle, 0,1,0);
                // flip model coords. to align vertically
                glRotatef(-90,1,0,0);
                // shift model downwards (so we rotate roughly about centre)
                glTranslatef(0,0,-200);
                // draw the floors
                glPushMatrix();
                for (int n=0; n<(levels>5?5:levels); n++) {
                    glTranslatef(0,0,50);
                    if (wire) _building[0].DrawWire(); else _building[0].Draw();
                }
                glPopMatrix();
                // draw roof detail if reqd.
                if (levels==6) {
                    if (wire) {
                        _building[1].DrawWire();
                        _building[2].DrawWire();
                    } else {
                        _building[1].Draw();
                        _building[2].Draw();
                    }
                }
                // draw room highlight
                if (wire) {
                    // fade in as required
                    glColor4f(1,0,0,(time<1.0)?0:(time<2.0)?(time-1.0):1);
                    _building[3].DrawWire();
                }
            glPopMatrix();
        glPopAttrib();
        glPopMatrix();
    }//for(pass)

    // Setup 2D Ortho View
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,w,0,h,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw Kana Script
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        float size=h/4, x=w-time*w/5.0, y=0;
        // draw shadow
        glColor3f(.2,.2,.2);
        glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
        drawKana(x+size/20,y-size/20, size,0);
        // draw script
        glColor3f(0,0,1);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        drawKana(x,y, size,0);
        //DrawKana(w/3.0,h-time*h/8.0, size,2);
    glPopAttrib();

    // Draw Snowy CRTs
    int dim=h/3;
    drawSnow(time,30,50+dim*time/6.0,dim,dim,false,(int)(1.2*time+2)%8);
    drawSnow(time,w-1.1*dim,h-1.1*dim,dim,dim,false,(int)(time)%8);

    // Draw Rasters
    drawRasters(time, w, h);

    return time >= 8.0f;
}


//---------------------------------------------------------------------------

void RasterSaver::SetupTextures()
{
    _crt.init(CRTTexture);
    _kana.init(KanaTexture);
    _code.init(CodeTexture);
    _numbers.init(NumbersTexture);

    // Raster

    string raster;
    raster.resize(16);
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            raster[(i<<2)|j] = (i<3)?255:200;
        _raster.init(4,4,raster);

    // Snow

    long w=128, h=128;

    string tex;
    tex.resize(w*h);
    for (int n=0; n<w*h; n++)
        tex[n] = _rng.base().rand()&0xff;

    _snow.init(w,h,tex);
}

//---------------------------------------------------------------------------

/**
 * Load 3D models
 */
void RasterSaver::SetupModels()
{
    // Build sphere display lists

    _sphere.resize(3);

    _sphere[0].newList();
        drawSphere(0.5+0.02,16,16);
    _sphere[0].endList();

    _sphere[1].newList();
        drawSphere(0.5-0.02,16,16,true);
    _sphere[1].endList();

    _sphere[2].newList();
        drawSphere(0.5,16,16);
    _sphere[2].endList();

    // Load building models

    _building.resize(4);

    string tmp;

    if (decompress(tmp,floorModel))
        _building[0].Load(tmp);

    if (decompress(tmp,roof1Model))
        _building[1].Load(tmp);

    if (decompress(tmp,roof2Model))
        _building[2].Load(tmp);

    if (decompress(tmp,roomModel))
        _building[3].Load(tmp);
}

//---------------------------------------------------------------------------


#include <iostream>
using namespace std;

bool GlutMain(const std::vector<std::string> &arg)
{
    static GlutWindow *main = new RasterSaver();
    main->open();

    return true;
}
