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

/* $Id: perlin.cpp,v 1.2 2011/04/19 05:14:15 nigels Exp $ */

/*! \file
    \brief   Utility for producing tilable greyscale perlin noise
    \ingroup Util
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

#include <glt/info.h>
#include <misc/image.h>
#include <misc/string.h>
#include <math/noise.h>

uint32 width          = 1024;
uint32 fractionalBits = 3;

std::string outputFilename;

const char *banner =
    "\n"                                           
    "perlin\n"
    "\n"                                           
    "Tileable Perlin Noise Texture Utility      \n"
    "GLT C++ OpenGL Toolkit                     \n"
    "http://www.nigels.com/glt/                 \n"
    "\n"                                           
    "Usage: bin2src [OPTION]                    \n"
    "\n"                                           
    "  -h       Help.                           \n"
    "  -w int   Texture width.   (default=1024) \n"
    "  -b int   Fractional bits. (default=25)   \n"
    "  -o file  Output to file instead of cout. \n";

bool 
tiledNoiseImage(std::string &image,const uint32 width,const uint32 height,const uint32 fractionalBits)
{
    const uint32 channels = image.size()/(width*height);
    assert(channels*width*height==image.size());

    byte *i = reinterpret_cast<byte *>(&image[0]);

    // Hard-coded to 1024 width/height - revisit

    const uint32 leftShift  = 22;
    const uint32 fractional = 22+fractionalBits;

    GltNoisePerlin noise;

    for (uint32 y=0; y<height; y++)
        for (uint32 x=0; x<width; x++)
        {
            real v = noise.val(x<<leftShift,y<<leftShift,fractional);
            byte b = (byte) floor((v+1)*0.5*255.0);

            for (uint32 c=0; c<channels; c++)
                *(i++) = b;
        }

    return true;
}

int 
main(int argc,char *argv[])
{
    // Parse command-line options

    for (int i=1; i<argc; i++)
    {
        const string &arg = argv[i];

        if (arg=="-o")      { i++; if (i<argc) outputFilename = argv[i];       continue; }
        if (arg=="-w")      { i++; if (i<argc) width = atoi(argv[i]);          continue; }
        if (arg=="-b")      { i++; if (i<argc) fractionalBits = atoi(argv[i]); continue; }

        cout << banner;
        cout << endl;
        cout << GltVersionInformation();
        return EXIT_FAILURE;
    }

    //

    std::string image;
    image.resize(width*width);
    tiledNoiseImage(image,width,width,fractionalBits);

    std::string data;
    #ifdef GLT_PNG
    encodePNG(data,width,width,image);
    #else
    encodeTGA(data,width,width,image);
    #endif

    if (outputFilename.size())
        writeFile(outputFilename,data);
    else
        writeStream(cout,data);

    return EXIT_SUCCESS;
}

