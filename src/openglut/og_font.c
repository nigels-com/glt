/*!
    \file  og_font.c
    \brief Bitmap and stroke fonts displaying.
*/
/*
 * Portions copyright (C) 2004, the OpenGLUT project contributors.
 * OpenGLUT branched from freeglut in February, 2004.
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Thu Dec 16 1999
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <GL/openglut.h>
#include "og_internal.h"

/*
 * TODO BEFORE THE STABLE RELEASE:
 *
 *  Test things out ...
 */

/* -- IMPORT DECLARATIONS -------------------------------------------------- */

/*
 * These are the font faces defined in og_font_data.c file:
 */
extern SOG_Font ogFontFixed8x13;
extern SOG_Font ogFontFixed9x15;
extern SOG_Font ogFontHelvetica10;
extern SOG_Font ogFontHelvetica12;
extern SOG_Font ogFontHelvetica18;
extern SOG_Font ogFontTimesRoman10;
extern SOG_Font ogFontTimesRoman24;
extern SOG_StrokeFont ogStrokeRoman;
extern SOG_StrokeFont ogStrokeMonoRoman;


/* -- PRIVATE FUNCTIONS ---------------------------------------------------- */

/*!
    Matches a font ID with a SOG_Font structure pointer.
    This was changed to match the GLUT header style.

    \bug  Only matches bitmapped fonts; the name should reflect that
          restriction.
*/
static SOG_Font *oghFontByID( void *font )
{
    if( font == GLUT_BITMAP_8_BY_13        )
        return &ogFontFixed8x13;
    if( font == GLUT_BITMAP_9_BY_15        )
        return &ogFontFixed9x15;
    if( font == GLUT_BITMAP_HELVETICA_10   )
        return &ogFontHelvetica10;
    if( font == GLUT_BITMAP_HELVETICA_12   )
        return &ogFontHelvetica12;
    if( font == GLUT_BITMAP_HELVETICA_18   )
        return &ogFontHelvetica18;
    if( font == GLUT_BITMAP_TIMES_ROMAN_10 )
        return &ogFontTimesRoman10;
    if( font == GLUT_BITMAP_TIMES_ROMAN_24 )
        return &ogFontTimesRoman24;

    ogWarning( "font 0x%08x not found", font );
    return 0;
}

/*!
    Matches a font ID with a SOG_StrokeFont structure pointer.
    This was changed to match the GLUT header style.
*/
static SOG_StrokeFont *oghStrokeByID( void *font )
{
    if( font == GLUT_STROKE_ROMAN      )
        return &ogStrokeRoman;
    if( font == GLUT_STROKE_MONO_ROMAN )
        return &ogStrokeMonoRoman;

    ogWarning( "stroke font 0x%08x not found", font );
    return 0;
}


/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*!
    \fn
    \brief    Draw a bitmapped character.
    \ingroup  fonts
    \param    fontID    A GLUT bitmapped font identifier.
    \param    character An ASCII character other than NUL.

              Draws one character in one font at the current
              OpenGL RasterPos.  Advances the RasterPos by
              the width of the \a character in the indicated font.

              Nothing happens if:
               - The \a character is not in the range [0..255], inclusive.
               - The \a fontID is not a valid font.

    \note     For long strings of text, it is faster to
              use glutBitmapString(), as that avoids a lot
              of OpenGL state changes between letters.
    \note     Does nothing if the RasterPos is offscreen.
    \see      glRasterPos(), glutBitmapWidth(), glutBitmapString(),
              glutBitmapHeight(), glutStrokeCharacter()
*/
void OGAPIENTRY glutBitmapCharacter( void *fontID, int character )
{
    const GLubyte *face;
    SOG_Font *font = oghFontByID( fontID );

    if( !font  ||
        ( 0 > character ) ||
        (255 < character ) )
        return;

    /* Find the glyph we want to draw. */
    face = font->Characters[ character ];

    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );
    glPixelStorei( GL_UNPACK_SWAP_BYTES,  GL_FALSE );
    glPixelStorei( GL_UNPACK_LSB_FIRST,   GL_FALSE );
    glPixelStorei( GL_UNPACK_ROW_LENGTH,  0        );
    glPixelStorei( GL_UNPACK_SKIP_ROWS,   0        );
    glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0        );
    glPixelStorei( GL_UNPACK_ALIGNMENT,   1        );
    glBitmap(
        face[ 0 ], font->Height,      /* The bitmap's width and height  */
        font->xorig, font->yorig,     /* The origin in the font glyph   */
        ( float )( face[ 0 ] ), 0.0,  /* The raster advance -- inc. x,y */
        ( face + 1 )                  /* The packed bitmap data...      */
    );
    glPopClientAttrib( );
}

