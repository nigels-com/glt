/*

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2000-2001 Nigel Stewart
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

#include <glutm/main.h>
#include <glutm/winexam.h>
#include <glutm/glut.h>

#include <glt/fontasci.h>
#include <glt/rgb.h>

#include <node/text.h>
#include <node/histogrm.h>
#include <fonts/fonts.h>
#include <math/random.h>
#include <misc/string.h>

#include <cstdio>
#include <cstdlib>

class RandomDemo : public GlutWindow
{
public:
    RandomDemo();
    ~RandomDemo();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnTick();

    GltRandomDouble<GltRandomLCG>     _rand1;
    GltRandomDouble<GltRandomLFSRMix> _rand2;

    GltHistogram            _hist1;
    GltHistogram            _hist2;

    GltFontAscii            _font;
    GltTextOverlay          _info1;
    GltTextOverlay          _info2;
};

RandomDemo::RandomDemo()
:
    GlutWindow("GLT Random Numbers",400,400,20,20),
    _info1(_font,_viewport),
    _info2(_font,_viewport)
{
    _hist1.size() = _hist2.size() = 200;
    _hist1.min()  = _hist2.min()  = 0.0;
    _hist1.max()  = _hist2.max()  = 1.0;

    _hist1.color() = yellow;
    _hist2.color() = green;

    _hist1.drawLine() = _hist2.drawLine() = true; // false;

    _info1.color() = yellow;
    _info2.color() = green;
    _info1.alignVertical() = GLT_ALIGN_BOTTOM;
    _info2.alignVertical() = GLT_ALIGN_BOTTOM;
    _info1.alignHorizontal() = GLT_ALIGN_LEFT;
    _info2.alignHorizontal() = GLT_ALIGN_RIGHT;
}

RandomDemo::~RandomDemo()
{
}

void
RandomDemo::OnOpen()
{
    _font.init(vga14Font);

    glDisable(GL_LIGHTING);

    setTick(1000/50); // 50 fps max
}

void
RandomDemo::OnClose()
{
    _font.init(NULL);
}

void RandomDemo::OnDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    _hist1.draw();
    _hist2.draw();

    sprintf(
        _info1.text(),
        "LCG Random Numbers\nSamples:  %8u\nOutliers: %8u\nMin:      %8u\nMax:      %8u",
        _hist1.samples(),
        _hist1.outlyers(),
        _hist1.minCount(),
        _hist1.maxCount());

    sprintf(
        _info2.text(),
        "LFSRMix Random Numbers\nSamples:  %8u\nOutliers: %8u\nMin:      %8u\nMax:      %8u",
        _hist2.samples(),
        _hist2.outlyers(),
        _hist2.minCount(),
        _hist2.maxCount());

    _info1.draw();
    _info2.draw();
}

void RandomDemo::OnTick()
{
    for (int i=0; i<100; i++)
    {
        _hist1.add(_rand1.rand());
        _hist2.add(_rand2.rand());
    }
    postRedisplay();
}

bool GlutMain(const std::vector<std::string> &arg)
{
    GlutWindow *main = new RandomDemo();
    main->open();

    return true;
}

