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

inline uint16 readUint16FromBuffer (const byte** buff)
{
    uint16 temp = littleEndian((uint16*)(*buff));
    (*buff)+=2;
    return temp;
}

inline uint32 readUint32FromBuffer (const byte** buff)
{
    uint32 temp = littleEndian((uint32*)(*buff));
    (*buff)+=4;
    return temp;
}

inline void writeUint16ToBuffer (uint16 val, byte** buff)
{
    byte* temp = (byte*)(&val);
    #ifdef GLT_BIG_ENDIAN
    flip(val);
    #endif

    **buff = *temp;
    ++(*buff); ++temp;

    **buff = *temp;
    ++(*buff);
}

inline void writeUint32ToBuffer (uint32 val, byte** buff)
{
    byte* temp = (byte*)(&val);
    #ifdef GLT_BIG_ENDIAN
    flip(val);
    #endif

    **buff = *temp;
    ++(*buff); ++temp;

    **buff = *temp;
    ++(*buff); ++temp;

    **buff = *temp;
    ++(*buff); ++temp;

    **buff = *temp;
    ++(*buff);
}

/**
 * public functions
 */

BitmapFileHeader::BitmapFileHeader( void )
:fileType (BMP_FILE_ID),
 fileSize (DEFAULT_FILE_SIZE),
 res1 (0),
 res2 (0),
 imageOffset (DEFAULT_IMAGE_OFFSET)
{
}

/* buffer version */
bool BitmapFileHeader::loadFromBuffer (const byte** buff)
{
    fileType = readUint16FromBuffer(buff);

    if (fileType != BMP_FILE_ID)/*check for the correct id*/
        return false;

    fileSize = readUint32FromBuffer(buff);

    /* these are always 0 so no need to worry about byte-order */
    res1 = readUint16FromBuffer(buff);
    res2 = readUint16FromBuffer(buff);

    imageOffset = readUint32FromBuffer(buff);

    return true;
}

/* buffer version */
void BitmapFileHeader::saveToBuffer (byte** buff)
{
    writeUint16ToBuffer(fileType, buff);
    writeUint32ToBuffer(fileSize, buff);

    /* these are always 0 so no need to worry about byte-order */
    writeUint16ToBuffer(res1, buff);
    writeUint16ToBuffer(res2, buff);

    writeUint32ToBuffer(imageOffset, buff);
}

BitmapInfoHeader::BitmapInfoHeader( void )
:infoSize (40),
 imageWidth (0),
 imageHeight (0),
 colourPlanes (1),
 bitCount (24),
 compression (NO_COMPRESSION),
 imageSize (0),
 pixelsX (DPI_TO_METERS),
 pixelsY (DPI_TO_METERS),
 numColours (0),
 numImportant (0),
 paletteData (NULL)
{
}

/* buffer version */
void BitmapInfoHeader::loadFromBuffer (const byte** buff)
{
    infoSize = readUint32FromBuffer(buff);
    imageWidth = readUint32FromBuffer(buff);
    imageHeight = readUint32FromBuffer(buff);
    colourPlanes = readUint16FromBuffer(buff);
    bitCount = readUint16FromBuffer(buff);
    compression = readUint32FromBuffer(buff);
    imageSize = readUint32FromBuffer(buff);
    pixelsX = readUint32FromBuffer(buff);
    pixelsY = readUint32FromBuffer(buff);
    numColours = readUint32FromBuffer(buff);
    numImportant = readUint32FromBuffer(buff);

    loadPaletteFromBuffer(buff);
}

/* buffer version */
void BitmapInfoHeader::loadPaletteFromBuffer (const byte** buff)
{
    if (numColours > 0)
    {
        /* generate an empty palette */
        setPaletteSize(numColours);

        memcpy(paletteData, *buff, numColours*4);

        (*buff) += numColours*4;
    }
}


/* buffer version */
void BitmapInfoHeader::saveToBuffer (byte** buff)
{
    writeUint32ToBuffer(infoSize, buff);
    writeUint32ToBuffer(imageWidth, buff);
    writeUint32ToBuffer(imageHeight, buff);
    writeUint16ToBuffer(colourPlanes, buff);
    writeUint16ToBuffer(bitCount, buff);
    writeUint32ToBuffer(compression, buff);
    writeUint32ToBuffer(imageSize, buff);
    writeUint32ToBuffer(pixelsX, buff);
    writeUint32ToBuffer(pixelsY, buff);
    writeUint32ToBuffer(numColours, buff);
    writeUint32ToBuffer(numImportant, buff);

    savePaletteToBuffer(buff);
}