/*!
    \fn
    \brief    Draw a string of bitmapped characters.
    \ingroup  fonts
    \param    fontID    A GLUT bitmapped font identifier.
    \param    string    A NUL-terminated ASCII string.

              A convenience function for drawing
              sequences of bitmapped characters, including
              linefeed handling.

              Likely to be more efficient than calling
              glutBitmapCharacter() in a loop.

              The first character displays at the OpenGL
              raster position.  The raster position is advanced
              horizontally as each character is rendered.
              Each newline character will reposition the
              raster position horizontally and advance
              vertically by the bitmap height.

              Nothing will be rendered if any of the following hold:
               - The \a fontID is invalid.
               - The current raster position is invalid.
               - The string is a NULL pointer or empty.

    \see      glRasterPos(), glutBitmapLength(), glutBitmapCharacter(),
              glutBitmapHeight(), glutStrokeString()
*/
void OGAPIENTRY glutBitmapString( void *fontID, const unsigned char *string )
{
    int c;
    int numchar;
    SOG_Font *font = oghFontByID( fontID );
    short x = 0;

    if( !font )
        return;
    if( !string || !*string )
        return;
    numchar = strlen( ( const char * )string );

    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );
    glPixelStorei( GL_UNPACK_SWAP_BYTES,  GL_FALSE );
    glPixelStorei( GL_UNPACK_LSB_FIRST,   GL_FALSE );
    glPixelStorei( GL_UNPACK_ROW_LENGTH,  0        );
    glPixelStorei( GL_UNPACK_SKIP_ROWS,   0        );
    glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0        );
    glPixelStorei( GL_UNPACK_ALIGNMENT,   1        );

    /*
     * Step through the string, drawing each character.
     * A newline will simply translate the next character's insertion
     * point back to the start of the line and down one line.
     */

    for( c = 0; c < numchar; c++ )
        if( string[ c ] == '\n' )
        {
            glBitmap( 0, 0, 0, 0, ( float )-x, ( float )-font->Height, NULL );
            x = 0;
        }
        else  /* Not an EOL, draw the bitmap character */
        {
            const GLubyte* face = font->Characters[ string[ c ] ];

            glBitmap(
                face[ 0 ], font->Height,     /* Bitmap's width and height    */
                font->xorig, font->yorig,    /* The origin in the font glyph */
                face[ 0 ], 0.0,              /* The raster advance; inc. x,y */
                face + 1                     /* The packed bitmap data...    */
            );

            x += face[ 0 ];
        }

    glPopClientAttrib( );
}

/*!
    \fn
    \brief    Returns the width in pixels of a character in a given font.
    \ingroup  fonts
    \param    fontID    A GLUT bitmapped font identifier.
    \param    character A character code.

              This function reports how far the RasterPos will advance
              if you putput this \a character in this \a font.
              It is also an upper bound
              on the width of the bitmapped glyph for \a character, though
              not all letters will use their full width, especially in the
              fixed-width fonts.

              Returns 0 if the \a character is out of the inclusive
              range [0,255] or if the \a fontID is invalid.

    \see      glutBitmapCharacter(), glutBitmapLength(), glutBitmapHeight()
              glutStrokeWidth()
*/
int OGAPIENTRY glutBitmapWidth( void *fontID, int character )
{
    int ret = 0;
    SOG_Font *font = oghFontByID( fontID );

    if( font &&
        ( 0 <= character ) &&
        ( 256 > character ) )
        ret = *( font->Characters[ character ] );

    return ret;
}

/*!
    \fn
    \brief    Returns the width in pixels of a string in a given font.
    \ingroup  fonts
    \param    fontID    A GLUT bitmapped font identifier.
    \param    string    A C-style (NUL-terminated) string.

              This function reports the sum of the widths of the
              characters in a \a string, using the font metrics of
              a given \a font.

              Like glutBitmapString(), glutBitmapLength() respects
              newlines in the input.

              Returns 0 if the \a fontID is invalid.

    \see      glutBitmapString(), glutBitmapWidth(), glutBitmapHeight(),
              glutStrokeLength()
*/
int OGAPIENTRY glutBitmapLength( void *fontID, const unsigned char *string )
{
    int c, length = 0, this_line_length = 0;
    SOG_Font *font = oghFontByID( fontID );
    int numchar = strlen( ( char * )string );

    if( font )
        for( c = 0; c < numchar; c++ )
        {
            if( string[ c ] != '\n' )/* Not an EOL, increment length of line */
                this_line_length += *( font->Characters[ string[ c ] ]);
            else  /* EOL; reset the length of this line */
            {
                if( length < this_line_length )
                    length = this_line_length;
                this_line_length = 0;
            }
        }

    if ( length < this_line_length )
        length = this_line_length;
    return length;
}

