#include "registry.h"

/*! \file
    \ingroup Node
*/

#include <glutm/glut.h>

#include <misc/string.h>
#include <math/real.h>

#include <cstdio>
#include <fstream>
using namespace std;

/////////////// GltRegistry /////////////////

GltRegistry::GltRegistry()
{
}

GltRegistry::~GltRegistry()
{
}

void
GltRegistry::set(const GltFieldPtr &root)
{
    _root = root;
}

void
GltRegistry::clear()
{
    _root.clear();
}

void
GltRegistry::reset()
{
    if (_root.get())
        _root->reset();
}

bool
GltRegistry::write(ostream &os,const string &prefix) const
{
    GltFieldPtr ptr = find(prefix);
    if (ptr.get())
    {
        string::size_type end = prefix.rfind('.');
        ptr->write(os,prefix.substr(0,end));
        return true;
    }

    return false;
}

bool
GltRegistry::read(istream &is)
{
    string file;
    readStream(is,file);
    return set(file);
}

bool
GltRegistry::write(const std::string &filename,const string &prefix) const
{
    ofstream os(filename.c_str());
    return write(os,prefix);
}

bool
GltRegistry::read(const std::string &filename)
{
    ifstream is(filename.c_str());
    return read(is);
}

bool
GltRegistry::set(const std::string &name,const std::string &value)
{
    GltFieldPtr ptr = find(name);
    if (ptr.get())
        return ptr->set(value);

    return false;
}

bool
GltRegistry::set(const std::string &settings)
{
    bool ok = true;

    // Split input settings into individual lines

    vector<string> lines;
    stringSplit(lines,settings,"\n");

    // For each line in the file...

    for (uint32 i=0; i<lines.size(); i++)
    {
        // Skip line if it's a comment

        string::size_type comment = lines[i].find_first_of("#");
        comment = MIN(comment,lines[i].find("//"));

        // Find the first colon character

        string::size_type j = lines[i].find_first_of(":");

        // Give up if it doesn't exist

        if (j==string::npos || comment<j)
        {
            ok = false;
            continue;
        }

        // Skip the whitespace after colon

        string::size_type k = lines[i].find_first_not_of(" \t",j+1);

        // Split line into name (full path) and value

        const string name = lines[i].substr(0,j);
        const string val  = (k==string::npos ? "" : lines[i].substr(k));

        // Set the field

        set(name,val);
    }

    return ok;
}

// Find field node by name

GltFieldPtr
GltRegistry::find(const std::string &name) const
{
    // Split the name into full path, using '.'
    // as delimiter

    vector<string> path;
    stringSplit(path,name,".");
    if (name.size()==0 || path.size()==0)
        return _root;

    // Start traversing from the root of the registry

    const GltFields *pos = dynamic_cast<const GltFields *>(_root.get());

    // Check that base name is first entry in path

    if (pos && pos->name()==path[0])
    {
        // Traverse downwards until path is fully resolved
        for (uint32 i=1; pos!=NULL && i<path.size(); i++)
        {
            bool found = false;

            // Check each field for matching name

            for (uint32 j=0; j<pos->_fields.size(); j++)
                if (pos->_fields[j]->name()==path[i])
                {
                    found = true;

                    if (i+1==path.size())
                        return pos->_fields[j];
                    else
                        pos = dynamic_cast<const GltFields *>(pos->_fields[j].get());

                    break;
                }

            // Path does not resolve, give up

            if (!found)
                break;
        }
    }

    return GltFieldPtr();
}

//
// Windows registry interface
//

#ifdef GLT_WIN32

bool
GltRegistry::writeRegistry(const std::string &key) const
{
    HKEY subKey = NULL;
    LONG res = RegCreateKeyEx(HKEY_CURRENT_USER,key.c_str(),0,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&subKey,NULL);

    if(res!=ERROR_SUCCESS)
        return false;

    if (_root.get())
        _root->writeRegistry(subKey);

    if (subKey)
        RegCloseKey(subKey);

    return true;
}

bool
GltRegistry::readRegistry(const std::string &key)
{
    HKEY subKey = NULL;
    LONG res = RegOpenKeyEx(HKEY_CURRENT_USER,key.c_str(),0,KEY_READ,&subKey);

    if(res!=ERROR_SUCCESS)
        return false;

    if (_root.get())
        _root->readRegistry(subKey);

    if (subKey)
        RegCloseKey(subKey);

    return true;
}

#endif

