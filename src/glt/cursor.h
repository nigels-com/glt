#ifndef GLT_CURSOR_H
#define GLT_CURSOR_H

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
    \brief OpenGL Cursor Interface
    \ingroup GLT

    $Id: cursor.h,v 1.2 2004/02/08 14:13:21 jgasseli Exp $

    These functions manage the raster position, and provide
    a wrapper for the OpenGL font routines.

    Part of the Glt C++ OpenGL Library
    http://www.nigels.com/glt/

    \author  Nigel Stewart (nigels@nigels.com)
    \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia

    $Log: cursor.h,v $
    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.11  2003/03/06 12:17:41  nigels
    *** empty log message ***

    Revision 1.10  2003/02/07 09:57:10  nigels
    Added GltChar and GltString

    Revision 1.9  2002/11/27 00:57:28  nigels
    expand

    Revision 1.8  2002/11/07 15:40:44  nigels
    *** empty log message ***

    Revision 1.7  2002/10/07 16:27:46  nigels
    Added CVS version control info


*/

class GltFont;
class GltViewport;

#include <misc/string.h>

/*! \class   GltCursor
    \brief   Cursor position class
    \ingroup GLT
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
