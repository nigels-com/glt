#ifndef GLT_CONFIG_H
#define GLT_CONFIG_H

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
    \brief GLT Configuration File
    \ingroup GLT

    $Id: config.h,v 2.4 2006/07/01 13:39:43 nigels Exp $
*/

#include <string>

/// GLT Version string
#define GLT_VERSION_STRING "0.8-rc4"

//
// General config options
//

// #define GLT_FAST_FLOAT               // Optional faster math
#define GLT_COLOR_NAMES             // Include string-based color-lookup
//#define GLT_POLYFONTS

#if defined(_MSC_VER) && defined(GLT_POLYFONTS)
#pragma comment(lib, "polyfonts.lib")  // Link against Polyfonts library
#endif

// Windows Config
//

#if defined(_MSC_VER) || defined(__BORLANDC__)

#define GLT_WIN32
#define GLT_LITTLE_ENDIAN

#pragma comment(lib, "opengl32.lib")  // Link against OpenGL library
#pragma comment(lib, "glu32.lib")     // Link against GLU library
#pragma comment(lib, "glt.lib")       // GLT Library
#pragma comment(lib, "glutm.lib")     // GlutMaster Library
#pragma comment(lib, "math.lib")      // GLT Math Library
#pragma comment(lib, "node.lib")      // GLT Node Library
#pragma comment(lib, "fonts.lib")     // GLT Fonts Library
#pragma comment(lib, "mesh.lib")      // GLT Mesh Library
#pragma comment(lib, "misc.lib")      // GLT Misc Library

#endif

//
// Intel/Windows Cygwin Config
//

#if defined(__CYGWIN__)
#define GLT_UNIX
#define GLT_LITTLE_ENDIAN
#endif

//
// Intel/Windows MingW Config
//

#if defined(__MINGW32__)
#define GLT_WIN32
#define GLT_LITTLE_ENDIAN
#endif

//
// Intel Linux Config
//

#if defined(linux) && defined(i386)
#define GLT_UNIX
#define GLT_LITTLE_ENDIAN
#endif

//
// iMac OSX Config
//

#if defined(__APPLE__) && defined(__ppc__)
#define GLT_UNIX
#define GLT_DARWIN
#define GLT_BIG_ENDIAN
#endif

//
// SGI Config
//

#if defined(sgi)
#define GLT_UNIX
#define GLT_SGI
#define GLT_BIG_ENDIAN
#endif

//
// Generic Unix Config
//

#if defined(__UNIX__)
#define GLT_UNIX
#endif

//
// Configure Unicode
//

//#define GLT_UNICODE

/////////////////////////////////////////////////////////////

#if !defined(GLT_WIN32) && !defined(GLT_UNIX)
#error Target not detected, Win32 or Unix.
#endif

#if !defined(GLT_LITTLE_ENDIAN) && !defined(GLT_BIG_ENDIAN)
#error Little-endian (Intel) or Big-endian (Motorolla or Sparc) is not known.
#endif

typedef signed short           int16;   ///< 16 bit signed integer
typedef signed int             int32;   ///< 32 bit signed integer

typedef unsigned char          byte;    ///< 8 bit unsigned char
typedef unsigned short         uint16;  ///< 16 bit unsigned integer
typedef unsigned int           uint32;  ///< 32 bit unsigned integer

// For now, 64-bit integer types are available on i386 Linux
// only...

#if defined(linux) && defined(i386)
typedef long long signed int   int64;   ///< 64 bit signed integer
typedef long long unsigned int uint64;  ///< 64 bit unsigned integer
#endif

#ifdef GLT_FAST_FLOAT
/// GLT real can be float or double
typedef float          real;
#else
/// GLT real can be float or double
typedef double         real;
#endif

#ifdef GLT_UNICODE
typedef wchar_t      GltChar;
typedef std::wstring GltString;
#else
typedef char         GltChar;
typedef std::string  GltString;
#endif

#ifndef NULL
/// NULL pointer
#define NULL (0)
#endif

#define GLT_UNUSED(x) (void)x;

#endif
