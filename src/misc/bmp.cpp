#include "image.h"

/*! \file
    \brief   Windows BMP image encoding and decoding
    \ingroup Misc

    $Id: bmp.cpp,v 2.10 2004/12/26 05:38:06 jgasseli Exp $

    $Log: bmp.cpp,v $
    Revision 2.10  2004/12/26 05:38:06  jgasseli
    Fixed source file arrangement for BMP_NEW

    Revision 2.9  2004/05/15 05:11:55  jgasseli
    modifying code for string use. Needs testing !

    Revision 2.8  2004/03/21 20:37:50  nigels
    Adjusted some formatting to bring it into GLT conventions

    Revision 2.7  2004/03/21 11:02:04  jgasseli
    commenting out define BMP_NEW

    Revision 2.5  2004/03/17 03:53:56  nigels
    Resolved compile error

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

    // BitmapFile object for .BMP I/O
    BitmapFile bitmap;

    // Get a pointer to the input byte buffer.

    if (!bitmap.loadFromString(data, image))
        return false;

    width  = bitmap.getWidth();
    height = bitmap.getHeight();

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

    const uint32 imagePos    = littleEndian((uint32 *)(data.data()+10));
    const uint32 imagePixels = imageWidth*imageHeight;
    const uint32 lineBytes   = (imageWidth*bytesPerPixel+3)&~3;
    const uint32 imageBytes  = lineBytes*imageHeight;

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

    uint32 imageSize = image.size();

    bitmap.setWidth(width);
    bitmap.setHeight(height);

    uint16 bpp = (imageSize*8) / (width*height);

    bitmap.setBpp(bpp);

    if (bpp == 8 || bpp == 4)
    {// we need a palette from the user
       //...
    }

    bitmap.saveToString(data, image);


    //we are done
    return true;

#else
    assert(0);
    // TODO
    return false;
#endif
}


#include <glt/config.h>

#ifdef BMP_NEW

struct BitmapFileHeader
{
    uint16    fileType;     ///< Specifies file type must be BM (4D42h)
    uint32    fileSize;     ///< file size in bytes (54)

    uint16    res1;         ///< must be 0
    uint16    res2;         ///< must be 0
    uint32    imageOffset;  ///< offset in bytes from the header to the data (40)

public:

    BitmapFileHeader();
    ~BitmapFileHeader();

    void saveToBuffer(byte **);
    bool loadFromBuffer(const byte **);

    inline void setFileSize(uint32 val)    { fileSize = val; }
    inline void setImageOffset(uint32 val) { imageOffset = val; }
};

/** wrapper for the palette data.
 * MS-WIN use 4 byte quads as opposed to Adobe with 3 byte entries.
 * Therefore a full 256 color palette in .pal format is 1K but a 256 color
 * .act is 768B
 */

/**
 * The sub header of a BMP file
 */

struct BitmapInfoHeader
{
    uint32    infoSize;     /* information header size in bytes (40) */
    uint32    imageWidth;   /* width of the bitmap in pixels (0) */
    uint32    imageHeight;  /* height of the bitmap in pixels (0) */
    uint16    colourPlanes; /* must be 1 */
    uint16    bitCount;     /* bits per pixel, 1, 4, 8, 16, (24), 32 */
    uint32    compression;  /* compression type (0) */
    uint32    imageSize;    /* size of image in bytes (0) */
    uint32    pixelsX;      /* number of pixels in x per meter (2834) */
    uint32    pixelsY;      /* number of pixels in y per meter (2834) */
    uint32    numColours;   /* number of colours used in the image (0) */
    uint32    numImportant; /* number of important colours (0) */
    byte *    paletteData;  /* the palette data that may follow */

public:

    BitmapInfoHeader ();
    ~BitmapInfoHeader ();

    void saveToBuffer(byte **);
    void loadFromBuffer(const byte **);

    void savePaletteToBuffer(byte **);
    void loadPaletteFromBuffer(const byte **);
    void setPalette(const byte *);

    inline uint32 getImageWidth()  const { return imageWidth;   }
    inline uint32 getImageHeight() const { return imageHeight;  }
    inline uint32 getBitCount()    const { return bitCount;     }
    inline uint32 getImageSize()   const { return imageSize;    }
    inline uint32 getNumColours()  const { return numColours;   }
    inline uint32 getPaletteSize() const { return numColours*4; }

