/*

  GltLife
  C++ OpenGL Implementation of Conways Game of Life
  http://www.nigels.com/glt/gltlife/

  Based on CAEL 1.5 by Abraham Egnor
  http://www.ugcs.caltech.edu/~abe/cael.html

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2000 Nigel Stewart
  Email: nigels@nigels.com   WWW: http://www.nigels.com/glt/

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

#include <glutm/main.h>
#include "window.h"

#include <iostream>
using namespace std;

bool GlutMain(const std::vector<std::string> &arg)
{
    cout << endl;
    cout << "gltLife" << endl;
    cout << endl;
    cout << "(C) 2001-2002 Nigel Stewart (nigels@nigels.com)" << endl;
    cout << "Source code available under terms of LGPL." << endl;
    cout << "For updates, source code and information:" << endl;
    cout << "http://www.nigels.com/glt/" << endl;
    cout << endl;
    cout << "Usage: gltLife" << endl;
    cout << endl;

    static GlutWindow *main = new GltLifeWindow(440,440,20,20);
    main->open();

    return true;
}

