/*!
    \file  og_init.c
    \brief Initialization
*/

/*
 * Portions copyright (C) 2004, the OpenGLUT project contributors.
 * OpenGLUT branched from freeglut in February, 2004.
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Thu Dec 2 1999
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
 *  ogDeinitialize()        -- Win32's OK, X11 needs the OS-specific
 *                             deinitialization done (What's missing?)
 *
 * Wouldn't it be cool to use gettext() for error messages? I just love
 * bash saying  "nie znaleziono pliku" instead of "file not found" :)
 * Is gettext easily portable?
 */

/* -- GLOBAL VARIABLES ----------------------------------------------------- */

/*
 * A structure pointed by ogDisplay holds all information
 * regarding the display, screen, root window etc.
 */
SOG_Display ogDisplay;

/*
 * The settings for the current OpenGLUT session
 */
SOG_State ogState =
{
    { -1, -1, GL_FALSE },   /* Position */
    { 300, 300, GL_TRUE },  /* Size */
    GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH,  /* DisplayMode */
    GL_FALSE,               /* Initialised */
    GL_FALSE,               /* ForceDirectContext */
    GL_TRUE,                /* TryDirectContext */
    GL_FALSE,               /* ForceIconic */
    GL_FALSE,               /* UseCurrentContext */
    GL_FALSE,               /* GLDebugSwitch */
    GL_FALSE,               /* XSyncSwitch */
    GL_TRUE,                /* KeyRepeat */
    0xffffffff,             /* Modifiers */
    0,                      /* FPSInterval */
    0,                      /* SwapCount */
    0,                      /* SwapTime */
#if TARGET_HOST_WIN32 || TARGET_HOST_WINCE
    { 0, GL_FALSE },        /* Time                */
#else
    { { 0, 0 }, GL_FALSE }, /* Time                */
#endif
    { NULL, NULL },         /* Timers              */
    { NULL, NULL },         /* FreeTimers          */
    NULL,                   /* IdleCallback        */
    0,                      /* ActiveMenus         */
    NULL,                   /* MenuStateCallback   */
    NULL,                   /* MenuStatusCallback  */
    { 640, 480, GL_TRUE },  /* GameModeSize        */
    16,                     /* GameModeDepth       */
    72,                     /* GameModeRefresh     */
    GLUT_ACTION_EXIT,       /* ActionOnWindowClose */
    GLUT_EXEC_STATE_INIT,   /* ExecState           */
    NULL,                   /* ProgramName         */
    GL_FALSE,               /* JoysticksInitted    */
#if TARGET_HOST_UNIX_X11
    {0},                    /* A jmpbuf BackToMainLoop */
#elif TARGET_HOST_WIN32 || TARGET_HOST_WINCE
    0,                      /* A jmpbuf BackToMainLoop */
#endif
    0,                      /* InMainLoop flag     */
};


/* -- PRIVATE FUNCTIONS ---------------------------------------------------- */

/*
 * A call to this function should initialize all the display stuff...
 */
