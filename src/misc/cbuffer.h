#ifndef MISC_CBUFFER_H
#define MISC_CBUFFER_H

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
    \brief   Templated Circular Buffer Container
    \ingroup Misc
*/

#include <vector>
#include <cassert>

/*! \class   cbuffer
    \brief   Templated Circular Buffer Container
    \ingroup Misc
    \todo    Regression test programs
    \todo    iterator and const_iterator implementation
    \todo    Should objects be deleted as needed, or on demand?
    \todo    Semantics for circular buffer of zero size?
*/

template<class T,class A = std::allocator<T> >
class cbuffer : private std::vector<T,A>
{
private:
    typedef typename std::vector<T,A> parent;

public:

    typedef typename parent::iterator       iterator;
    typedef typename parent::const_iterator const_iterator;
    typedef typename parent::size_type      size_type;

    /*! \brief Construct a circular buffer, specifying the capacity
        \param capacity  Capacity of buffer
        \param def       Default
    */
    cbuffer(const size_type capacity = 0,const T &def = T())
    : _size(0), _full(false)
    {
            parent::reserve(capacity);
            parent::resize(capacity,def);
            _begin = _end = parent::begin();
    }

    /*! \brief Destructor
    */
    ~cbuffer()
    {
    }

    /*! \brief Get the buffer capacity (maximim size)
    */
    size_type capacity() const
    {
        return parent::size();
    }

    /*! \brief Get the buffer size
    */
    size_type size() const
    {
        return _size;
    }

    /// Is the buffer empty?
    bool empty() const
    {
        return !_full && _begin==_end;
    }

    /// Is the buffer full?
    bool full() const
    {
        return _full;
    }

    /*! \brief Push an item to the front of the buffer
        \param x Item to push to the front

        Because the buffer is circular, the last item will
        be overwritten if the buffer is already full.
    */
    void push_front(const T &x)
    {
        if (parent::size())
        {
            decrement(_begin);
            *_begin = x;

            if (_full)
                decrement(_end);
            else
            {
                _size++;
                if (_size==parent::size())
                    _full = true;
            }
        }
    }

    /*! \brief Push an item to the back of the buffer
        \param x Item to push to the back

        Because the buffer is circular, the first item will
        be overwritten if the buffer is already full.
    */
    void push_back(const T &x)
    {
        if (parent::size())
        {
            *_end = x;
            increment((iterator &)_end);
            if (_full)
                increment((iterator &)_begin);
            else
            {
                _size++;
                if (_size==parent::size())
                    _full = true;
            }
        }
    }

    /// Erase the item at the front of the buffer
    void pop_front()
    {
        assert(parent::size());
        assert(_size>0);
        if (_size>0)
        {
            increment((const_iterator &)_begin);
            _size--;
            _full = false;
        }
    }

    /// Erase the item at the back of the buffer
    void pop_back()
    {
        assert(parent::size());
        assert(_size>0);
        if (_size>0)
        {
            decrement((iterator &)_end);
            _size--;
            _full = false;
        }
    }

    /// Access the front item
    T &front()
    {
        assert(parent::size());
        assert(_size>0);
        return *_begin;
    }

    /// Access the front item
    const T &front() const
    {
        assert(parent::size());
        assert(_size>0);
        return *_begin;
    }

    /// Access the back item
    T &back()
    {
        assert(parent::size());
        assert(_size>0);
        iterator i=_end;
        decrement(i);
        return *i;
    }

    /// Access the back item
    const T &back() const
    {
        assert(parent::size());
        assert(_size>0);
        iterator i=_end;
        decrement((const_iterator&)i);
        return *i;
    }

    /// Access the i'th item in the buffer
    T &operator[](const size_type i)
    {
        if (_begin<_end)
            return *(_begin+i);
        else
        {
            const size_type s1 = parent::end()-_begin;
            if (i<s1)
                return *(_begin+i);
            else
                return *(parent::begin()+i-s1);
        }
    }

    /// Access the i'th item in the buffer
    const T &operator[](const size_type i) const
    {
        if (_begin<_end)
            return *(_begin+i);
        else
        {
            const size_type s1 = parent::end()-_begin;
            if (i<s1)
                return *(_begin+i);
            else
                return *(parent::begin()+i-s1);
        }
    }

    /// Shift the contents left
    void leftShift()
    {
        decrement(_begin);
        decrement(_end);
    }

    /// Shift the contents right
    void rightShift()
    {
        decrement(_begin);
        decrement(_end);
    }

    /// Clear the buffer
    void clear()
    {
        _begin = _end = parent::begin();
        _size = 0;
        _full = false;
    }

    /// Swap the contents of this buffer with another
    void swap(cbuffer<T,A> &buffer)
    {
        parent::swap(buffer);
        std::swap(_begin,buffer._begin);
        std::swap(_end  ,buffer._end  );
        std::swap(_size ,buffer._size );
        std::swap(_full ,buffer._full );
    }

    /*! \brief Resize the (capacity) of the buffer
        \param cap new capacity

        If the new buffer capacity is too small for the
        existing contents, only the front-most items will
        remain.
    */
    void resize(const size_type cap)
    {
        if (cap==capacity())
            return;

        cbuffer<T,A> tmp(cap);
        swap(tmp);

        iterator i = tmp._begin;
        iterator j = _begin;
        size_type k=0;

        for (; k<cap && k<capacity() && k<tmp.size(); j++,k++)
        {
            *j = *i;
            tmp.increment((const_iterator &)i);
        }

        _end = j;
        _size = k;
        _full = (_size==cap);
    }

private:

    iterator _begin;
    iterator _end;
    size_type        _size;
    bool             _full;

    /// Increment an iterator, checking for wrap-around
    void increment(const_iterator &i) const
    {
        i++;
        if (i==parent::end())
            i = parent::begin();
    }

    /// Decrement an iterator, checking for wrap-around
    void decrement(const_iterator &i) const
    {
        if (i==parent::begin())
            i += parent::size()-1;
        else
            i--;
    }

    /// Increment an iterator, checking for wrap-around
    void increment(iterator &i)
    {
        i++;
        if (i==parent::end())
            i = parent::begin();
    }

    /// Decrement an iterator, checking for wrap-around
    void decrement(iterator &i)
    {
        if (i==parent::begin())
            i += parent::size()-1;
        else
            i--;
    }
};

#endif

