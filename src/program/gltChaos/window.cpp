/*
  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2007 Nigel Stewart

  WWW:    http://www.nigels.com/glt/
  Forums: http://sourceforge.net/forum/?group_id=36869

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

#include "window.h"
#include "chaos.h"
#include "svg.h"

#include <glt/rgb.h>
#include <glt/buffer.h>

#include <ctime>
#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

GltChaos::GltChaos(int width,int height,int x,int y)
: GlutWindow("gltChaos",width,height,x,y,GLUT_SINGLE|GLUT_RGBA),
   _back(black),
   _front(white),
   _drawn(0),
   _screenSize(0),
   _minTime(5.0),
   _saveSeed(false),
   _demoMode(true),
   _demoIdx(-1),
   _doClear(false)
{
    _undo.resize(100);
    _redo.resize(100);
}

GltChaos::~GltChaos()
{
}

void
GltChaos::OnOpen()
{
    setTick(1000/10);
    set();

    if (_demoMode)
        nextDemo();

    enterGameMode();

    glDisable(GL_LIGHTING);
    glDrawBuffer(GL_FRONT);

    _back.glClearColor();
    _front.alpha() = 0.15;
    _front.glColor();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    GLERROR
}

void
GltChaos::OnClose()
{
    leaveGameMode();

    if (_saveSeed)
        cout << "\t0 /* last entry must be zero! */" << endl << "};" << endl << endl;

    _saveSeed = false;
}

void
GltChaos::OnReshape(int w, int h)
{
    GlutWindow::OnReshape(w,h);
    _screenSize = w*h;
    _doClear = true;
    _drawn = 0;
    postRedisplay();
}

void
GltChaos::OnVisibility(int visible)
{
    if (visible!=GLUT_FULLY_COVERED)
    {
        _doClear = true;
        _drawn = 0;
        postRedisplay();
    }
}

void
GltChaos::OnDisplay()
{
    if (_doClear)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        _doClear = false;
    }

    if (_drawn<(_screenSize<<1))
    {
        const uint32 n = (_screenSize>>6)+1;
        draw(n);
        _drawn += n;
    }
    else
    {
        if (_demoMode && _timer.elapsed()>_minTime)
            nextDemo();
    }

    glFlush();
}

void
GltChaos::OnKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'm':
        _undo.push_front(*this);
        _redo.clear();
        mutate(0.001);
        _doClear  = true;
        _demoMode = false;
        redraw();
        break;

    case 'M':
        _undo.push_front(*this);
        _redo.clear();
        mutate(0.005);
        _doClear  = true;
        _demoMode = false;
        redraw();
        break;

    case 'u':
        if (_undo.size())
        {
            _redo.push_front(*this);
            *((ChaosSystem *) this) = _undo.front();
            _undo.pop_front();
            _doClear  = true;
            _demoMode = false;
            findSize();
            redraw();
        }
        break;

    case 'r':
        if (_redo.size())
        {
            _undo.push_front(*this);
            *((ChaosSystem *) this) = _redo.front();
            _redo.pop_front();
            _doClear  = true;
            _demoMode = false;
            findSize();
            redraw();
        }
        break;

    case ' ':
        {
            _undo.push_front(*this);
            _redo.clear();

            // You'll never see the same thing twice
            set(time(NULL)^_random.base().rand());

            _doClear  = true;
            _demoMode = false;
            redraw();
            break;
        }

    case '/':
        {
            if (!_saveSeed)
            {
                cout << "uint32 GltChaos::_demoSeed[] = {" << endl;
                _saveSeed = true;
            }

            cout << '\t' << lastSeed() << ',' << endl;
            break;
        }

    case 13:
        {
            _demoMode = true;
            nextDemo();
            break;
        }

    case 's':
        {
#if 1
            //Set up a FBO with one renderbuffer attachment
            
            GLuint framebuffer;
            glGenFramebuffersEXT(1, &framebuffer);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
        
            const GLuint texWidth = 1024;
            const GLuint texHeight = 768;

            GLuint renderbuffer;
            glGenRenderbuffersEXT(1, &renderbuffer);
            glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbuffer);
            glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB, texWidth, texHeight);
            glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,GL_RENDERBUFFER_EXT, renderbuffer);
        
            printf("renderbuffer=%d\n",renderbuffer);
            
            GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);    
            assert(status==GL_FRAMEBUFFER_COMPLETE_EXT);
        
            glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
            glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);

            GltViewport viewport;
            viewport.get();

            glViewport(0,0,texWidth,texHeight);
            glClear(GL_COLOR_BUFFER_BIT);
            draw((texWidth*texHeight)<<1);

