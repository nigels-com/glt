/*!
    \file  og_font.c
    \brief Bitmap and stroke fonts
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
    \brief    Draw a bitmapped character
    \ingroup  bitmapfont
    \param    font      A bitmapped font identifier.
    \param    character A character code.

              Draw a \a character at the current OpenGL raster position
              using a bitmapped \a font.  The raster position is advanced
              by the width of the character.

              Nothing is drawn, and the raster position is unaffected when
              either:
              - \a character is out of range
              - \a font is not a valid OpenGLUT bitmap font
              - The current OpenGL raster position is invalid

    \note     glutBitmapString() is generally more efficient for 
              strings of characters.

    \see      glRasterPos(), glutBitmapString(), glutBitmapWidth(), 
              glutBitmapHeight()
*/
void OGAPIENTRY glutBitmapCharacter( void *font, int character )
{
    const GLubyte *face;
    SOG_Font *f = oghFontByID( font );

    if( !f ||
        ( 0 > character ) ||
        (255 < character ) )
        return;

    /* Find the glyph we want to draw. */
    face = f->Characters[ character ];

    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );

        glPixelStorei( GL_UNPACK_SWAP_BYTES,  GL_FALSE );
        glPixelStorei( GL_UNPACK_LSB_FIRST,   GL_FALSE );
        glPixelStorei( GL_UNPACK_ROW_LENGTH,  0        );
        glPixelStorei( GL_UNPACK_SKIP_ROWS,   0        );
        glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0        );
        glPixelStorei( GL_UNPACK_ALIGNMENT,   1        );
        glBitmap(
            face[ 0 ], f->Height,         /* The bitmap's width and height  */
            f->xorig, f->yorig,           /* The origin in the font glyph   */
            ( float )( face[ 0 ] ), 0.0,  /* The raster advance -- inc. x,y */
            ( face + 1 )                  /* The packed bitmap data...      */
        );

    glPopClientAttrib( );
}

/*!
    \fn
    \brief    Draw a string of bitmapped characters
    \ingroup  bitmapfont
    \param    font    A bitmapped font identifier.
    \param    string  A NUL-terminated ASCII string.

              Draw a \a string the current OpenGL raster position
              using a bitmapped \a font.  The raster position is advanced
              by the width of the string.

              The starting raster position is used as
              the left margin for multi-line strings.
              Each newline character repositions the raster 
              position at the beginning of the next line.  

              Nothing is drawn, and the raster position is unaffected when
              either:
              - \a font is not a valid OpenGLUT bitmap font
              - \a string is an empty string or NULL pointer
              - The current OpenGL raster position is invalid

    \see      glRasterPos(), glutBitmapCharacter()
*/
void OGAPIENTRY glutBitmapString( void *font, const unsigned char *string )
{
    SOG_Font *f = oghFontByID( font );
    short x = 0;
    unsigned char c;

    if( !f )
        return;

    if( !string || !*string )
        return;

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
    while( c = *string++ )
        if( c == '\n' )
        {
            /* glBitmap can be used to reposition the raster position */

            glBitmap( 0, 0, 0, 0, - ( float ) x, - ( float ) f->Height, NULL );
            x = 0;
        }
        else  /* Not an EOL, draw the bitmap character */
        {
            const GLubyte* face = f->Characters[ c ];
            glBitmap(
                face[ 0 ], f->Height,     /* Bitmap's width and height    */
                f->xorig, f->yorig,       /* The origin in the font glyph */
                face[ 0 ], 0.0,           /* The raster advance; inc. x,y */
                face + 1                  /* The packed bitmap data...    */
            );

            x += face[ 0 ];
        }

    glPopClientAttrib( );
}

