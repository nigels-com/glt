#ifndef MISC_CONFIG_H
#define MISC_CONFIG_H

/*
  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2007 Nigel Stewart

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

/* $Id: config.h,v 2.3 2007/05/08 04:29:31 nigels Exp $ */

/*! \file
    \brief   GLT Misc configuration file
    \ingroup Misc
    \note    zLib and PNG support can be configured here
*/

#include <glt/config.h>

// GLT_ZLIB                 Define this for zlib support
// GLT_PNG                  Define this for PNG support
// GLT_JPEG                 Define this for JPEG support
// GLT_UNICODE              Define this for UNICODE (wide string) support
// GLT_HASH_MAP             Define this to make use of std::hash_map

// Normally the CMake build system chooses these, but they
// can also be hard-coded here...

//#define GLT_ZLIB
//#define GLT_PNG
//#define GLT_JPEG
//#define GLT_UNICODE
//#define GLT_HASH_MAP

//

// PNG depends on ZLib

#if defined(GLT_PNG) && !defined(GLT_ZLIB)
#define GLT_ZLIB
#endif

// MS Visual C++ compiler has the facility
// to specify libraries at compile-time

#ifdef _MSC_VER
#pragma comment (lib, "advapi32")    // Windows registry interface

#ifdef GLT_ZLIB
#pragma comment(lib, "zlib.lib")      // zLib compression library
#endif

#ifdef GLT_PNG
#pragma comment(lib, "png.lib")      // PNG library
#endif

#ifdef GLT_JPEG
#pragma comment(lib, "jpeg.lib")     // Independent JPEG Group library
#endif

#endif
#endif