/*!
    \fn
    \brief    Returns the height of a given font.
    \ingroup  fonts
    \param    fontID    A GLUT bitmapped font identifier.

              Reports the height of a \a font as a global
              characteristic of that font.

              Returns 0 if \a fontID is out of range.

    \note     Does <i>not</i> report the height used by individual
              characters.  This may limit its usefulness; perhaps we
              should change it?  (And/or add a new function.)
    \todo     We have discussed adding a "font descender" query.
              We should go ahead and do it.
    \see      glutBitmapCharacter(), glutBitmapString(), glutBitmapWidth(),
              glutBitmapLength(), glutStrokeHeight()
*/
int OGAPIENTRY glutBitmapHeight( void *fontID )
{
    SOG_Font *font = oghFontByID( fontID );
    int ret = 0;

    if( font )
        ret = font->Height;

    return ret;
}

/*!
    \fn
    \brief    Draw a stroked character.
    \ingroup  fonts
    \param    fontID    A GLUT stroked font identifier.
    \param    character An ASCII character other than NUL.

              Draws one \a character from one stroked font
              using OpenGL \a GL_LINE_STRIP.  These characters
              are drawn at the origin in model space.
              Advances the the model space origin according to the
              font width.

              Does nothing if \a fontID is invalid, or if
              the \a character is out of the font's range.

    \note     For long strings of text, it is faster to use
              glutStrokeString().
    \see      glBegin(), glTranslatef(), glutStrokeWidth(), glutStrokeString(),
              glutStrokeHeight(), glutBitmapCharacter()
*/
void OGAPIENTRY glutStrokeCharacter( void *fontID, int character )
{
    const SOG_StrokeChar *schar;
    const SOG_StrokeStrip *strip;
    int i, j;
    SOG_StrokeFont *font = oghStrokeByID( fontID );

    if( !font ||
        ( 1 > character ) ||
        ( font->Quantity < character ) )
        return;

    schar = font->Characters[ character ];
    freeglut_return_if_fail( schar );
    strip = schar->Strips;

    for( i = 0; i < schar->Number; i++, strip++ )
    {
        glBegin( GL_LINE_STRIP );
        for( j = 0; j < strip->Number; j++ )
            glVertex2f( strip->Vertices[ j ].X, strip->Vertices[ j ].Y );
        glEnd( );
    }
    glTranslatef( schar->Right, 0.0, 0.0 );
}

/*!
    \fn
    \brief    Draw a string of stroked characters.
    \ingroup  fonts
    \param    fontID    A GLUT stroked font identifier.
    \param    string    A NUL-terminated ASCII string.

              <i>Almost</i> equivalent to calling glutStrokeCharacter()
              on each character in the string, successively.
              Mostly, it is a convenience function to hide the loop,
              and to treat \\n as a special symbol rather than a normal
              glyph.

              The first character displays at the current model space
              origin,  The origin changes by successive translations.

              The newline character, \\n (ASCII LF) is treated as
              a newline and resets the origin horizontally
              while advancing the line 1 font-height down the y-axis.

              Does nothing if:
               - \a fontID is out of range.
               - \a string is \a NULL
               - \a string is empty

    \see      glutStrokeLength(), glutStrokeCharacter(),
              glutStrokeHeight(), glutBitmapString()
*/
void OGAPIENTRY glutStrokeString( void *fontID, const unsigned char *string )
{
    int c, i, j;
    int numchar;
    float length = 0.0;
    SOG_StrokeFont *font = oghStrokeByID( fontID );

    if( font && string && *string )
        /*
         * Step through the string, drawing each character.
         * A newline will simply translate the next character's insertion
         * point back to the start of the line and down one line.
         */
        for( c = 0, numchar = strlen( ( char * )string ); c < numchar; c++ )
            if( string[ c ] < font->Quantity )
            {
                if( string[ c ] == '\n' )
                {
                    glTranslatef ( -length, -( float )( font->Height ), 0.0 );
                    length = 0.0;
                }
                else  /* Not an EOL, draw the bitmap character */
                {
                    const SOG_StrokeChar *schar =
                        font->Characters[ string[ c ] ];
                    if( schar )
                    {
                        const SOG_StrokeStrip *strip = schar->Strips;

                        for( i = 0; i < schar->Number; i++, strip++ )
                        {
                            glBegin( GL_LINE_STRIP );
                            for( j = 0; j < strip->Number; j++ )
                                glVertex2f( strip->Vertices[ j ].X,
                                            strip->Vertices[ j ].Y);

                            glEnd( );
                        }

                        length += schar->Right;
                        glTranslatef( schar->Right, 0.0, 0.0 );
                    }
                }
            }
}