/*!
    \fn
    \brief    Return the width of a bitmapped character, in pixels.
    \ingroup  bitmapfont
    \param    font      A bitmapped font identifier.
    \param    character A character code.

              Returns the horizontal OpenGL raster position
              offset for a \a character in a bitmapped \a font.

              It is also an upper bound on the width of the bitmapped glyph 
              for \a character, though not all letters will use their full 
              width, especially fixed-width fonts.

              Returns 0 if the \a character is out of the inclusive
              range [0,255] or if the \a font is invalid.

    \note     In GLUT, some glyphs could render to the left of the
              starting position, in some fonts.  OpenGLUT's fonts all
              position all of their glyphs to start at, or to the right of,
              the initial position.

    \see      glutBitmapCharacter(), glutBitmapLength(), glutBitmapHeight()
*/
int OGAPIENTRY glutBitmapWidth( void *font, int character )
{
    int ret = 0;
    SOG_Font *f = oghFontByID( font );

    if( f &&
        ( 0 <= character ) &&
        ( 256 > character ) )
        ret = *( f->Characters[ character ] );

    return ret;
}

/*!
    \fn
    \brief    Return the width of a bitmapped string, in pixels.
    \ingroup  bitmapfont
    \param    font    A bitmapped font identifier.
    \param    string  A NUL-terminated ASCII string.

              Returns the maximum horizontal OpenGL raster position
              offset for a \a string in a bitmapped \a font.

              As with glutBitmapString(), newlines are taken into
              consideration.

              Returns 0 if the \a font is invalid or if the 
              \a string is empty or \a NULL.

    \see      glutBitmapString(), glutBitmapWidth(), glutBitmapHeight()
*/
int OGAPIENTRY glutBitmapLength( void *font, const unsigned char *string )
{
    int length = 0, this_line_length = 0;
    SOG_Font *f = oghFontByID( font );
    unsigned char c;

    if( f && string )
    {
        while( c = *string++ )
            if( c != '\n' ) /* Not an EOL, increment length of line */
                this_line_length += *( f->Characters[ c ]);
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
    \brief    Return the height of a given font, in pixels.
    \ingroup  bitmapfont
    \param    font    A bitmapped font identifier.

              Return the line-to-line vertical spacing (in pixels) 
              between lines of a bitmapped \a font.

              Returns 0 if \a font is invalid.

    \see      glutBitmapWidth(), glutBitmapLength(),
              glutBitmapString()

    \internal
    \todo     We have discussed adding a "font descender" query.
              We should go ahead and do it.
    \note     Does <i>not</i> report the height used by individual
              characters.  This may limit its usefulness; perhaps we
              should change it?  (And/or add a new function.)
*/
int OGAPIENTRY glutBitmapHeight( void *font )
{
    SOG_Font *f = oghFontByID( font );
    int ret = 0;

    if( f )
        ret = f->Height;

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

              Does nothing if:
               - The \a fontID is invalid.
               - The \a character is out of the font's range.

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
    if( schar )
    {
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
    int i, j;
    float length = 0.0;
    SOG_StrokeFont *font = oghStrokeByID( fontID );
    unsigned char c;

    if( font && string )
        /*
         * Step through the string, drawing each character.
         * A newline will simply translate the next character's insertion
         * point back to the start of the line and down one line.
         */
        while( c = *string++ )
            if( c < font->Quantity )
                if( c == '\n' )
                {
                    glTranslatef ( -length, -( float )( font->Height ), 0.0 );
                    length = 0.0;
                }
                else  /* Not an EOL, draw the bitmap character */
                {
                    const SOG_StrokeChar *schar =
                        font->Characters[ c ];
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

              Returns 0 if:
               - The \a fontID is out of range.
               - The \a string is \a NULL.
               - All characters in the \a string are zero-width.

    \note     Truncates the width to an integer; the rationale for
              truncation is unknown.
    \see      glutStrokeString(), glutStrokeWidth(), glutStrokeHeight(),
              glutBitmapLength()
*/
int OGAPIENTRY glutStrokeLength( void *fontID, const unsigned char *string )
{
    unsigned char c;
    float length = 0.0;
    float this_line_length = 0.0;
    SOG_StrokeFont *font = oghStrokeByID( fontID );

    if( font && string )
        while( c = *string++ )
            if( c < font->Quantity )
            {
                if( c == '\n' )
                {
                    if( length < this_line_length )
                        length = this_line_length;
                    this_line_length = 0.0;
                }
                else  /* Not an EOL, increment the length of this line */
                {
                    const SOG_StrokeChar *schar =
                        font->Characters[ c ];
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
