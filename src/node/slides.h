#ifndef NODE_SLIDES_H
#define NODE_SLIDES_H

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
    \brief   Slideshow Node
    \author  Nigel Stewart, RMIT (nigels@nigels.com)
    \ingroup Node
*/

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <node/sprite.h>
#include <node/shapes.h>
#include <misc/lru.h>

#include <vector>

///////////////////////////// GltSlides ///////////////////////////////////////

/*! \class   GltSlides
    \brief   Slideshow
    \author  Nigel Stewart, RMIT (nigels@nigels.com)
    \ingroup Node
*/

class GltSlides : public GltShape
{
public:
             GltSlides();                           ///< Constructor
    virtual ~GltSlides();                           ///< Destructor

    void push_back(const std::string &filename);    ///< Insert image file
    void push_back(const void *buffer);             ///< Insert image buffer pointer

    void init();                                    ///< Pre-load images
    void clear();                                   ///< Reset slides and release OpenGL resources

    virtual void draw() const;

    void next();                                    ///< Next slide
    void prev();                                    ///< Previous slide

    // User Interface

    void OnKeyboard(unsigned char key, int x, int y); ///< Keyboard event handler
    void OnSpecial(int key, int x, int y);            ///< Special key event handler

    // Get/Set

          uint32 &current();         ///< Current slide
    const uint32 &current() const;   ///< Current slide

    const uint32  size() const;      ///< Total number of slides

          uint32 &cacheSize();       ///< Number of cached slides
    const uint32 &cacheSize() const; ///< Number of cached slides

private:


    std::vector<std::string>         _slideFilename;
    std::vector<const void *>        _slideBuffer;

    bool                             _preload;
    std::vector<GltSprite>           _preloadSprite;

    uint32                           _current;
    uint32                           _cacheSize;
    mutable std::vector<time_t>      _slideFileTime;
    mutable lru<uint32,GltSprite>    _slideCache;

    bool                             _autoScale;
    bool                             _preserveAspectRatio;
    bool                             _blend;
};

#endif
