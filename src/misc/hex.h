#ifndef MISC_HEX_H
#define MISC_HEX_H

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
    \brief   Hexadecimal (base 16) conversion routines
    \author  Nigel Stewart
    \ingroup Misc
*/

#include <glt/config.h>

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include <string>
#include <cassert>

//
// hex conversion
//

/*!
    \brief      Convert from ASCII character to binary
    \ingroup    Misc
*/
byte fromHex(const char ch);

/*!
    \brief      Convert from ASCII character pair to binary
    \ingroup    Misc
*/
byte fromHex(const char a,const char b);

/*!
    \brief      Convert from 4-bits binary to ASCII character
    \ingroup    Misc
*/
char toHex(const uint32 val);

/*!
    \brief      Convert from 4-bits binary to ASCII character
    \ingroup    Misc
*/
char toHex(const int32 val);

/*!
    \brief      Generic conversion from ASCII hex string
    \ingroup    Misc

    \warning    On failure, return value is uninitialised
*/
template<class T>
T fromHex(const std::string &str)
{
    // Temporary copy, which will be
    // returned once completed

    T tmp;

    // Hex string begins with a prefix of 0x

    std::string::size_type prefix = str.find("0x");

    if (prefix!=std::string::npos)
    {
        // Input buffer begins after the prefix
        const char *begin = str.c_str() + prefix + 2;
        const char *end   = str.c_str() + str.size();

        // Input iterator
        const char *i = begin;

        // Output iterator
        byte *j = reinterpret_cast<byte *>(&tmp);

        // Iterate through our input string,
        // each pair corresponds to one byte

        for (uint32 k=0; k<sizeof(T) && i+1<end; i+=2, j++, k++)
            *j = fromHex(*i,*(i+1));
    }

    return tmp;
}

/*!
    \brief      Generic conversion to ASCII hex string
    \ingroup    Misc
*/
template<class T>
std::string toHex(const T &val)
{
    // Temporary string for output
    std::string tmp;

    // Size is two characters per byte
    // plus two byte prefix

    const std::string::size_type size = 2+sizeof(val)*2;
    tmp.resize(size);

    // Check that output buffer has been
    // allocated correctly
    assert(tmp.size()==size);
    if (tmp.size()!=size)
        return std::string();

    // Input iterator
    const byte *i = reinterpret_cast<const byte *>(&val);

    // Output iterator
    char *j = &tmp[0];

    // Prefix
    *(j++) = '0';
    *(j++) = 'x';

    // Traverse input and convert to ASCII hex characters
    for (uint32 k=0; k<sizeof(val); i++,k++)
    {
        *(j++) = toHex(static_cast<uint32>(*i)>>4);
        *(j++) = toHex(static_cast<uint32>(*i)&15);
    }

    // All done
    return tmp;
}

#endif