static void ogInitializeDisplay( const char *displayName )
{
#if TARGET_HOST_UNIX_X11
    ogDisplay.Display = XOpenDisplay( displayName );

    if( ogDisplay.Display == NULL )
        ogError( "failed to open display '%s'", XDisplayName( displayName ) );

    if( !glXQueryExtension( ogDisplay.Display, NULL, NULL ) )
        ogError( "OpenGL GLX extension not supported by display '%s'",
            XDisplayName( displayName ) );

    ogDisplay.Screen = DefaultScreen( ogDisplay.Display );
    ogDisplay.RootWindow = RootWindow(
        ogDisplay.Display,
        ogDisplay.Screen
    );

    ogDisplay.ScreenWidth  = DisplayWidth(
        ogDisplay.Display,
        ogDisplay.Screen
    );
    ogDisplay.ScreenHeight = DisplayHeight(
        ogDisplay.Display,
        ogDisplay.Screen
    );

    ogDisplay.ScreenWidthMM = DisplayWidthMM(
        ogDisplay.Display,
        ogDisplay.Screen
    );
    ogDisplay.ScreenHeightMM = DisplayHeightMM(
        ogDisplay.Display,
        ogDisplay.Screen
    );

    ogDisplay.Connection = ConnectionNumber( ogDisplay.Display );

    /* Create the window deletion atom */
    ogDisplay.DeleteWindow = XInternAtom(
        ogDisplay.Display,
        "WM_DELETE_WINDOW",
        FALSE
    );

#elif TARGET_HOST_WIN32 || TARGET_HOST_WINCE

    WNDCLASS wc;
    ATOM atom;

    /* We need to initialize the ogDisplay global structure here. */
    ogDisplay.Instance = GetModuleHandle( NULL );

    atom = GetClassInfo( ogDisplay.Instance, _T( OPENGLUT_STRING ), &wc );
    if( !atom )
    {
        ZeroMemory( &wc, sizeof(WNDCLASS) );

        /*
         * Each of the windows should have its own device context, and we
         * want redraw events during Vertical and Horizontal Resizes by
         * the user.
         *
         * XXX Old code had "| CS_DBCLCKS" commented out.  Plans for the
         * XXX future?  Dead-end idea?
         */
#if TARGET_HOST_WIN32
        wc.style          = CS_OWNDC;
#endif
        wc.style         |= CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = ogWindowProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = 0;
        wc.hInstance      = ogDisplay.Instance;
        wc.hIcon          = LoadIcon( ogDisplay.Instance, _T( "GLUT_ICON" ) );
        if( !wc.hIcon )
            wc.hIcon      = LoadIcon( NULL, IDI_WINLOGO );

        wc.hCursor        = LoadCursor( NULL, IDC_ARROW );
        wc.hbrBackground  = NULL;
        wc.lpszMenuName   = NULL;
        wc.lpszClassName  = _T( OPENGLUT_STRING );

        /* Register the window class */
        atom = RegisterClass( &wc );
        assert( atom );
    }

    /* The screen dimensions can be obtained via GetSystemMetrics() calls */
    ogDisplay.ScreenWidth  = GetSystemMetrics( SM_CXSCREEN );
    ogDisplay.ScreenHeight = GetSystemMetrics( SM_CYSCREEN );

    {
        HWND desktop = GetDesktopWindow( );
        HDC  context = GetDC( desktop );

        ogDisplay.ScreenWidthMM  = GetDeviceCaps( context, HORZSIZE );
        ogDisplay.ScreenHeightMM = GetDeviceCaps( context, VERTSIZE );

        ReleaseDC( desktop, context );
    }

#endif

    ogState.Initialised = GL_TRUE;
}

/*
 * Perform the OpenGLUT deinitialization...
 */
void ogDeinitialize( void )
{
    SOG_Timer *timer;

    if( !ogState.Initialised )
    {
        ogWarning( "ogDeinitialize(): "
                   "no valid initialization has been performed" );
        return;
    }

    /* If there was a menu created, destroy the rendering context */
    if( ogStructure.MenuContext )
    {
        free( ogStructure.MenuContext );
        ogStructure.MenuContext = NULL;
    }

    ogDestroyStructure( );

    while( timer = ogState.Timers.First )
    {
        ogListRemove( &ogState.Timers, &timer->Node );
        free( timer );
    }

    while( timer = ogState.FreeTimers.First )
    {
        ogListRemove( &ogState.FreeTimers, &timer->Node );
        free( timer );
    }

    if( ogState.JoysticksInitted )
        ogJoystickClose( );
    ogState.JoysticksInitted = GL_FALSE;

    ogState.Initialised = GL_FALSE;

    ogState.Position.X = -1;
    ogState.Position.Y = -1;
    ogState.Position.Use = GL_FALSE;

    ogState.Size.X = 300;
    ogState.Size.Y = 300;
    ogState.Size.Use = GL_TRUE;

    ogState.DisplayMode = GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH;

    ogState.ForceDirectContext  = GL_FALSE;
    ogState.TryDirectContext    = GL_TRUE;
    ogState.ForceIconic         = GL_FALSE;
    ogState.UseCurrentContext   = GL_FALSE;
    ogState.GLDebugSwitch       = GL_FALSE;
    ogState.XSyncSwitch         = GL_FALSE;
    ogState.ActionOnWindowClose = GLUT_ACTION_EXIT;
    ogState.ExecState           = GLUT_EXEC_STATE_INIT;

    ogState.KeyRepeat       = GL_FALSE;  /* XXX Was staticly set GL_TRUE? */
    ogState.Modifiers       = 0xffffffff;

    ogState.GameModeSize.X  = 640;
    ogState.GameModeSize.Y  = 480;
    ogState.GameModeDepth   =  16;
    ogState.GameModeRefresh =  72;

    ogState.Time.Set = GL_FALSE;

    ogListInit( &ogState.Timers );
    ogListInit( &ogState.FreeTimers );

    ogState.IdleCallback = NULL;
    ogState.MenuStateCallback = ( OGCBMenuState )NULL;
    ogState.MenuStatusCallback = ( OGCBMenuStatus )NULL;

    ogState.SwapCount   = 0;
    ogState.SwapTime    = 0;
    ogState.FPSInterval = 0;

    if( ogState.ProgramName )
    {
        free( ogState.ProgramName );
        ogState.ProgramName = NULL;
    }


#if TARGET_HOST_UNIX_X11
    /* Ask that X-client data we have created be destroyed on display close. */
    XSetCloseDownMode( ogDisplay.Display, DestroyAll );

    /* Close display connection; destroy all windows we have created so far. */
    XCloseDisplay( ogDisplay.Display );
#endif
}

