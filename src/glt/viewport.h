#ifndef GLT_VIEWPORT_H
#define GLT_VIEWPORT_H

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

/* $Id: viewport.h,v 2.2 2007/05/06 16:46:24 nigels Exp $ */

/*! \file
    \brief   OpenGL Viewport Class
    \ingroup GLT
*/

#include <glt/config.h>
#include <glt/gl.h>

#include <iosfwd>

class GltTexture;
class BoundingBox;

/////////////////////////// GltViewport ////////////////////////////////////

/*! \enum    GltHorizontalAlignment
    \brief   Horizontal alignment
    \ingroup GLT
*/

typedef enum GltHorizontalAlignment
{
    GLT_ALIGN_LEFT = 0,
    GLT_ALIGN_HCENTER,
    GLT_ALIGN_RIGHT
} GltHorizontalAlignment;

/*! \enum    GltVerticalAlignment
    \brief   Vertical alignment
    \ingroup GLT
*/

typedef enum GltVerticalAlignment
{
    GLT_ALIGN_TOP = 0,
    GLT_ALIGN_VCENTER,
    GLT_ALIGN_BOTTOM
} GltVerticalAlignment;

/*! \class   GltViewport
    \brief   OpenGL Viewport Class
    \ingroup GLT

    Convenient manipulation of viewport information.
*/

class GltViewport
{
public:

    GltViewport(bool getIt = false);                                                ///< Default constructor
    GltViewport(const GltViewport &viewport);                                       ///< Copy constructor
    GltViewport(const GLint x,const GLint y,const GLint width,const GLint height);  ///< Constructor
    ~GltViewport();                                                                 ///< Destructor

    // Get/Set

    GLint &x();                  ///< Left position of viewport
    GLint &y();                  ///< Bottom position of viewport
    GLint &width();              ///< Width of viewport
    GLint &height();             ///< Height of viewport

    const GLint &x() const;      ///< Left position of viewport
    const GLint &y() const;      ///< Bottom position of viewport
    const GLint &width() const;  ///< Width of viewport
    const GLint &height() const; ///< Height of viewport

    operator       GLint *();       ///< Access array of x,y,width and height
    operator const GLint *() const; ///< Access array of x,y,width and height

    bool resize(const GLint width,const GLint height);                             ///< Resize the viewport
    bool resize(const GLint x,const GLint y,const GLint width,const GLint height); ///< Resize the viewport
    bool resize(const GltTexture &texture);                                        ///< Resize the viewport to fit a texture
    bool resize(const BoundingBox &box);                                           ///< Resize the viewport to fit an (image-space) bounding box

    bool align(const GltHorizontalAlignment &align,const GltViewport &window);     ///< Position viewport horizontally, relative to another viewport
    bool align(const GltVerticalAlignment   &align,const GltViewport &window);     ///< Position viewport vertically, relative to another viewport

    bool shrink(const GLint w);                                                    ///< Shrink a viewport by a particular margin (in pixels)

    GltViewport &operator=(const GltViewport &viewport);                           ///< Assignment operator

    // Query

    bool valid() const;                                     ///< Is the viewport a valid size?

    const GLint pixels() const;                             ///< Viewport size, in pixels

    bool operator==(const GltViewport &viewport) const;     ///< Compare viewports
    bool operator!=(const GltViewport &viewport) const;     ///< Compare viewports

    // OpenGL Interface

    void get();                                                                    ///< Get the current OpenGL viewport

    void set() const;                                                              ///< Set the current OpenGL viewport
    void set(const GLint width,const GLint height);                                ///< Set the current OpenGL viewport width and height
    void set(const GLint x,const GLint y,const GLint width,const GLint height);    ///< Set the current OpenGL viewport x, y, width and height

    void drawQuad() const;          ///< Draw a covering quad relative to viewport
    void drawLines() const;         ///< Draw surrounding lines relative to viewport

private:
    GLint _viewport[4];
};

#endif
