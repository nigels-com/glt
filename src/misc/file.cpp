#include "file.h"

/*! \file
    \brief   Filesystem utility routines
    \ingroup Misc

    $Id: file.cpp,v 2.1 2004/02/10 13:39:12 nigels Exp $

    $Log: file.cpp,v $
    Revision 2.1  2004/02/10 13:39:12  nigels
    no message

    Revision 1.4  2003/10/08 05:22:53  nigels
    Added file time API

    Revision 1.3  2003/09/19 12:02:14  nigels
    Unix opendir needs non-empty directory

    Revision 1.2  2003/09/16 09:47:29  nigels
    :

    Revision 1.1  2003/09/16 01:45:20  nigels
    Initial file handling API


*/

#include <misc/string.h>

#ifdef GLT_WIN32
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#ifdef GLT_UNIX
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif

using namespace std;

bool isFile(const string &path)
{
    #ifdef GLT_WIN32
    struct _stat buf;
    if (::_stat(path.c_str(),&buf)==0)
        return (buf.st_mode&_S_IFREG)!=0;
    #endif

    #ifdef GLT_UNIX
    struct stat buf;
    if (::stat(path.c_str(),&buf)==0)
        return S_ISREG(buf.st_mode);
    #endif

    return false;
}

bool isDirectory(const string &path)
{
    #ifdef GLT_WIN32
    struct _stat buf;
    if (::_stat(path.c_str(),&buf)==0)
        return (buf.st_mode&_S_IFDIR)!=0;
    #endif

    #ifdef GLT_UNIX
    struct stat buf;
    if (::stat(path.c_str(),&buf)==0)
        return S_ISDIR(buf.st_mode);
    #endif

    return false;
}

void listFiles(vector<string> &dirs,vector<string> &files,const string &dir)
{
    dirs.clear();
    files.clear();

    #ifdef GLT_WIN32
    long h;
    _finddata_t f;

    h = _findfirst(path(dir,"*.*").c_str(),&f);

    while (h!=-1)
    {
        string p = path(dir,f.name);

        if (isDirectory(p))
            dirs.push_back(f.name);

        if (isFile(p))
            files.push_back(f.name);

        if (_findnext(h,&f)==-1)
            break;
    }
    _findclose(h);
    #endif

    #ifdef GLT_UNIX
    DIR *h = opendir(dir.size() ? dir.c_str() : ".");

    while (h)
    {
        struct dirent *entry = readdir(h);
        if (entry)
        {
            string p = path(dir,entry->d_name);

            if (isDirectory(p))
                dirs.push_back(entry->d_name);

            if (isFile(p))
                files.push_back(entry->d_name);
        }
        else
        {
            closedir(h);
            break;
        }
    }
    #endif
}

time_t timeFileModified(const std::string &path)
{
    #ifdef GLT_WIN32
    struct _stat buf;
    if (::_stat(path.c_str(),&buf)==0)
        return buf.st_mtime;
    #endif

    return 0;
}

time_t timeFileCreated(const std::string &path)
{
    #ifdef GLT_WIN32
    struct _stat buf;
    if (::_stat(path.c_str(),&buf)==0)
        return buf.st_ctime;
    #endif

    return 0;
}

time_t timeFileAccess(const std::string &path)
{
    #ifdef GLT_WIN32
    struct _stat buf;
    if (::_stat(path.c_str(),&buf)==0)
        return buf.st_atime;
    #endif

    return 0;
}