/*
 * Everything inside the following #if is copied from the X sources.
 *
 * (NB: "The X sources" are presumably something like the standard
 *  XFree86 v4.4 release.  Unfortunately, the importer neglected
 *  to say, so that will probably remain a mystery.  Since the
 *  code is embedded in an OpenGLUT source file, it was reformatted
 *  to OpenGLUT style.  Should we ever wish to refresh this
 *  function from another X server in the future, it should probably
 *  be stuck in a SEPARATE file, and should be ATTRIBUTED properly so
 *  that we can figure out where the heck it came from (specific
 *  versions, people), and allowed to stay in its own style.)
 */
#if TARGET_HOST_WIN32 || TARGET_HOST_WINCE

/*

Copyright 1985, 1986, 1987,1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/

#define NoValue         0x0000
#define XValue          0x0001
#define YValue          0x0002
#define WidthValue      0x0004
#define HeightValue     0x0008
#define AllValues       0x000F
#define XNegative       0x0010
#define YNegative       0x0020

/*
 *    XParseGeometry parses strings of the form
 *   "=<width>x<height>{+-}<xoffset>{+-}<yoffset>", where
 *   width, height, xoffset, and yoffset are unsigned integers.
 *   Example:  "=80x24+300-49"
 *   The equal sign is optional.
 *   It returns a bitmask that indicates which of the four values
 *   were actually found in the string.  For each value found,
 *   the corresponding argument is updated;  for each value
 *   not found, the corresponding argument is left unchanged.
 */

static int
ReadInteger(char *string, char **NextString)
{
    register int Result = 0;
    int Sign = 1;

    if( *string == '+' )
        string++;
    else if( *string == '-' )
    {
        string++;
        Sign = -1;
    }
    for( ; ( *string >= '0' ) && ( *string <= '9' ); string++ )
        Result = ( Result * 10 ) + ( *string - '0' );
    *NextString = string;
    if( Sign >= 0 )
        return Result;
    else
        return -Result;
}

static int XParseGeometry(
    const char *string,
    int *x,
    int *y,
    unsigned int *width,    /* RETURN */
    unsigned int *height    /* RETURN */
)
{
    int mask = NoValue;
    register char *strind;
    unsigned int tempWidth = 0, tempHeight = 0;
    int tempX = 0, tempY = 0;
    char *nextCharacter;

    if( ( string == NULL ) || ( *string == '\0' ) )
        return mask;
    if( *string == '=' )
        string++;  /* ignore possible '=' at beg of geometry spec */

    strind = ( char * )string;
    if( *strind != '+' && *strind != '-' && *strind != 'x' )
    {
        tempWidth = ReadInteger(strind, &nextCharacter);
        if( strind == nextCharacter )
            return 0;
        strind = nextCharacter;
        mask |= WidthValue;
    }

    if( *strind == 'x' || *strind == 'X' )
    {
        strind++;
        tempHeight = ReadInteger( strind, &nextCharacter );
        if( strind == nextCharacter )
            return 0;
        strind = nextCharacter;
        mask |= HeightValue;
    }

    if( ( *strind == '+' ) || ( *strind == '-' ) )
    {
        if( *strind == '-' )
        {
            strind++;
            tempX = -ReadInteger( strind, &nextCharacter );
            if( strind == nextCharacter )
                return 0;
            strind = nextCharacter;
            mask |= XNegative;
        }
        else
        {
            strind++;
            tempX = ReadInteger(strind, &nextCharacter);
            if( strind == nextCharacter )
                return 0;
            strind = nextCharacter;
        }
        mask |= XValue;
        if( ( *strind == '+' ) || ( *strind == '-' ) )
        {
            if( *strind == '-' )
            {
                strind++;
                tempY = -ReadInteger( strind, &nextCharacter );
                if( strind == nextCharacter )
                    return 0;
                strind = nextCharacter;
                mask |= YNegative;
            }
            else
            {
                strind++;
                tempY = ReadInteger( strind, &nextCharacter );
                if( strind == nextCharacter )
                    return 0;
                strind = nextCharacter;
            }
            mask |= YValue;
        }
    }

    /*
     * If strind isn't at the end of the string the it's an invalid
     * geometry specification.
     */
    if( *strind != '\0' )
        return 0;

    if( mask & XValue )
        *x = tempX;
    if( mask & YValue )
        *y = tempY;
    if( mask & WidthValue )
        *width = tempWidth;
    if( mask & HeightValue )
        *height = tempHeight;
    return mask;
}
#endif

