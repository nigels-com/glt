#ifndef NODE_REGISTRY_H
#define NODE_REGISTRY_H

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
    \brief   Field heirachy based registry
    \author  Nigel Stewart, RMIT (nigels.com@gmail.com)
    \ingroup Node
    \todo    Make Registry library?  Keybindings?  Scripting?  Undo/Redo?
*/

#include <string>
#include <iosfwd>
#include <list>

#include <node/field.h>
#include <node/fields.h>

class GltRegistryMenu;

///////////////////////////// GltRegistry ///////////////////////////////////////

/*! \class   GltRegistry
    \brief   Field Heirachy Container
    \ingroup Node
*/

class GltRegistry
{
    friend class GltRegistryMenu;

private:

    GltRegistry(const GltRegistry &);               ///< Registry can not be copied
    GltRegistry &operator=(const GltRegistry &);    ///< Registry can not be copied

public:

    GltRegistry();                                  ///< Constructor
    ~GltRegistry();                                 ///< Destructor

    ///

    void set(const GltFieldPtr &root);              ///< Set the root field for the registry
    void reset();                                   ///< Reset the registry
    void clear();                                   ///< Clear the registry

    //
    // I/O
    //

    ///

    bool write(std::ostream &os,const std::string &prefix = "") const;            ///< Write to output stream
    bool read(std::istream &os);                                                  ///< Read from input stream

    bool write(const std::string &filename,const std::string &prefix = "") const; ///< Write to file
    bool read (const std::string &filename);                                      ///< Read from file

#ifdef GLT_WIN32
    bool writeRegistry(const std::string &key) const;                             ///< Write to Windows registry
    bool readRegistry(const std::string &key);                                    ///< Read from Windows registry
#endif

    bool set(const std::string &name,const std::string &value);                   ///< Set field by name
    bool set(const std::string &settings);                                        ///< Set fields from string buffer

private:
    GltFieldPtr               _root;

    GltFieldPtr find(const std::string &name) const;        ///< Find field node by name
};

#endif
