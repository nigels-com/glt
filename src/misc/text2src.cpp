#include "text2src.h"

/*! \file
    \brief   Routines for converting data to C/C++ source code
    \ingroup Misc

    $Id: text2src.cpp,v 2.0 2004/02/08 19:44:13 nigels Exp $

    $Log: text2src.cpp,v $
    Revision 2.0  2004/02/08 19:44:13  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:22  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.12  2003/03/06 12:34:47  nigels
    *** empty log message ***

    Revision 1.10  2003/02/07 10:04:38  nigels
    Improved robustness of text2src

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
            size = in.size()+cr*5+dq+1;
        else
            size = in.size()+cr*5+dq+5;

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

            // If we're finished, semicolon,
            // otherwise backslash

            if (i+1<end)
                *(j++) = '\\';
            else
                *(j++) = ';';

            // Next line of output

            *(j++) = '\n';
        }

        // Output is NUL terminated

        *(j++) = 0;

        // Check our sanity

        assert(i==end || i==(end+1));
        assert((j-output.c_str())==output.size());
    }
}

#if 0   // Seems to be bin2src duplicate
//

void
binary2source(ostream &os,istream &is)
{
    // Set hex number output
    os.setf(ios::hex,ios::basefield);

    // Begin array
    os << '{' << endl;

    bool firstTime = true;
    while (is.good() && !is.eof())
    {
        // Read next 16 bytes into buffer

        unsigned char buffer[16];
        is.read(reinterpret_cast<char *>(buffer),16);

        // Query input stream for number of
        // bytes actually read into buffer

        streamsize size = is.gcount();

        // Advance to next line of output, if
        // necessary

        if (size>0 && !firstTime)
        {
            os << ',';
            os << endl;
        }

        // Output bytes in hex
        for (streamsize i=0; i<size; i++)
        {
            os << "0x" << setw(2) << setfill('0') << static_cast<unsigned int>(buffer[i]);

            // Output commas between each byte
            if (i<size-1)
                os << ',';
        }

        // Now that we have written some output,
        // each new line of output needs a comma
        // and endline

        firstTime = false;

    }

    // End array
    os << endl << "};" << endl;
}

#endif
