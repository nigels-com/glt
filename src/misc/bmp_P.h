/***************************************************************************
                          bmp_P.h  -  description
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

#ifndef BITMAP_P_H
#define BITMAP_P_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "image_helper_P.h"

typedef struct 
{
   word_t   fileType;     /* specifies file type must be BM (4D42h) */
   dword_t  fileSize;     /* file size in bytes (54) */
            
   word_t   res1;         /* must be 0 */
   word_t   res2;         /* must be 0 */
   dword_t  imageOffset;  /* offset in bytes from the header to the data (40) */
   
} BitmapFileHeader;

/** wrapper for the palette data.
 * MS-WIN use 4 byte quads as opposed to Adobe with 3 byte entries.
 * Therefore a full 256 color palette in .pal format is 1K but a 256 color
 * .act is 768B
 */

/**
 * The sub header of a BMP file
 */

typedef struct 
{
   dword_t  infoSize;     /* information header size in bytes (40) */
   dword_t  imageWidth;   /* width of the bitmap in pixels (0) */
   dword_t  imageHeight;  /* height of the bitmap in pixels (0) */
   word_t   colourPlanes; /* must be 1 */
   word_t   bitCount;     /* bits per pixel, 1, 4, 8, 16, (24), 32 */
   dword_t  compression;  /* compression type (0) */
   dword_t  imageSize;    /* size of image in bytes (0) */
   dword_t  pixelsX;      /* number of pixels in x per meter (2834) */
   dword_t  pixelsY;      /* number of pixels in y per meter (2834) */
   dword_t  numColours;   /* number of colours used in the image (0) */
   dword_t  numImportant; /* number of important colours (0) */
   byte_t*  paletteData;  /* the palette data that may follow */
} BitmapInfoHeader;


/**
 * Wrapper struct to hold image & palette data and interface with the headers
 */

typedef struct 
{
   BitmapFileHeader  fileHeader;
   BitmapInfoHeader  infoHeader;
   byte_t*    imageData;
} BitmapFileStructure;


/**
 * Handler object, interfaces between end user and wrapper class
 * Use only this struct in your program
 */

typedef struct 
{
   BitmapFileStructure fileStructure;
   char* fileName;
} BitmapFile;

/**
 * Loading, saving and initalising
 */
 
void initBitmapFile(BitmapFile*);
void saveBitmapFile(BitmapFile*);
void loadBitmapFile(BitmapFile*);
void deleteBitmapFile(BitmapFile*);

void saveBitmapFileToBuffer(BitmapFile*, byte_t*);

/** returns 0 if the buffer does not contain a bmp structure */
int loadBitmapFileFromBuffer(BitmapFile*, const byte_t*);

void setBitmapFileName(BitmapFile*, const char*);

/**
 * Getting & setting dimensions and other info
 */

dword_t getBitmapWidth(const BitmapFile* const );
dword_t getBitmapHeight(const BitmapFile* const );
word_t getBitmapBpp(const BitmapFile* const );
dword_t getBitmapImageSize(const BitmapFile* const );

void setBitmapWidth(BitmapFile* const,  dword_t);
void setBitmapHeight(BitmapFile* const, dword_t);
void setBitmapBpp(BitmapFile* const, word_t);

void setBitmapDimensions(BitmapFile* const, dword_t w, dword_t h, word_t bpp);

/**
 * Palette specific functions
 */

dword_t getBitmapPaletteSize(const BitmapFile* const );
const byte_t* getBitmapPalette(const BitmapFile* const );

void setBitmapPaletteSize(BitmapFile* const, dword_t);

void setBitmapPalette(BitmapFile* const, const byte_t* );


/**
 * Getting and setting the image data
 */
 
byte_t* getBitmapImageData(const BitmapFile* const);
void setBitmapImageData(BitmapFile* const, const byte_t*);

void convertBitmapFileRGBtoBGR(BitmapFile* const);

#ifdef __cplusplus
}
#endif

#endif
