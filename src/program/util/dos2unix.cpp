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
    \brief   Utility for converting DOS/Windows text files to UNIX
    \ingroup Util
*/

#include <misc/string.h>
#include <misc/file.h>

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

void dos2unix(const vector<string> &files)
{
    for (uint32 i=0; i<files.size(); i++)
    {
        if (isFile(files[i]))
    {
        // Read the file into a string

        string in;

        {
                ifstream is(files[i].c_str(),ios::in|ios::binary);
            readStream(is,in);
        }

            // Convert the string and write it, as long as it is
            // not determined to be a binary file

        if (isBinary(in))
            cout << "Binary:   ";
        else
            if (in.size()>0)
            {
                string out;
                dos2unix(out,in);

                if (in!=out)
                {
                    cout << "Updated:  ";
                        ofstream os(files[i].c_str(),ios::out|ios::binary);
                    writeStream(os,out);
                }
                else
                    cout << "Skipped:  ";
            }
            else
                cout << "Empty:    ";

    }
        else
        {
            cout << "NotFound:  ";
        }

        cout << files[i] << endl;
    }
}

const char *banner =
    "                                           \n"
    "dos2unix                                   \n"
    "                                           \n"
    "UNIX end-of-line conversion tool.          \n"
    "GLT C++ OpenGL Toolkit                     \n"
    "http://www.nigels.com/glt/                 \n"
    "                                           \n"
    "Usage: dos2unix files...                   \n"
    "                                           \n"
    "  Each source file is converted to a       \n"
    "  UNIX style ASCII file.                   \n"
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

    vector<string> files;
    files.insert(files.begin(),arg.begin()+1,arg.end());
    dos2unix(files);

    return true;
}
