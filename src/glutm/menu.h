#ifndef GLUTM_MENU_H
#define GLUTM_MENU_H

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
    \brief   GLUT menu management class
    \ingroup GlutMaster
*/

#include <glutm/config.h>
#include <glutm/glut.h>

#ifdef _MSC_VER
#pragma warning(disable : 4786)     // Lengthy STL symbols
#endif

#include <string>
#include <list>

///////////////////////////// GlutMenu ///////////////////////////////////////

/*! \class   GlutMenu
    \brief   GLUT Menu Class
    \ingroup GlutMaster
    \note    GLUT menu handles are managed automatically by this wrapper.
*/

class GlutMenu
{
public:
    /*!
        \brief      Constructor
        \param      button  Optional mouse-button to bind to.<br>GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON or GLUT_RIGHT_BUTTON
    */
    GlutMenu(int button = GLUT_LEFT_BUTTON);
    /// Destructor
    ~GlutMenu();

    /// Add a menu entry with a menu event ID
    void addEntry(const std::string &name,int value = -1);

    //
    // Sub-menu management
    //

    /*!
        \brief      Create a sub-menu
        \note       Submenus are deleted when the parent menu is destroyed
    */
    GlutMenu &subMenu();

    /// Add a sub-menu
    void addEntry(const std::string &name,GlutMenu &menu);

    /// Clear the contents of the menu
    void reset();

    /// Bind the menu to the mouse button
    void attach();

    /// Dettach the menu from the mouse button
    void detach();

protected:

                                    /// Mouse button to attach/detach
    int  _button;
                                    /// GLUT menu ID
    int  _menuID;

                                    /// Free all resources
    void resetList();
                                    /// List of child menus
    std::list<GlutMenu *> _subMenu;
};

#endif
