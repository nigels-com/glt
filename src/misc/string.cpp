#include "string.h"

/*! \file
    \brief   string and wstring utility routines
    \ingroup Misc

    $Id: string.cpp,v 1.1 2004/02/08 11:55:06 jgasseli Exp $

    $Log: string.cpp,v $
    Revision 1.1  2004/02/08 11:55:06  jgasseli
    Initial revision

    Revision 1.30  2003/07/22 03:58:58  nigels
    *** empty log message ***

    Revision 1.29  2003/06/26 09:59:47  nigels
    Strip comments from string added

    Revision 1.28  2003/05/31 12:53:11  nigels
    Added readFile and writeFile

    Revision 1.27  2003/05/31 11:38:50  nigels
    Major speedup for reading large files into std::string

    Revision 1.26  2003/05/10 17:04:23  nigels
    *** empty log message ***

    Revision 1.24  2003/03/06 12:34:47  nigels
    *** empty log message ***

*/

/*! \example string.cpp

    String functionality example and regression test.

    Output:
    \include string.ok
*/

#include <cassert>
#include <cstdlib>
#include <cstdarg>

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

bool isBinary(const std::string &str)
{
    const char *begin = str.c_str();
    const char *end   = begin + str.size();

    for (const char *i=begin; i!=end; i++)
    {
        char c = *i;
        if ((c<32 || c>126) && c!='\t' && c!='\r' && c!='\n')
            return true;
    }

    return false;
}

void stripComments(string &dest,const string &src)
{
    // Break input string into lines

    vector<string> lines;
    stringSplit(lines,src,"\n");

    // Keep track of multi-line comment mode

    bool comment = false;

    // Examine each line, stripping out comments

    vector<string>::iterator i;

    for (i=lines.begin(); i!=lines.end();)
    {
        string &str = (*i);     // For convenience

        // In multi-line comment mode, look for
        // ending, clear all lines inside

        if (comment)
        {
            string::size_type j = str.find("*/");
            if (j==string::npos)
            {
                str = string();
                i++;
            }
            else
            {
                comment = false;
                str = str.substr(j+2);
            }
        }

        // In non multi-line mode, look for
        // one liners and the beginning of
        // a multi-line

        if (!comment)
        {
            string::size_type j;

            j = str.find('#');
            if (j!=string::npos)
                str = str.substr(0,j);

            j = str.find("//");
            if (j!=string::npos)
                str = str.substr(0,j);

            j = str.find("/*");
            if (j!=string::npos)
            {
                // If multi-line ends on same line,
                // strip it out and reprocess this line

                string::size_type k = str.find("*/",j);
                if (k!=string::npos)
                    str = str.substr(0,j) + str.substr(k+2);
                else
                {
                    // Otherwise, go into multi-line mode

                    comment = true;
                    str = str.substr(0,j);
                    i++;
                }
            }
            else
                i++;
        }
    }

    // Examine each line, removing whitespace from front and back

    for (i=lines.begin(); i!=lines.end(); i++)
    {
        string &str = (*i);                         // For convenience
        if (str.size())
        {
            string::size_type j = str.find_first_not_of(" \t");
            string::size_type k = str.find_last_not_of(" \t");
            if (j==string::npos && k==string::npos)
                str = string();
            else
                str = str.substr(j,k+1);
        }

    }

    // Count total size

    uint32 total = 0;
    for (i=lines.begin(); i!=lines.end(); i++)
        if ((*i).size())
            total += 1 + (*i).size();

    // Output

    dest = string();
    dest.reserve(total);

    for (i=lines.begin(); i!=lines.end(); i++)
        if ((*i).size())
            dest += *i + '\n';
}

// Note, would be faster perhaps to use char *
// instead of integer index

