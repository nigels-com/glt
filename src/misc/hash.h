#ifndef MISC_HASH_H
#define MISC_HASH_H

#error OBSOLETE

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
    \brief   Integer Hashing Functions
    \ingroup Math
*/

#include <glt/config.h>

/*!
    \brief      Donald Knuth's 32 bit Mix Function
    \ingroup    Misc
    \param      key     32 bit integer key

    Discussed by Thomas Wang, HP
    http://www.concentric.net/~Ttwang/tech/inthash.htm
*/

inline uint32 hashKnuth32(uint32 key)
{
    // 2654435761 is the golden ratio of 2^32
    return key*2654435761u;
}

/*!
    \brief      Robert Jenkin's 32 bit Mix Function
    \ingroup    Misc
    \param      key     32 bit integer key

    Better variation in low order bits than Knuth's method

    Discussed by Thomas Wang, HP
    http://www.concentric.net/~Ttwang/tech/inthash.htm
*/

inline uint32 hashJenkins32(uint32 key)
{
  key += (key << 12);
  key ^= (key >> 22);
  key += (key << 4);
  key ^= (key >> 9);
  key += (key << 10);
  key ^= (key >> 2);
  key += (key << 7);
  key ^= (key >> 12);
  return key;
}

/*!
    \brief      Thomas Wang's 32 bit Mix Function
    \ingroup    Misc
    \param      key     32 bit integer key

    Better variation in low order bits than Knuth's method

    Discussed by Thomas Wang, HP
    http://www.concentric.net/~Ttwang/tech/inthash.htm
*/

inline uint32 hashWang32(uint32 key)
{
  key += ~(key << 15);
  key ^=  (key >> 10);
  key +=  (key << 3);
  key ^=  (key >> 6);
  key += ~(key << 11);
  key ^=  (key >> 16);
  return key;
}

#endif
