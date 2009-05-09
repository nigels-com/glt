//
// Benchmark of glCopyPixels for GL_COLOR,GL_STENCIL,GL_DEPTH
//
// System Setup:
//  Windows NT 3.51, Pentium 100, 32Meg RAM
//  3Demon SX88, Display Driver 2.0, OpenGL driver 1.0.9
//  Visual C++ V4.0
//
// Sample Output:
//
// (500x500)
// Color rate  : 1.5625e+007
// Depth rate  : 3.90625e+006
// Stencil rate: 3.90625e+006
//
// (1024x745)
// Color rate  : 1.12188e+007
// Depth rate  : 3.97333e+006
// Stencil rate: 4.04926e+006
//
// (554x115)
// Color rate  : 1.59275e+007
// Depth rate  : 3.98187e+006
// Stencil rate: 3.98187e+006
//
// Prepared by Nigel Stewart, RMIT University, 1999-2006
// Email: nigels@nigels.com
//

#include <glt/gl.h>
#include <glt/color.h>
#include <glt/info.h>
#include <glt/rgb.h>

#include <misc/timer.h>
#include <misc/string.h>

#include <glutm/main.h>
#include <glutm/window.h>

#include <iostream>
using namespace std;

class OpenGLCopySpeed : public GlutWindow
{
public:
    OpenGLCopySpeed(const GLdouble maximumSamplePeriod = 0.5);
   ~OpenGLCopySpeed();

   void OnOpen();
   void OnClose();
   void OnDisplay();

private:

    const GLdouble _maximumSamplePeriod;

    const static GltString _banner;
    const static GLdouble  _mill;
};

///////////////////////////////////////////////////////////////////////////////

const GltString OpenGLCopySpeed::_banner =
        "OpenGL glCopyPixels Benchmark  \n"
        "(C) 1999-2006 Nigel Stewart    \n"
        "http://www.nigels.com/research/\n";

const GLdouble OpenGLCopySpeed::_mill = 1.0/1000000.0;

OpenGLCopySpeed::OpenGLCopySpeed(const GLdouble maximumSamplePeriod)
: GlutWindow("OpenGL glCopyPixels Benchmark"),
  _maximumSamplePeriod(maximumSamplePeriod)
{
}

OpenGLCopySpeed::~OpenGLCopySpeed()
{
}

void
OpenGLCopySpeed::OnOpen()
{
    GlutMenu &save = _leftButtonMenu.subMenu();
    save.addEntry("RGB"     ,MENU_CAPTURE_RGB);
    save.addEntry("z-buffer",MENU_CAPTURE_ZBUFFER);

    _leftButtonMenu.addEntry("Save PPM",save);
    _leftButtonMenu.addEntry("Close" ,MENU_CLOSE);
    _leftButtonMenu.attach();

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glTranslatef(0.0,0.0,-1.0);

    cout << _banner << endl << GltSystemInfo() << endl << GltInfo() << endl << endl;
    cout << "Sample Period: " << _maximumSamplePeriod << endl << endl;
    cout << "width\theight\tcolour\t\tdepth\t\tstencil" << endl;
}

void
OpenGLCopySpeed::OnClose()
{
    _leftButtonMenu.reset();
}

void
OpenGLCopySpeed::OnDisplay()
{
    GLuint viewport[4];
    GLuint width,height;

    glGetIntegerv(GL_VIEWPORT,(GLint *) viewport);
    width = viewport[2];
    height = viewport[3];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

    glViewport(0,0,width>>1,height>>1);
    red.glColor();
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glDepthFunc(GL_LESS);
    glutSolidSphere(1.0,10,10);

    glViewport(0,0,width,height);
    glRasterPos2i(0,0);

    cout << width << '\t' << height << '\t';

    GLenum modes[3] = { GL_COLOR, GL_DEPTH, GL_STENCIL};

    blue.glColor();

    for (uint32 i=0; i<3; i++)
    {
        GLuint repetitions = 0;
        Timer timer;

        switch (modes[i])
        {
        case GL_COLOR:
            glDepthFunc(GL_ALWAYS);
            break;

        case GL_DEPTH:
            glDepthFunc(GL_NOTEQUAL);
            break;

        case GL_STENCIL:
             glDepthFunc(GL_LESS);
            break;
        }

        do
        {
            glCopyPixels(0,0,width>>1,height>>1,modes[i]);
            glFinish();

            repetitions++;

        } while (timer.elapsed()<=_maximumSamplePeriod);

        const GLdouble rate = 0.25*repetitions*width*height/timer.elapsed();

        string out;
        sprintf(out,"%u %7.2lfM \t",repetitions,rate*_mill);
        cout << out;
    }

    cout << endl;
 }

bool GlutMain(const vector<string> &arg)
{
    GlutWindow *main = new OpenGLCopySpeed(arg.size()>1 ? atof(arg[1]) : 0.2);
    main->open();
    return true;
}
