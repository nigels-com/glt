#include "error.h"

#include <string>
#include <iostream>
using namespace std;

#ifdef GLT_WIN32
#include <windows.h>
#endif

/*! \file
    \ingroup GLT

    $Id: error.cpp,v 1.2 2004/02/08 14:13:21 jgasseli Exp $

    $Log: error.cpp,v $
    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.6  2003/05/10 16:58:11  nigels
    Last tweaks for 0.8

    Revision 1.4  2002/11/27 00:57:28  nigels
    expand

    Revision 1.3  2002/11/07 15:40:44  nigels
    *** empty log message ***

    Revision 1.2  2002/10/09 15:09:38  nigels
    Added RCS Id and Log tags


*/

void
gltError(const std::string &message)
{
    #if defined(GLT_WIN32) && 0
    MessageBox(NULL,message.c_str(),"Runtime Error",MB_OK | MB_ICONERROR);
    #else
    cerr << "GLT ERROR: " << message << endl;
    #endif
}

void
gltWarning(const std::string &message)
{
    #if defined(GLT_WIN32) && 0
    MessageBox(NULL,message.c_str(),"Runtime Warning",MB_OK | MB_ICONWARNING);
    #else
    cerr << "GLT WARNING: " << message << endl;
    #endif
}