void dos2unix(string &dest, const string &src)
{
    // Find the size of the destination string

    string::size_type size = src.size();
    for (string::size_type i=0;i<src.size();i++)
        if (src[i]==13)
            size--;

    // Bail out early, if possible

    if (size==src.size())
    {
        dest = src;
        return;
    }

    // Allocate the correct size for destination

    dest.resize(size);

    // Copy everything except ASCII 13

    string::size_type k = 0;
    for (string::size_type j=0;j<src.size();j++)
        if (src[j]!=13)
            dest[k++] = src[j];

    assert(k==size);
}

void unix2dos(string &dest, const string &src)
{
    // Insert carriage returns, where necessary (ASCII 13)

    // Find the size of the destination string

    string::size_type size = src.size();

    // Take first character into account

    if (src.size()>0)
        if (src[0]==10)
            size++;

    for (string::size_type i=0;i<src.size()-1;i++)
        if (src[i]!=13 && src[i+1]==10)
            size++;

    // Allocate the correct size for destination

    dest.resize(size);

    // Copy everything, inserting linefeeds where necessary

    string::size_type j = 0;
    string::size_type k = 0;

    if (src.size()>0)
        if (src[0]==10)
            dest[k++] = 13;

    for (;j<src.size()-1;j++)
        if (src[j]!=13 && src[j+1]==10)
        {
            dest[k++] = src[j];
            dest[k++] = 13;
        }
        else
            dest[k++] = src[j];

    if (j<src.size())
        dest[k++] = src[j++];

    assert(k==size);
}

#ifdef GLT_UNICODE

void dos2unix(wstring &dest, const wstring &src)
{
    // Remove all instances of carriage return (ASCII 13)

    // Find the size of the destination string

    wstring::size_type size = src.size();
    for (wstring::size_type i=0;i<src.size();i++)
        if (src[i]==13)
            size--;

    // Bail out early, if possible

    if (size==src.size())
    {
        dest = src;
        return;
    }

    // Allocate the correct size for destination

    dest.resize(size);

    // Copy everything except the linefeeds

    wstring::size_type k = 0;
    for (wstring::size_type j=0;j<src.size();j++)
        if (src[j]!=13)
            dest[k++] = src[j];

    assert(k==size);
}


void unix2dos(wstring &dest, const wstring &src)
{
    // Insert carriage returns, where necessary (ASCII 13)

    // Find the size of the destination string

    wstring::size_type size = src.size();

    // Take first character into account

    if (src.size()>0)
        if (src[0]==10)
            size++;

    for (wstring::size_type i=0;i<src.size()-1;i++)
        if (src[i]!=13 && src[i+1]==10)
            size++;

    // Allocate the correct size for destination

    dest.resize(size);

    // Copy everything, inserting linefeeds where necessary

    wstring::size_type j = 0;
    wstring::size_type k = 0;

    if (src.size()>0)
        if (src[0]==10)
            dest[k++] = 13;

    for (;j<src.size()-1;j++)
        if (src[j]!=13 && src[j+1]==10)
        {
            dest[k++] = src[j];
            dest[k++] = 13;
        }
        else
            dest[k++] = src[j];

    if (j<src.size())
        dest[k++] = src[j++];

    assert(k==size);
}
#endif

void readStream(istream &is, string &dest)
{
    vector<char *> buffer;
    vector<uint32> size;
    uint32         total = 0;

    // Read blocks

    while (is.good() && !is.eof())
    {
        const int bufferSize = 10240;

        buffer.push_back(new char [bufferSize]);
        is.read(buffer.back(),bufferSize);

        size.push_back(is.gcount());
        total += size.back();
    }

    // Combine blocks into output buffer

    dest.resize(total);

    for (uint32 i=0,j=0; i<buffer.size(); i++)
    {
        memcpy(&dest[j],buffer[i],size[i]);
        j += size[i];
        delete [] buffer[i];
    }
}

void writeStream(ostream &os, const string &src)
{
    os.write(src.c_str(),src.length());
}

void readFile(const string &filename, string &dest)
{
    ifstream is(filename.c_str(),ios::binary);
    readStream(is,dest);
}

