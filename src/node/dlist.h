#ifndef NODE_DLIST_H
#define NODE_DLIST_H

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
    \brief   OpenGL Display List Node
    \ingroup Node
*/

#include <glt/gl.h>

#include <node/shape.h>
#include <misc/refcount.h>

///////////////////////////// GltDisplayList ///////////////////////////////////////

/*! \class   GltDisplayListPtr
    \brief   OpenGL Display List Node Pointer
    \ingroup Node
*/

class GltDisplayList;
typedef ReferenceCountPtr<GltDisplayList> GltDisplayListPtr;

/*! \class   GltDisplayList
    \brief   OpenGL Display List Node
    \ingroup Node
*/

class GltDisplayList : public GltShape
{
public:

             GltDisplayList();              ///< Constructor
    virtual ~GltDisplayList();              ///< Destructor

    virtual void draw() const;

    bool defined() const;                   ///< Is the display list defined?

    void newList(GLenum mode = GL_COMPILE); ///< Create or replace the display list
    void endList();                         ///< Complete display list compilation
    void reset();                           ///< Clear the display list

private:

    GLint       _list;
};

#endif
