#ifndef MISC_LRU_H
#define MISC_LRU_H

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
    \brief   Templated LRU (Least Recently Used) Cache
    \ingroup Misc
*/

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <glt/config.h>

#include <cassert>
#include <list>
#include <map>

#ifdef GLT_HASH_MAP
#include <hash_map>
using namespace std;
#endif

/*! \class   lru
    \brief   Templated LRU (Least Recently Used) Cache
    \ingroup Misc
*/

template<class T1,class T2>
class lru
{
public:

    typedef std::list< std::pair<T1,T2> >              List;

    #ifdef GLT_HASH_MAP
    typedef std::hash_map<T1,typename List::iterator>  Index;
    #else
    typedef std::map<T1,typename List::iterator>       Index;
    #endif

    /// Constructor
    lru()
    {
    }

    /// Destructor
    ~lru()
    {
        clear();
    }

    /// Return the current size of container
    const uint32 size() const
    {
        return _list.size();
    }

    /// Is the container empty?
    const bool empty() const
    {
        return _list.empty();
    }

    /// Front most (most recently used) item
    const T2 &front() const
    {
        assert(size());
        return _list.front().second;
    }

    /// Back most (least recently used) item
    const T2 &back() const
    {
        assert(size());
        return _list.back().second;
    }

    /// Pop front item (most recently used)
    const T2 pop_front()
    {
        const T1 id  = _list.front().first;
        _index.erase(id);

        const T2 tmp = _list.front().second;
        _list.erase(_list.begin());
        return tmp;
    }

    /// Pop back item (least recently used)
    const T2 pop_back()
    {
        const T1 id  = _list.back().first;
        _index.erase(id);

        const T2 tmp = _list.back().second;
        _list.erase(--_list.end());

        return tmp;
    }

    /// Recycle last recently used (LRU) item
    T2 &insert(const T1 &first)
    {
        // Check that container is not empty
        assert(size());

        // Check that the item is not already inserted
        assert(!find(first,false));

        // Take the least recently used (LRU) item in the list
        typename List::iterator n = _list.end();
        --n;

        // Move it to front of list
        _list.splice(_list.begin(),_list,n);

        // Remove it from index
        _index.erase(n->first);

        // Replace with current data
        n->first = first;

        // Update index
        _index[first] = n;

        // Return second
        return n->second;
    }

    /// Insert new item
    const T2 &insert(const T1 &first,const T2 &second)
    {
        // Check that the item is not already inserted
        assert(!find(first,false));

        // Insert into list
        _list.push_front(std::make_pair(first,second));

        // Iterator
        typename List::iterator n = _list.begin();

        // Insert into balanced tree index
        _index[first] = n;

        // Return second
        return n->second;
    }

    /// Lookup cached item
    T2 *find(const T1 &first,bool touch = true)
    {
        typename Index::iterator i = _index.find(first);

        if (i==_index.end())
            return NULL;
        else
        {
            // Move node to front of list, if necessary
            if (touch)
            {
                typename List::iterator n = i->second;
                _list.splice(_list.begin(),_list,n);
                return &(_list.front().second);
            }
            else
                return &(i->second->second);
        }
    }

    /// Random access to items
    const T2 &operator[](const uint32 n) const
    {
        assert(_list.size());

        typename List::const_iterator i = _list.begin();
        for (uint32 j=0; j<n-1; j++,i++)
            if (i==_list.end())
                return _list.back().second;

        return i->second;
    }

    /// Erase specific item from cache
    void erase(const T1 &x)
    {
        _index.erase(x);

        for (typename List::iterator i = _list.begin(); i!=_list.end(); i++)
            if (i->first==x)
            {
                _list.erase(i);
                return;
            }
    }

    /// Clear cache
    void clear()
    {
        _index.clear();
        _list.clear();
    }

private:

    List    _list;
    Index   _index;
};

#endif

