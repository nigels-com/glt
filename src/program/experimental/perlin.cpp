/*
  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2011 Nigel Stewart

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
    \brief   Utility for producing tilable greyscale perlin noise
    \ingroup Util
*/

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cassert>
using namespace std;

#include <glt/info.h>
#include <misc/image.h>
#include <misc/string.h>
#include <math/noise.h>

uint32                    width          = 1024;
uint32                    subSample      = 1;
uint32                    fractionalBits = 27;
GltNoisePerlin::NoiseType type           = GltNoisePerlin::NOISE_PERLIN;
uint32                    randomSeed     = 0;

std::string outputFilename;

const char *banner =
    "\n"                                           
    "perlin\n"
    "\n"                                           
    "Tileable Perlin Noise Texture Utility                \n"
    "GLT C++ OpenGL Toolkit                               \n"
    "http://www.nigels.com/glt/                           \n"
    "\n"                                           
    "Usage: perlin [OPTION]                               \n"
    "\n"                                           
    "  -h       Help.                                     \n"
    "  -w int   Texture width.           (default=1024)   \n"
    "  -s int   i^2 subsampling.         (default=1)      \n"
    "  -b int   Fractional bits.         (default=27)     \n"
    "  -t name  perlin, fbm, turbulence. (default=perlin) \n"
    "  -r int   random integer seed.     (default=0)      \n"
    "  -o file  Output to file instead of cout.           \n";

bool 
tiledNoiseImage
(
    std::string                    &image,
    const uint32                    width,
    const uint32                    height,
    const uint32                    subSample,
    const uint32                    fractionalBit,
    const GltNoisePerlin::NoiseType type,
    const uint32                    randomSeed
)
{
    const uint32 channels = image.size()/(width*height);
    assert(channels*width*height==image.size());

    byte *i = reinterpret_cast<byte *>(&image[0]);

    const uint32 ss     = subSample-1;
    const uint32 xMax   = width<<ss;
    const uint32 yMax   = height<<ss;
    const uint32 step   = 1<<ss;
    const float  step2i = real(1.0)/real(step*step); 
    const uint32 shift  = 32-std::log2(xMax);

    GltNoisePerlin noise(randomSeed);
    noise.type() = type;
    noise.octaves() = 3;

    for (uint32 y=0; y<yMax; y += step)
        for (uint32 x=0; x<xMax; x += step)
        {
            real v = 0.0;
            for (uint32 sy=0; sy<step; ++sy)
                for (uint32 sx=0; sx<step; ++sx)
                {
                  v += noise.val
                    (
                      (x+sx)<<shift,
                      (y+sy)<<shift,
                      fractionalBit
                    );
                }

            const byte b = 
                noise.type()==GltNoisePerlin::NOISE_TURBULENCE ?
                    (byte) clamp((v*step2i)*255.0,0.0,255.0) :
                    (byte) clamp((v*step2i+1)*0.5*255.0,0.0,255.0);

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
        if (arg=="-s")      { i++; if (i<argc) subSample = atoi(argv[i]);      continue; }
        if (arg=="-b")      { i++; if (i<argc) fractionalBits = atoi(argv[i]); continue; }
        if (arg=="-t")
        { 
            i++;
            if (i<argc)
            {
                if (!strcmp(argv[i],"perlin")) { type = GltNoisePerlin::NOISE_PERLIN; continue; }
                if (!strcmp(argv[i],"fbm")) { type = GltNoisePerlin::NOISE_FBM; continue; }
                if (!strcmp(argv[i],"turbulence")) { type = GltNoisePerlin::NOISE_TURBULENCE; continue; }
            }
        }
        if (arg=="-r")      { i++; if (i<argc) randomSeed = atoi(argv[i]); continue; }

        cout << banner;
        cout << endl;
        cout << GltVersionInformation();
        return EXIT_FAILURE;
    }

    //

    std::string image;
    image.resize(width*width);
    
    fractionalBits = clamp(fractionalBits,0u,31u);

    tiledNoiseImage(image,width,width,subSample,fractionalBits,type,randomSeed);

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