    inline byte *getPaletteData () const { return paletteData;  }

    inline void setImageWidth(uint32 w)  { imageWidth = w;   }
    inline void setImageHeight(uint32 h) { imageHeight = h;  }
    inline void setBitCount(uint16 bpp)  { bitCount = bpp;   }
    inline void setImageSize(uint32 s)   { imageSize = s;    }
    inline void setPaletteSize(uint32 s) { numColours = s/4; }
};


/**
 * Wrapper struct to hold image & palette data and interface with the headers
 */

struct BitmapFile
{
    BitmapFileHeader *fileHeader;
    BitmapInfoHeader *infoHeader;
    byte *imageData;

    public:

    BitmapFile();
    ~BitmapFile();

/**
 * Loading, saving and initalising
 */

    //void saveToBuffer(byte *);
    void saveToString(std::string& out, const std::string& in);

    //bool loadFromBuffer(const byte *);
    bool loadFromString(const std::string& in, std::string& out);
/**
 * Getting & setting dimensions and other info
 */
    uint32 getWidth()     const;
    uint32 getHeight()    const;
    uint16 getBpp()       const;
    uint32 getImageSize() const;

    void setWidth(uint32);
    void setHeight(uint32);
    void setBpp(uint16);

    void setDimensions(uint32 w, uint32 h, uint16 bpp);

/**
 * Palette specific functions
 */

    uint32 getPaletteSize()  const;
    const byte *getPalette()     const;

    void setPaletteSize(uint32);

    void setPalette(const byte *);

/**
 * Getting and setting the image data
 */

    byte *getImageData() const;
    void  setImageData(const byte *);

    void convertRGBtoBGR();

private:

    void adjustInternalDimensions();
};



#include <cstdlib>
#include <cstdio>
#include <cstring>


#include "endian.h"


#define BMP_FILE_ID 0x04D42
#define DEFAULT_FILE_SIZE 54
#define DEFAULT_IMAGE_OFFSET 54
#define NO_COMPRESSION 0
#define DPI_TO_METERS 2834

/**
 * private functions
 */

template <typename T>
inline T readFromBuffer(const byte **pos)
{
    T tmp = reinterpret_cast<const T *>(*pos);
    *pos += sizeof(T);
    return tmp;
}

template <typename T>
inline void writeToBuffer (T val, byte **buff)
{
    T *tmp = reinterpret_cast<T*>(*buff);

    *tmp = val;
    (*buff) += sizeof(T);
}

/**
 * public functions
 */

BitmapFileHeader::BitmapFileHeader()
:  fileType(BMP_FILE_ID),
   fileSize(DEFAULT_FILE_SIZE),
   res1(0),
   res2(0),
   imageOffset(DEFAULT_IMAGE_OFFSET)
{
}

BitmapFileHeader::~BitmapFileHeader()
{
}

bool
BitmapFileHeader::loadFromBuffer(const byte **buff)
{
    fileType = littleEndian(readFromBuffer<uint16>(buff));

    if (fileType != BMP_FILE_ID)/*check for the correct id*/
        return false;

    fileSize = littleEndian(readFromBuffer<uint32>(buff));

    /* these are always 0 so no need to worry about byte-order */
    res1 = readFromBuffer<uint16>(buff);
    res2 = readFromBuffer<uint16>(buff);

    imageOffset = littleEndian(readFromBuffer<uint32>(buff));

    return true;
}

void
BitmapFileHeader::saveToBuffer(byte **buff)
{
    writeToBuffer<uint16>(littleEndian(fileType), buff);
    writeToBuffer<uint32>(littleEndian(fileSize), buff);

    /* these are always 0 so no need to worry about byte-order */
    writeToBuffer<uint16>(res1, buff);
    writeToBuffer<uint16>(res2, buff);

    writeToBuffer<uint32>(littleEndian(imageOffset), buff);
}

BitmapInfoHeader::BitmapInfoHeader()
:  infoSize(40),
   imageWidth(0),
   imageHeight(0),
   colourPlanes(1),
   bitCount(24),
   compression(NO_COMPRESSION),
   imageSize(0),
   pixelsX(DPI_TO_METERS),
   pixelsY(DPI_TO_METERS),
   numColours(0),
   numImportant(0),
   paletteData(NULL)
{
}

