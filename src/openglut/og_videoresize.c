/*!
    \file  og_videoresize.c
    \brief Video resizing
*/

/*
 * Portions copyright 2004, the OpenGLUT project contributors.
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


/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*!
    \fn
    \brief    Undocumented, unimplemented.
    \ingroup  videomode
    \param    eWhat    An enumerated tag.

              This function is undocumented.  This function is
              unimplemeneted.

    \see      glutVideoResizeGet(), glutSetupVideoResizing(),
              glutStopVideoResizing(), glutVideoResize(), glutVideoPan()
*/
/* ARGSUSED0 */
int  OGAPIENTRY glutVideoResizeGet( GLenum eWhat )
{
    return 0;
}

/*!
    \fn
    \brief    Undocumented, unimplemented.
    \ingroup  videomode

              This function is undocumented.  This function is
              unimplemeneted.

    \see      glutVideoResizeGet(), glutSetupVideoResizing(),
              glutStopVideoResizing(), glutVideoResize(), glutVideoPan()
*/
void OGAPIENTRY glutSetupVideoResizing( void )
{
}

/*!
    \fn
    \brief    Undocumented, unimplemented.
    \ingroup  videomode

              This function is undocumented.  This function is
              unimplemeneted.

    \see      glutVideoResizeGet(), glutSetupVideoResizing(),
              glutStopVideoResizing(), glutVideoResize(), glutVideoPan()
*/
void OGAPIENTRY glutStopVideoResizing( void )
{
}

/*!
    \fn
    \brief    Undocumented, unimplemented.
    \ingroup  videomode
    \param    x    A horizontal position.
    \param    y    A vertical position.
    \param    w    A width.
    \param    h    A height.

              This function is undocumented.  This function is
              unimplemeneted.

    \see      glutVideoResizeGet(), glutSetupVideoResizing(),
              glutStopVideoResizing(), glutVideoResize(), glutVideoPan()
*/
/* ARGSUSED0 */
void OGAPIENTRY glutVideoResize( int x, int y, int w, int h )
{
}

/*!
    \fn
    \brief    Undocumented, unimplemented.
    \ingroup  videomode
    \param    x    A horizontal position.
    \param    y    A vertical position.
    \param    w    A width.
    \param    h    A height.

              This function is undocumented.  This function is
              unimplemeneted.

    \see      glutVideoResizeGet(), glutSetupVideoResizing(),
              glutStopVideoResizing(), glutVideoResize(), glutVideoPan()
*/
/* ARGSUSED0 */
void OGAPIENTRY glutVideoPan( int x, int y, int w, int h )
{
}






