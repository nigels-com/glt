/***************************************************************************
                          image_helper_P.h  -  description
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

#ifndef IMAGE_HELPER_P_H
#define IMAGE_HELPER_P_H

#include <stdio.h>

typedef unsigned char byte_t;
typedef unsigned short word_t;
typedef unsigned int dword_t;

/** increments the position in the file */
word_t readWordFromFile( FILE* );
dword_t readDwordFromFile( FILE* );

/** increments the position in the file */
void writeWordToFile( word_t, FILE* );
void writeDwordToFile( dword_t, FILE* );

/** increments the position in the buffer */
word_t readWordFromBuffer( const byte_t** );
dword_t readDwordFromBuffer( const byte_t** );

/** increments the position in the buffer */
void writeWordToBuffer( word_t, byte_t** );
void writeDwordToBuffer( dword_t, byte_t** );

#endif
