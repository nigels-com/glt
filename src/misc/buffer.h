#ifndef MISC_BUFFER_H
#define MISC_BUFFER_H

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
    \brief   Memory Buffer Interators
    \ingroup Misc

    \note These classes are still experimental
*/

#include <glt/config.h>

#include <cassert>
#include <vector>
#include <string>

typedef std::vector<byte> buffer;

class buffer_iterator;
class const_buffer_iterator;

////////////////////////////////////////////////////////////////////////////////

class buffer_iterator
{
    friend class const_buffer_iterator;

public:

    buffer_iterator();                                  ///< Empty block

    buffer_iterator(void *begin, void *end);            ///<
    buffer_iterator(void *begin, const uint32 size);    ///<

    template<typename T>                                ///< Any native type or struct
    buffer_iterator(T &val)
    : _begin(reinterpret_cast<byte *>(&val)),
      _end(reinterpret_cast<byte *>(&val)+sizeof(T))
    {
    }

    // Specialisations

    #ifdef _MSC_VER
    buffer_iterator(buffer_iterator &i);            ///< Copy constructor
    buffer_iterator(buffer &);                      ///< Specialisation for buffer
    buffer_iterator(char *string);                  ///< C String
    buffer_iterator(std::string &string);           ///< C++ String
    #endif

    ~buffer_iterator();

    // Access

    const bool   empty() const;                     ///< Is the block empty?
    const uint32 size()  const;                     ///< How large is the block (in bytes)

    const bool   valid() const;                     ///< Is current position valid?
    const bool   valid(const byte  *pos) const;     ///< Is a pointer in range?
    const bool   valid(const uint32 pos) const;     ///< Is an index in range?

          byte &operator*();
    const byte &operator*() const;

          byte *pos();
          byte *begin();                            ///<
          byte *end();

    const byte *pos() const;
    const byte *begin() const;
    const byte *end()   const;

          byte &operator[](const uint32 i);
    const byte &operator[](const uint32 i) const;

    void clear(const byte val = 0);

    buffer_iterator &operator++();
    buffer_iterator &operator+=(const uint32 i);

    template<typename T>                        ///< Any native type or struct
    inline T *get(const uint32 offset = 0)
    {
        if ((_pos + offset + sizeof(T))<=_end)
            return reinterpret_cast<const T *>(_pos + offset);

        return NULL;
    }

    template<typename T>                        ///< Any native type or struct
    inline bool read(T &val)
    {
        const uint32 bytes = get(val,0);
        if (bytes>0)
        {
            _pos += bytes;
            return true;
        }
        else
            return false;
    }

//  #ifdef _MSC_VER
//  uint32 get(std::string &string,const uint32 offset); ///< C++ String
//  #endif

private:

    byte *_begin;
    byte *_end;
    byte *_pos;

    #ifdef _MSC_VER
    buffer_iterator(const buffer_iterator &i);          ///< Invalid copy constructor
    buffer_iterator(const_buffer_iterator &block);      ///< Invalid copy constructor
    #endif
};

///////////////////////////////////////////////////////////////////////

class const_buffer_iterator
{
    friend class buffer_iterator;

public:

    const_buffer_iterator();                                        ///< Empty const_buffer_iterator

    const_buffer_iterator(const void *begin, const void *end);      ///<
    const_buffer_iterator(const void *begin, const uint32 size);    ///<

    template<typename T>                                            ///< Any native type or struct
    const_buffer_iterator(const T &val)
    : _begin(reinterpret_cast<const byte *>(&val)),
      _end(reinterpret_cast<const byte *>(&val)+sizeof(T))
    {
    }

    #ifdef _MSC_VER
    const_buffer_iterator(const buffer_iterator       &i);  ///< Copy constructor
    const_buffer_iterator(const const_buffer_iterator &i);  ///< Copy constructor
    const_buffer_iterator(const buffer &);                  ///< Specialisation for buffer
    const_buffer_iterator(const char *string);              ///< C String
    const_buffer_iterator(const std::string &string);       ///< C++ String
    #endif

    ~const_buffer_iterator();

    const bool   empty() const;                     ///< Is the block empty?
    const uint32 size()  const;                     ///< How large is the block (in bytes)

    const bool   valid() const;                     ///< Is current position valid?
    const bool   valid(const byte  *pos) const;     ///< Is a pointer in range?
    const bool   valid(const uint32 pos) const;     ///< Is an index in range?

    const byte &operator*() const;

    const byte *pos() const;
    const byte *begin() const;
    const byte *end()   const;

