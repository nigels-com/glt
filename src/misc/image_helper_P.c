/***************************************************************************
                          image_helper_P.c  -  description
                             -------------------
    begin                : Tue Feb 10 2004
    copyright            : (C) 2004 by jgasseli
    email                : jgasseli@jacques.home
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *                                                                         *
 ***************************************************************************/

#include "image_helper_P.h"

word_t readWordFromFile( FILE* infile)
{
   byte_t ax[2];   /*mimic the x86 so that we know which order they go in */

   fread(ax,1,2,infile);

   return ((word_t)ax[0]) + (((word_t)ax[1])<<8);
}

dword_t readDwordFromFile( FILE* infile)
{
   byte_t eax[4];   /*mimic the x86 so that we know which order they go in */

   fread(eax,1,4,infile);

   return ((dword_t)eax[0]) + (((dword_t)eax[1])<<8) + (((dword_t)eax[2])<<16) + (((dword_t)eax[3])<<24);
}

void writeWordToFile( word_t val, FILE* outfile)
{
   byte_t ax[2];   /*mimic the x86 so that we know which order they go in */

   ax[0] = val & 0xFF;
   val = val >> 8;
   ax[1] = val & 0xFF;

   fwrite(ax,1,2,outfile);
}

void writeDwordToFile( dword_t val, FILE* outfile)
{
   byte_t eax[4];   /*mimic the x86 so that we know which order they go in */

   eax[0] = val & 0xFF;
   val = val >> 8;
   eax[1] = val & 0xFF;
   val = val >> 8;
   eax[2] = val & 0xFF;
   val = val >> 8;
   eax[3] = val & 0xFF;

   fwrite(eax,1,4,outfile);
}

word_t readWordFromBuffer( const byte_t** buff )
{
   byte_t ax[2];   /*mimic the x86 so that we know which order they go in */

   ax[0] = **buff;
   ++(*buff);
   ax[1] = **buff;
   ++(*buff);

   return ((word_t)ax[0]) + (((word_t)ax[1])<<8);
}

dword_t readDwordFromBuffer( const byte_t** buff)
{
   byte_t eax[4];   /*mimic the x86 so that we know which order they go in */

   eax[0] = **buff;
   ++(*buff);
   eax[1] = **buff;
   ++(*buff);
   eax[2] = **buff;
   ++(*buff);
   eax[3] = **buff;
   ++(*buff);

   return ((dword_t)eax[0]) + (((dword_t)eax[1])<<8) + (((dword_t)eax[2])<<16) + (((dword_t)eax[3])<<24);
}

void writeWordToBuffer( word_t val, byte_t** buff)
{
   byte_t ax[2];   /*mimic the x86 so that we know which order they go in */

   ax[0] = val & 0xFF;
   val = val >> 8;
   ax[1] = val & 0xFF;

   **buff = ax[0];
   ++(*buff);
   **buff = ax[1];
   ++(*buff);
   
}

void writeDwordToBuffer( dword_t val, byte_t** buff)
{
   byte_t eax[4];   /*mimic the x86 so that we know which order they go in */

   eax[0] = val & 0xFF;
   val = val >> 8;
   eax[1] = val & 0xFF;
   val = val >> 8;
   eax[2] = val & 0xFF;
   val = val >> 8;
   eax[3] = val & 0xFF;

   **buff = eax[0];
   ++(*buff);
   **buff = eax[1];
   ++(*buff);
   **buff = eax[2];
   ++(*buff);
   **buff = eax[3];
   ++(*buff);
}