/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*!
    \fn
    \brief    Initialize OpenGLUT data structures.
    \ingroup  mainloop
    \param    pargc    Pointer to something like main()'s \a argc.
    \param    argv     Something like main()'s \a argv.

              This function should be called once, near the start of
              any GLUT, freeglut, or OpenGLUT program.  It serves two
              vital roles:

               - It allows OpenGLUT to initialize internal structures.
               - It allows OpenGLUT to process command-line arguments
                 to control the initial window position, etc.

              You should take note of the interaction between
              glutInit() and the related functions such as
              glutInitWindowPosition().  OpenGLUT always uses
              the most recent configuration information, so
              if you call glutInit(), then glutInitWindowPosition(),
              you prevent the user from controlling the initial
              window position via a command-line parameter.

              glutInit() will remove from \a pargc, \a argv
              any parameters that it
              recognizes in the command line.  The following
              command-line parameters are suported:

               - \a -display <i>display-id</i>
                 This allows connection to an alternate X server.
               - \a -geometry <i>geometry-spec</i>
                 This takes width, height, and
                 window position.  The position is given as
                 a signed value (negative values being distance
                 from the far boundary of the screen).  For example,
                 a window geometry of 5x7+11-17 is 5 pixels
                 wide, 7 pixels tall, 11 pixels from the left,
                 and 17 pixels from the bottom edge of the screen.
               - \a -direct Insist on only OpenGL direct rendering.
                 Direct rendering is normally requested but indirect
                 is normally accepted.
                 \a -direct is not always available.
                 See \a -indirect.
               - \a -indirect Attempt only indirect OpenGL rendering.
                 \a -indirect is always available.
                 See \a -direct.
               - \a -iconic Open the window in iconized form.
               - \a -gldebug Print any detected OpenGL errors via
                 glutReportErrors().  Presently
                 done at the bottom of glutMainLoopEvent().
               - \a -sync Synchronize the window system communications
                 heavily.

              Additionally, this function checks whether the
              environment variable \a GLUT_FPS is defined (only on
              UNIX_X11); if so, OpenGLUT will periodically print
              the average number of times per second that your program calls
              glutSwapBuffers().

    \note     You really should always call this, even if you are
              a WIN32 user.  It provides a way for the user to
              directly inform OpenGLUT about preferences without
              the application needing to explicitly deal with
              those issues.  This is also where OpenGLUT retrieves
              your program's name to help disambiguate error and
              warning messages it may be forced to emit.
    \note     Option \a -sync sets a flag,
              but is not actually used at this time.
    \note     Lots of code does XFlush() on the X server, regardless
              of whether \a -sync is specified.  Much of that appears to
              be required in order to support direct client invocation
              of  glutMainLoopEvent(), regrettably.
              However, if one calls glutMainLoop(), instead, we might
              avoid gratuitous XFlush() calls.  (That last sentence
              isn't particularly germain to this function, but there's
              no better place to make this remark at this time.)
              Even for glutMainLoopEvent(), we may be able to coalesce
              many XFlush() calls.
    \see      glutInitWindowPosition(), glutInitWindowSize(),
              glutInitDisplayMode(), glutInitDisplayString(),
              glutCreateWindow(), glutDisplayFunc(),
              glutMainLoop(), glutMainLoopEvent(), glutReportErrors(),
              glutSwapBuffers()
