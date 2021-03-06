/*
  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2007 Nigel Stewart

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

/* $Id: bin2src.cpp,v 2.5 2010/06/11 18:27:52 nigels Exp $ */

/*! \file
    \brief   Utility for converting binary data into C/C++ source
    \ingroup Util
*/

#include <iostream>
#include <fstream>
#include <string>

#include <cassert>
#include <cstdlib>
#include <cstring>

using namespace std;

#include <misc/string.h>
#include <misc/hex.h>
#include <misc/compress.h>
#include <misc/image.h>

#include <glt/fontasci.h>
#include <glt/fontunic.h>
#include <glt/texture.h>
#include <glt/info.h>

// Cygwin defines this
#undef unix

bool font2src (ostream &os, const string &name, string &data);
bool ufont2src(ostream &os, const string &name, string &data);
bool image2src(ostream &os, const string &name, string &data);

std::string outputFilename;
std::string inputFilename;
std::string variableName;

bool lzf    = false;
bool zlib   = false;

bool image  = false;
bool alpha  = false;     // Turn greyscale into alpha image
bool mirror = false;
bool flip   = false;

bool jpeg      = false;
uint32 quality = 97;

bool font  = false;
bool ufont = false;

bool unix  = false;
bool dos   = false;

const char *banner =
    "\n"                                           
    "bin2src                                    \n"
    "\n"                                           
    "C/C++ source code generation tool.         \n"
    "GLT C++ OpenGL Toolkit                     \n"
    "http://www.nigels.com/glt/                 \n"
    "\n"                                           
    "Usage: bin2src [OPTION]... SOURCE          \n"
    "\n"                                           
    "  -o file  Output to file instead of cout. \n"
    "  -n name  Variable name.                  \n"
    "  -c       Compress.                       \n"
    "  -font    Convert from VGA font.          \n"
    "  -ufont   Convert from Unicode font.      \n"
    "  -image   Convert from image.             \n"
    "  -mirror  Mirror image horizontally.      \n"
    "  -flip    Flip image vertically.          \n"
    "  -u       Convert to UNIX text.           \n"
    "  -d       Convert to DOS/Windows text.    \n";

