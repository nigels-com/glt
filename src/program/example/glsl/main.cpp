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

#include <GL/glew.h>

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

extern unsigned char texture[];

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

    bool               _shader;
    GLuint v,f,f2,p;
};

GlutWindowGlslDemo::GlutWindowGlslDemo(int width,int height,int x,int y,unsigned int displayMode)
: GlutWindowExaminer("GLT GLSL Demo",width,height,x,y,displayMode),
  _shader(true)
{
}

GlutWindowGlslDemo::~GlutWindowGlslDemo()
{
}

static const char *vs =
"void main(void)"
"{"
"    gl_TexCoord[0]  = gl_MultiTexCoord0;"
"    gl_Position     = gl_ModelViewMatrix * gl_Vertex;"
"}";

static const char *fs =
"uniform sampler2D texture;"
""
"vec3 rgb2hsv(vec3 RGB)"
"{"
"    float MIN = min(RGB.x,min(RGB.y,RGB.z));"
"    float MAX = max(RGB.x,max(RGB.y,RGB.z));"
"    float DELTA = MAX-MIN;"
"    vec3 HSV;"
"    HSV.z = MAX;"
"    if (DELTA!=0.0)"
"    {"
"        HSV.y = DELTA/MAX;"
"        vec3 delRGB = ( ( ( MAX.xxx - RGB) / 6.0 ) + ( DELTA / 2.0 ) ) / DELTA;"
"        if      ( RGB.x == MAX ) HSV.x = delRGB.z - delRGB.y;"
"        else if ( RGB.y == MAX ) HSV.x = ( 1.0/3.0) + delRGB.x - delRGB.z;"
"        else if ( RGB.z == MAX ) HSV.x = ( 2.0/3.0) + delRGB.y - delRGB.x;"
"        if ( HSV.x < 0.0 ) { HSV.x += 1.0; }"
"        if ( HSV.x > 1.0 ) { HSV.x -= 1.0; }"
"    }"
"    return HSV;"
"}"
""
"vec3 hsv2rgb(vec3 HSV)"
"{"
"    vec3 RGB = HSV.z;"
"    if ( HSV.y != 0.0 ) {"
"       float var_h = HSV.x * 6.0;"
"       float var_i = floor(var_h);"
"       float var_1 = HSV.z * (1.0 - HSV.y);"
"       float var_2 = HSV.z * (1.0 - HSV.y * (var_h-var_i));"
"       float var_3 = HSV.z * (1.0 - HSV.y * (1-(var_h-var_i)));"
"       if      (var_i == 0) { RGB = vec3(HSV.z, var_3, var_1); }"
"       else if (var_i == 1) { RGB = vec3(var_2, HSV.z, var_1); }"
"       else if (var_i == 2) { RGB = vec3(var_1, HSV.z, var_3); }"
"       else if (var_i == 3) { RGB = vec3(var_1, var_2, HSV.z); }"
"       else if (var_i == 4) { RGB = vec3(var_3, var_1, HSV.z); }"
"       else                 { RGB = vec3(HSV.z, var_1, var_2); }"
"   }"
"   return RGB;"
"}"
""
"void main(void)"
"{"
"    vec3 color = texture2D(texture,gl_TexCoord[0].st);"
"    vec3 hsv = rgb2hsv(color);"
"    hsv.x = fract(hsv.x+0.6);"
"    gl_FragColor = vec4(hsv2rgb(hsv), 1.0);"
"}";

void
GlutWindowGlslDemo::OnOpen()
{
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
//  glEnable(GL_CULL_FACE);
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
        const char * vv = vs;
    
        glShaderSource(v, 1, &vv,NULL);
        glShaderSource(f, 1, &ff,NULL);
    
        glCompileShader(v);
        glCompileShader(f);
    
        const int len = 1024;
        GLchar buffer[1024];
        glGetShaderInfoLog(v,len,NULL,buffer);
        cout << buffer << endl;

        glGetShaderInfoLog(f,len,NULL,buffer);
        cout << buffer << endl;

        p = glCreateProgram();
        glAttachShader(p,f);
        glAttachShader(p,v);
    
        glLinkProgram(p);

        if (_shader)
            glUseProgram(p);
    }

    //

    _texture.init(texture);
}

void
GlutWindowGlslDemo::OnClose()
{
    _texture.init(NULL);
}

void 
GlutWindowGlslDemo::OnDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    white.glColor();
//    glutSolidTeapot(0.5);

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    _texture.set();
    glBegin(GL_QUADS);
        glNormal3i(0,0,1);
        glTexCoord2i(0,0); glVertex2i(-1,-1);
        glTexCoord2i(1,0); glVertex2i( 1,-1);
        glTexCoord2i(1,1); glVertex2i( 1, 1);
        glTexCoord2i(0,1); glVertex2i(-1, 1);
    glEnd();
}

bool 
GlutMain(const std::vector<std::string> &arg)
{
    static GlutWindow *main = new GlutWindowGlslDemo(600,600,10,10);
    main->open();
    return true;
}
