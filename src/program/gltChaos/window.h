#ifndef CHAOS_WINDOW_H
#define CHAOS_WINDOW_H

/*

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2001 Nigel Stewart
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

#include <glutm/winexam.h>

#include <glt/color.h>

#include <misc/timer.h>
#include <misc/cbuffer.h>

#include "chaos.h"

class GltChaos : public GlutWindow, private ChaosSystem
{
public:
    GltChaos
    (
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault
    );

   ~GltChaos();

    void OnOpen();
    void OnClose();
    void OnReshape(int w, int h);
    void OnDisplay();
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);

private:

    void nextDemo();
    void prevDemo();
    void redraw();

    GltColor _back;     // Background colour
    GltColor _front;    // Foreground colour

    uint32 _drawn;      // Number of pixels drawn so far
    uint32 _screenSize; // Number of pixels on the screen
    real   _minTime;    // Minimum display time in demo mode
    Timer  _timer;      // Timer

    bool   _saveSeed;   // In 'save seed' mode, output C++ array

    bool   _demoMode;   // In 'demo' mode cyclic through saved configurations
    int    _demoIdx;    // Index of config in demo mode

    bool   _doClear;    // Flag screen-clear

    cbuffer<ChaosSystem> _undo;
    cbuffer<ChaosSystem> _redo;

    static uint32 _demoSeed[];  // Saved configurations
    static char  *_demoID[];    // Book examples
};

#endif

