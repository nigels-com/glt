/*

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2000 Nigel Stewart
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

#include <glutm/glut.h>
#include <glutm/master.h>
#include <glutm/window.h>
#include <glutm/main.h>

#include <glt/light.h>
#include <glt/material.h>
#include <glt/lightm.h>
#include <glt/texture.h>
#include <glt/matrix.h>
#include <glt/error.h>

#include <node/tiled.h>
#include <misc/timer.h>

#include "textures.h"

#include <iostream>
using namespace std;

class GlutWindowTextureDemo : public GlutWindow
{
public:
    GlutWindowTextureDemo
    (
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault,
        unsigned int displayMode = displayModeDefault
    );

    ~GlutWindowTextureDemo();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnReshape(int w, int h);
    void OnIdle();

protected:
    GltTexture         _glt;
    GltTexture         _opengl;
    GltTexture         _vrml;
    GltTexture         _linux;
    GltTexture         _inventor;
    GltTexture         _raypp;

    GltTexture         _background;
    GltTextureViewport _tiled;

    Timer              _timer;
};

GlutWindowTextureDemo::GlutWindowTextureDemo(int width,int height,int x,int y,unsigned int displayMode)
: GlutWindow("GLT Texturing Demo",width,height,x,y,displayMode),
  _tiled(_background,true)
{
}

GlutWindowTextureDemo::~GlutWindowTextureDemo()
{
}

void
GlutWindowTextureDemo::OnOpen()
{
    glDisable(GL_DITHER);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    glScale(0.5);
    _timer.start();

    setIdle(true);

    glRotateX(45);

    _glt       .init(gltTexture);
    _opengl    .init(openglTexture);
    _vrml      .init(vrmlTexture);
    _linux     .init(linuxTexture);
    _inventor  .init(inventorTexture);
    _raypp     .init(rayppTexture);
    _background.init(backgroundTexture);
}

void
GlutWindowTextureDemo::OnClose()
{
    _glt       .init(NULL);
    _opengl    .init(NULL);
    _vrml      .init(NULL);
    _linux     .init(NULL);
    _inventor  .init(NULL);
    _raypp     .init(NULL);
    _background.init(NULL);
}

void 
drawFace(const GltTexture &texture,const Matrix &matrix)
{
    GLERROR;

    glPushMatrix();
        matrix.glMultMatrix();
        texture.set();
        glBegin(GL_QUADS);
            glNormal3i(0,0,1);
            glTexCoord2i(0,0); glVertex3i(-1,-1,1);
            glTexCoord2i(1,0); glVertex3i( 1,-1,1);
            glTexCoord2i(1,1); glVertex3i( 1, 1,1);
            glTexCoord2i(0,1); glVertex3i(-1, 1,1);
        glEnd();
    glPopMatrix();

    GLERROR;
}

void 
GlutWindowTextureDemo::OnDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _tiled.draw();

    glEnable(GL_TEXTURE_2D);

    drawFace(_glt     ,Matrix());
    drawFace(_opengl  ,matrixRotate(VectorY,90));
    drawFace(_inventor,matrixRotate(VectorY,180));
    drawFace(_vrml    ,matrixRotate(VectorY,270));
    drawFace(_linux   ,matrixRotate(VectorX,90));
    drawFace(_raypp   ,matrixRotate(VectorX,-90));
}

void 
GlutWindowTextureDemo::OnIdle()
{
    glRotateY(_timer.elapsed()*30.0);
    _timer.start();
    postRedisplay();
}

void
GlutWindowTextureDemo::OnReshape(int w, int h)
{
    GlutWindow::OnReshape(w,h);

    if (w!=0 && h!=0)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        const double r = double(w)/double(h);
        gluOrtho2D(-r,r,-1.0,1.0);
        glMatrixMode(GL_MODELVIEW);
    }

}

bool GlutMain(const std::vector<std::string> &arg)
{
    static GlutWindow *main = new GlutWindowTextureDemo(600,600,10,10);
    main->open();

    return true;
}