*/
void OGAPIENTRY glutInit( int *pargc, char **argv )
{
    char *displayName = NULL;
    char *geometry = NULL;
    int i, j, argc = *pargc;

    if( ogState.Initialised )
        ogError( "illegal glutInit() reinitialization attempt" );

    if( pargc && *pargc && argv && *argv && **argv )
    {
        ogState.ProgramName = ogStrDup( *argv );

        if( !ogState.ProgramName )
            ogError( "Could not allocate space for the program's name." );
    }

    ogCreateStructure( );

    ogElapsedTime( );

    /* check if GLUT_FPS env var is set */
#if !TARGET_HOST_WINCE
    {
        const char *fps = getenv( "GLUT_FPS" );
        if( fps )
        {
            int interval;
            sscanf( fps, "%d", &interval );

            if( interval <= 0 )
                ogState.FPSInterval = 5000;  /* 5000 millisecond default */
            else
                ogState.FPSInterval = interval;
        }
    }

    displayName = getenv( "DISPLAY");

    for( i = 1; i < argc; i++ )
    {
        if( strcmp( argv[ i ], "-display" ) == 0 )
        {
            if( ++i >= argc )
                ogError( "-display option must be followed by display name" );

            displayName = argv[ i ];

            argv[ i - 1 ] = NULL;
            argv[ i     ] = NULL;
            ( *pargc ) -= 2;
        }
        else if( strcmp( argv[ i ], "-geometry" ) == 0 )
        {
            if( ++i >= argc )
                ogError(
                    "-geometry option must be followed by window "
                    "geometry settings"
                );

            geometry = argv[ i ];

            argv[ i - 1 ] = NULL;
            argv[ i     ] = NULL;
            ( *pargc ) -= 2;
        }
        else if( strcmp( argv[ i ], "-direct" ) == 0)
        {
            if( ! ogState.TryDirectContext )
                ogError(
                    "option ambiguity, -direct and -indirect "
                    "cannot be both specified"
                );

            ogState.ForceDirectContext = GL_TRUE;
            argv[ i ] = NULL;
            ( *pargc )--;
        }
        else if( strcmp( argv[ i ], "-indirect" ) == 0 )
        {
            if( ogState.ForceDirectContext )
                ogError(
                    "option ambiguity, -direct and -indirect "
                    "cannot be both specified"
                );

            ogState.TryDirectContext = GL_FALSE;
            argv[ i ] = NULL;
            (*pargc)--;
        }
        else if( strcmp( argv[ i ], "-iconic" ) == 0 )
        {
            ogState.ForceIconic = GL_TRUE;
            argv[ i ] = NULL;
            ( *pargc )--;
        }
        else if( strcmp( argv[ i ], "-gldebug" ) == 0 )
        {
            ogState.GLDebugSwitch = GL_TRUE;
            argv[ i ] = NULL;
            ( *pargc )--;
        }
        else if( strcmp( argv[ i ], "-sync" ) == 0 )
        {
            ogState.XSyncSwitch = GL_TRUE;
            argv[ i ] = NULL;
            ( *pargc )--;
        }
    }

    /* Compact {argv}. */
    j = 2;
    for( i = 1; i < *pargc; i++, j++ )
        if( argv[ i ] == NULL )
        {
            /* Guaranteed to end because there are {*pargc} arguments left */
            while( argv[ j ] == NULL )
                j++;
            argv[ i ] = argv[ j ];
        }
#endif

    /*
     * Have the display created now. If there wasn't a "-display"
     * in the program arguments, we will use the DISPLAY environment
     * variable for opening the X display (see code above):
     */
    ogInitializeDisplay( displayName );

    /*
     * Geometry parsing deffered until here because we may need the screen
     * size.
     */

    if( geometry )
    {
        int mask = XParseGeometry( geometry,
                                   &ogState.Position.X, &ogState.Position.Y,
                                   &ogState.Size.X, &ogState.Size.Y );

        if( ( mask & ( WidthValue | HeightValue ) ) ==
            ( WidthValue | HeightValue ) )
            ogState.Size.Use = GL_TRUE;

        if( mask & XNegative )
            ogState.Position.X += ogDisplay.ScreenWidth - ogState.Size.X;

        if( mask & YNegative )
            ogState.Position.Y += ogDisplay.ScreenHeight - ogState.Size.Y;

        if( ( mask & ( XValue | YValue ) ) == ( XValue | YValue ) )
            ogState.Position.Use = GL_TRUE;
    }
}

/*!
    \fn
    \brief    Requests future windows to open at a given position.
    \ingroup  window
    \param    x    X coordinate.
    \param    y    Y coordinate.

              This function allows you to request an initial position
              for future windows.

    \see      glutPositionWindow(), glutInit(), glutInitWindowSize(),
              glutInitDisplayMode(), glutInitDisplayString(), glutGet()
*/
void OGAPIENTRY glutInitWindowPosition( int x, int y )
{
    ogState.Position.X = x;
    ogState.Position.Y = y;

    if( ( x >= 0 ) && ( y >= 0 ) )
        ogState.Position.Use = GL_TRUE;
    else
        ogState.Position.Use = GL_FALSE;
}

/*!
    \fn
    \brief    Requests future windows to open at a given width/height..
    \ingroup  window
    \param    width    Width of future windows.
    \param    height   Height of future windows.

              This function allows you to request initial dimensions
              for future windows.

              There is a callback function to inform you of the new
              window shape (whether initially opened, changed by
              your glutReshapeWindow() request, or changed directly
              by the user).
    \see      glutReshapeWindow(), glutInit(), glutInitWindowPosition(),
              glutInitDisplayMode(), glutInitDisplayString(),
              glutReshapeFunc(), glutGet()
*/
void OGAPIENTRY glutInitWindowSize( int width, int height )
{
    ogState.Size.X = width;
    ogState.Size.Y = height;

    if( ( width > 0 ) && ( height > 0 ) )
        ogState.Size.Use = GL_TRUE;
    else
        ogState.Size.Use = GL_FALSE;
}