#endif
            // Get the frame buffer

            GltFrameBufferRGB rgb;
            rgb.read();

#if 1
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            glDeleteRenderbuffersEXT(1, &renderbuffer);
            glDeleteFramebuffersEXT(1, &framebuffer);

            glDrawBuffer(GL_FRONT);
            viewport.set();
#endif

            string filename;
            sprintf(filename,"%u.png",lastSeed());

            #ifdef GLT_PNG
            // Write PNG file
            ofstream os(filename.c_str(),ios::binary);
            rgb.writePNG(os);
            #else
            // Write PPM file
            ofstream os(filename.c_str(),ios::binary);
            rgb.writePPM(os);
            #endif

            break;
        }

    case 'S':
        {
#if 0
            string filename;
            sprintf(filename,"%u.svg",lastSeed());

            ofstream os(filename.c_str());
            SvgOutput svg(os,100,100);
            svg.defCircle("p",0.1,"black");
            output(svg,"p",40000);
#endif

#if 0
            const int width  = 1024;
            const int height = 1024;
#else
            const int width  = 2048;
            const int height = 2048;
#endif

            unsigned int *image = new unsigned int [width*height];
            std::memset(image,0,width*height*sizeof(unsigned int));

            double minx,miny,maxx,maxy;
            size(minx,miny,maxx,maxy);

            draw(image,width,height,minx,miny,maxx,maxy,width*height*200);

            unsigned int limit = 0;
            for (unsigned int i=0; i<width*height; ++i)
                limit = std::max(limit,image[i]);

            std::string tmp;
            tmp.resize(width*height);
            byte *p = (byte *) tmp.data();

            for (unsigned int i=0; i<width*height; ++i)
                p[i] =(int)  std::floor(std::pow(float(image[i])/limit,0.5f)*255.9);

            std::string data;
            if (encodePNG(data,width,height,tmp))
            {
                string filename;
                sprintf(filename,"%u.png",lastSeed());

                ofstream os(filename.c_str(),ios::binary);
                writeStream(os,data);
            }
            break;
        }

    default:
        GlutWindow::OnKeyboard(key,x,y);
    }
}

void
GltChaos::OnSpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:  prevDemo(); break;
    case GLUT_KEY_RIGHT: nextDemo(); break;
    case GLUT_KEY_HOME:  redraw();   break;
    default:             GlutWindow::OnSpecial(key,x,y);
    }
}

void
GltChaos::nextDemo()
{
    _demoIdx++;
    if (_demoSeed[_demoIdx]==0)
        _demoIdx = 0;

    set(_demoSeed[_demoIdx]);
    redraw();
}

void
GltChaos::prevDemo()
{
    if (_demoIdx>0)
        --_demoIdx;

    set(_demoSeed[_demoIdx]);
    redraw();
}

void
GltChaos::redraw()
{
    _doClear = true;
    _drawn = 0;
    _timer.start();
}

#include <glutm/main.h>

// This is the main entry point for GltChaos,
// since GlutMaster supplies both main() and
// WinMain()

bool GlutMain(const std::vector<std::string> &arg)
{
    cout << endl;
    cout << "gltChaos 0.5" << endl;
    cout << endl;
    cout << "gltChaos" << endl;
    cout << "(C) 2001-2007 Nigel Stewart (nigels@nigels.com)" << endl;
    cout << "Source code available under terms of LGPL." << endl;
    cout << "For updates, source code and information:" << endl;
    cout << "http://www.nigels.com/glt/gltchaos" << endl;
    cout << endl;
    cout << "Usage: gltChaos" << endl;
    cout << endl;

    GlutWindow *main = new GltChaos(440,440,20,20);
    main->open();

    return true;
}