void writeFile(const string &filename,const string &src)
{
    ofstream os(filename.c_str(),ios::binary);
    writeStream(os,src);
}

#ifdef GLT_UNICODE

//
// Read a file into a Unicode string
//
// This function assumes that the file is
// in "normal" Unicode format, as a sequence
// of 16 bit codes.  The BOM (Byte Order
// Marker) is used to detect Unicode, and
// to swap endianess, if necessary.
//

const wchar_t BOM  = 0xFEFF;
const wchar_t BOMe = 0xFFFE;    // Handle opposite endian

void readUnicodeStream(istream &is,wstring &dest)
{
    const int  bufferSize=1024;     // Buffer Size
    wchar_t    buffer[bufferSize];  // Buffer
    bool       firstBlock = true;   // Check header of first block
    bool       swap = false;        // Opposite Endian Origin

    dest = wstring();

    // As long as input stream is good

    while (is.good())
    {
        // Read into buffer and find out
        // how many bytes were read.

        is.read((char *) buffer,bufferSize*sizeof(wchar_t));
        int count = is.gcount()/sizeof(wchar_t);

        // If we read something, lets
        // do some processing.

        if (count)
        {
            // Check the first 16 bits
            // of first block for BOM
            // marker.  If it's in the
            // wrong order, enable swapping

            if (firstBlock)
            {
                if (buffer[0]!=BOM && buffer[0]!=BOMe)
                    return;

                if (buffer[0]==BOMe)
                    swap = true;

                firstBlock = false;
            }

            // If we're in swap mode,
            // swap high and low bytes
            // of each code

            if (swap)
                for (int c=0; c<count; c++)
                    buffer[c] = (buffer[c]<<8)|(buffer[c]>>8);

            // Add the buffer to the
            // Unicode string, ignoring
            // the BOM, if it exists as
            // the first element in the
            // buffer

            if (buffer[0]==BOM)
                dest.append(buffer+1,count-1);
            else
                dest.append(buffer,count);
        }
    }
}

//
// Write a unicode string to a file
//

void writeUnicodeStream(ostream &os,const wstring &src)
{
    os.write(reinterpret_cast<const char *>(&BOM),sizeof(wchar_t));
    os.write(reinterpret_cast<const char *>(src.data()),src.size()*sizeof(wchar_t));
}

void string2wstring(wstring &dest,const string &src)
{
    dest.resize(src.size());

    assert(dest.size()==src.size());
    if (dest.size()!=src.size())
        return;

    for (uint32 i=0; i<src.size(); i++)
        dest[i] = static_cast<unsigned char>(src[i]);
}

void wstring2string(string &dest,const wstring &src)
{
    dest.resize(src.size());
    for (uint32 i=0; i<src.size(); i++)
        dest[i] = src[i] < 256 ? src[i] : ' ';
}

//

// http://www.cl.cam.ac.uk/~mgk25/unicode.html#utf-8
//
// TODO: Support U-10000 onwards

void utf8decode(wstring &dest, const string &src)
{
    int i = 0;
    unsigned char *s = (unsigned char *) src.c_str();

    while (i<src.size())
    {
        const wchar_t c = s[i++];

        // U-0 to U-7F

        if ((c&0x80) == 0x00)
        {
            dest += c;
            continue;
        }

        // U-80 to U-7FF

        if ((c&0xE0) == 0xC0)
        {
            if (i<src.size())
            {
                const wchar_t d = s[i++];
                dest += (c&0x1f)<<6 | (d&0x3f);
                continue;
            }
        }

        // U-800 to U-FFFF

        if ((c&0xF0) == 0xE0)
        {
            if (i+1<src.size())
            {
                const wchar_t d = s[i++];
                const wchar_t e = s[i++];
                dest += (c&0x0f)<<12 | (d&0x3f)<<6 | (e&0x3f);
                continue;
            }
        }
    }
}