/*!
    \fn
    \brief    Requests future windows to open with a given display mode.
    \ingroup  window
    \param    displayMode    Requested display mode.

              When opening a new window, OpenGLUT permits you to set
              several options which will affect the window's behavior
              throughout the program's life.  For partial compatibility,
              freeglut defined some unsupported features and ignored
              applications' requests for them; OpenGLUT presently inherits
              those.  However, as OpenGLUT's goal is to rationalize and
              cleanse the GLUT API, it is likely that those features will
              either be removed or fully supported.

              OpenGLUT also may experimentally or permamently add to
              the supported display modes.

              The various requestable display modes are packed into a
              bitmask.  The symbolic names for the bits are as follows:

               - \a GLUT_RGB selects a Red-Green-Blue window type.
               - \a GLUT_RGBA is a synonym for \a GLUT_RGB.
               - \a GLUT_INDEX Use an indexed color mode rather than
                 RGB.  \a GLUT_INDEX takes precedence over both
                 \a GLUT_RGB and \a GLUT_RGBA.
               - \a GLUT_SINGLE Use a single-buffered display.  If specified,
                 graphics appears directly on the window and it is not
                 necessary to call glutSwapBuffers().
               - \a GLUT_DOUBLE Double-buffered rather than single-buffered.
                 glutSwapBuffers() is required to see the resulting
                 graphics.  Overrides \a GLUT_SINGLE if both are requested.
               - \a GLUT_ACCUM Requests an accumulation buffer be initialized.
               - \a GLUT_ALPHA Requests that we really get an alpha channel.
               - \a GLUT_DEPTH Requests a depth-buffer for the window.
               - \a GLUT_STENCIL Requests a stencil buffer.
               - \a GLUT_MULTISAMPLE Requests a multisampling window.
                 Unlike most display mode options, multitasmpling may be
                 silently ignored if the feature is not available or if
                 OpenGLUT does not know how to use it.
               - \a GLUT_STEREO Requests a stereovision window.
               - \a GLUT_LUMINANCE Requests a luminance-only window.

              Additionally, the following <i>experimental</i> features
              are implemented:

               - \a GLUT_OFFSCREEN Offscreen windows are very much
                 like onscreen windows that have been dragged off of the
                 edge of the screen.  The biggest issue is that offscreen
                 windows do not support subwindows.  Other than that,
                 onscreen windows that are dragged off of the edge may not
                 store graphics that you render (while \a GLUT_OFFSCREEN
                 windows do), and there is no way to drag an offscreen
                 window onscreen for user interaction.
               - \a GLUT_BORDERLESS Borderless windows are very experimental,
                 and their precise behavior is not set in stone.
                 See also glutCreateMenuWindow().

              The following are <i>defaults</i>:

               - \a GLUT_RGB
               - \a GLUT_SINGLE

    \bug      \a GLUT_OFFSCREEN windows do not work on some nVidia
              cards/drivers.  (No other known cases at this time, but
              seems to apply to both WIN32 and UNIX_X11 systems.)
    \bug      \a GLUT_BORDERLESS seems to vary by the window manager on X11,
              though twm (for example) performs very similarly to WIN32.
              But KDE's window manager (for example) does not let you send
              keystrokes to borderless windows without OpenGLUT hacks.
    \todo     The \a GLUT_RGBA symbol should probably not be used.
              The flag's name is misleading (there is no Alpha component),
              and it is a duplicate of \a GLUT_RGB.  If you want a window
              with an Alpha channel, include the \a GLUT_ALPHA flag.
    \note     Arguably, offscreen and borderless support have less to
              do with the display mode than with the window system.  Perhaps
              they should not be bundled into the \a displayMode mask?
    \note     I do not think that \a GLUT_MULTISAMPLE is supported by
              OpenGLUT.
    \note     I do not recall ever seeing stereovision support in the
              code, and someone was complaining that it does not work
              with freeglut.
    \note     There is no way to change the display mode of an open window.
    \note     If a window opened, you may (and must) assume that it is
              in the requested display mode.
    \see      glutCreateMenuWindow(),
              glutInit(), glutInitWindowSize(),
              glutInitWindowPosition(), glutInitDisplayString(),
              glutSwapBuffers()
*/
void OGAPIENTRY glutInitDisplayMode( unsigned int displayMode )
{
    ogState.DisplayMode = displayMode;
}


/* -- INIT DISPLAY STRING PARSING ------------------------------------------ */

static const char *Tokens[ ] =
{
    "alpha", "acca", "acc", "blue", "buffer", "conformant", "depth", "double",
    "green", "index", "num", "red", "rgba", "rgb", "luminance", "stencil",
    "single", "stereo", "samples", "slow", "win32pdf", "win32pfd", "xvisual",
    "xstaticgray", "xgrayscale", "xstaticcolor", "xpseudocolor",
    "xtruecolor", "xdirectcolor"
};
#define NUM_TOKENS             (sizeof(Tokens)/sizeof(*Tokens))

