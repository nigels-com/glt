#ifndef MISC_STLUTIL_H
#define MISC_STLUTIL_H

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
    \brief   Utility functions for STL containers
    \ingroup Misc
*/

#include <glt/config.h>

#include <vector>
#include <iosfwd>
#include <string>

/*!
    \brief      Shrink std::vector memory buffer to size of contents
    \ingroup    Misc
    \param      v  std::vector to be shrunk
    \todo       deque version

    A little trick to shrink vector
    back to minimum possible size.
    Works on MSVC 6.0 and cygwin gcc 2.95.3-5.
*/

template<class T,class A>
void shrink(std::vector<T,A> &v)
{
    if (v.size()!=v.capacity())
    {
        std::vector<T,A> tmp;
        tmp.reserve(v.size());
        tmp.insert(tmp.begin(),v.begin(),v.end());
        v.swap(tmp);
    }
}

/*!
    \brief      Delete a container of dynamically allocated objects
    \ingroup    Misc
    \param      v  container of pointers
*/

template<class T,class A>
void deleteAll(std::vector<T,A> &v)
{
    // For each pointer, call delete
    typename std::vector<T,A>::iterator i = v.begin();
    while (i!=v.end())
        delete *i;

    // Clear container of dangling pointers
    v.clear();
}

/*!
    \brief      Print std::vector contents to stream
    \ingroup    Misc
    \param      os       Output stream
    \param      v        std::vector to be printed
    \param      delim    Delimiter
*/

template<class T,class A>
std::ostream &print(std::ostream &os,const std::vector<T,A> &v,const std::string &delim = ",")
{
    const int size = v.size();
    for (int i=0; i<size; i++)
    {
        if (i>0)
            os << delim;
        os << v[i];
    }

    return os;
}

#endif
