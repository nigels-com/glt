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
    \brief   Utility for converting text files to C/C++ source
    \ingroup Util
*/

#include <misc/string.h>
#include <misc/file.h>
#include <misc/text2src.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

const char *banner =
    "                                           \n"
    "text2src                                   \n"
    "                                           \n"
    "Text to C/C++ source conversion tool.      \n"
    "GLT C++ OpenGL Toolkit                     \n"
    "http://www.nigels.com/glt/                 \n"
    "                                           \n"
    "Usage: text2src file                       \n"
    "                                           \n";

bool GlutMain(const vector<string> &arg)
{
    uint32 i;
    bool help = false;

    for (i=1; i<arg.size(); i++)
        if (arg[i]=="--help" || arg[i]=="/?")
            help = true;

    if (arg.size()==1 || help)
    {
        cout << banner;
        return false;
    }

    ifstream is(arg[1].c_str());
    text2source(cout,is);

    return true;
}