/*!
    \fn
    \brief    String-based display mode control.
    \ingroup  window
    \param    displayMode    The mode string.

              This provides a string-based mechanism for defining
              display mode options.  Because we are not stuck with
              a handful of bits in a 32-bit integer, finer control
              is offered.  The following, case-sensitive options
              are provided.  Generally, they either map in an
              obvious way to a glutInitDisplayMode() flag (or a
              sub-feature), or else they are unimplemented or even
              undocumented.

               - \a alpha        Sets number of bits in the alpha channel.
                                 Enables \a GLUT_ALPHA.
               - \a acca         Sets number of \a RGBA accumulation bits.
               - \a acc          Sets number of \a RGB accumulation bits.
                                 Enables \a GLUT_ACCUM.
               - \a blue         Sets number of Blue bits.
               - \a buffer       Sets bits in index mode?
               - \a conformant   Conformant with what?
               - \a depth        Sets number of bits in depth buffer.
                                 Enables \a GLUT_DEPTH.
               - \a double       Enables \a GLUT_DOUBLE.
               - \a green        Sets number of Green bits.
               - \a index        Enables \a GLUT_INDEX.
               - \a num          Appears to select a frame-buffer configuration
                                 by number from an unspecified list.  Probably
                                 very non-portable.
               - \a red          sets number of Red bits.
               - \a rgba         Sets number of \a RGBA bits.
                                 Enables \a GLUT_RGBA.
               - \a rgb          Sets number of \a RGB bits;
                                 sets Alpha bits to 0.
                                 Enables \a GLUT_RGB.
               - \a luminance    Sets number of Red bits;
                                 sets \a GBA bits to 0.
                                 Enables \a GLUT_LUMINANCE.
               - \a stencil      Sets number of stencil bits.
                                 Enables \a GLUT_STENCIL.
               - \a single       Enables \a GLUT_SINGLE.
               - \a stereo       Enables \a GLUT_STERO.
               - \a samples      Number of samples for \a SGIS_Multisample.
                                 Enables \a GLUT_MULTISAMPLE.
               - \a slow         Indicates if a frame-buffer is slow.
               - \a win32pdf     Requests a WIN32 Pixel Format Descriptor
                                 by number (compare \a num).  Non-portable.
               - \a win32pfd     The original GLUT term; freeglut typoed
                                 this as \a win32pdf and so we support
                                 both for now.
               - \a xvisual      Requests an X configuration by number.
                                 See \a win32pdf.
               - \a xstaticgray  Selects X-specific "staticgray" mode.
               - \a xgrayscale   Selects X-specific "grayscale" mode.
               - \a xstaticcolor Selects X-specific "staticcolor" mode.
               - \a xpseudocolor Selects X-specific "pseudocolor" mode.
               - \a xtruecolor   Selects X-specific "trueolor" mode.
               - \a xdirectcolor Selects X-specific "directcolor" mode.

    \note     Only the common U.S. spellings of gray[sic] and color[sic]
              are supported.  If you write ``grey'' or ``colour'', beware!
    \note     Conflicting modes, such as \a single and \a double
              have the same interaction as for glutInitDisplayMode().
    \todo     Maybe deprecate glutInitDisplayMode() in favor of this
              string-based mechanism?
    \todo     Maybe a tag-value list of pairs would be even better?
    \bug      The underlying structure is fragile and needs to be reworked.
    \bug      \a GLUT_BORDERLESS and \a GLUT_OFFSCREEN are not represented.
    \bug      Some features are WIN32-only, some are X only.  Some appear
              to simply be unimplemented.
    \see      glutInit(), glutInitWindowPosition(), glutInitWindowSize(),
              glutInitDisplayMode()
*/
void OGAPIENTRY glutInitDisplayString( const char *displayMode )
{
    int glut_state_flag = 0;
    /*
     * Unpack a lot of options from a character string.  The options are
     * delimited by blanks or tabs.
     */
    char *token;
    int len = strlen ( displayMode );
    char *buffer = ( char * )malloc( ( len + 1 ) * sizeof( char ) );
    memcpy( buffer, displayMode, len );
    buffer[ len ] = '\0';

    token = strtok( buffer, " \t" );
    while( token )
    {
        /* Process this token */
        unsigned i;
        for( i = 0; i < NUM_TOKENS; i++ )
            if( strcmp( token, Tokens[ i ] ) == 0 )
                break;

        switch( i )
        {
        case 0:  /* "alpha":  Alpha color buffer precision in bits */
            glut_state_flag |= GLUT_ALPHA;  /* Somebody fix this for me! */
            break;

        case 1:  /* "acca":  Red, green, blue, and alpha accumulation buffer
                     precision in bits */
            break;

        case 2:  /* "acc":  Red, green, and blue accumulation buffer precision
                     in bits with zero bits alpha */
            glut_state_flag |= GLUT_ACCUM;  /* Somebody fix this for me! */
            break;

        case 3:  /* "blue":  Blue color buffer precision in bits */
            break;

        case 4:  /* "buffer":  Number of bits in the color index color buffer
                   */
            break;

        case 5:  /* "conformant":  Boolean indicating if the frame buffer
                     configuration is conformant or not */
            break;

        case 6: /* "depth":  Number of bits of precsion in the depth buffer */
            glut_state_flag |= GLUT_DEPTH;  /* Somebody fix this for me! */
            break;

        case 7:  /* "double":  Boolean indicating if the color buffer is
                     double buffered */
            glut_state_flag |= GLUT_DOUBLE;
            break;

        case 8:  /* "green":  Green color buffer precision in bits */
            break;

        case 9:  /* "index":  Boolean if the color model is color index or not
                   */
            glut_state_flag |= GLUT_INDEX;
            break;

        case 10:  /* "num":  A special capability  name indicating where the
                      value represents the Nth frame buffer configuration
                      matching the description string */
            break;

        case 11:  /* "red":  Red color buffer precision in bits */
            break;

        case 12:  /* "rgba":  Number of bits of red, green, blue, and alpha in
                      the RGBA color buffer */
            glut_state_flag |= GLUT_RGBA;  /* Somebody fix this for me! */
            break;

        case 13:  /* "rgb":  Number of bits of red, green, and blue in the
                      RGBA color buffer with zero bits alpha */
            glut_state_flag |= GLUT_RGB;  /* Somebody fix this for me! */
            break;

        case 14:  /* "luminance":  Number of bits of red in the RGBA and zero
                      bits of green, blue (alpha not specified) of color buffer
                      precision */
            glut_state_flag |= GLUT_LUMINANCE; /* Somebody fix this for me! */
            break;

        case 15:  /* "stencil":  Number of bits in the stencil buffer */
            glut_state_flag |= GLUT_STENCIL;  /* Somebody fix this for me! */
            break;

        case 16:  /* "single":  Boolean indicate the color buffer is single
                      buffered */
            glut_state_flag |= GLUT_SINGLE;
            break;

        case 17:  /* "stereo":  Boolean indicating the color buffer supports
                      OpenGL-style stereo */
            glut_state_flag |= GLUT_STEREO;
            break;

        case 18:  /* "samples":  Indicates the number of multisamples to use
                      based on GLX's SGIS_multisample extension (for
                      antialiasing) */
            glut_state_flag |= GLUT_MULTISAMPLE; /*Somebody fix this for me!*/
            break;

        case 19:  /* "slow":  Boolean indicating if the frame buffer
                      configuration is slow or not */
            break;

        case 20:  /* "win32pdf":  matches the Win32 Pixel Format Descriptor by
                      number */
        case 21: /* "win32pfd" is the proper name; alias for freeglut typo */
#if TARGET_HOST_WIN32
#endif
            break;

        case 22:  /* "xvisual":  matches the X visual ID by number */
#if TARGET_HOST_UNIX_X11
#endif
            break;

        case 23:  /* "xstaticgray":  boolean indicating if the frame buffer
                      configuration's X visual is of type StaticGray */
#if TARGET_HOST_UNIX_X11
#endif
            break;

        case 24:  /* "xgrayscale":  boolean indicating if the frame buffer
                      configuration's X visual is of type GrayScale */
#if TARGET_HOST_UNIX_X11
#endif
            break;

        case 25:  /* "xstaticcolor":  boolean indicating if the frame buffer
                      configuration's X visual is of type StaticColor */
#if TARGET_HOST_UNIX_X11
#endif
            break;

        case 26:  /* "xpseudocolor":  boolean indicating if the frame buffer
                      configuration's X visual is of type PseudoColor */
#if TARGET_HOST_UNIX_X11
#endif
            break;

        case 27:  /* "xtruecolor":  boolean indicating if the frame buffer
                      configuration's X visual is of type TrueColor */
#if TARGET_HOST_UNIX_X11
#endif
            break;

        case 28:  /* "xdirectcolor":  boolean indicating if the frame buffer
                      configuration's X visual is of type DirectColor */
#if TARGET_HOST_UNIX_X11
#endif
            break;

        case 29:  /* Unrecognized */
            ogWarning(
                "Display string token not recognized:  %s\n",
                token
            );
            break;
        }

        token = strtok( NULL, " \t" );
    }

    free( buffer );

    /* We will make use of this value when creating a new OpenGL context... */
    ogState.DisplayMode = glut_state_flag;
}
