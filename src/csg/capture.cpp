/** \file
 *  \brief Frame-buffer capturing class
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 */

#include "capture.h"

#include <glt/buffer.h>
#include <misc/compress.h>
#include <node/fields.h>
#include <glutm/window.h>

#include <iostream>
using namespace std;

GltBufferCapture::GltBufferCapture(GlutWindow &window)
: _window(window),
  _active(false),
  _countColor(0),
  _countDepth(0),
  _countStencil(0),
  _countColorCRC(0),
  _finished(false)
{
}

GltBufferCapture::~GltBufferCapture()
{
}

bool &GltBufferCapture::active()        { return _active; }

int &GltBufferCapture::countColor()     { return _countColor;    }
int &GltBufferCapture::countDepth()     { return _countDepth;    }
int &GltBufferCapture::countStencil()   { return _countStencil;  }
int &GltBufferCapture::countColorCRC()  { return _countColorCRC; }

bool GltBufferCapture::finished() const { return _finished;     }

void
GltBufferCapture::capture()
{
    if (!_active)
        return;

    bool any = false;

    if (_countColor>0)
    {
        any = true;
        _countColor--;
        _window.OnMenu(GlutWindow::MENU_CAPTURE_RGB);
    }

    if (_countDepth>0)
    {
        any = true;
        _countDepth--;
        _window.OnMenu(GlutWindow::MENU_CAPTURE_ZBUFFER);
    }

    if (_countStencil>0)
    {
        any = true;
        _countStencil--;
        _window.OnMenu(GlutWindow::MENU_CAPTURE_STENCIL);
    }

    if (_countColorCRC>0)
    {
        any = true;
        _countColorCRC--;

        #ifdef GLT_ZLIB
        GltFrameBufferRGB rgb;
        cout << crc32(rgb[0],rgb.size()*3) << endl;
        #endif
    }

    // Check if the last frames have been captured

    if (any && _countColor==0 && _countDepth==0 && _countStencil==0 && _countColorCRC==0)
    {
        _finished = true;
        _active = false;
    }
}

GltFieldPtr
GltBufferCapture::settings()
{
    GltFields *root = new GltFields("capture");

    root->add(_active,        "active");
    root->add(_countColor,    "color");
    root->add(_countDepth,    "depth");
    root->add(_countStencil,  "stencil");
    root->add(_countColorCRC, "colorCRC");

    return root;
}
