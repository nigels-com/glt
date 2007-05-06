#ifndef GLT_DLCACHE_H
#define GLT_DLCACHE_H

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

/* $Id: dlcache.h,v 2.6 2007/05/06 16:46:24 nigels Exp $ */

/*! \file
    \brief   Display List Cache
    \ingroup GLT
*/

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <glt/gl.h>
#include <glt/config.h>
#include <glt/error.h>

#include <misc/lru.h>

#ifndef NDEBUG
#include <iostream>
#endif

///////////////////////////// GltDisplayListCache //////////////////////////////////

/*! \class   GltDisplayListCache
    \brief   Display List Cache
    \ingroup GLT
    \todo    When _timeStamp exceeds 2^32, all timestamps should be adjusted!

    Version II OpenGL Display List Cache
    Developed by Nigel Stewart and Stefan Greuter, RMIT University, Sept 2002

    The least recently used display list is reused when:
    1. At least _minAge frames have elapsed since it's last use.
    2. The cache has reached capacity and more than one frame
       has elapsed since it's last use.

    Least recently used display lists are deleted when:
    1. At least _maxAge frames have elapsed since it's last use.

    Therefore, the display lists used in the previous frame will
    always remained cached.  The cache will never contain display
    lists that are older than _maxAge and may retain display lists
    upto an age of _minAge until the cache capacity is reached.
*/

template<class Key>
class GltDisplayListCache
{
public:
    /// Constructor
    GltDisplayListCache(const uint32 capacity = 1000,const uint32 minAge = 100,const uint32 maxAge = 500)
    : _frameNumber(0),
      _enable(true),
      _minAge(minAge),
      _maxAge(maxAge),
      _capacity(capacity)
    {
    }

    /// Destructor
    virtual ~GltDisplayListCache()
    {
        #ifndef NDEBUG
        std::cout << "Cache size: " << _lru.size() << std::endl;
        #endif

        clear();
    }

    /// Draw object with a given ID
    void draw(const Key &id)
    {
        GLERROR;

        // If caching is disbled, draw directly.

        if (!_enable)
        {
            clear();
            OnDraw(id);
            return;
        }

        // Firstly, flush all items that are (very) old and
        // havn't been used for _maxAge frames.

        while (_lru.size() && _frameNumber-_lru.back()._timeStamp>_maxAge)
        {
            const GLuint list = _lru.pop_back()._displayList;
            glDeleteLists(list,1);
        }

        // Secondly, lookup the requested item

        item   *i = _lru.find(id);

        GLERROR;

        if (i)
        {
            // Call the cached Display List

            i->_timeStamp = _frameNumber;
            glCallList(i->_displayList);
        }
        else
        {
            // Age of least-recently used item
            const uint32 age = _lru.size() ? _frameNumber - _lru.back()._timeStamp : 0;

            // OpenGL display list ID
            GLuint list;

            // Recycle an item, if possible and necessary
            if (_lru.size() && age>_minAge || _lru.size()>=_capacity && age>1)
            {
                item &i = _lru.insert(id);
                i._timeStamp = _frameNumber;
                list = i._displayList;
            }
            else
            {
                // Create a new item for the cache
                item i;
                i._displayList = list = glGenLists(1);
                i._timeStamp   = _frameNumber;
                _lru.insert(id,i);
            }

            // Compile and draw the display list

            glNewList(list,GL_COMPILE_AND_EXECUTE);
            OnDraw(id);
            glEndList();
        }

        GLERROR;
    }

    /// Clear the cache
    void clear()
    {
        if (_lru.empty())
            return;

        _frameNumber = 0;

        GLERROR;

        // Free OpenGL display lists

            // (Probably not the fastest way to get the job done,
            //  we really want to iterate through lru and then clear
            //  it in one go...)

        while (_lru.size())
            glDeleteLists(_lru.pop_back()._displayList,1);

        GLERROR;

        // Clear LRU Cache
        _lru.clear();
    }

    /// Callback draw function
    virtual void OnDraw(const Key &id) const = 0;

    /// Called once per frame to reset timer
    GltDisplayListCache &operator++()
    {
        _frameNumber++;
        return *this;
    }


    /// Get the current cache size
    const uint32 size() const         { return _lru.size(); }

    ///
    bool &enable()                    { return _enable;     }

private:

    /// Store the OpenGL display-list index, along with timestamp

    struct item
    {
        GLuint  _displayList;               ///< OpenGL Display List ID
        uint32  _timeStamp;                 ///< Timestamp for frame of last use
    };

    lru<Key,item>   _lru;                   ///< LRU Cache
    uint32          _frameNumber;           ///< Frame number

    // Configuration options

    bool                _enable;
    uint32              _minAge;            ///< Cache for at least this many frames
    uint32              _maxAge;            ///< Cache for this many frames at most
    uint32              _capacity;          ///< Maximum size of cache
};

#endif

