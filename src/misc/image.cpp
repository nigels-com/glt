#include "image.h"

/*! \file
    \brief   Image utility routines
    \ingroup Misc

    $Id: image.cpp,v 2.2 2007/04/27 06:01:30 nigels Exp $
*/

#include <misc/endian.h>
#include <glt/color.h>
#include <math/noise.h>

#include <cassert>
#include <cstring>
#include <cstdio>
#include <cmath>

#include <set>
#include <map>
#include <list>
#include <iostream>
using namespace std;

bool isGreyscale(const string &rgb)
{
    assert(rgb.size()%3==0);

    if (rgb.size()%3)
        return false;

    for (size_t i=0; i<rgb.size(); i+=3)
        if (rgb[i]!=rgb[i+1] || rgb[i]!=rgb[i+2])
            return false;

    return true;
}

bool is256Colors(const string &rgb)
{
    assert(rgb.size()%3==0);

    if (rgb.size()%3)
        return false;

    set<uint32> colors;

    for (size_t i=0; i<rgb.size(); i+=3)
    {
        const uint32 col = (byte(rgb[i])<<16) | (byte(rgb[i+1])<<8) | byte(rgb[i+2]);

        colors.insert(col);

        if (colors.size()>256)
            return false;
    }

    return true;
}

bool getChannel(string &dest,const string &src,const uint32 size,const uint32 channel)
{
    assert(src.size()%size==0);
    assert(channel<size);

    if (src.size()%size || channel>=size)
        return false;

    dest.resize(src.size()/size);

    for (string::size_type i=channel,j=0; i<src.size(); i+=size,j++)
       dest[j] = src[i];

    return true;
}

void rgb2Indexed(string &dest,const string &rgb)
{
    assert(rgb.size()%3==0);

    if (rgb.size()%3)
        return;

    // Output buffer will begin with lookup-table,
    // followed by pixel indexes

    const int tableSize = 256*3;
    dest.resize(tableSize+rgb.size()/3);

    // First find the first 256 unique colors
    // we initialise lookup-table as we go

    map<uint32,byte> colors;

    for (size_t i=0,j=0; i<rgb.size();)
    {
        const uint32 col = (byte(rgb[i])<<16) | (byte(rgb[i+1])<<8) | byte(rgb[i+2]);

        // Is this a new colour?

        if (colors.find(col)==colors.end())
        {
            // Add it
            colors.insert(make_pair(col,j/3));

            // Copy it into lookup-table
            dest[j++] = rgb[i++];
            dest[j++] = rgb[i++];
            dest[j++] = rgb[i++];

            // Stop if we've found them all
            if (colors.size()==256)
                break;
        }
        else
            i += 3;
    }

    // Now use map to convert pixels to indexes

    {
        for (size_t i=0,j=tableSize; i<rgb.size(); i+=3,j++)
        {
            const uint32 col = (byte(rgb[i])<<16) | (byte(rgb[i+1])<<8) | byte(rgb[i+2]);
            assert(colors.find(col)!=colors.end());
            dest[j] = colors[col];
        }
    }
}

void indexed2rgb(string &dest,const string &indexed)
{
    const int tableSize = 256*3;
    const int pixels = indexed.size()-tableSize;

    assert(pixels>=0);
    if (pixels<0)
        return;

    dest.resize(pixels*3);

    for (size_t i=tableSize,j=0; i<indexed.size(); i++,j+=3)
    {
        const size_t p = 3*(byte)(indexed[i]);

        dest[j]   = indexed[p];
        dest[j+1] = indexed[p+1];
        dest[j+2] = indexed[p+2];
    }
}

void flipImage(string &dest,const string &src,const uint32 width,const uint32 height)
{
    const int lineSize = src.size()/height;

    assert(lineSize>0);
    assert(src.size()%lineSize==0);

    if (lineSize==0 || src.size()%lineSize!=0)
        return;

    dest.erase(dest.begin(),dest.end());
    dest.resize(src.size());

    const char *i = src.c_str();
    const char *j = dest.c_str()+dest.size()-lineSize;

    for (uint32 k=0; k<height; i+=lineSize,j-=lineSize,k++)
        memcpy((void *)j,i,lineSize);
}