    const byte &operator[](const uint32 i) const;

    const_buffer_iterator &operator++();
    const_buffer_iterator &operator+=(const uint32 i);

    template<typename T>                        ///< Any native type or struct
    inline const T *get(const uint32 offset = 0)
    {
        if ((_pos + offset + sizeof(T))<=_end)
            return reinterpret_cast<const T *>(_pos + offset);

        return NULL;
    }

    template<typename T>                        ///< Any native type or struct
    inline bool read(T &val)
    {
        const uint32 bytes = get(val,0);
        if (bytes>0)
        {
            _pos += bytes;
            return true;
        }
        else
            return false;
    }

//  #ifdef _MSC_VER
//  const char *get(std::string &string,const uint32 offset); ///< C++ String
//  #endif

private:

    const byte *_begin;
    const byte *_end;
    const byte *_pos;
};

/////////////////////////////////////////////////////////////////

// Note - Would like to have std::vector<T> specialisation,
// but msvc 6 doesn't seem to like that

template<>                                  ///< C++ Vector
inline buffer_iterator::buffer_iterator(buffer &vec)
: _begin(reinterpret_cast<byte *>(&vec[0])),
  _end(reinterpret_cast<byte *>(&vec[0]+vec.size())),
  _pos(reinterpret_cast<byte *>(&vec[0]))
{
}

template<>                                  ///< Copy Constructor
inline buffer_iterator::buffer_iterator(buffer_iterator &v)
: _begin(v._begin),
  _end(v._end),
  _pos(v._pos)
{
}

/*
template<>
inline buffer_iterator::buffer_iterator(char *str)
: _begin(reinterpret_cast<byte *>(str)),
  _end(reinterpret_cast<byte *>(str)+strlen(str)+1),
  _pos(reinterpret_cast<byte *>(str))
{
}
*/

template<>
inline buffer_iterator::buffer_iterator(std::string &str)
: _begin(reinterpret_cast<byte *>(&str[0])),
  _end(reinterpret_cast<byte *>(&str[0])+str.size()+1),
  _pos(reinterpret_cast<byte *>(&str[0]))
{
}

/*
template<>
inline uint32 buffer_iterator::get(std::string &val,const uint32 offset)
{
    byte *i = _pos+offset;

    if (i<_end)
    {
        byte *j = i;
        while (j<_end && *j!='\0')
            j++;

        if (*j=='\0' && j<_end)
        {
            val = std::string(reinterpret_cast<char *>(i),j-i);
            return j-i+1;
        }
    }

    return 0;
}
*/

// Note - Would like to have std::vector<T> specialisation,
// but msvc 6 doesn't seem to like that

template<>                                  ///< C++ Vector
inline const_buffer_iterator::const_buffer_iterator(const buffer &vec)
: _begin(reinterpret_cast<const byte *>(&vec[0])),
  _end(reinterpret_cast<const byte *>(&vec[0]+vec.size())),
  _pos(reinterpret_cast<const byte *>(&vec[0]))
{
}

template<>                                  ///< Copy Constructor
inline const_buffer_iterator::const_buffer_iterator(const const_buffer_iterator &v)
: _begin(v._begin),
  _end(v._end),
  _pos(v._pos)
{
}

template<>                                  ///< Pseudo copy Constructor
inline const_buffer_iterator::const_buffer_iterator(const buffer_iterator &v)
: _begin(v._begin),
  _end(v._end),
  _pos(v._pos)
{
}

/*
template<>
inline const_buffer_iterator::const_buffer_iterator(const char *str)
: _begin(reinterpret_cast<const byte *>(str)),
  _end(reinterpret_cast<const byte *>(str)+strlen(str)+1),
  _pos(reinterpret_cast<const byte *>(str))
{
}
*/

template<>
inline const_buffer_iterator::const_buffer_iterator(const std::string &str)
: _begin(reinterpret_cast<const byte *>(&str[0])),
  _end(reinterpret_cast<const byte *>(&str[0])+str.size()+1),
  _pos(reinterpret_cast<const byte *>(&str[0]))
{
}

/*
template<>
inline uint32 const_buffer_iterator::get(std::string &val,const uint32 offset = 0)
{
    const byte *i = _pos+offset;

    if (i<_end)
    {
        const byte *j = i;
        while (j<_end && *j!='\0')
            j++;

        if (*j=='\0' && j<_end)
        {
            val = std::string(reinterpret_cast<const char *>(i),j-i);
            return j-i+1;
        }
    }

    return 0;
}
*/

#endif
