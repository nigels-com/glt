#ifndef NODE_FIELDMEN_H
#define NODE_FIELDMEN_H

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
    \brief   Menu system for field heirachy
    \author  Nigel Stewart, RMIT (nigels.com@gmail.com)
    \ingroup Node
    \todo    Document and rename GltFieldRegistry to Registry?
    \todo    Make Registry library?  Keybindings?  Scripting?  Undo/Redo?
*/

#include <string>
#include <iosfwd>
#include <list>

class GltRegistry;
class GltFields;

///////////////////////////// GltRegistryMenu ///////////////////////////////

/*!
    \class   GltRegistryMenu
    \brief   Field Heirachy Browser
    \ingroup Node

    \todo    Derive from GltShape?
*/

class GltRegistryMenu
{
public:

    GltRegistryMenu(GltRegistry &registry);     ///< Constructor
    ~GltRegistryMenu();                         ///< Destructor

    //

    bool OnKeyboard(unsigned char key, int x, int y);   ///< Keyboard event handler
    bool OnSpecial(int key, int x, int y);              ///< Special key event handler

    //

    void reset();                   ///< Return to root of heirachy
    std::string menu() const;       ///< Current menu state
    bool &active();                 ///< Is the menu currently active?

    //

    /// Set registry entry by name
    bool set(const std::string &name,const std::string &value);

private:

    GltRegistry              &_registry;

    bool                      _active;
    int                       _position;
    GltFields                *_current;

    std::list< std::pair<GltFields *,int> >    _stack;

    bool pop();
    bool push();
};

#endif
