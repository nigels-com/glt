#ifndef GLUTM_INPUT_H
#define GLUTM_INPUT_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2003 Nigel Stewart

  Email:  nigels@nigels.com
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
    \brief   GLUT Input Receiver Class
    \ingroup GlutMaster
*/

#include <glutm/config.h>
#include <glutm/glut.h>

#include <glt/viewport.h>

/////////////////////////// GlutInput ////////////////////////////////////

/*! \class   GlutInput
    \brief   Base class for GLUT objects that receive keyboard and mouse events
    \ingroup GlutMaster
    \author  Nigel Stewart (nigels@nigels.com)
*/

class GlutInput
{
    friend class GlutMaster;

public:

    GlutInput();                ///< Constructor
    virtual ~GlutInput();       ///< Destructor

    // Callback handlers

    virtual void OnKeyboard(unsigned char key, int x, int y);   ///< Handler for keyboard events
    virtual void OnKeyboardUp(unsigned char key, int x, int y); ///< Handler for keyboard-up events
    virtual void OnSpecial(int key, int x, int y);              ///< Handler for special keyboard events (function keys, etc)
    virtual void OnSpecialUp(int key, int x, int y);            ///< Handler for special keyboard-up events
    virtual void OnMouse(int button, int state, int x, int y);  ///< Handler for mouse button events
    virtual void OnMotion(int x, int y);                        ///< Handler for mouse movement events
    virtual void OnPassiveMotion(int x, int y);                 ///< Handler for passive mouse motion events (no button pressed)
    virtual void OnJoystick(unsigned int buttonMask, int x, int y, int z);  //< Handler for joystick events
};

#endif