bool 
convert(ostream &os)
{
    // Read the file into memory

    string input;
    ifstream is(inputFilename.c_str(),ios::in|ios::binary);
    ::readStream(is,input);

    if (!variableName.length())
    {
      variableName = inputFilename;
      string::size_type i;

      i = variableName.rfind('.');
      if (i!=string::npos)
          variableName.erase(i);

      i = variableName.rfind('/');
      if (i!=string::npos)
          variableName.erase(0,i+1);
    }

    // Convert from PPM image

    if (image)
    {
        bool ok = image2src(os,variableName,input);
        return ok ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    //

    if (font)
    {
        bool ok = font2src(os,variableName,input);
        return ok ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    if (ufont)
    {
        bool ok = ufont2src(os,variableName,input);
        return ok ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    // Convert to DOS or UNIX ascii

    if (unix)
    {
        string tmp;
        dos2unix(tmp,input);
        input = tmp;
    }

    if (dos)
    {
        string tmp;
        unix2dos(tmp,input);
        input = tmp;
    }

    if (lzf || zlib)
    {
        // Compress it into a temporary buffer

        string zip;

        #ifdef GLT_ZLIB
        if (zlib)
            ::compressZLib(zip,input,9);
        else
        #endif
            ::compress(zip,input);

        // Check that it decompresses OK

        #ifndef NDEBUG
        string unzip;
        if (!::decompress(unzip,zip) || input!=unzip)
            os << "/* Compression FAILED! */" << endl;
        #endif

        // Compression info

        os << "/* Compressed data: " << input.size() << " -> " << zip.size() << " */" << endl;

        // Output
        os << "unsigned char " << variableName.c_str() << "[] = " << endl;
        ::bin2src(os,zip);
    }
    else
    {
        os << "unsigned char " << variableName.c_str() << "[] = " << endl;
        ::bin2src(os,input);
    }

    return EXIT_SUCCESS;
}

void
args(std::ostream &os, const int argc, const char * const argv[])
{
    os << "/* ";
    for (int i=0; i<argc; ++i)
        os << argv[i] << ' ';
    os << "*/" << endl;
}

int 
main(int argc,char *argv[])
{
    if (argc==1)
    {
        cout << banner;
        #ifdef GLT_ZLIB
        cout << "  -z       zLib compress." << endl;
        #endif
        #ifdef GLT_JPEG
        cout << "  -j       JPEG compress image." << endl;
        cout << "  -q nn    JPEG quality setting. (10-95)" << endl;
        #endif
        cout << endl;
        cout << GltVersionInformation();

        return EXIT_FAILURE;
    }

    // Parse command-line options

    for (int i=1; i<argc; i++)
    {
        const string &arg = argv[i];

        if (arg=="-o")      { i++; if (i<argc) outputFilename = argv[i]; continue; }
        if (arg=="-n")      { i++; if (i<argc) variableName = argv[i];   continue; }

        if (arg=="-c")      { lzf  = true; continue; }
        if (arg=="-z")      { zlib = true; continue; }

        if (arg=="-image")  { image  = true; continue; }
        if (arg=="-mirror") { mirror = true; continue; }
        if (arg=="-flip")   { flip   = true; continue; }

        if (arg=="-j")      { jpeg = true; continue;                              }
        if (arg=="-q")      { i++; if (i<argc) quality = atoi(argv[i]); continue; }

        if (arg=="-alpha")  { alpha = true; continue; }
        if (arg=="-font")   { font  = true; continue; }
        if (arg=="-ufont")  { ufont = true; continue; }

        if (arg=="-u")      { unix = true; continue; }
        if (arg=="-d")      { dos  = true; continue; }

        inputFilename = arg;
    }

    //

    if (outputFilename.size())
    {
        ofstream os(outputFilename.c_str(),ios::out);
        args(os,argc,argv);
        return convert(os);
    }
    else
    {
        args(cout,argc,argv);
        return convert(cout);
    }
}

//////////////////////////////////////////////

bool font2src(ostream &os, const string &name, string &data)
{
    if (data.size()%256)
    {
        cerr << "This file doesn't seem to be a VGA font." << endl;
        return false;
    }

    const int width = 8;
    const int height = data.size()>>8;

    /* Flip */

    {
        GLubyte *ptr = (GLubyte *) data.c_str();

        for (int i=0; i<256; i++,ptr+=height)
            for (int j=0; j<height/2; j++)
                swap(ptr[j],ptr[height-1-j]);
    }

    string head;
    GltFontAscii::makeHeader(head,width,height);
    os << "/* Font data " << width << 'x' << height << " */" << endl;

    ::bin2src(os,head+data);
    return true;
}

bool ufont2src(ostream &os, const string &name, string &data)
{
    //
    // On the first pass, create the index
    //

    const unsigned int maxChars = 0x10000;
    byte index[maxChars];
    memset(index,0,sizeof(index));

    char *p = (char *) data.c_str();
    uint32 size = 0;

    for (;;)
    {
        // Convert hex index to integer
        // (sscanf is much slower than this)

        uint32 j =
            fromHex(*(p++))<<12 |
            fromHex(*(p++))<< 8 |
            fromHex(*(p++))<< 4 |
            fromHex(*(p++));

        // Skip colon
        p++;

        // Find end-of-line
        char *n = p;
        while (*n!='\n' && *n!='\0') 
            n++;
        if (*n=='\0') 
            break;

        // Update size, and point to next line

        size += index[j] = (n-p)>>1;
        p = n+1;

        if (*p=='\0') 
            break;
    }

    //
    // On the second pass, create the raw font data
    //

    // Store raw data in string

    string output;
    output.resize(sizeof(index)+size);
    memcpy((void *) output.data(),index,sizeof(index));

    // Input buffer pointer

    p = (char *) data.c_str();

    // Output buffer pointer

    unsigned char *q = (unsigned char *) output.data();
    q += sizeof(index);

    for (;;)
    {
        // Find colon

        while (*p!=':' && *p!='\0') p++;
        if (p=='\0') break; else p++;

        // Find end-of-line

        char *n = p;
        while (*n!='\n' && *n!='\0') n++;
        if (*n=='\0') break;

        switch (n-p)    // Copy and vertical flip
        {
            // These loops could be optimised/unrolled

            case 32:
                {
                    for (int j=30; j>=0; j-=2)
                        *(q++) = fromHex(p[j  ])<<4 | fromHex(p[j+1]);
                    break;
                }
            case 64:
                {
                    for (int j=60; j>=0; j-=4)
                    {
                        *(q++) = fromHex(p[j  ])<<4 | fromHex(p[j+1]);
                        *(q++) = fromHex(p[j+2])<<4 | fromHex(p[j+3]);
                    }
                    break;
                }
            default:
                return false;
        }
    }

    if (lzf || zlib)
    {
        string zip;
        #ifdef GLT_ZLIB
        if (zlib)
            ::compressZLib(zip,output,9);
        else
        #endif
            ::compress(zip,output);
        data += zip;

        string head;
        GltFontUnicode::makeHeader(head,1);

        os << "/* Compressed Unicode Font: " << zip.size() << " bytes */" << endl;
        ::bin2src(os,head+zip);
    }
    else
    {
        string head;
        GltFontUnicode::makeHeader(head,0);

        os << "/* Unicode Font: " << output.size() << " bytes */" << endl;
        ::bin2src(os,head+output);
    }

    return true;
}

bool image2src(ostream &os, const string &name, string &data)
{
    string image,tmp;

    uint32 type       = 0;
    uint32 width      = 0;
    uint32 height     = 0;
    uint32 alignment  = 1;
    uint32 compressed = 0;
    uint32 bytes      = 0;

    bool ok = decode(width,height,image,data);

    if (!ok)
    {
        cerr << "Image file not recognized." << endl;
        return false;
    }

    if (flip)
    {
        flipImage(tmp,image,width,height);
        image = tmp;
    }

    if (mirror)
    {
        mirrorImage(tmp,image,width,height);
        image = tmp;
    }

    //
    // RGB image
    //

    compressed = (jpeg ? 3 : ( zlib ? 2 : (lzf ? 1 : 0 )));

    if (width*height*3==image.size())
    {
        if (isGreyscale(image))
        {
            // Extract grey from the red channel
            getChannel(tmp,image,3,0);
            image = tmp;

            //

            type = GltTexture::TEXTURE_TYPE_GREY;
            os << "/* Image data " << width << 'x' << height << " Grey */" << endl;
        }
        else
            if (is256Colors(image) && !jpeg)
            {
                // Convert from RGB to indexed
                rgb2Indexed(tmp,image);
                image = tmp;

                //

                type = GltTexture::TEXTURE_TYPE_INDEXED_RGB;
                os << "/* Image data " << width << 'x' << height << " Indexed */" << endl;
            }
            else
            {
                type = GltTexture::TEXTURE_TYPE_RGB;
                os << "/* Image data " << width << 'x' << height << " RGB */" << endl;
            }
    }
    else

        //
        // RGBA Image
        //

        if (width*height*4==image.size())
        {
            type = GltTexture::TEXTURE_TYPE_RGBA;
            os << "/* Image data " << width << 'x' << height << " RGBA */" << endl;
        }
        else

            //
            // Greyscale Image
            //

            if (width*height==image.size())
            {
                // Convert to white with alpha channel, if specified

                if (alpha)
                {
                    type = GltTexture::TEXTURE_TYPE_GREYA;
                    os << "/* Image data " << width << 'x' << height << " Grey+Alpha */" << endl;

                    // Combine white image with alpha channel

                    tmp = string();
                    tmp.resize(image.size()<<1);

                    size_t i = 0;
                    size_t j = 0;
                    while (i<image.size())
                    {
                        tmp[j++] = char(255);
                        tmp[j++] = image[i++];
                    }

                    image = tmp;
                }
                else
                {
                    type = GltTexture::TEXTURE_TYPE_GREY;
                    os << "/* Image data " << width << 'x' << height << " Grey */" << endl;
                }
            }
            else

                //
                // Greyscale with Alpha Image
                //

                if (width*height*2==image.size())
                {
                    type = GltTexture::TEXTURE_TYPE_GREYA;
                    os << "/* Image data " << width << 'x' << height << " Grey+Alpha */" << endl;
                }
                else
                    return false;

    // Do compression, if necessary

    if (compressed)
    {
        #ifdef GLT_JPEG
        if (jpeg)
            ::encodeJPG(tmp,width,height,image,quality);
        else
        #endif
        {
        #ifdef GLT_ZLIB
            if (zlib)
            {
                ::compressZLib(tmp,image,9);
                os << "/* Zlib compressed: " << image.size() << " -> " << tmp.size() << " */" << endl;
            }
            else
        #endif
            {
                ::compress(tmp,image);
                os << "/* Compressed: " << image.size() << " -> " << tmp.size() << " */" << endl;
            }
        }

        bytes = tmp.size();

        os << "unsigned char " << name.c_str() << "[] = " << endl;

        string output;
        GltTexture::makeHeader(output,type,width,height,alignment,compressed,bytes);
        output += tmp;
        ::bin2src(os,output);
    }
    else
    {
        bytes = image.size();

        os << "unsigned char " << name.c_str() << "[] = " << endl;

        string output;
        GltTexture::makeHeader(output,type,width,height,alignment,compressed,bytes);
        output += image;
        ::bin2src(os,output);
    }

    return true;
}
