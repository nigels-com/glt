#ifndef MISC_TEXT2SRC_H
#define MISC_TEXT2SRC_H

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
    \brief   Routines for converting data to C/C++ source code
    \ingroup Misc
*/

#include <glt/config.h>

#include <iosfwd>
#include <string>

/*!
    \brief      Convert text to C/C++ source code
    \ingroup    Misc

    \param      os      Output stream
    \param      is      Input stream

    \note       On failure, nothing will be written to output
*/
void text2source(std::ostream &os,std::istream &is);

/*!
    \brief      Convert text to C/C++ source code
    \ingroup    Misc

    \param      os      Output stream
    \param      text    Input string for text

    \note       On failure, nothing will be written to output
*/
void text2source(std::ostream &os,const std::string &text);

/*!
    \brief      Convert text to C/C++ source code
    \ingroup    Misc

    \param      source  Output string for source code
    \param      text    Input string for text

    \note       On failure, source will be an empty string
*/
void text2source(std::string &source,const std::string &text);

#if 0   // Seems to be bin2src duplicate
/*!
    \brief      Convert binary data to C/C++ source code
    \ingroup    Misc
*/
void binary2source(std::ostream &os,std::istream &is);
#endif

#endif
