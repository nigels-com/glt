/***************************************************************************
                          bmp_P.c  -  description
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bmp_P.h"


/**
 * private functions
 */
#define DEFAULT_FILE_SIZE 54
#define DEFAULT_IMAGE_OFFSET 54
#define NO_COMPRESSION 0
#define DPI_TO_METERS 2834

/*File header methods*/
void initBitmapFileHeader(BitmapFileHeader*);
void loadBitmapFileHeader(BitmapFileHeader*, FILE*);
void saveBitmapFileHeader(BitmapFileHeader*, FILE*);

int loadBitmapFileHeaderFromBuffer(BitmapFileHeader*, const byte_t**);
void saveBitmapFileHeaderToBuffer(BitmapFileHeader*, byte_t**);

/*File info header methods*/
void initBitmapInfoHeader(BitmapInfoHeader*);
void loadBitmapInfoHeader(BitmapInfoHeader*, FILE*);
void saveBitmapInfoHeader(BitmapInfoHeader*, FILE*);

void loadBitmapInfoHeaderFromBuffer(BitmapInfoHeader*, const byte_t**);
void saveBitmapInfoHeaderToBuffer(BitmapInfoHeader*, byte_t**);

/*File structure methods*/
void initBitmapFileStructure(BitmapFileStructure*);
void loadBitmapFileStructure(BitmapFileStructure*, FILE*);
void saveBitmapFileStructure(BitmapFileStructure*, FILE*);

int loadBitmapFileStructureFromBuffer(BitmapFileStructure*, const byte_t**);
void saveBitmapFileStructureToBuffer(BitmapFileStructure*, byte_t**);

/*palette methods*/
void loadBitmapPalette(BitmapInfoHeader*, FILE*);
void saveBitmapPalette(BitmapInfoHeader*, FILE*);

void loadBitmapPaletteFromBuffer(BitmapInfoHeader*, const byte_t**);
void saveBitmapPaletteToBuffer(BitmapInfoHeader*, byte_t**);

/*private internal functions*/
void adjustInternalDimensions(BitmapFileStructure*);

void setBitmapPaletteSizeIH(BitmapInfoHeader*, dword_t);
void setBitmapPaletteIH(BitmapInfoHeader*, const byte_t* );


void initBitmapFileHeader(BitmapFileHeader* fh)
{
   fh->fileType = 0x04D42;
   fh->fileSize = DEFAULT_FILE_SIZE;
   fh->res1 = 0;
   fh->res2 = 0;
   fh->imageOffset = DEFAULT_IMAGE_OFFSET;
}

void loadBitmapFileHeader(BitmapFileHeader* fh, FILE* infile)
{

   fh->fileType = readWordFromFile( infile );
   fh->fileSize = readDwordFromFile( infile );
   
   /* these are always 0 so no need to worry about byte-order */
   fread(&(fh->res1), 2, 1, infile);
   fread(&(fh->res2), 2, 1, infile);
   
   fh->imageOffset = readDwordFromFile( infile );
   
}
   
void saveBitmapFileHeader(BitmapFileHeader* fh, FILE* outfile)
{
   writeWordToFile( fh->fileType, outfile );
   writeDwordToFile( fh->fileSize, outfile );
   
   /* these are always 0 so no need to worry about byte-order */
   fwrite(&(fh->res1), 2, 1, outfile);
   fwrite(&(fh->res2), 2, 1, outfile);

   writeDwordToFile( fh->imageOffset, outfile );
}

/* buffer version */
int loadBitmapFileHeaderFromBuffer(BitmapFileHeader* fh, const byte_t** buff)
{
   fh->fileType = readWordFromBuffer( buff );

   if( fh->fileType != 0x04D42 )/*check for the correct id*/
      return 0;
      
   fh->fileSize = readDwordFromBuffer( buff );

   /* these are always 0 so no need to worry about byte-order */
   fh->res1 = readWordFromBuffer( buff );
   fh->res2 = readWordFromBuffer( buff );

   fh->imageOffset = readDwordFromBuffer( buff );

   return 1;
}

/* buffer version */
void saveBitmapFileHeaderToBuffer(BitmapFileHeader* fh, byte_t** buff)
{
   writeWordToBuffer( fh->fileType, buff );
   writeDwordToBuffer( fh->fileSize, buff );

   /* these are always 0 so no need to worry about byte-order */
   writeWordToBuffer( fh->res1, buff );
   writeWordToBuffer( fh->res2, buff );

   writeDwordToBuffer( fh->imageOffset, buff );
}