#endif

//

void bin2src_(std::ostream &os,bool &begin,const unsigned char *buffer,const int n)
{
    os.setf(ios::hex,ios::basefield);

    if (n>0 && !begin)
    {
        os << ',';
        os << endl;
    }

    begin = false;

    for (int i=0; i<n;i++)
    {
        os << "0x" << setw(2) << setfill('0') << (unsigned int) buffer[i];
        if (i<n-1)
            os << ',';
    }
}

void bin2src(std::ostream &os,const unsigned char *buffer,const int n)
{
    os << '{' << endl;

    bool begin = true;

    for (int i=0; i<n; i+=16)
        if (n-i>16)
            bin2src_(os,begin,buffer+i,16);
        else
            bin2src_(os,begin,buffer+i,n-i);

    os << endl << "};" << endl;
}

void bin2src(std::ostream &os, const std::string &src)
{
    bin2src(os,(const unsigned char *) src.c_str(),src.length());
}

void bin2src(std::ostream &os, std::istream &is)
{
    os << '{' << endl;

    bool begin = true;

    while (is.good() && !is.eof())
    {
        unsigned char buffer[16];
        is.read((char *) buffer,16);

        int size = is.gcount();

        bin2src_(os,begin,buffer,size);
    }

    os << endl << "};" << endl;
}

//

void bin2asm_(std::ostream &os,const unsigned char *buffer,const int n)
{
    if (n<=0)
        return;

    os.setf(ios::hex,ios::basefield);

    os << "\t.byte ";

    for (int i=0; i<n;i++)
    {
        os << "0x" << setw(2) << setfill('0') << (unsigned int) buffer[i];
        if (i<n-1)
            os << ',';
    }

    os << endl;
}

void bin2asm(std::ostream &os,const unsigned char *buffer,const int n)
{
    for (int i=0; i<n; i+=16)
        if (n-i>16)
            bin2asm_(os,buffer+i,16);
        else
            bin2asm_(os,buffer+i,n-i);
}

void bin2asm(std::ostream &os, const std::string &src)
{
    bin2asm(os,(const unsigned char *) src.c_str(),src.length());
}

void bin2asm(std::ostream &os, std::istream &is)
{
    while (is.good() && !is.eof())
    {
        unsigned char buffer[16];
        is.read((char *) buffer,16);
        int size = is.gcount();
        bin2asm_(os,buffer,size);
    }
}

int sprintf(std::string &str,const char *format, ...)
{
    va_list argp;
    va_start(argp, format);

    // TODO - Prevent buffer overrun!

    char buffer[10240];
    int ret = ::vsprintf(buffer,format,argp);
    va_end(argp);

    str.resize(ret);
    memcpy(&str[0],buffer,ret);

    return ret;
}


bool stringSplit(vector<string> &vec,const string &str,const string &delim)
{
    vec.clear();

    if (delim.empty())
    {
        vec.push_back(str);
        return false;
    }

    string::size_type i = 0;
    string::size_type j = 0;

    for (;;)
    {
        j = str.find(delim,i);
        if (j==string::npos)
        {
            vec.push_back(str.substr(i));
            break;
        }

        vec.push_back(str.substr(i,j-i));
        i = j + delim.size();

        if (i==str.size())
        {
            vec.push_back(string());
            break;
        }
    }

    return true;
}

bool stringMerge(const vector<string> &vec, string &str,const string &delim)
{
    str = string();

    for (uint32 i=0; i<vec.size(); i++)
    {
        if (i>0)
            str += delim;

        str += vec[i];
    }

    return true;
}

double atof(const std::string &str) { return atof(str.c_str());                   }
int    atoi(const std::string &str) { return atoi(str.c_str());                   }
long   atol(const std::string &str) { return atol(str.c_str());                   }
bool   atob(const std::string &str) { return atoi(str.c_str())!=0 || str.substr(0,4)=="true"; }