void
mirrorImage(std::string &dest,const std::string &src,const uint32 width,const uint32 height)
{
    const int lineSize = static_cast<int>(src.size())/height;
    const int channels = lineSize/width;

    assert(channels>0);
    assert(src.size()%lineSize==0);
    assert(src.size()==width*height*channels);

    if (channels==0 || src.size()%lineSize!=0 || src.size()!=width*height*channels)
        return;

    dest.resize(src.size());

    const char *i = src.c_str();
    const char *j = dest.c_str()+lineSize-channels;

    for (uint32 k=0; k<height; j+=lineSize*2,k++)
        for (uint32 l=0; l<width; i+=channels,j-=channels,l++)
            memcpy((void *)j,i,channels);
}

void adjustGamma(std::string &image,const double gamma)
{
    byte table[256];
    for (int i=0; i<256; i++)
        table[i] = (byte) floor( pow(double(i)/255.0, 1.0/gamma)*255.0 + 0.5);

          byte *j   =       (byte *) image.c_str();
    const byte *end = (const byte *) image.c_str() + image.size();

    for (;j<end;j++)
        *j = table[*j];
}

void
adjustHSV
(
    std::string &image,
    const int width,
    const int height,
    const real hue,
    const real saturation,
    const real value
)
{
    const int channels = image.size()/(width*height);
    assert(channels*width*height==int(image.size()));

          byte *i   =       (byte *) image.data();
    const byte *end = (const byte *) image.data() + image.size();

    for (;i<end;i+=channels)
    {
        GltColor col(*i/255.0,*(i+1)/255.0,*(i+2)/255.0);

        real h,s,v;
        col.toHSV(h,s,v);

        h = fmod(h+hue+360.0,360.0);
        s = clamp(s+saturation,0.0,1.0);
        v = clamp(v+value,0.0,1.0);

        col.fromHSV(h,s,v);

        *i     = (byte) floor(col.red()  *255.0+0.5);
        *(i+1) = (byte) floor(col.green()*255.0+0.5);
        *(i+2) = (byte) floor(col.blue() *255.0+0.5);
    }
}

bool stitchImages(string &image,const int dx,const int dy,const vector<string> &src,const int lineSize)
{
    const int n=src.size();

    if (dx<1 || dy<1 || dx*dy!=n)
        return false;

    const int tileSize = src[0].size();

    // Allocate size of output image
    image.resize(n*tileSize);

    // Process each input in turn

    for (int y=0; y<dy; y++)
        for (int x=0; x<dx; x++)
        {
            const int k = x+y*dx;

                  byte *i    =       (byte *) image.data()+x*lineSize+y*dx*tileSize;
            const byte *iMax = (const byte *) image.data()+image.size();
            const byte *j    = (const byte *) src[k].data();
            const byte *jMax = (const byte *) src[k].data() + src[k].size();

            while (i<iMax && j<jMax)
            {
                memcpy(i,j,lineSize);
                i += lineSize*dx;
                j += lineSize;
            }
        }

    return true;
}

//
// Image decoding
//

bool decode(uint32 &width,uint32 &height,std::string &image,const std::string &data)
{
    if (!data.size())
        return false;

    string type;

    // PPM

    if (decodePPM(type,width,height,image,data))
        return true;

    // BMP

    if (decodeBMP(width,height,image,data))
        return true;

    // TGA

    if (decodeTGA(width,height,image,data))
        return true;

    // PNG

    #ifdef GLT_PNG
    if (decodePNG(width,height,image,data))
        return true;
    #endif

    // JPG

    #ifdef GLT_JPEG
    if (decodeJPG(width,height,image,data))
        return true;
    #endif

    // TGA

    return false;
}

bool noiseImage(std::string &image,const uint32 width,const uint32 height,const uint32 fractionalBits)
{
    const uint32 channels = image.size()/(width*height);
    assert(channels*width*height==image.size());

    byte *i = reinterpret_cast<byte *>(&image[0]);

    GltNoisePerlin noise;

    for (uint32 y=0; y<height; y++)
        for (uint32 x=0; x<width; x++)
        {
            real v = noise.val(x,y,fractionalBits);
            byte b = (byte) floor((v+1)*0.5*255.0);

            for (uint32 c=0; c<channels; c++)
                *(i++) = b;
        }

    return true;
}