/* buffer version */
void BitmapInfoHeader::savePaletteToBuffer (byte** buff)
{
    if (numColours > 0)
    {
        memcpy(*buff, paletteData, numColours*4);

       (*buff) += numColours*4;
    }
}

void BitmapInfoHeader::setPalette (const byte* pal)
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

BitmapFile::BitmapFile (void)
:fileHeader (NULL),
 infoHeader (NULL),
 imageData (NULL)
{
    fileHeader = new BitmapFileHeader;
    infoHeader = new BitmapInfoHeader;
}

BitmapFile::~BitmapFile (void)
{
    if (fileHeader)
        delete fileHeader;
    if (infoHeader)
        delete infoHeader;
    if (imageData)
        delete [] imageData;
}

/* buffer version */
/* returns true on success*/
bool BitmapFile::loadFromBuffer (const byte* buffPtr)
{
    const byte* buff = buffPtr;

    if (buff == NULL)
        return false;

    if (fileHeader->loadFromBuffer(&buff) == 0)
        return false;

    infoHeader->loadFromBuffer(&buff);

    if (infoHeader->getImageSize() == 0)
        return false;

    if (imageData)
        delete [] imageData;

    imageData = new byte [infoHeader->getImageSize()];

    memcpy(imageData, buff, infoHeader->getImageSize());

    buff += infoHeader->getImageSize();

    return true;
}

/* buffer version */
void BitmapFile::saveToBuffer (byte* buffPtr)
{
    byte* buff = buffPtr;

    if (buff == NULL)
        return;

    fileHeader->saveToBuffer(&buff);
    infoHeader->saveToBuffer(&buff);

    if (infoHeader->getImageSize() == 0)
        return;
    else
    {
        memcpy(buff, imageData, infoHeader->getImageSize() );
        buff += infoHeader->getImageSize();
    }
}

void BitmapFile::adjustInternalDimensions (void)
{
    uint32 w, h, palSize;
    uint16 bpp;

    w = infoHeader->getImageWidth();
    h = infoHeader->getImageHeight();
    palSize = infoHeader->getPaletteSize();
    bpp = infoHeader->getBitCount();

    infoHeader->setImageSize((uint32)(w * h * ( (float) bpp / 8 )));
    fileHeader->setFileSize(DEFAULT_FILE_SIZE + infoHeader->getImageSize() + palSize);
    fileHeader->setImageOffset(DEFAULT_IMAGE_OFFSET + palSize);
}

/**
 * public functions
 */




uint32 BitmapFile::getWidth (void) const
{
    return infoHeader->getImageWidth();
}

uint32 BitmapFile::getHeight (void) const
{
    return infoHeader->getImageHeight();
}

uint16 BitmapFile::getBpp (void) const
{
    return infoHeader->getBitCount();
}

uint32 BitmapFile::getImageSize (void) const
{
    return infoHeader->getImageSize();
}

void BitmapFile::setWidth (uint32 w)
{
    infoHeader->setImageWidth(w);
    adjustInternalDimensions();
}

void BitmapFile::setHeight (uint32 h)
{
    infoHeader->setImageHeight(h);
    adjustInternalDimensions();
}

void BitmapFile::setBpp (uint16 bpp)
{
    infoHeader->setBitCount(bpp);
    adjustInternalDimensions();
}

void BitmapFile::setDimensions (uint32 w, uint32 h, uint16 bpp)
{
    infoHeader->setImageWidth(w);
    infoHeader->setImageHeight(h);
    infoHeader->setBitCount(bpp);
    adjustInternalDimensions();
}

uint32 BitmapFile::getPaletteSize (void) const
{
    return infoHeader->getNumColours();
}

const byte* BitmapFile::getPalette (void) const
{
    return infoHeader->getPaletteData();
}


void BitmapFile::setPaletteSize (uint32 size)
{
    infoHeader->setPaletteSize(size);
    infoHeader->setPalette(NULL);
    adjustInternalDimensions();
}

void BitmapFile::setPalette (const byte* pal)
{
    infoHeader->setPalette(pal);
}


byte* BitmapFile::getImageData () const
{
    return imageData;
}

void BitmapFile::setImageData (const byte* buff)
{
    if (imageData != NULL)
        delete [] imageData;

    imageData = new byte [infoHeader->getImageSize()];

    memcpy(imageData, buff, infoHeader->getImageSize());
}

void BitmapFile::convertRGBtoBGR (void)
{
    int bpp = 0;
    int width, height;
    int numEntries;
    register int i;
    byte tempCol;

    switch (infoHeader->getBitCount())
    {
        case 8:
            bpp = 1;
            break;
        case 16:
            bpp = 2;
            break;
        case 24:
            bpp = 3;
            break;
        case 32:
            bpp = 4;
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
        };
    }
}
