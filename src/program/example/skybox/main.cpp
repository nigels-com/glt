#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <glutm/master.h>
#include <glutm/winexam.h>

#include <node/skybox.h>

#include <glt/error.h>

#include <algorithm>
#include <iostream>
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

private:

    GltSkyBox           _skyBox;
    bool                _showWire;

    void setCurrent();

    //

    typedef vector<string> CubeMap;

    vector<CubeMap> _maps;
    uint32          _map;
    uint32          _mapMax;
};

#ifdef GLT_WIN32
#include <io.h>
#endif

#include <misc/string.h>

void toLower(string &str)
{
    for (uint32 i=0; i<str.size(); i++)
        str[i] = ::tolower(str[i]);
}

void listFiles(vector<string> &files,const string &dir = string())
{
    files.clear();

    #ifdef GLT_WIN32
    long h;
    _finddata_t f;

    string filespec;
    sprintf
    (
        filespec,
        "%s%s*.*",
        dir.c_str(),
        dir.size() && dir[dir.size()-1]!='\\' ? "\\" : ""
    );

    h = _findfirst(filespec.c_str(),&f);

    while (h!=-1)
    {
        if ((f.attrib&(_A_SUBDIR|_A_SYSTEM))==0)
        {
            files.push_back(f.name);
            toLower(files.back());
        }

        if (_findnext(h,&f)==-1)
            break;
    }
    _findclose(h);
    #endif
}

SkyBoxWindow::SkyBoxWindow(int width,int height,int x,int y,const std::string &location)
: GlutWindowExaminer("SkyBox Browser",width,height,x,y,GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH),
  _showWire(false),
  _mapMax(0)
{
    // Append backslash to location if necessary
    string dir(location);
    if (dir.size() && dir[dir.size()-1]!='\\')
        dir += '\\';

    vector<string> files;
    listFiles(files,dir);

    for (uint32 i=0; i<files.size(); i++)
    {
        // Skip empty filenames
        if (files[i].size()==0)
            continue;
        
        // Skip filenames without extensions
        if (files[i].find('.')==string::npos)
            continue;

        // Break into name and extension
        string name = files[i].substr(0,files[i].find_last_of('.'));
        string ext  = files[i].substr(files[i].find_last_of('.'));

        if (name.size()>0 && (ext==".ppm" || ext==".tga" || ext==".png" || ext==".jpg" || ext==".bmp"))
        {
            const uint32 suffixes = 6;

            const char *suffix[suffixes][6] =
            {
                { "0", "1", "2", "3", "4", "5" },                   // NVIDIA SDK examples
                { "l", "d", "f", "r", "u", "b" },                   // VRML Convention
                { "l", "bt", "f", "r", "t", "b" },                  // Panorama Tools Convention
                { "xneg", "yneg", "zpos", "xpos", "ypos", "zneg" }, // NVIDIA SDK examples
                { "negx", "posy", "posz", "posx", "negy", "negz" }, // NVIDIA SDK examples
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
                        sprintf(map[j],"%s%s%s",prefix.c_str(),suffix[i][j],ext.c_str());

                        // Check that the file is available
                        if (std::find(files.begin(),files.end(),map[j])==files.end())
                        {
                            map.clear();
                            break;
                        }

                        // Add location
                        map[j] = dir + map[j];
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

void
SkyBoxWindow::OnOpen()
{
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

#include <glutm/main.h>

bool GlutMain(const std::vector<std::string> &arg)
{
    GlutWindow *main = new SkyBoxWindow(400,400,20,20,arg.size()>1 ? arg[1] : "");
    main->open();

    return true;
}
