#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <glt/error.h>

#include <node/skybox.h>

#include <glutm/master.h>
#include <glutm/winexam.h>

#include <misc/file.h>
#include <misc/string.h>

#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

#include "textures.h"

class SkyBoxWindow : public GlutWindowExaminer
{
public:
    SkyBoxWindow
    (
        int                width    = widthDefault,
        int                height   = heightDefault,
        int                x        = xDefault,
        int                y        = yDefault,
        const std::string &location = std::string()
    );

   ~SkyBoxWindow();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);
    void OnMenu(int value);

private:

    void buildMenu();
    void setCurrent();

    GltSkyBox           _skyBox;
    bool                _showWire;

    //

    typedef vector<string> CubeMap;

    vector<CubeMap> _maps;
    uint32          _map;
    uint32          _mapMax;
};

SkyBoxWindow::SkyBoxWindow(int width,int height,int x,int y,const std::string &location)
: GlutWindowExaminer("SkyBox Browser",width,height,x,y,GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH),
  _showWire(false),
  _mapMax(0)
{

    mouseMode() = MODE_MOUSE_LEFT;

    vector<string> dirs,files;
    listFiles(dirs,files,location);

    for (uint32 i=0; i<files.size(); i++)
    {
        string name = pathFilename(files[i]);
        string ext  = pathExtension(files[i]);
        string extL = toLower(ext);

        if (name.size()>0 && (extL=="ppm" || extL=="tga" || extL=="png" || extL=="jpg" || extL=="bmp"))
        {
            const uint32 suffixes = 6;

            const char *suffix[suffixes][6] =
            {
                { "0", "1", "2", "3", "4", "5" },                   // NVIDIA SDK examples
                { "l", "d", "f", "r", "u", "b" },                   // VRML Convention
                { "l", "bt", "f", "r", "t", "b" },                  // Panorama Tools Convention
                { "xneg", "yneg", "zpos", "xpos", "ypos", "zneg" }, // NVIDIA SDK examples
                { "negx", "negy", "posz", "posx", "posy", "negz" }, // NVIDIA SDK examples
                { "bk", "dn", "rt", "ft", "up", "lf" }              // Quake3 and Half-Life
            };

            for (uint32 i=0; i<suffixes; i++)
            {
                const uint32 len = strlen(suffix[i][0]);

                if (name.size()<len)
                    continue;

                if (name.substr(name.size()-len)==string(suffix[i][0]))
                {
                    CubeMap map;
                    map.resize(6);

                    string prefix = name.substr(0,name.size()-len);
                    for (uint32 j=0; j<6 ;j++)
                    {
                        // Form filename
                        sprintf(map[j],"%s%s.%s",prefix.c_str(),suffix[i][j],ext.c_str());

                        // Check that the file is available
                        if (!isFile(path(location,map[j])))
                        {
                            map.clear();
                            break;
                        }

                        // Add location
                        map[j] = path(location,map[j]);
                    }

                    if (map.size()==6)
                        _maps.push_back(map);
                }
            }
        }
    }

    _map = 0;

    if (_maps.size())
        _mapMax = _maps.size();
    else
        _mapMax = 2;
}

SkyBoxWindow::~SkyBoxWindow()
{
}

void
SkyBoxWindow::OnOpen()
{
    buildMenu();
    setCurrent();
}

void
SkyBoxWindow::OnClose()
{
    _skyBox.clear();
}

void
SkyBoxWindow::OnDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _skyBox.solid() = true;
    _skyBox.draw();

    if (_showWire)
    {
        _skyBox.solid() = false;
        _skyBox.draw();
    }

    GLERROR;
}

void
SkyBoxWindow::OnKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        _map = (_map+1)%_mapMax;
        setCurrent();
        break;

    case 'w':
        _showWire = !_showWire;
        break;

    default:
        GlutWindowExaminer::OnKeyboard(key,x,y);
        return;
    }

    postRedisplay();
}

void
SkyBoxWindow::OnSpecial(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:
    case GLUT_KEY_RIGHT:
        _map = (_map+1)%_mapMax;
        setCurrent();
        break;

    case GLUT_KEY_UP:
    case GLUT_KEY_LEFT:
        _map = (_map+_mapMax-1)%_mapMax;
        setCurrent();
        break;

    default:
        GlutWindowExaminer::OnSpecial(key,x,y);
        return;
    }

    postRedisplay();
}

void
SkyBoxWindow::OnMenu(int value)
{
    _map = value%_mapMax;
    setCurrent();
    postRedisplay();
}

void
SkyBoxWindow::buildMenu()
{
    _rightButtonMenu.reset();

    if (_maps.size())
    {
        for (uint32 i=0; i<_maps.size(); i++)
            _rightButtonMenu.addEntry(pathFilename((_maps[i])[0]),i);
    }
    else
    {
        _rightButtonMenu.addEntry("Blue Sky",0);
        _rightButtonMenu.addEntry("Hills",   1);
    }

    _rightButtonMenu.attach();
}

void
SkyBoxWindow::setCurrent()
{
    _skyBox.clear();

    if (_maps.size())
    {
        assert(_maps[_map].size()==6);

        const CubeMap &map = _maps[_map];

        cout << map[0] << endl;

        _skyBox.negativeX().init(map[0]);
        _skyBox.negativeY().init(map[1]);
        _skyBox.negativeZ().init(map[2]);
        _skyBox.positiveX().init(map[3]);
        _skyBox.positiveY().init(map[4]);
        _skyBox.positiveZ().init(map[5]);
    }
    else
    {
        switch (_map)
        {
            /* Blue Sky textures from OpenGL Feathers */

        case 0:
            _skyBox.negativeX().init(blueskynxTexture);
            _skyBox.negativeY().init(blueskynyTexture);
            _skyBox.negativeZ().init(blueskynzTexture);
            _skyBox.positiveX().init(blueskypxTexture);
            _skyBox.positiveY().init(blueskypyTexture);
            _skyBox.positiveZ().init(blueskypzTexture);
            break;

            /* Hills textures from NVIDIA SDK */

        case 1:
            _skyBox.negativeX().init(hillsnxTexture);
            _skyBox.negativeY().init(hillsnyTexture);
            _skyBox.negativeZ().init(hillsnzTexture);
            _skyBox.positiveX().init(hillspxTexture);
            _skyBox.positiveY().init(hillspyTexture);
            _skyBox.positiveZ().init(hillspzTexture);
            break;

        }
    }
}

#include <glutm/main.h>

bool GlutMain(const std::vector<std::string> &arg)
{
    GlutWindow *main = new SkyBoxWindow(400,400,20,20,arg.size()>1 ? arg[1] : "");
    main->open();

    return true;
}
