#ifndef GLUTM_MASTER_H
#define GLUTM_MASTER_H

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
    \brief   GlutMaster C++ Wrapper for GLUT
    \ingroup GlutMaster
*/

#include <glutm/config.h>

///////////////////////////// GlutMaster ///////////////////////////////////////

/*! \class   GlutMaster
    \brief   GlutMaster C++ Wrapper for GLUT event loop
    \ingroup GlutMaster
    \author  Nigel Stewart (nigels@nigels.com)
    \author  George Stetten and Korin Crawford (stetten@acpub.duke.edu)

    Adapted from original public domain version by George Stetten and
    Korin Crawford beta version 0.3 - 9/9/97

    Enhancements for GlutMaster
    <ul>
    <li>Make use of C++ standard library</li>
    <li>Idle and tick messages configurable on per-window basis</li>
    <li>Wrappers supplied for GLUT shapes - sphere, cylinder, etc.</li>
    <li>Pre-supplied main() and WinMain() for true portability</li>
    <li>Examiner style window with mouse manipulation via GlutWindowExaminer class</li>
    <li>glutGet() interface supplied via GlutWindow class</li>
    <li>Optional OpenInventor support via GlutWindowInventor class</li>
    <li>Optional Win32 screen saver support</li>
    </ul>

    \todo   SDL backend
    \todo   KDE/Qt backend
    \todo   GTK backend
    \todo   Improve seperation between GlutMaster interface and back-ends
*/

class GlutTimer;
class GlutWindow;
class GlutMenu;

class GlutMaster
{
    friend class GlutTimer;
    friend class GlutWindow;
    friend class GlutMenu;

public:

    /*! \brief      Initialise GLUT
        \note       Manual initialisation of GLUT is optional.
        \note       GLUT can only be initialised once.
        \note       Initialisation should be done before any windows are created.
    */
    static void init();

    /*! \brief      Initialise GLUT with command-line parameters
        \note       Manual initialisation of GLUT is optional.
        \note       GLUT can only be initialised once.
        \note       Initialisation should be done before any windows are created.
    */
    static void init(int argc,char *argv[]);

    /*! \brief      Enter the GLUT event loop
        \note       No windows will receive events until the event loop has started.
        \note       According to GLUT specification, this function never returns.
    */
    static void mainLoop();

    /*! \brief      Determine if any GLUT windows are open
    */
    static bool active();

    //
    // glutGet()
    //

    ///
    static int getScreenWidth();    ///< Get the width of the screen in pixels
    static int getScreenHeight();   ///< Get the height of the screen in pixels
    static int getScreenWidthMm();  ///< Get the width of the screen in mm
    static int getScreenHeightMm(); ///< Get the height of the screen in mm
    static int getElapsedTime();    ///< Get the elapsed time (in sec)

private:

    // GlutMaster internals are hidden from user.
    // The GLUT library is initialised by default,
    // but can be initialised via init(), if necessary

     GlutMaster();                      ///< Singleton class: default construtor is private
     GlutMaster(const GlutMaster &);    ///< Singleton class: copy construtor is private
    ~GlutMaster();                      ///< Singleton class: destructor is private

    static GlutMaster _glutMaster;      ///< GlutMaster is a singleton

    static GlutWindow *currentWindow(); ///< Get a pointer to the current GLUT window

    static void openWindow    (GlutWindow *glutWindow);                  //< Create a window
    static void closeWindow   (GlutWindow *glutWindow);                  //< Close a window
    static void positionWindow(GlutWindow *window,int x,int y);          //< Position a window
    static void reshapeWindow (GlutWindow *window,int width,int height); //< Resize a window
    static void setCursor     (GlutWindow *window,int cursor);           //< Set cursor style

    static void setIdle       (GlutTimer *target,bool idle);                 //< Set idle events
    static void setTick       (GlutTimer *target,unsigned int msec);         //< Set tick events
    static void setTimer      (GlutTimer *target,unsigned int msec,int val); //< Set timer event

    static void postRedisplay (GlutWindow *window); //< Trigger window redraw
    static void swapBuffers   (GlutWindow *window); //< Trigger window swap buffers
    static void fullScreen    (GlutWindow *window); //< Trigger window fullscreen mode
    static void gameMode      (GlutWindow *window); //< Trigger window game mode

    static int  get           (const GlutWindow *window,int info);

    //

    static bool _glutInit;                              //< True once GLUT is intialised
    static void updateModifiers(GlutWindow *window);    //< Update window modifiers

    //
    // All GLUT events are routed through these handlers.
    // They will be passed along to the appropriate window(s) automatically.
    //

    static void OnDisplay();
    static void OnKeyboard(unsigned char key, int x, int y);
    static void OnKeyboardUp(unsigned char key, int x, int y);
    static void OnSpecial(int key, int x, int y);
    static void OnSpecialUp(int key, int x, int y);
    static void OnMenu(int value);
    static void OnMotion(int x, int y);
    static void OnMouse(int button, int state, int x, int y);
    static void OnPassiveMotion(int x, int y);
    static void OnJoystick(unsigned int buttonMask, int x, int y, int z);
    static void OnEntry(int state);
    static void OnReshape(int w, int h);
    static void OnVisibility(int visible);

    //

    static void CheckShutdown(int val);
    static void CheckOnOpen  (int val);
    static void CheckOnClose (int val);
};

#endif