/*!
    \fn
    \brief    Returns the width in pixels of a character in a given font.
    \ingroup  fonts
    \param    fontID    A GLUT stroked font identifier.
    \param    character A character code.

              This function reports how far the model space originwill advance
              if you putput this \a character in this \a font.
              It is also an upper bound
              on the width of the stroked glyph for \a character, though
              not all letters will use their full width, especially in
              fixed-width fonts.

              Returns 0 if \a character is out of range or if the
              \a fontID is invalid.

    \note     The character widths are stored in floating point, but
              this function rounds to an integer, so the result may
              be rather inaccurate.
    \note     freeglut, and at least some original GLUT documentation,
              claim that this function returns the width of the glyph
              in <b>pixels</b>.  But that is not what the freeglut
              code does.  It is presumed that freeglut's code is
              correct, and other documentation is in error.
    \todo     Change this to report a float instead?  Quite possibly, the
              integer return-type is part of the same documentation error
              that led to claiming that this returns a width in pixels.
    \see      glutStrokeCharacter(), glutStrokeLength(), glutStrokeHeight()
              glutBitmapWidth()
*/
int OGAPIENTRY glutStrokeWidth( void *fontID, int character )
{
    int ret = 0;
    SOG_StrokeFont *font = oghStrokeByID( fontID );

    if( font &&
        ( 0 < character ) &&
        ( font->Quantity > character ) )
    {
        const SOG_StrokeChar *schar = font->Characters[ character ];
        if( schar )
            ret = ( int )( schar->Right + 0.5 );
    }

    return ret;
}

/*!
    \fn
    \brief    Returns model space width of a string in a given font.
    \ingroup  fonts
    \param    fontID    A GLUT stroked font identifier.
    \param    string    A C-style (NUL-terminated) string.

              This function reports the sum of the widths of the
              characters in a \a string, using the font metrics of
              a given \a font.  (It also rounds to an integer only
              once for the whole string.)

              Like glutStrokeString(), glutStrokeLength() respects
              newlines in the input.

              Returns 0 if \a fontID is out of range.

    \see      glutStrokeString(), glutStrokeWidth(), glutStrokeHeight(),
              glutBitmapLength()
*/
int OGAPIENTRY glutStrokeLength( void *fontID, const unsigned char *string )
{
    int c;
    float length = 0.0;
    float this_line_length = 0.0;
    SOG_StrokeFont *font = oghStrokeByID( fontID );
    int numchar = strlen( (char *) string );

    if( font )
        for( c = 0; c < numchar; c++ )
            if( string[ c ] < font->Quantity )
            {
                if( string[ c ] == '\n' )
                {
                    if( length < this_line_length )
                        length = this_line_length;
                    this_line_length = 0.0;
                }
                else  /* Not an EOL, increment the length of this line */
                {
                    const SOG_StrokeChar *schar =
                        font->Characters[ string[ c ] ];
                    if( schar )
                        this_line_length += schar->Right;
                }
            }

    if( length < this_line_length )
        length = this_line_length;
    return( int )( length + 0.5 );
}

/*!
    \fn
    \brief    Returns the height of a given font.
    \ingroup  fonts
    \param    fontID    A GLUT stroked font identifier.

              Reports the height of a \a font as a global
              characteristic of that font.

              Returns 0 if \a fontID is invalid.

    \note     Unlike <i>all</i> other font metrics, this returns
              a floating point value.
    \note     Does <i>not</i> report the height used by individual
              characters.  This may limit its usefulness; perhaps we
              should change it?  (And/or add a new function.)
    \todo     We have discussed adding a "font descender" query.
              We should go ahead and do it.
    \see      glutStrokeCharacter(), glutStrokeString(), glutStrokeWidth(),
              glutStrokeLength(), glutBitmapHeight()
*/
GLfloat OGAPIENTRY glutStrokeHeight( void *fontID )
{
    GLfloat ret = 0;
    SOG_StrokeFont *font = oghStrokeByID( fontID );

    if( font )
        ret = font->Height;

    return ret;
}