void initBitmapInfoHeader(BitmapInfoHeader* fh)
{
   fh->infoSize = 40;
   fh->imageWidth = 0;
   fh->imageHeight = 0;
   fh->colourPlanes = 1;
   fh->bitCount = 24;
   fh->compression = NO_COMPRESSION;
   fh->imageSize = 0;
   fh->pixelsX = DPI_TO_METERS;
   fh->pixelsY = DPI_TO_METERS;
   fh->numColours = 0;
   fh->numImportant = 0;
   fh->paletteData = NULL;
}

void loadBitmapInfoHeader(BitmapInfoHeader* fh, FILE* infile)
{
   fh->infoSize = readDwordFromFile( infile );
   fh->imageWidth = readDwordFromFile( infile );
   fh->imageHeight = readDwordFromFile( infile );
   fh->colourPlanes = readWordFromFile( infile );
   fh->bitCount = readWordFromFile( infile );
   fh->compression = readDwordFromFile( infile );
   fh->imageSize = readDwordFromFile( infile );
   fh->pixelsX = readDwordFromFile( infile );
   fh->pixelsY = readDwordFromFile( infile );
   fh->numColours = readDwordFromFile( infile );
   fh->numImportant = readDwordFromFile( infile );

   loadBitmapPalette( fh, infile );
}

void loadBitmapPalette(BitmapInfoHeader* fh, FILE* infile)
{
   if( fh->numColours > 0 )
   {
      register unsigned i;

      /* generate an empty palette */
      setBitmapPaletteSizeIH( fh, fh->numColours );

      for(i = 0; i < fh->numColours; ++i)
         fread( (fh->paletteData)+(i*4), 4, 1, infile );
   }      
}


void saveBitmapInfoHeader(BitmapInfoHeader* fh, FILE* outfile)
{
   writeDwordToFile( fh->infoSize, outfile);
   writeDwordToFile( fh->imageWidth, outfile);
   writeDwordToFile( fh->imageHeight, outfile);
   writeWordToFile( fh->colourPlanes, outfile);
   writeWordToFile( fh->bitCount, outfile);
   writeDwordToFile( fh->compression, outfile);
   writeDwordToFile( fh->imageSize, outfile);
   writeDwordToFile( fh->pixelsX, outfile);
   writeDwordToFile( fh->pixelsY, outfile);
   writeDwordToFile( fh->numColours, outfile);
   writeDwordToFile( fh->numImportant, outfile);

   saveBitmapPalette( fh, outfile );
}   

void saveBitmapPalette(BitmapInfoHeader* fh, FILE* outfile)
{
   if( fh->numColours > 0 )
   {
      register unsigned i;

      for(i = 0; i < fh->numColours; ++i)
         fwrite( (fh->paletteData)+(i*4), 4, 1, outfile );
   }
}

/* buffer version */
void loadBitmapInfoHeaderFromBuffer(BitmapInfoHeader* fh, const byte_t** buff)
{
   fh->infoSize = readDwordFromBuffer( buff );
   fh->imageWidth = readDwordFromBuffer( buff );
   fh->imageHeight = readDwordFromBuffer( buff );
   fh->colourPlanes = readWordFromBuffer( buff );
   fh->bitCount = readWordFromBuffer( buff );
   fh->compression = readDwordFromBuffer( buff );
   fh->imageSize = readDwordFromBuffer( buff );
   fh->pixelsX = readDwordFromBuffer( buff );
   fh->pixelsY = readDwordFromBuffer( buff );
   fh->numColours = readDwordFromBuffer( buff );
   fh->numImportant = readDwordFromBuffer( buff );

   loadBitmapPaletteFromBuffer( fh, buff );
}

/* buffer version */
void loadBitmapPaletteFromBuffer(BitmapInfoHeader* fh, const byte_t** buff)
{
   if( fh->numColours > 0 )
   {
      /* generate an empty palette */
      setBitmapPaletteSizeIH( fh, fh->numColours );

      memcpy( (fh->paletteData), *buff, fh->numColours*4 );
      
      (*buff) += fh->numColours*4;
   }
}


/* buffer version */
void saveBitmapInfoHeaderToBuffer(BitmapInfoHeader* fh, byte_t** buff)
{
   writeDwordToBuffer( fh->infoSize, buff);
   writeDwordToBuffer( fh->imageWidth, buff);
   writeDwordToBuffer( fh->imageHeight, buff);
   writeWordToBuffer( fh->colourPlanes, buff);
   writeWordToBuffer( fh->bitCount, buff);
   writeDwordToBuffer( fh->compression, buff);
   writeDwordToBuffer( fh->imageSize, buff);
   writeDwordToBuffer( fh->pixelsX, buff);
   writeDwordToBuffer( fh->pixelsY, buff);
   writeDwordToBuffer( fh->numColours, buff);
   writeDwordToBuffer( fh->numImportant, buff);

   saveBitmapPaletteToBuffer( fh, buff );
}

