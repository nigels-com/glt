#ifndef GLT_FONT_H
#define GLT_FONT_H

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
    \brief OpenGL Font Interface
    \ingroup GLT

    $Id: font.h,v 2.0 2004/02/08 19:44:11 nigels Exp $

    $Log: font.h,v $
    Revision 2.0  2004/02/08 19:44:11  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.18  2003/03/06 12:18:38  nigels
    *** empty log message ***

    Revision 1.17  2003/02/07 09:57:10  nigels
    Added GltChar and GltString

    Revision 1.16  2002/11/27 00:57:28  nigels
    expand

    Revision 1.15  2002/11/07 15:40:44  nigels
    *** empty log message ***

    Revision 1.14  2002/10/07 16:27:46  nigels
    Added CVS version control info


*/

#include <glt/config.h>
#include <glt/gl.h>

//#include <misc/string.h>

class GltFont;

/*! \class GltFont
    \brief Abstract base class for bitmap fonts
    \ingroup GLT
*/

class GltFont
{
public:

    //
    // Constructor/Destructor
    //

    /// Constructor
    GltFont();
    /// Destructor
    virtual ~GltFont();

private:
    /// Private copy constructor to prevent copying
    GltFont(const GltFont &);
    /// Private assignment operator to prevnt copying
    GltFont &operator=(const GltFont &);

public:

    /// Initialise font using current OpenGL context.
    virtual void init(void *) = 0;
    /// Free all OpenGL resources (textures and display lists)
    virtual void clear() = 0;

    /// Print a character at the current OpenGL raster position
    virtual bool print(const GltChar ch) const = 0;
    /// Print a string at the current OpenGL raster position
    virtual bool print(const GltString &str) const = 0;

    /// Get the size (in pixels) of a string
    virtual void size(int &width,int &height,const GltString &str) const;
    /// Get the width of a particular character
    virtual int  width(const GltChar ch) const;

    /// Maximum horizontal distance between characters
    const int hStep()  const;
    /// Maximum vertical distance between characters
    const int vStep()  const;

protected:

    int   _hStep;
    int   _vStep;
    bool  _init;
};

#endif
