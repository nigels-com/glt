#include "text2src.h"

/*! \file
    \brief   Routines for converting data to C/C++ source code
    \ingroup Misc

    $Id: text2src.cpp,v 2.2 2006/07/09 15:13:46 nigels Exp $
*/

#include <misc/string.h>

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

//

void
text2source(ostream &os,istream &is)
{
    // Read input into string
    string text;
    readStream(is,text);

    text2source(os,text);
}

//

void
text2source(ostream &os,const std::string &text)
{
    // Convex input to C source
    string source;
    text2source(source,text);

    // Output C source
    os << source;
}

//

void
text2source(string &output,const string &input)
{
    // If all else fails, output is empty

    output.resize(0);

    // Convert input to UNIX CR convention

    string in;
    dos2unix(in,input);

    // Trivial case - empty string.

    if (in.size()==0)
    {
        output = "\"\";\n";
        return;
    }

    // Copy the input string to the output string

    else
    {
        // This strategy doesn't work for an empty
        // input string.

        assert(in.size());

        const char *begin = in.c_str();
        const char *end   = begin + in.size();

        // Input iterator
        const char *i;

        // Count the carriage returns and double-quotes

        int cr = 0;
        int dq = 0;
        for (i=begin; i<end; i++)
        {
            if (*i=='\n')
                cr++;
            else
                if (*i=='"')
                    dq++;
        }

        // Output size depends on whether input
        // ends with CR

        string::size_type size;

        i--;
        if (*i=='\n')
            size = in.size()+cr*4+dq+2;
        else
            size = in.size()+cr*4+dq+5;

        // Allocate output buffer
        output.resize(size);

        // Check that allocation succeeded, after this
        // we use a pointer with no bounds checking

        assert(output.size()==size);
        if (output.size()!=size)
            return;

        // Output iterator

        char *j = const_cast<char *>(output.c_str());

        // Convert

        for (i=begin; i<end; i++)
        {
            // Open quote for string

            *(j++) = '\"';

            // Copy characters upto end of string or CR

            while (i<end && *i!='\n')
            {
                // Escape double quotes with backslash

                if (*i=='"')
                    *(j++) = '\\';

                *(j++) = *(i++);
            }

            // If CR found, output CR in escaped form

            if (i<end && *i=='\n')
            {
                *(j++) = '\\';
                *(j++) = 'n';
            }

            // Closing quote for string

            *(j++) = '\"';

            // If we're finished: semicolon,

            if (i+1>=end)
                *(j++) = ';';

            // Next line of output

            *(j++) = '\n';
        }

        // Output is NUL terminated

        *(j++) = 0;

        // Check our sanity

        assert(i==end || i==(end+1));
        assert((j-output.c_str())==int(output.size()));
    }
}