char *GltChaos::_demoID[] = {
    "EBCQAFMFVPXKQ",
    "ECDJXIYLSYQUM",
    "ECVQKGHQTPHTE",
    "EGLXOESFTTPSV",
    "EJXAICXIXFRHI",
    "EMCRBIPOPHTBN",
    "EMDVAIDOYHYEA",
    "EMTGETXEJWCUR",
    "EUEBJLCDISIIQ",
    "EUWACXDQIGKHF",
//  "EVDUOTLRBKTJD",
    "EWLDREDHHWTTN",
    NULL
};

uint32 GltChaos::_demoSeed[] = {
        77993231,
        1367920388,
        1734464951,
        449896995,
        1608616200,
        6100194,
        1678076991,
        84862865,
        322006170,
        245502008,
        1032851705,
        38732865,
        1607223141,
        942357584,
        806031853,
        1118542043,
        526502223,
        9171057,
        1049554245,
        576268943,
        1728374663,
        70271058,
        919444224,
        1313518705,
        2095908727,
        1932699511,
        2137045628,
        2084033392,
        875964408,
        562180277,
        1288638764,
        1387769561,
        561346421,
        275634313,
        438173737,
        653821670,
        1928075777,
        745911728,
        1667943043,
        848924675,
        2142923664,
        974411240,
        939273322,
        931967883,
        1268713683,
        1651472765,
        1762612467,
        787883950,
        1910598941,
        722077720,
        760576209,
        781050842,
        1153301614,
        1967297763,
        1682038299,
        512375186,
        1108518299,
        1080945472,
        698779680,
        210550256,
        1246537736,
        704042755,
        359837679,
        1432335442,
        1897456468,
        1773229015,
        1042422874,
        1395970175,
        901928100,
        933019885,
        1937435613,
        796542755,
        1124364793,
        1192056862,
        1271671742,
        1317084111,
        1994238652,
        1760955900,
        1197886524,
        1036537160,
        543676015,
        972781598,
        917913986,
        1648844483,
        1647324350,
        1607945562,
        1434774064,
        387372366,
        266998280,
        990840118,
        973972004,
        181808783,
        426792858,
        1704956062,
        347069291,
        1095821165,
        1188273686,
        930233478,
        24866928,
        1350381641,
        173568458,
        1256752456,
        657353390,
        955971710,
        473724616,
        407184090,
        1341694783,
        1964167738,
        542160792,
        593149806,
        72530235,
        815723071,
        1265736832,
        101531737,
        1705369886,
        203537024,
        1356607341,
        1249567150,
        1975454626,
        107967241,
        1649293522,
        644044341,
        1370481811,
        1346182987,
        1656734112,
        539601004,
        1327957646,
        1873340503,
        965073776,
        163377600,
        1300218493,
        1394223801,
        1438623892,
        1868223630,
        2101999672,
        723494693,
        461975376,
        1688333660,
        1928300270,
        442170868,
        787262647,
        387017871,
        1127749612,
        210139610,
        1769207883,
        1905666819,
        578816034,
        1629484764,
        1367419204,
        922918752,
        2085500937,
        1208837983,
        15259021,
        1973662093,
        1847799811,
        2078859096,
        1746789634,
        300788629,
        1534596047,
        1845317142,
        1476398144,
        716557490,
        495470154,
        276840454,
        965272359,
        1937641559,
        296653186,
        1168672176,
        1075562751,
        1891794567,
        1617765661,
        1356598331,
        1903143993,
        293635630,
        204707835,
        238914751,
        1430264615,
        625556957,
        1337058307,
        752860935,
        360939994,
        914090603,
        1720949272,
        175080450,
        375136880,
        492272098,
        553600144,
        724845951,
        349060423,
        1541507642,
        1152431939,
        1148428839,
        1199785,
        848074785,
        1161710772,
        601206438,
        226201978,
        1077241010,
        0 /* last entry must be zero! */
};
