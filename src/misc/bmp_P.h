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

#include <glt/config.h>

struct BitmapFileHeader
{
   uint16   fileType;     /* specifies file type must be BM (4D42h) */
   uint32  fileSize;     /* file size in bytes (54) */

   uint16   res1;         /* must be 0 */
   uint16   res2;         /* must be 0 */
   uint32  imageOffset;  /* offset in bytes from the header to the data (40) */

   public:

   BitmapFileHeader();
   ~BitmapFileHeader();

   void saveToBuffer( byte** );
   int loadFromBuffer( const byte** );

   inline void setFileSize( uint32 val ) { fileSize = val; }
   inline void setImageOffset( uint32 val ) { ImageOffset = val; }


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
   uint32  infoSize;     /* information header size in bytes (40) */
   uint32  imageWidth;   /* width of the bitmap in pixels (0) */
   uint32  imageHeight;  /* height of the bitmap in pixels (0) */
   uint16   colourPlanes; /* must be 1 */
   uint16   bitCount;     /* bits per pixel, 1, 4, 8, 16, (24), 32 */
   uint32  compression;  /* compression type (0) */
   uint32  imageSize;    /* size of image in bytes (0) */
   uint32  pixelsX;      /* number of pixels in x per meter (2834) */
   uint32  pixelsY;      /* number of pixels in y per meter (2834) */
   uint32  numColours;   /* number of colours used in the image (0) */
   uint32  numImportant; /* number of important colours (0) */
   byte*  paletteData;  /* the palette data that may follow */

   public:

   BitmapInfoHeader();
   ~BitmapInfoHeader();

   void saveToBuffer( byte** );
   int loadFromBuffer( const byte** );

   void savePaletteToBuffer( byte** );
   void loadPaletteBuffer( const byte** );

   inline uint32 getImageWidth() const { return imageWidth; }
   inline uint32 getImageHeight() const { return imageHeight; }
   inline uint32 getImageSize() const { return imageSize; }
   inline uint32 getNumberOfColours() const { return numColours; }
   inline uint32 getBitCount() const { return bitCount; }
};


/**
 * Wrapper struct to hold image & palette data and interface with the headers
 */

struct BitmapFile
{
   BitmapFileHeader*  fileHeader;
   BitmapInfoHeader*  infoHeader;
   byte*    imageData;

   public:

   BitmapFile();
   ~BitmapFile();

/**
 * Loading, saving and initalising
 */

   void saveToBuffer( byte** );
   /* returns 1 on error */
   int loadFromBuffer( const byte** );

/**
 * Getting & setting dimensions and other info
 */
   uint32 getWidth( );
   uint32 getHeight( );
   uint16 getBpp( );
   uint32 getImageSize( );

   void setWidth( uint32 );
   void setHeight( uint32 );
   void setBpp( uint16 );

   void setDimensions( uint32 w, uint32 h, uint16 bpp );

/**
 * Palette specific functions
 */

   uint32 getPaletteSize( );
   const byte* getPalette( );

   void setPaletteSize( uint32 );

   void setPalette( const byte* );

/**
 * Getting and setting the image data
 */

   byte* getImageData( );
   void setImageData( const byte* );

   void convertRGBtoBGR( );

};


#endif
