/***************************************************************************
                          bmp_P.cpp  -  description
                             -------------------
    begin                : Fri Jun 27 2003
    copyright            : (C) 2003 by Jacques Gasselin de Richebourg
    email                : jacquesgasselin@hotmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA *
 *                                                                         *
 ***************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "bmp_P.h"

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
