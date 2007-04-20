/*
  Based on GLSL Tutorial Program for GLUT
  http://www.lighthouse3d.com/opengl/glsl/

  GLT OpenGL C++ Toolkit
  Copyright (C) 2000-2007 Nigel Stewart
  http://www.nigels.com/glt/

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
#include <glutm/winexam.h>
#include <glutm/main.h>

#include <glt/light.h>
#include <glt/material.h>
#include <glt/lightm.h>
#include <glt/texture.h>
#include <glt/matrix.h>
#include <glt/error.h>
#include <glt/rgb.h>

#include <iostream>
using namespace std;

class GlutWindowGlslDemo : public GlutWindowExaminer
{
public:
    GlutWindowGlslDemo
    (
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault,
        unsigned int displayMode = displayModeDefault
    );

    ~GlutWindowGlslDemo();

    void OnOpen();
    void OnClose();
    void OnDisplay();

protected:
    GltTexture         _texture;
    GLuint v,f,f2,p;
};

GlutWindowGlslDemo::GlutWindowGlslDemo(int width,int height,int x,int y,unsigned int displayMode)
: GlutWindowExaminer("GLT GLSL Demo",width,height,x,y,displayMode)
{
}

GlutWindowGlslDemo::~GlutWindowGlslDemo()
{
}

static const char *vs =
"varying vec3 normal, lightDir;\n"
"\n"
"void main()\n"
"{      \n"
"       lightDir = normalize(vec3(gl_LightSource[0].position));\n"
"       normal = normalize(gl_NormalMatrix * gl_Normal);\n"
"               \n"
"       gl_Position = ftransform();\n"
"}\n";

static const char *fs =
"varying vec3 normal, lightDir;\n"
"\n"
"void main()\n"
"{\n"
"       float intensity;\n"
"       vec3 n;\n"
"       vec4 color;\n"
"\n"
"       n = normalize(normal);\n"
"       intensity = max(dot(lightDir,n),0.0); \n"
"\n"
"       if (intensity > 0.8)\n"
"               color = vec4(0.8,0.8,0.8,1.0);\n"
"       else if (intensity > 0.6)\n"
"               color = vec4(0.4,0.4,0.8,1.0);  \n"
"       else if (intensity > 0.4)\n"
"               color = vec4(0.2,0.2,0.4,1.0);\n"
"       else\n"
"               color = vec4(0.1,0.1,0.1,1.0);          \n"
"               \n"
"       gl_FragColor = color;\n"
"}\n";

static const char *fs2 =
"vec4 toonify(in float intensity) {\n"
"\n"
"       vec4 color;\n"
"\n"
"       if (intensity > 0.98)\n"
"               color = vec4(0.8,0.8,0.8,1.0);\n"
"       else if (intensity > 0.5)\n"
"               color = vec4(0.4,0.4,0.8,1.0);  \n"
"       else if (intensity > 0.25)\n"
"               color = vec4(0.2,0.2,0.4,1.0);\n"
"       else\n"
"               color = vec4(0.1,0.1,0.1,1.0);          \n"
"\n"
"       return(color);\n"
"}";

void
GlutWindowGlslDemo::OnOpen()
{
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glDisable(GL_DITHER);
    glCullFace(GL_BACK);
    glClearDepth(1.0);
    glLoadIdentity();

    GLERROR

    black.glClearColor();
    
    GltLight light0(GL_LIGHT0);
    light0.ambient()  = GltColor(0.1, 0.1, 0.1, 1.0);
    light0.specular() = GltColor(0.5, 0.5, 0.5, 0.0);
    light0.position() = Vector(1.5, 4.0, -8.0);
    light0.enabled()  = true;
    light0.set();

    bronzeMaterial.set();

    GltLightModel lightModel;
    lightModel.setAmbient(0.0, 0.0, 0.0, 0.0);
    lightModel.setLocalViewer(GL_FALSE);
    lightModel.setTwoSide(GL_TRUE);

    GLERROR

    glewInit();
    if (glewIsSupported("GL_VERSION_2_0"))
    {
        v  = glCreateShader(GL_VERTEX_SHADER);
        f  = glCreateShader(GL_FRAGMENT_SHADER);
        f2 = glCreateShader(GL_FRAGMENT_SHADER);
    
        const char * ff = fs;
        const char * ff2 = fs2;
        const char * vv = vs;
    
        glShaderSource(v, 1, &vv,NULL);
        glShaderSource(f, 1, &ff,NULL);
        glShaderSource(f2, 1, &ff2,NULL);
    
        glCompileShader(v);
        glCompileShader(f);
        glCompileShader(f2);
    
        p = glCreateProgram();
        glAttachShader(p,f);
        glAttachShader(p,f2);
        glAttachShader(p,v);
    
        glLinkProgram(p);
        glUseProgram(p);
    }

    //

//    _texture.init(backgroundTexture);
}

void
GlutWindowGlslDemo::OnClose()
{
//    _texture.init(NULL);
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
GlutWindowGlslDemo::OnDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    white.glColor();
    glutSolidTeapot(0.5);

//    glEnable(GL_TEXTURE_2D);
//    drawFace(_raypp   ,matrixRotate(VectorX,-90));
}

bool 
GlutMain(const std::vector<std::string> &arg)
{
    static GlutWindow *main = new GlutWindowGlslDemo(600,600,10,10);
    main->open();
    return true;
}
