#ifndef GLT_LIGHTM_H
#define GLT_LIGHTM_H

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
    \brief OpenGL Lighting Model Class
    \ingroup GLT

    $Id: lightm.h,v 1.1 2004/02/08 11:46:28 jgasseli Exp $

    $Log: lightm.h,v $
    Revision 1.1  2004/02/08 11:46:28  jgasseli
    Initial revision

    Revision 1.9  2003/03/06 12:21:05  nigels
    Documentation refinements

    Revision 1.8  2002/11/27 00:57:28  nigels
    expand

    Revision 1.7  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.6  2002/10/07 16:33:35  nigels
    Added CVS info


*/

#include <glt/config.h>
#include <glt/gl.h>

#include <iosfwd>

/*! \class GltLightModel
    \brief OpenGL Lighting Model Class
    \ingroup GLT

    Convenient manipulation of lighting model configuration.
*/

class GltLightModel
{
public:

    GltLightModel(const bool getIt = false);        ///< Constructor
    ~GltLightModel();                               ///< Destructor

    void get();     ///< Get the current OpenGL light model settings
    void set();     ///< Set the current OpenGL light model settings

    void setAmbient    (const GLfloat r,const GLfloat g,const GLfloat b,const GLfloat a); ///< OpenGL ambient lighting (RGBA)
    void setLocalViewer(const GLboolean localViewer);                                     ///< OpenGL local viewer mode
    void setTwoSide    (const GLboolean twoSide);                                         ///< OpenGL two-sided mode

    GLfloat   *ambient();       ///< OpenGL ambient lighting (RGBA)
    GLboolean &localViewer();   ///< OpenGL local viewer mode
    GLboolean &twoSide();       ///< OpenGL two-sided mode

private:

    GLfloat _ambient[4];
    GLboolean  _localViewer;
    GLboolean  _twoSide;
};

#endif
