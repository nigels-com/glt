#ifndef MISC_ENDIAN_H
#define MISC_ENDIAN_H

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
    \brief   Endian conversion routines
    \author  Nigel Stewart (nigels.com@gmail.com)
    \ingroup Misc
    \todo    Endian test program
*/

#include <glt/config.h>

#if !defined(GLT_LITTLE_ENDIAN) && !defined(GLT_BIG_ENDIAN)
#error GLT_LITTLE_ENDIAN or GLT_BIG_ENDIAN is not defined!
#endif

#if defined(GLT_LITTLE_ENDIAN) && defined(GLT_BIG_ENDIAN)
#error GLT_LITTLE_ENDIAN and GLT_BIG_ENDIAN are both defined!
#endif

/*!
    \brief      Flip 32 bit integer
    \ingroup    Misc
*/
inline uint32 flip(const uint32 *v)
{
    const byte *b = (const byte *) v;
    return b[0]<<24 | b[1]<<16 | b[2]<<8 | b[3];
}

inline uint32 flip(const uint32 &v)
{
    return flip(&v);
}

inline uint32 flip(const int32 &v)
{
    return flip(reinterpret_cast<const uint32 *>(&v));
}

/*!
    \brief      Flip 16 bit integer
    \ingroup    Misc
*/
inline uint16 flip(const uint16 *v)
{
    const byte *b = (const byte *) v;
    return b[0]<<8 | b[1];
}

inline uint16 flip(const uint16 &v)
{
    return flip(&v);
}

inline int16 flip(const int16 &v)
{
    return flip(reinterpret_cast<const uint32 *>(&v));
}

/*!
    \brief      Convert little-endian 32 bit integer to local format
    \note       Intel x86 is little-endian
    \ingroup    Misc
*/
inline uint32 littleEndian(const uint32 *v)
{
    #ifdef GLT_LITTLE_ENDIAN
    return *v;
    #endif

    #ifdef GLT_BIG_ENDIAN
    return flip(v);
    #endif
}

/*!
    \brief      Convert little-endian 16 bit integer to local format
    \note       Intel x86 is little-endian
    \ingroup    Misc
*/
inline uint16 littleEndian(const uint16 *v)
{
    #ifdef GLT_LITTLE_ENDIAN
    return *v;
    #endif

    #ifdef GLT_BIG_ENDIAN
    return flip(v);
    #endif
}

/*!
    \brief      Convert little-endian 32 bit integer to local format
    \note       Intel x86 is little-endian
    \ingroup    Misc
*/
inline uint32 littleEndian(const uint32 &v)
{
    #ifdef GLT_LITTLE_ENDIAN
    return v;
    #endif

    #ifdef GLT_BIG_ENDIAN
    return flip(&v);
    #endif
}

/*!
    \brief      Convert little-endian 32 bit integer to local format
    \note       Intel x86 is little-endian
    \ingroup    Misc
*/
inline uint16 littleEndian(const uint16 &v)
{
    #ifdef GLT_LITTLE_ENDIAN
    return v;
    #endif

    #ifdef GLT_BIG_ENDIAN
    return flip(&v);
    #endif
}

/*!
    \brief      Convert big-endian 32 bit integer to local format
    \note       Sparc and Motorolla are big-endian
    \ingroup    Misc
*/
inline uint32 bigEndian(const uint32 *v)
{
    #ifdef GLT_BIG_ENDIAN
    return *v;
    #endif

    #ifdef GLT_LITTLE_ENDIAN
    return flip(v);
    #endif
}

/*!
    \brief      Convert big-endian 16 bit integer to local format
    \note       Sparc and Motorolla are big-endian
    \ingroup    Misc
*/
inline uint16 bigEndian(const uint16 *v)
{
    #ifdef GLT_BIG_ENDIAN
    return *v;
    #endif

    #ifdef GLT_LITTLE_ENDIAN
    return flip(v);
    #endif
}

/*!
    \brief      Convert big-endian 32 bit integer to local format
    \note       Sparc and Motorolla are big-endian
    \ingroup    Misc
*/
inline uint32 bigEndian(const uint32 &v)
{
    #ifdef GLT_BIG_ENDIAN
    return v;
    #endif

    #ifdef GLT_LITTLE_ENDIAN
    return flip(&v);
    #endif
}

/*!
    \brief      Convert big-endian 16 bit integer to local format
    \note       Sparc and Motorolla are big-endian
    \ingroup    Misc
*/
inline uint32 bigEndian(const uint16 &v)
{
    #ifdef GLT_BIG_ENDIAN
    return v;
    #endif

    #ifdef GLT_LITTLE_ENDIAN
    return flip(&v);
    #endif
}

#endif
