#include <glutm/main.h>
#include <glutm/window.h>
#include <glutm/glut.h>
#include <glutm/shape.h>

#include <glt/gl.h>
#include <glt/buffer.h>
#include <glt/rgb.h>

#include <misc/string.h>

#include <iostream>
using namespace std;

class GlutWindowCSGVolume : public GlutWindow
{
public:
    GlutWindowCSGVolume(int width,int height,int slices,int stacks);
   ~GlutWindowCSGVolume();

   void OnOpen();
   void OnClose();
   void OnDisplay();

private:

    GlutSphere _sphere;
};

GlutWindowCSGVolume::GlutWindowCSGVolume(int width,int height,int slices,int stacks)
: GlutWindow("OpenGL Z-Buffer Volume Calculation",width,height)
{
    _sphere.color()  = yellow;
    _sphere.slices() = slices;
    _sphere.stacks() = stacks;
}

GlutWindowCSGVolume::~GlutWindowCSGVolume()
{
}

void
GlutWindowCSGVolume::OnOpen()
{
    GlutMenu &save = _leftButtonMenu.subMenu();
    save.addEntry("RGB"     ,MENU_CAPTURE_RGB);
    save.addEntry("z-buffer",MENU_CAPTURE_ZBUFFER);

    _leftButtonMenu.addEntry("Save PPM",save);
    _leftButtonMenu.addEntry("Close" ,MENU_CLOSE);
    _leftButtonMenu.attach();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearDepth(1.0);
    glDepthRange(0.0,1.0);
    glLoadIdentity();

    black.glClearColor();

    cout << "Volume\twidth\theight\tslices\tstacks\tvolume" << endl;
}

void
GlutWindowCSGVolume::OnClose()
{
    _leftButtonMenu.detach();
}

void
GlutWindowCSGVolume::OnDisplay()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glCullFace(GL_BACK);
    _sphere.draw();
    GltFrameBufferZFloat front;

    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);
    _sphere.draw();
    GltFrameBufferZFloat back;

    double vol = 0.0;
    for (uint32 i=0; i<front.size(); i++)
            vol += front[i]-back[i];

    // Scale each pixel volume by width and height of
    // viewport pixel, scale depth from [0,1] to [-1,1]

    vol *= (2.0*2.0*2.0)/(front.width()*front.height());

    cout << _sphere.volume() << '\t';
    cout << front.width() << '\t';
    cout << front.height() << '\t';
    cout << _sphere.slices() << '\t';
    cout << _sphere.stacks() << '\t';
    cout << vol << endl;
}

// OpenGL program for calculating the volume of
// a unit sphere.  The triangle mesh of points on
// the sphere surface will always underestimate
// the volume of the true analytic shape.  Note that
// the viewport size makes little difference to
// the the answer. (Less than 1%)

bool GlutMain(const std::vector<std::string> &arg)
{
    int width = 400;
    int height = 400;
    int slices = 40;
    int stacks = 40;

    if (arg.size()==5)
    {
        width = atoi(arg[1]);
        height = atoi(arg[2]);
        slices = atoi(arg[3]);
        stacks = atoi(arg[4]);
    }
    else
    {
        cout << endl;
        cout << "volume" << endl;
        cout << endl;
        cout << "Usage: volume width height slices stacks" << endl;
        cout << endl;
    }

    static GlutWindow *main = new GlutWindowCSGVolume(width,height,slices,stacks);
    main->open();

    return true;
}
