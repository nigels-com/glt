#include "image.h"

/*! \file
    \brief   Windows BMP image encoding and decoding
    \ingroup Misc

    $Id: bmp.cpp,v 2.4 2004/03/17 03:28:23 nigels Exp $

    $Log: bmp.cpp,v $
    Revision 2.4  2004/03/17 03:28:23  nigels
    Converted #define to upper case, include bmp_P.cpp directly

    Revision 2.3  2004/03/17 02:41:44  jgasseli
    fixed style and code to better suit GLT. Removed bmp_P.cpp from build.

    Revision 2.2  2004/03/15 11:12:50  jgasseli
    patched in the routines from bmp_P.h, Load and Save.

    Revision 2.1  2004/02/10 13:39:12  nigels
    no message

    Revision 1.6  2003/08/25 06:08:15  nigels
    *** empty log message ***

    Revision 1.5  2003/08/25 06:07:39  nigels
    Issues dealing with indexed BMP

    Revision 1.4  2003/07/22 03:55:30  nigels
    Added support for indexed BMP

    Revision 1.3  2003/03/06 12:34:46  nigels
    *** empty log message ***

*/

#include <misc/endian.h>
#include <glt/error.h>

#include <cassert>

//#define BMP_NEW

#ifdef BMP_NEW
#include "bmp_P.h"
#include "bmp_P.cpp"
#endif

using namespace std;

bool
decodeBMP(uint32 &width,uint32 &height,string &image,const string &data)
{
    //
    // For information about the BMP File Format:
    //
    // http://www.daubnet.com/formats/BMP.html
    // http://www.dcs.ed.ac.uk/home/mxr/gfx/2d/BMP.txt
    //

#ifdef BMP_NEW
    /* Alternative file loading using bmp_P.cpp */


    // make a BitmapFile object for .BMP I/O
    BitmapFile bitmap;

    // generate the byte buffer.
    // don't copy, just reference
    // std::string should keep data as long as we don't change the string
    const byte* inputBuffer = data.data();

    if (!(bitmap->loadFromBuffer(&inputBuffer)))
    { //an error occured
        gltWarning("Unsupported BMP variant.");
        assert(0);
        return false;
    }
    //otherwise assume structure is correct

    //extract the data
    width = bitmap->getWidth();
    height = bitmap->getHeight();

    uint16 bpp = bitmap->getBpp();
    uint32 imageSize = bitmap->getImageSize();
    uint32 bufferSize = 0;

    switch (bpp)
    {
    /* Not yet supported
       case 1:
          bufferSize = (uint32) ceil( (float)(imageSize)/(float)8 );
	  break;
       case 4:
          bufferSize = (uint32) ceil( (float)(imageSize)/(float)2 );
	  break;
   */
        case 8:
	    bufferSize = imageSize;
	    break;
        case 16:
            bufferSize = imageSize*2;
	    break;
        case 24:
            bufferSize = imageSize*3;
	    break;
    }

    image.resize(bufferSize);

    //flip the colors internally
    bitmap->convertRGBtoBGR();

    //make a pointer for output
    byte* outputBuffer = image.data();

    //copy it over and voila
    memcpy(outputBuffer, bitmap->getImageData(), bufferSize);

    //we are done
    return true;
#else

    /* previous code */


    const uint32 fileHeaderSize = 14;
    if (data.size()<fileHeaderSize)
        return false;

    // Check for "BM"

    if (data[0]!='B' || data[1]!='M')
        return false;

    // Check the filesize matches string size

    const uint32 fileSize = littleEndian((uint32 *)(data.data()+2));
    if (data.size()!=fileSize)
        return false;

    // Get the size of the image header

    const uint32 imageHeaderSize = littleEndian((uint32 *)(data.data()+fileHeaderSize));
    if (fileHeaderSize+imageHeaderSize>data.size())
        return false;

    // Get some image info

    const uint32 imageWidth    = littleEndian((uint32 *)(data.data()+fileHeaderSize+4 ));
    const uint32 imageHeight   = littleEndian((uint32 *)(data.data()+fileHeaderSize+8 ));
    const uint16 imageBits     = littleEndian((uint16 *)(data.data()+fileHeaderSize+14));
    const uint32 imageCompress = littleEndian((uint32 *)(data.data()+fileHeaderSize+16));

    // Do some checking

    // We support only RGB or indexed

    if (imageBits!=24 && imageBits!=8)
        return false;

    const uint32 bytesPerPixel    = imageBits>>3;
    const uint32 colorTableOffset = 54;


    // We don't support compressed BMP.
    //
    // According to the specs, 4-bit and 8-bit RLE
    // compression is used only for indexed images.

    if (imageCompress!=0)
        return false;

    /*
    const uint32 imagePos    = littleEndian((uint32 *)(data.data()+10));
    const uint32 imagePixels = imageWidth*imageHeight;
    const uint32 lineBytes   = (imageWidth*bytesPerPixel+3)&~3;
    const uint32 imageBytes  = lineBytes*imageHeight;
    */

    if (imagePos+imageBytes!=data.size())
        return false;


    // Extract the image as RGB


    width  = imageWidth;
    height = imageHeight;
    image.resize(imagePixels*3);

    // Destination iterator

    byte *i = (byte *) image.data();

    // Uncompressed RGB

    if (bytesPerPixel==3 && imageCompress==0)
    {
        for (uint32 y=0; y<imageHeight; y++)
        {
            // Source iterator, beginning of y-th scanline

            const byte *j = (const byte *) data.data()+imagePos+lineBytes*y;

            // Copy the RGB scanline, swapping red and blue channels
            // as we go...

            for (uint32 x=0; x<imageWidth; x++)
            {
                *(i++) = *(j++ + 2);
                *(i++) = *(j++);
                *(i++) = *(j++ - 2);
            }
        }
    }

    // Uncompressed Indexed

    else if (bytesPerPixel==1 && imageCompress==0)
    {
        for (uint32 y=0; y<imageHeight; y++)
        {
            // Source iterator, beginning of y-th scanline

            const byte *j = (const byte *) data.data()+imagePos+lineBytes*y;

            // Copy the indexed scanline
            for (uint32 x=0; x<imageWidth; x++)
            {
                const byte *c = reinterpret_cast<const byte *>(data.data()+colorTableOffset+(*j)*4);
                *(i++) = c[2];
                *(i++) = c[1];
                *(i++) = c[0];
                j++;
            }
        }
    }

    else
    {
        gltWarning("Unsupported BMP variant.");
        assert(0);
        return false;
    }

    return true;
#endif
}

