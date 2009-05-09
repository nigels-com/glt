//
// Benchmark of glReadPixels for GL_COLOR,GL_STENCIL,GL_DEPTH
//
//
// Prepared by Nigel Stewart, RMIT University, 1999-2003
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

class OpenGLReadWriteSpeed : public GlutWindow
{
public:
    OpenGLReadWriteSpeed(const GLdouble maximumSamplePeriod = 0.5);
   ~OpenGLReadWriteSpeed();

   void OnOpen();
   void OnClose();
   void OnDisplay();

private:

    const GLdouble  _maximumSamplePeriod;

    const static GltString _banner;
    const static GLdouble  _mill;

    typedef struct
    {
        GLenum format;
        GLenum type;
        string name;
    } modeType;

    const static modeType  _modes[11];
};

//////////////////////////////////////////////////////////////////

const GltString OpenGLReadWriteSpeed::_banner =
        "OpenGL glReadPixels/glDrawPixels Benchmark\n"
        "(C) 1999-2003 Nigel Stewart               \n"
        "http://www.nigels.com/research/           \n";

const GLdouble OpenGLReadWriteSpeed::_mill = 1.0/1000000.0;

const OpenGLReadWriteSpeed::modeType OpenGLReadWriteSpeed::_modes[11] =
{
       { GL_DEPTH_COMPONENT,  GL_INT,            "GLint    Depth"   },
       { GL_DEPTH_COMPONENT,  GL_UNSIGNED_INT,   "GLuint   Depth"   },
       { GL_DEPTH_COMPONENT,  GL_SHORT,          "GLshort  Depth"   },
       { GL_DEPTH_COMPONENT,  GL_UNSIGNED_SHORT, "GLushort Depth"   },
       { GL_DEPTH_COMPONENT,  GL_FLOAT,          "GLfloat  Depth"   },
       { GL_STENCIL_INDEX,    GL_BYTE,           "GLbyte   Stencil" },
       { GL_STENCIL_INDEX,    GL_UNSIGNED_BYTE,  "GLubyte  Stencil" },
       { GL_RGBA,             GL_BYTE,           "GLbyte   RGBA"    },
       { GL_RGBA,             GL_UNSIGNED_BYTE,  "GLubyte  RGBA"    },
       { GL_BGRA,             GL_BYTE,           "GLbyte   BGRA"    },
       { GL_BGRA,             GL_UNSIGNED_BYTE,  "GLubyte  BGRA"    }
};

OpenGLReadWriteSpeed::OpenGLReadWriteSpeed(const GLdouble maximumSamplePeriod)
: GlutWindow("glReadPixels/glDrawPixels Benchmark"),
  _maximumSamplePeriod(maximumSamplePeriod)
{
}

OpenGLReadWriteSpeed::~OpenGLReadWriteSpeed()
{
}

void
OpenGLReadWriteSpeed::OnOpen()
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
}

void
OpenGLReadWriteSpeed::OnClose()
{
    _leftButtonMenu.reset();
}

void
OpenGLReadWriteSpeed::OnDisplay()
{
    GLuint viewport[4];
    GLuint width,height;

    glGetIntegerv(GL_VIEWPORT,(GLint *) viewport);
    width = viewport[2];
    height = viewport[3];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

    glViewport(0,0,width,height);
    red.glColor();
    glDepthFunc(GL_LESS);
    glutSolidSphere(1.0,10,10);

    GLbyte *buffer = new GLbyte[ width*height*sizeof(GLint) ];

    cout << width << ' ' << height << " glReadPixels" << endl;

    for (uint32 i=0; i<11; i++)
    {
        GLuint repetitions = 0;
        Timer timer;

        do
        {
            glReadPixels(0,0,width,height,_modes[i].format,_modes[i].type,buffer);
            glFinish();

            repetitions++;
        }
        while (timer.elapsed()<=_maximumSamplePeriod);

        GLdouble rate = repetitions*width*height/timer.elapsed();

        string info;
        sprintf(info,"%4d % 6.1lfM %s\n",
            repetitions,
            rate*_mill,
            _modes[i].name.c_str());

        cout << info;
    }
    cout << endl;

    cout << width << ' ' << height << " glDrawPixels:" << endl;

    for (uint32 i=0; i<11; i++)
    {
        GLuint repetitions = 0;
        Timer timer;

        glReadPixels(0,0,width,height,_modes[i].format,_modes[i].type,buffer);
        glFinish();
        glRasterPos2i(-1,-1);
        glDepthFunc(GL_ALWAYS);

        if (_modes[i].format==GL_DEPTH_COMPONENT || _modes[i].format==GL_STENCIL_INDEX)
            glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
        else
            glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

        timer.start();

        do
        {
            glDrawPixels(width,height,_modes[i].format,_modes[i].type,buffer);
            glFinish();

            repetitions++;
        }
        while (timer.elapsed()<=_maximumSamplePeriod);

        GLdouble rate = repetitions*width*height/timer.elapsed();

        string info;
        sprintf(info,"%4d % 6.1lfM %s\n",
            repetitions,
            rate*_mill,
            _modes[i].name.c_str());

        cout << info;
    }
    cout << endl;

    delete [] buffer;
}

bool GlutMain(const vector<string> &arg)
{
    GlutWindow *main = new OpenGLReadWriteSpeed(arg.size()>1 ? atof(arg[1]) : 0.2);
    main->open();
    return true;
}