BitmapInfoHeader::~BitmapInfoHeader()
{
    if (paletteData)
        delete [] paletteData;
}

void
BitmapInfoHeader::loadFromBuffer(const byte **buff)
{
    infoSize     = littleEndian(readFromBuffer<uint32>(buff));
    imageWidth   = littleEndian(readFromBuffer<uint32>(buff));
    imageHeight  = littleEndian(readFromBuffer<uint32>(buff));
    colourPlanes = littleEndian(readFromBuffer<uint16>(buff));
    bitCount     = littleEndian(readFromBuffer<uint16>(buff));
    compression  = littleEndian(readFromBuffer<uint32>(buff));
    imageSize    = littleEndian(readFromBuffer<uint32>(buff));
    pixelsX      = littleEndian(readFromBuffer<uint32>(buff));
    pixelsY      = littleEndian(readFromBuffer<uint32>(buff));
    numColours   = littleEndian(readFromBuffer<uint32>(buff));
    numImportant = littleEndian(readFromBuffer<uint32>(buff));

    loadPaletteFromBuffer(buff);
}

void
BitmapInfoHeader::loadPaletteFromBuffer(const byte **buff)
{
    if (numColours > 0)
    {
        /* generate an empty palette */
        setPaletteSize(numColours);
        memcpy(paletteData, *buff, numColours*4);
        (*buff) += numColours*4;
    }
}


void
BitmapInfoHeader::saveToBuffer(byte **buff)
{
    writeToBuffer<uint32>(littleEndian(infoSize), buff);
    writeToBuffer<uint32>(littleEndian(imageWidth), buff);
    writeToBuffer<uint32>(littleEndian(imageHeight), buff);
    writeToBuffer<uint16>(littleEndian(colourPlanes), buff);
    writeToBuffer<uint16>(littleEndian(bitCount), buff);
    writeToBuffer<uint32>(littleEndian(compression), buff);
    writeToBuffer<uint32>(littleEndian(imageSize), buff);
    writeToBuffer<uint32>(littleEndian(pixelsX), buff);
    writeToBuffer<uint32>(littleEndian(pixelsY), buff);
    writeToBuffer<uint32>(littleEndian(numColours), buff);
    writeToBuffer<uint32>(littleEndian(numImportant), buff);

    savePaletteToBuffer(buff);
}

void
BitmapInfoHeader::savePaletteToBuffer(byte **buff)
{
    if (numColours > 0)
    {
        memcpy(*buff, paletteData, numColours*4);
       (*buff) += numColours*4;
    }
}

void
BitmapInfoHeader::setPalette(const byte *pal)
{
    if (paletteData)
        delete [] paletteData;

    paletteData = new byte [numColours * 4];

    if (pal)
        memcpy(paletteData, pal, numColours * 4);
    else
    {
        register unsigned i;
        for (i = 0; i < numColours*4; ++i)
            paletteData[i] = 0;
    }
}

BitmapFile::BitmapFile()
:  fileHeader(NULL),
   infoHeader(NULL),
   imageData(NULL)
{
    fileHeader = new BitmapFileHeader;
    infoHeader = new BitmapInfoHeader;
}

BitmapFile::~BitmapFile()
{
    if (fileHeader)
        delete fileHeader;

    if (infoHeader)
        delete infoHeader;

    if (imageData)
        delete [] imageData;
}

/* returns true on success*/
bool
BitmapFile::loadFromString(const std::string& inStr, std::string& outStr)
{
    uint32 imageSize;

    const byte *buff = reinterpret_cast<const byte*>(inStr.data());

    if (buff == NULL)
    {
        gltWarning("No data in image string.");
        return false;
    }

    if (!fileHeader->loadFromBuffer(&buff))
    {
        gltWarning("Unsupported BMP variant.");
        return false;
    }

    infoHeader->loadFromBuffer(&buff);

    if ( (imageSize = infoHeader->getImageSize()) == 0)
    {
        gltWarning("0 sized image in input string.");
        return false;
    }

    if (imageData)
        delete [] imageData;

    imageData = new byte [imageSize];

    /* double copy at the moment */
    /* needs to change */
    memcpy(imageData, buff, imageSize);

    outStr.resize(imageSize);

    // flip the colors internally
    convertRGBtoBGR();

    // make a pointer for output
    byte *outputBuffer = (byte*)(outStr.data());

    //copy it over and voila
    memcpy(outputBuffer, imageData, imageSize);

    return true;
}