bool
encodeBMP(string &data,const uint32 width,const uint32 height,const string &image)
{
#ifdef BMP_NEW
    /* Alternative file loading using bmp_P.cpp */


    // make a BitmapFile object for .BMP I/O
    BitmapFile bitmap;

    // generate the byte buffer.
    // don't copy, just reference
    // std::string should keep data as long as we don't change the string
    const byte* inputBuffer = data.data();
    uint32 imageSize = data.size();

    bitmap->setWidth(width);
    bitmap->setHeight(height);

    uint16 bpp = (imageSize*8) / (width*height);

    bitmap->setBpp(bpp);

    if (bpp == 8 || bpp == 4)
    {// we need a palette from the user
       //...
    }

    bitmap->setImageData( inputBuffer );

    uint32 bufferSize = 0;

    switch (bpp)
    {
    /* Not yet supported
       case 1:
          bufferSize = (uint32) ceil( (float)(imageSize)/(float)8 );
	  break;
       case 4:
          bufferSize = (uint32) ceil( (float)(imageSize)/(float)2 );
	  break;
   */
        case 8:
	    bufferSize = imageSize;
	    break;
        case 16:
            bufferSize = imageSize*2;
	    break;
        case 24:
            bufferSize = imageSize*3;
	    break;
    }

    image.resize(bufferSize);

    byte* outputBuffer = image.data();

    bitmap->convertRGBtoBGR();

    bitmap->saveToBuffer(&outputBuffer);


    //we are done
    return true;

#else
    assert(0);
    // TODO
    return false;
#endif
}