/* buffer version */
void saveBitmapPaletteToBuffer(BitmapInfoHeader* fh, byte_t** buff)
{
   if( fh->numColours > 0 )
   {
      memcpy( *buff, (fh->paletteData), fh->numColours*4 );

      (*buff) += fh->numColours*4;
   }
}
                  
void initBitmapFileStructure(BitmapFileStructure* fs)
{
   initBitmapFileHeader(&(fs->fileHeader));
   initBitmapInfoHeader(&(fs->infoHeader));
   
   fs->imageData = NULL;
}

void loadBitmapFileStructure(BitmapFileStructure* fs, FILE* infile)
{
   loadBitmapFileHeader(&(fs->fileHeader), infile);
   loadBitmapInfoHeader(&(fs->infoHeader), infile);

   if(fs->infoHeader.imageSize == 0)
      return;

   if( fs->imageData )
      free( fs->imageData );
      
   fs->imageData = malloc( fs->infoHeader.imageSize );

   fread(fs->imageData, 1, fs->infoHeader.imageSize, infile);
}

void saveBitmapFileStructure(BitmapFileStructure* fs, FILE* outfile)
{
   saveBitmapFileHeader(&(fs->fileHeader), outfile);
   saveBitmapInfoHeader(&(fs->infoHeader), outfile);

   if(fs->infoHeader.imageSize == 0)
      return;
   else
      fwrite(fs->imageData, 1, fs->infoHeader.imageSize, outfile);
}

/* buffer version */
int loadBitmapFileStructureFromBuffer(BitmapFileStructure* fs, const byte_t** buff)
{
   if( loadBitmapFileHeaderFromBuffer(&(fs->fileHeader), buff) == 0 )
      return 0;
      
   loadBitmapInfoHeaderFromBuffer(&(fs->infoHeader), buff);

   if(fs->infoHeader.imageSize == 0)
      return 1;

   if( fs->imageData )
      free( fs->imageData );

   fs->imageData = malloc( fs->infoHeader.imageSize );

   memcpy(fs->imageData, *buff, fs->infoHeader.imageSize);
   (*buff) += fs->infoHeader.imageSize;

   return 1;
}

/* buffer version */
void saveBitmapFileStructureToBuffer(BitmapFileStructure* fs, byte_t** buff)
{
   saveBitmapFileHeaderToBuffer(&(fs->fileHeader), buff);
   saveBitmapInfoHeaderToBuffer(&(fs->infoHeader), buff);

   if(fs->infoHeader.imageSize == 0)
      return;
   else
   {
      memcpy(*buff, fs->imageData, fs->infoHeader.imageSize);
      (*buff) += fs->infoHeader.imageSize;
   }
      
}

void adjustInternalDimensions(BitmapFileStructure* fs)
{
   dword_t w, h, palSize;
   word_t bpp;

   w = fs->infoHeader.imageWidth;
   h = fs->infoHeader.imageHeight;
   palSize = fs->infoHeader.numColours * 4;
   bpp = fs->infoHeader.bitCount;

   fs->infoHeader.imageSize = (dword_t)(w * h * ( (float) bpp / 8 ));
   fs->fileHeader.fileSize = DEFAULT_FILE_SIZE + fs->infoHeader.imageSize + palSize;
   fs->fileHeader.imageOffset = DEFAULT_IMAGE_OFFSET + palSize;   
}
         
/**
 * public functions
 */
 
void initBitmapFile(BitmapFile* bf)
{
   initBitmapFileStructure(&bf->fileStructure);
   bf->fileName = NULL;
}

void saveBitmapFile(BitmapFile* bf)
{
   FILE* file = fopen( bf->fileName, "wb" );

   if(file)
   {
      saveBitmapFileStructure( &bf->fileStructure, file);

      fclose(file);
   }
}

void loadBitmapFile(BitmapFile* bf)
{
   FILE* file = fopen( bf->fileName, "rb" );

   if(file)
   {
      loadBitmapFileStructure( &bf->fileStructure, file);
      fclose(file);
   }
}

/* buffer version */
void saveBitmapFileToBuffer(BitmapFile* bf, byte_t* buff)
{
   byte_t* ptr = buff;

   if( buff == NULL )
      return;


   saveBitmapFileStructureToBuffer( &bf->fileStructure, &ptr );
}   

/* buffer version */
/** returns 0 if the buffer does not contain a bmp structure */
int loadBitmapFileFromBuffer(BitmapFile* bf, const byte_t* buff)
{
   const byte_t* ptr = buff;

   if( buff == NULL )
      return 0;

   return loadBitmapFileStructureFromBuffer( &bf->fileStructure, &ptr );
   /* the buffer is a valid bitmap? 0 = No; anything else = Yes */
}

