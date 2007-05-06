#ifndef GLT_CURSOR_H
#define GLT_CURSOR_H

/*
  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2007 Nigel Stewart

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

/* $Id: cursor.h,v 2.2 2007/05/06 16:46:24 nigels Exp $ */

/*! \file
    \brief OpenGL Cursor Interface
    \ingroup GLT
*/

class GltFont;
class GltViewport;

#include <misc/string.h>

/*! \class   GltCursor
    \brief   Cursor position class
    \ingroup GLT

    These functions manage the raster position, and provide
    a wrapper for the OpenGL font routines.

    Part of the Glt C++ OpenGL Library
    http://www.nigels.com/glt/

    \author  Nigel Stewart (nigels@nigels.com)
    \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
*/

class GltCursor
{
public:
    /// Constructor
    GltCursor(const GltFont &font,const GltViewport &area);
    /// Destructor
    ~GltCursor();

    /// Print a string at the current position
    void print(const GltString &str);

private:

    const GltFont     &_font;
    const GltViewport &_area;

    void printLine(const GltString &str);
};

#endif
