#ifndef GLUTM_WINIV_H
#define GLUTM_WINIV_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2004 Nigel Stewart


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

/*! \file
    \brief   GLUT OpenInventor Window Class
    \ingroup GlutMaster
*/

#include <glutm/master.h>
#include <glutm/window.h>

#ifdef GLUTM_OPEN_INVENTOR

#include <Inventor/SoSceneManager.h>

/*! \class   GlutWindowInventor
    \brief   GLUT OpenInventor Window Class
    \ingroup GlutMaster
*/

class GlutWindowInventor : public GlutWindow, public SoSceneManager
{
    friend GlutMaster;

public:
    GlutWindowInventor(
        const std::string &title = titleDefault,
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault,
        unsigned int displayMode = displayModeDefault
    );
   ~GlutWindowInventor();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnTick();
    void OnReshape(int w, int h);
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);
    void OnMouse(int button, int state, int x, int y);
    void OnMotion(int x, int y);
    void OnPassiveMotion(int x, int y);

private:

    static void initOpenInventor();
    static void inventorTick();

    static bool _initOpenInventor;
};

#endif
#endif
