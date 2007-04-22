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

    GLuint _vShader;
    GLuint _fShader;
    GLuint _program;
    GLuint _uniformWallHue;
    GLuint _uniformWallSaturation;
    GLuint _uniformWallContrast;
    GLuint _uniformWallBrightness;

    void drawWall
    (
        const GLint   n, 
        const GLfloat z, 
        const GLfloat hue, 
        const GLfloat saturation, 
        const GLfloat contrast, 
        const GLfloat brightness
    );
};

GlutWindowGlslDemo::GlutWindowGlslDemo(int width,int height,int x,int y,unsigned int displayMode)
:   GlutWindowExaminer("GLT GLSL Demo",width,height,x,y,displayMode),
    _shader(true),
    _vShader(0),
    _fShader(0),
    _program(0),
    _uniformWallHue(0),
    _uniformWallSaturation(0),
    _uniformWallContrast(0),
    _uniformWallBrightness(0)
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
"uniform float WallHue;"
"uniform float WallSaturation;"
"uniform float WallContrast;"
"uniform float WallBrightness;"
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
"        vec3 delRGB = ( ((vec3(MAX,MAX,MAX)-RGB)/6.0) + (vec3(DELTA,DELTA,DELTA)/2.0) )/DELTA;"
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
"    vec3 RGB = HSV.zzz;"
"    if ( HSV.y != 0.0 ) {"
"       float var_h = HSV.x * 6.0;"
"       float var_i = floor(var_h);"
"       float var_1 = HSV.z * (1.0 - HSV.y);"
"       float var_2 = HSV.z * (1.0 - HSV.y * (var_h-var_i));"
"       float var_3 = HSV.z * (1.0 - HSV.y * (1.0-(var_h-var_i)));"
"       if      (var_i == 0.0) { RGB = vec3(HSV.z, var_3, var_1); }"
"       else if (var_i == 1.0) { RGB = vec3(var_2, HSV.z, var_1); }"
"       else if (var_i == 2.0) { RGB = vec3(var_1, HSV.z, var_3); }"
"       else if (var_i == 3.0) { RGB = vec3(var_1, var_2, HSV.z); }"
"       else if (var_i == 4.0) { RGB = vec3(var_3, var_1, HSV.z); }"
"       else                   { RGB = vec3(HSV.z, var_1, var_2); }"
"   }"
"   return RGB;"
"}"
""
"vec3 fsGrey(float T)"
"{"
"    return vec3(T,T,T);"
"}"
""
"vec3 fsRGB(vec3 T)"
"{"
"    return T;"
"}"
""
"vec3 fsHSV(vec3 T)"
"{"
"    return hsv2rgb(T);"
"}"
""
"vec4 fsWall1(vec4 RGBA, float Hue, float Saturation, float Contrast, float Brightness)"
"{"
"    vec3 HSV= rgb2hsv(RGBA.xyz);"
"    if (HSV.y<0.5)"
"        return vec4(hsv2rgb(vec3(Hue,Saturation,(HSV.z-0.5)*Contrast+0.5+Brightness)),RGBA.a);"
"    else"
"        return RGBA;"
"}"
""
"void main(void)"
"{"
"    gl_FragColor = vec4(fsGrey(gl_TexCoord[0].s),1.0);"
"    gl_FragColor = vec4(fsRGB(gl_TexCoord[0].xyz),1.0);"
"    gl_FragColor = vec4(fsRGB(vec3(gl_TexCoord[0].s,0,gl_TexCoord[0].t)),1.0);"
"    gl_FragColor = fsWall1(texture2D(texture,gl_TexCoord[0].st),WallHue,WallSaturation,WallContrast,WallBrightness);"
//"    gl_FragColor = vec4(fsHSV(gl_TexCoord[0].st,1.0).xyz,1.0);"
//"    vec3 RGB = texture2D(texture,gl_TexCoord[0].st);"
//"    vec3 HSV = rgb2hsv(RGB);"
//"    if (HSV.x<0.5) { HSV.x = fract(gl_TexCoord[0].s/2); HSV.y = fract(gl_TexCoord[0].t/2); } else { HSV.x = 0.65; }"
//"    if (HSV.y<0.5) { HSV.x = fract(gl_TexCoord[0].s/4); HSV.y = fract(gl_TexCoord[0].t/4); } else { HSV.y = 0.7; }"
//"    if (HSV.y<0.5) { HSV.x = 0.45; HSV.y = 0.14; } else { HSV.y = 0.5; }"
//"    if (HSV.y<0.5) { gl_FragColor = vec4(hsv2rgb(vec3(0.05,0.2,HSV.z)),1.0); } else { gl_FragColor = vec4(0.0,0.0,1.0,1.0); }"
//"    gl_FragColor = vec4(HSV.xxx,0);"
//"    gl_FragColor = vec4(hsv2rgb(HSV), 1.0);"
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
        _vShader  = glCreateShader(GL_VERTEX_SHADER);
        _fShader  = glCreateShader(GL_FRAGMENT_SHADER);
    
        const char *ff = fs;
        const char *vv = vs;
    
        glShaderSource(_fShader, 1, &ff,NULL);
        glShaderSource(_vShader, 1, &vv,NULL);
    
        glCompileShader(_fShader);
        glCompileShader(_vShader);
    
        const int len = 1024;
        GLchar buffer[1024];
        glGetShaderInfoLog(_fShader,len,NULL,buffer);
        cout << buffer << endl;

        glGetShaderInfoLog(_vShader,len,NULL,buffer);
        cout << buffer << endl;

        _program = glCreateProgram();
        glAttachShader(_program,_fShader);
        glAttachShader(_program,_vShader);
    
        glLinkProgram(_program);

        if (_shader)
        {
            glUseProgram(_program);

            _uniformWallHue        = glGetUniformLocation(_program,"WallHue");
            _uniformWallSaturation = glGetUniformLocation(_program,"WallSaturation");
            _uniformWallContrast   = glGetUniformLocation(_program,"WallContrast");
            _uniformWallBrightness = glGetUniformLocation(_program,"WallBrightness");
        }
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
GlutWindowGlslDemo::drawWall
(
    const GLint n, 
    const GLfloat x, 
    const GLfloat hue, 
    const GLfloat saturation,
    const GLfloat contrast,
    const GLfloat brightness
)
{
    if (_shader)
    {
        glUniform1f(_uniformWallHue,       hue);
        glUniform1f(_uniformWallSaturation,saturation);
        glUniform1f(_uniformWallContrast,  contrast);
        glUniform1f(_uniformWallBrightness,brightness);
    }

    glBegin(GL_QUADS);
        glNormal3i(0,0,1);
        glTexCoord2i(0,0); glVertex2f(x,      0.0f);
        glTexCoord2i(n,0); glVertex2f(x+1.0f, 0.0f);
        glTexCoord2i(n,n); glVertex2f(x+1.0f, 1.0f);
        glTexCoord2i(0,n); glVertex2f(x,      1.0f);
    glEnd();
}

void 
GlutWindowGlslDemo::OnDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    white.glColor();

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    _texture.set();

    drawWall(2,0.0f,0.1f,0.30f,1.0f, 0.0f);
    drawWall(2,1.0f,0.3f,0.05f,1.5f, 0.2f);
    drawWall(2,2.0f,0.8f,0.05f,0.5f, 0.1f);
    drawWall(2,3.0f,0.8f,0.05f,1.0f,-0.4f);
}

bool 
GlutMain(const std::vector<std::string> &arg)
{
    static GlutWindow *main = new GlutWindowGlslDemo(600,600,10,10);
    main->open();
    return true;
}
