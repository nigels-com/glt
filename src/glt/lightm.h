#ifndef GLT_LIGHTM_H
#define GLT_LIGHTM_H

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

/* $Id: lightm.h,v 2.3 2007/05/06 16:46:24 nigels Exp $ */

/*! \file
    \brief OpenGL Lighting Model Class
    \ingroup GLT
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