void deleteBitmapFile(BitmapFile* bf)
{
   if( bf->fileStructure.infoHeader.paletteData )
      free( bf->fileStructure.infoHeader.paletteData );
   if( bf->fileStructure.imageData )
      free( bf->fileStructure.imageData );
}

void setBitmapFileName(BitmapFile* bf, const char* fname)
{
   if( bf->fileName )
      free( bf->fileName );

   bf->fileName = malloc( strlen(fname) + 1);
   
   strcpy(bf->fileName, fname);
}
   

dword_t getBitmapWidth(const BitmapFile* const bf)
{
   return bf->fileStructure.infoHeader.imageWidth;
}

dword_t getBitmapHeight(const BitmapFile* const bf)
{
   return bf->fileStructure.infoHeader.imageHeight;
}

word_t getBitmapBpp(const BitmapFile* const bf)
{
   return bf->fileStructure.infoHeader.bitCount;
}

dword_t getBitmapImageSize(const BitmapFile* const bf)
{
   return bf->fileStructure.infoHeader.imageSize;
}

void setBitmapWidth(BitmapFile* bf, dword_t w)
{
   bf->fileStructure.infoHeader.imageWidth = w;
   adjustInternalDimensions(&bf->fileStructure);
}
   
void setBitmapHeight(BitmapFile* bf, dword_t h)
{
   bf->fileStructure.infoHeader.imageHeight = h;
   adjustInternalDimensions(&bf->fileStructure);
}

void setBitmapBpp(BitmapFile* bf, word_t bpp)
{
   bf->fileStructure.infoHeader.bitCount = bpp;
   adjustInternalDimensions(&bf->fileStructure);
}

void setBitmapDimensions(BitmapFile* bf, dword_t w, dword_t h, word_t bpp)
{
   bf->fileStructure.infoHeader.imageWidth = w;
   bf->fileStructure.infoHeader.imageHeight = h;
   bf->fileStructure.infoHeader.bitCount = bpp;
   adjustInternalDimensions(&bf->fileStructure);
}

dword_t getBitmapPaletteSize(const BitmapFile* const bf)
{
   return bf->fileStructure.infoHeader.numColours;
}

const byte_t* getBitmapPalette(const BitmapFile* const bf)
{
   return bf->fileStructure.infoHeader.paletteData;
}
   
void setBitmapPaletteSizeIH(BitmapInfoHeader* fh, dword_t size)
{
   fh->numColours = size;
   /*bf->fileStructure.infoHeader.numImportant = size;*/

   setBitmapPaletteIH( fh, NULL );
}

void setBitmapPaletteSize(BitmapFile* bf, dword_t size)
{
   setBitmapPaletteSizeIH( &bf->fileStructure.infoHeader , size );
   adjustInternalDimensions( &bf->fileStructure );
}
      
void setBitmapPaletteIH(BitmapInfoHeader* fh, const byte_t* pal)
{
   if( fh->paletteData )
      free( fh->paletteData );

   fh->paletteData = malloc( fh->numColours * 4 );

   if( pal )
      memcpy( fh->paletteData, pal, fh->numColours * 4 );
   else
   {
      register unsigned i;
      for( i = 0; i < fh->numColours*4; ++i )
         fh->paletteData[i] = 0;
   }
         
}

void setBitmapPalette(BitmapFile* bf, const byte_t* pal)
{
   setBitmapPaletteIH(&bf->fileStructure.infoHeader, pal);
}

byte_t* getBitmapImageData(const BitmapFile* const bf)
{
   return bf->fileStructure.imageData;
}

void setBitmapImageData(BitmapFile* const bf, const byte_t* buff)
{
   if( bf->fileStructure.imageData != NULL )
      free( bf->fileStructure.imageData );

   bf->fileStructure.imageData = malloc( bf->fileStructure.infoHeader.imageSize );

   memcpy( bf->fileStructure.imageData, buff, bf->fileStructure.infoHeader.imageSize );
}

void convertBitmapFileRGBtoBGR( BitmapFile* bf )
{
   int bpp = 0;
   int width, height;
   int numEntries;
   register int i;
   byte_t tempCol;

   switch( bf->fileStructure.infoHeader.bitCount )
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

   width = bf->fileStructure.infoHeader.imageWidth;
   height = bf->fileStructure.infoHeader.imageHeight;
   
   numEntries = width*height*bpp;

   if(bpp == 3)
   {
      for( i = 0; i < numEntries; i+=3)
      {
         tempCol = bf->fileStructure.imageData[i+2];
         bf->fileStructure.imageData[i+2] = bf->fileStructure.imageData[i];
         bf->fileStructure.imageData[i] = tempCol;
      };
   }
}
