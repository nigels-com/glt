#ifndef MISC_COMPRESS_H
#define MISC_COMPRESS_H

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
    \brief   Compression routines
    \ingroup Misc
    \todo    Compression test program(s)
*/

#include <misc/config.h>

#include <string>

/*!
    \brief      Compress memory block using LZF algorithm.
    \ingroup    Misc
    \note       Based on lzf: http://liblzf.plan9.de/
    \note       This algorithm is believed to be patent-free.

    Lzf compression library
    Copyright (c) 2000 Marc Alexander Lehmann <pcg@goof.com>
    An extremely fast/free compression/decompression-method
    http://liblzf.plan9.de/

    Based on ideas by Hermann Vogt, but liblzf is a total
    re-implementation of LZV that is not compatible to the
    original lzv code.
*/
bool compress(std::string  &dest,const std::string &src);

/*!
    \brief      Decompress memory block using LZF algorithm or zLib
    \ingroup    Misc
    \note       Based on lzf: http://liblzf.plan9.de/
    \note       This algorithm is believed to be patent-free.
*/
bool decompress(std::string &dest,const std::string &src);

/*!
    \brief      Decompress memory block using LZF algorithm or zLib
    \ingroup    Misc
    \note       Based on lzf: http://liblzf.plan9.de/
    \note       This algorithm is believed to be patent-free.
    \note       This version is less bullet-proof than via std::string
*/
bool decompress(std::string &dest,const void *src);

//
// ZLib support can be configured
// in misc/config.h
//

#ifdef GLT_ZLIB

/*!
    \brief      Compress memory block using zLib
    \note       Decompress with the generic decompress functions
    \ingroup    Misc
*/
bool compressZLib(std::string &dest,const std::string &src,const int level);

/*!
    \brief      Extract CRC Checksum for memory block
    \ingroup    Misc
*/
uint32 crc32(const std::string &data);

/*!
    \brief      Extract CRC Checksum for memory block
    \ingroup    Misc
*/
uint32 crc32(const void *data,const uint32 bytes);

#endif

#endif