void
BitmapFile::saveToString(std::string& outStr, const std::string& inStr)
{
    const byte* inputBuffer = reinterpret_cast<const byte*>(inStr.data());

    setImageData( inputBuffer );

    outStr.resize( infoHeader->getImageSize() );

    byte *buff = (byte*)(outStr.data());

    if (buff == NULL)
        return;

    fileHeader->saveToBuffer(&buff);
    infoHeader->saveToBuffer(&buff);

    if (infoHeader->getImageSize() == 0)
        return;
    else
    {
        convertRGBtoBGR();
        memcpy(buff, imageData, infoHeader->getImageSize() );
        buff += infoHeader->getImageSize();
    }
}

void
BitmapFile::adjustInternalDimensions()
{
    uint32 w, h, palSize;
    uint16 bpp;

    w = infoHeader->getImageWidth();
    h = infoHeader->getImageHeight();
    palSize = infoHeader->getPaletteSize();
    bpp = infoHeader->getBitCount();

    infoHeader->setImageSize((uint32)(w * h * ( (double)bpp / 8 )));
    fileHeader->setFileSize(DEFAULT_FILE_SIZE + infoHeader->getImageSize() + palSize);
    fileHeader->setImageOffset(DEFAULT_IMAGE_OFFSET + palSize);
}

/**
 * public functions
 */

uint32 BitmapFile::getWidth()     const { return infoHeader->getImageWidth();  }
uint32 BitmapFile::getHeight()    const { return infoHeader->getImageHeight(); }
uint16 BitmapFile::getBpp()       const { return infoHeader->getBitCount();    }
uint32 BitmapFile::getImageSize() const { return infoHeader->getImageSize();   }

void
BitmapFile::setWidth(uint32 w)
{
    infoHeader->setImageWidth(w);
    adjustInternalDimensions();
}

void
BitmapFile::setHeight(uint32 h)
{
    infoHeader->setImageHeight(h);
    adjustInternalDimensions();
}

void
BitmapFile::setBpp(uint16 bpp)
{
    infoHeader->setBitCount(bpp);
    adjustInternalDimensions();
}

void
BitmapFile::setDimensions(uint32 w, uint32 h, uint16 bpp)
{
    infoHeader->setImageWidth(w);
    infoHeader->setImageHeight(h);
    infoHeader->setBitCount(bpp);
    adjustInternalDimensions();
}

     uint32 BitmapFile::getPaletteSize() const { return infoHeader->getNumColours();  }
const byte *BitmapFile::getPalette()     const { return infoHeader->getPaletteData(); }

void
BitmapFile::setPaletteSize(uint32 size)
{
    infoHeader->setPaletteSize(size);
    infoHeader->setPalette(NULL);
    adjustInternalDimensions();
}

void
BitmapFile::setPalette(const byte *pal)
{
    infoHeader->setPalette(pal);
}


byte *BitmapFile::getImageData() const { return imageData; }

void
BitmapFile::setImageData(const byte *buff)
{
    if (imageData != NULL)
        delete [] imageData;

    imageData = new byte [infoHeader->getImageSize()];

    memcpy(imageData, buff, infoHeader->getImageSize());
}

void
BitmapFile::convertRGBtoBGR()
{
    int bpp = 0;
    int width, height;
    int numEntries;
    register int i;
    byte tempCol;

    switch (infoHeader->getBitCount())
    {
        case 8:  bpp = 1; break;
        case 16: bpp = 2; break;
        case 24: bpp = 3; break;
        case 32: bpp = 4; break;
    };

    width = infoHeader->getImageWidth();
    height = infoHeader->getImageHeight();

    numEntries = width*height*bpp;

    if (bpp == 3)
    {
        for (i = 0; i < numEntries; i+=3)
        {
            tempCol = imageData[i+2];
            imageData[i+2] = imageData[i];
            imageData[i] = tempCol;
        }
    }
}
#endif

