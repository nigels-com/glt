#ifndef GLT_INFO_H
#define GLT_INFO_H

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
    \brief Output OpenGL information
    \ingroup GLT

    $Id: info.h,v 2.1 2004/08/11 05:20:18 nigels Exp $

    $Log: info.h,v $
    Revision 2.1  2004/08/11 05:20:18  nigels
    Updated copyright and removed email address from headers

    Revision 2.0  2004/02/08 19:44:11  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.11  2003/08/05 08:04:02  nigels
    *** empty log message ***

    Revision 1.10  2003/03/06 12:20:35  nigels
    *** empty log message ***

    Revision 1.8  2002/11/27 00:57:28  nigels
    expand

    Revision 1.7  2002/10/07 16:27:46  nigels
    Added CVS version control info

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
