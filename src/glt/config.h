#ifndef GLT_CONFIG_H
#define GLT_CONFIG_H

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
    \brief GLT Configuration File
    \ingroup GLT

    $Id: config.h,v 1.1 2004/02/08 11:46:10 jgasseli Exp $

    $Log: config.h,v $
    Revision 1.1  2004/02/08 11:46:10  jgasseli
    Initial revision

    Revision 1.30  2003/07/22 03:39:08  nigels
    Added compile-time color name lookup option

    Revision 1.29  2003/05/10 17:47:29  nigels
    *** empty log message ***

    Revision 1.28  2003/03/06 12:16:38  nigels
    *** empty log message ***

    Revision 1.26  2003/02/07 09:52:47  nigels
    Added mingw support and optional UNICODE

    Revision 1.25  2002/11/27 00:57:28  nigels
    expand

    Revision 1.24  2002/11/07 15:40:44  nigels
    *** empty log message ***

    Revision 1.23  2002/10/07 16:27:46  nigels
    Added CVS version control info

    Revision 1.22  2002/10/07 16:16:36  nigels
    Mark GLT for "gamma" (nearly 0.7) release version

    Revision 1.21  2002/10/07 16:13:35  nigels
    *** empty log message ***

*/

#include <string>

/// GLT Version string
#define GLT_VERSION_STRING "0.8-rc3"

//
// General config options
//

// #define GLT_FAST_FLOAT               // Optional faster math
#define GLT_COLOR_NAMES             // Include string-based color-lookup

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

/// 8 bit unsigned char
typedef unsigned char  byte;

/// 16 bit unsigned integer
typedef unsigned short uint16;

/// 32 bit unsigned integer
typedef unsigned int   uint32;

/// 16 bit signed integer
typedef signed short   int16;

/// 32 bit signed integer
typedef signed int     int32;

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

#endif
