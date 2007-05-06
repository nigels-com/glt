#ifndef GLT_INFO_H
#define GLT_INFO_H

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

/* $Id: info.h,v 2.2 2007/05/06 16:46:24 nigels Exp $ */

/*! \file
    \brief Output OpenGL information
    \ingroup GLT
*/

#include <string>

/// Get OpenGL driver information
std::string GltInfo();

/// Get current date and time
std::string GltDate();

/// Get system info
std::string GltSystemInfo();

/// Get GLT version
std::string GltVersion();

/// Get Extended version information
std::string GltVersionInformation();

#endif
