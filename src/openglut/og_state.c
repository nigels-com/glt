/*!
    \file  og_state.c
    \brief OpenGLUT state query methods.
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
 *  glutGet()               -- X11 tests passed, but check if all enums
 *                             handled (what about Win32?)
 *  glutDeviceGet()         -- X11 tests passed, but check if all enums
 *                             handled (what about Win32?)
 *  glutGetModifiers()      -- OK, but could also remove the limitation
 *  glutLayerGet()          --
 */

/* -- LOCAL DEFINITIONS ---------------------------------------------------- */

/* -- PRIVATE FUNCTIONS ---------------------------------------------------- */

#if TARGET_HOST_UNIX_X11
/*
 * Queries the GL context about some attributes
 */
static int oghGetConfig( int attribute )
{
    int returnValue = 0;

    if( ogStructure.Window )
        glXGetConfig( ogDisplay.Display, ogStructure.Window->Window.VisualInfo,
                      attribute, &returnValue );

  return returnValue;
}
#endif

/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*!
    \fn
    \brief    Allows you to set some general state/option variables.
    \ingroup  state
    \param    eWhat    Enumerated parameter ID.
    \param    value    New value.

              Stores the \a value into a state variable named by
              \a eWhat.

              Allowable \a eWhat IDs are:

               - \a GLUT_ACTION_ON_WINDOW_CLOSE Controls what OpenGLUT
                 will do if the user (or system) closes an OpenGLUT window that
                 you did not ask to have closed.
               - \a GLUT_INIT_DISPLAY_MODE An alternate way to set
                 the display mode for a new window.
               - \a GLUT_INIT_WINDOW_HEIGHT An alternate way to set the
                 height of new windows.
               - \a GLUT_INIT_WINDOW_WIDTH An alterate way to set the
                 width of new windows.
               - \a GLUT_INIT_WINDOW_X An alternate way to set the
                 initial horizontal position of new windows.
               - \a GLUT_INIT_WINDOW_Y An alternate way to set the
                 initial vertical position of new windows.
               - \a GLUT_RENDERING_CONTEXT Set to either \a GL_TRUE
                 or \a GL_FALSE to indicate whether to share the
                 current OpenGL rendering context with new windows.
               - \a GLUT_WINDOW_CURSOR Get the <i>current window</i>'s
                 current cursor setting, as used by glutSetCursor().

    \see      glutGet(), glutDeviceGet(), glutGetModifiers(),
              glutLayerGet(), glutDestroyWindow(), glutMainLoop(),
              glutInitDisplayMode(), glutInit(), glutInitWindowSize(),
              glutInitWindowPosition(), glutSetCursor()
*/
void OGAPIENTRY glutSetOption( GLenum eWhat, int value )
{
    freeglut_assert_ready;

    switch( eWhat )
    {
    case GLUT_ACTION_ON_WINDOW_CLOSE:
        ogState.ActionOnWindowClose = value;
        break;

    case GLUT_INIT_DISPLAY_MODE:
        ogState.DisplayMode = ( unsigned int )value;
        break;

    case GLUT_INIT_WINDOW_HEIGHT:
        ogState.Size.Y = ( GLint )value;
        break;

    case GLUT_INIT_WINDOW_WIDTH:
        ogState.Size.X = ( GLint )value;
        break;

    case GLUT_INIT_WINDOW_X:
        ogState.Position.X = ( GLint )value;
        break;

    case GLUT_INIT_WINDOW_Y:
        ogState.Position.Y = ( GLint )value;
        break;

    case GLUT_RENDERING_CONTEXT:
        ogState.UseCurrentContext = ( GLboolean )
            ( ( value == GLUT_USE_CURRENT_CONTEXT ) ? GL_TRUE : GL_FALSE );
        break;

    case GLUT_WINDOW_CURSOR:
        if( ogStructure.Window )
            ogStructure.Window->State.Cursor = value;
        break;

    default:
        ogWarning( "glutSetOption(): missing enum handle %i\n", eWhat );
        break;
    }
}

/*!
    \fn
    \brief    Allows you to query some general state/option variables.
    \ingroup  state
    \param    eWhat    Enumerated parameter ID.

              This function permits you to query for the current value
              of many different OpenGLUT state variables.  The current
              list is:

               - \a GLUT_ACTION_ON_WINDOW_CLOSE
                 Allows you to do something other than die if the
                 user closes one of your windows.
               - \a GLUT_DISPLAY_MODE_POSSIBLE
               - \a GLUT_ELAPSED_TIME
               - \a GLUT_INIT_DISPLAY_MODE
               - \a GLUT_INIT_STATE
               - \a GLUT_INIT_WINDOW_HEIGHT
               - \a GLUT_INIT_WINDOW_WIDTH
               - \a GLUT_INIT_WINDOW_X
               - \a GLUT_INIT_WINDOW_Y
               - \a GLUT_MENU_NUM_ITEMS
               - \a GLUT_RENDERING_CONTEXT
                 Allows you to specify context-sharing when you open
                 new windows.
               - \a GLUT_SCREEN_HEIGHT
               - \a GLUT_SCREEN_HEIGHT_MM
                 Height in millimeters.
               - \a GLUT_SCREEN_WIDTH
               - \a GLUT_SCREEN_WIDTH_MM
                 Width in millimeters.
               - \a GLUT_VERSION
               - \a GLUT_WINDOW_ACCUM_ALPHA_SIZE
               - \a GLUT_WINDOW_ACCUM_BLUE_SIZE
               - \a GLUT_WINDOW_ACCUM_GREEN_SIZE
               - \a GLUT_WINDOW_ACCUM_RED_SIZE
               - \a GLUT_WINDOW_ALPHA_SIZE
               - \a GLUT_WINDOW_BLUE_SIZE
               - \a GLUT_WINDOW_BORDER_WIDTH
               - \a GLUT_WINDOW_BUFFER_SIZE
               - \a GLUT_WINDOW_COLORMAP_SIZE
               - \a GLUT_WINDOW_CURSOR
               - \a GLUT_WINDOW_DEPTH_SIZE
               - \a GLUT_WINDOW_DOUBLEBUFFER
               - \a GLUT_WINDOW_FORAMT_ID
                 System dependant.
               - \a GLUT_WINDOW_GREEN_SIZE
               - \a GLUT_WINDOW_HEADER_HEIGHT
               - \a GLUT_WINDOW_HEIGHT
               - \a GLUT_WINDOW_NUM_CHILDREN
               - \a GLUT_WINDOW_NUM_SAMPLES
               - \a GLUT_WINDOW_PARENT
               - \a GLUT_WINDOW_RED_SIZE
               - \a GLUT_WINDOW_RGBA
               - \a GLUT_WINDOW_STENCIL_SIZE
               - \a GLUT_WINDOW_STEREO
               - \a GLUT_WINDOW_WIDTH
               - \a GLUT_WINDOW_X
               - \a GLUT_WINDOW_Y

              Most of the above are very obvious, and so full documentation
              is postponed for now.

    \todo     Go back and flesh out the above list.
    \todo     This function is a bit messy, especially the WINCE part.  Fix.
    \see      glutSetOption(), glutDeviceGet(), glutGetModifiers(),
              glutLayerGet()
*/
int OGAPIENTRY glutGet( GLenum eWhat )
{
#if TARGET_HOST_WIN32 || TARGET_HOST_WINCE
    int returnValue;
    GLboolean boolValue;
#endif

    switch( eWhat )
    {
    case GLUT_INIT_STATE:
        return ogState.Initialised;

    case GLUT_ELAPSED_TIME:
        /*!
            \bug  This returns a {long}, but the function only is
                  defined to return an {int}.
        */
        return ogElapsedTime( );
    }

    freeglut_assert_ready;

    /* XXX In no meaningful or useful order */
    switch( eWhat )
    {
    case GLUT_SCREEN_WIDTH:         return ogDisplay.ScreenWidth;
    case GLUT_SCREEN_HEIGHT:        return ogDisplay.ScreenHeight;
    case GLUT_SCREEN_WIDTH_MM:      return ogDisplay.ScreenWidthMM;
    case GLUT_SCREEN_HEIGHT_MM:     return ogDisplay.ScreenHeightMM;
    case GLUT_INIT_WINDOW_X:        return ogState.Position.X;
    case GLUT_INIT_WINDOW_Y:        return ogState.Position.Y;
    case GLUT_INIT_WINDOW_WIDTH:    return ogState.Size.X;
    case GLUT_INIT_WINDOW_HEIGHT:   return ogState.Size.Y;
    case GLUT_INIT_DISPLAY_MODE:    return ogState.DisplayMode;

    /*
     * The window/context specific queries are handled mostly by
     * oghGetConfig().
     */
    case GLUT_WINDOW_NUM_SAMPLES:
        return 0;  /* XXX Return what I know about multisampling. */

#if TARGET_HOST_UNIX_X11
    /*
     * The rest of GLX queries under X are general enough to use a macro to
     * check them
     */
#   define GLX_QUERY(a,b) case a: return oghGetConfig( b );

    GLX_QUERY( GLUT_WINDOW_RGBA,                GLX_RGBA                );
    GLX_QUERY( GLUT_WINDOW_DOUBLEBUFFER,        GLX_DOUBLEBUFFER        );
    GLX_QUERY( GLUT_WINDOW_BUFFER_SIZE,         GLX_BUFFER_SIZE         );
    GLX_QUERY( GLUT_WINDOW_STENCIL_SIZE,        GLX_STENCIL_SIZE        );
    GLX_QUERY( GLUT_WINDOW_DEPTH_SIZE,          GLX_DEPTH_SIZE          );
    GLX_QUERY( GLUT_WINDOW_RED_SIZE,            GLX_RED_SIZE            );
    GLX_QUERY( GLUT_WINDOW_GREEN_SIZE,          GLX_GREEN_SIZE          );
    GLX_QUERY( GLUT_WINDOW_BLUE_SIZE,           GLX_BLUE_SIZE           );
    GLX_QUERY( GLUT_WINDOW_ALPHA_SIZE,          GLX_ALPHA_SIZE          );
    GLX_QUERY( GLUT_WINDOW_ACCUM_RED_SIZE,      GLX_ACCUM_RED_SIZE      );
    GLX_QUERY( GLUT_WINDOW_ACCUM_GREEN_SIZE,    GLX_ACCUM_GREEN_SIZE    );
    GLX_QUERY( GLUT_WINDOW_ACCUM_BLUE_SIZE,     GLX_ACCUM_BLUE_SIZE     );
    GLX_QUERY( GLUT_WINDOW_ACCUM_ALPHA_SIZE,    GLX_ACCUM_ALPHA_SIZE    );
    GLX_QUERY( GLUT_WINDOW_STEREO,              GLX_STEREO              );

#   undef GLX_QUERY

    /* Colormap size is handled in a bit different way than all the rest*/
    case GLUT_WINDOW_COLORMAP_SIZE:
        if( ( oghGetConfig( GLX_RGBA ) ) || ( ogStructure.Window == NULL ) )
            /*
             * We've got a RGBA visual, so there is no colormap at all.
             * The other possibility is that we have no current window set.
             */
            return 0;
        return ogStructure.Window->Window.VisualInfo->visual->map_entries;

    /*
     * Those calls are somewhat similiar, as they use XGetWindowAttributes()
     * function
     */
    case GLUT_WINDOW_X:
    case GLUT_WINDOW_Y:
    case GLUT_WINDOW_BORDER_WIDTH:
    case GLUT_WINDOW_HEADER_HEIGHT:
    {
        int x, y;
        Window w;

        if( ogStructure.Window == NULL )
            return 0;

        XTranslateCoordinates(
            ogDisplay.Display,
            ogStructure.Window->Window.Handle,
            ogDisplay.RootWindow,
            0, 0, &x, &y, &w);

        switch( eWhat )
        {
        case GLUT_WINDOW_X: return x;
        case GLUT_WINDOW_Y: return y;
        }

        if ( w == 0 )
            return 0;
        XTranslateCoordinates(
            ogDisplay.Display,
            ogStructure.Window->Window.Handle,
            w, 0, 0, &x, &y, &w);

        switch( eWhat )
        {
        case GLUT_WINDOW_BORDER_WIDTH:  return x;
        case GLUT_WINDOW_HEADER_HEIGHT: return y;
        }
        break;
    }

    case GLUT_WINDOW_WIDTH:
    case GLUT_WINDOW_HEIGHT:
    {
        XWindowAttributes winAttributes;

        if( ogStructure.Window->State.IsOffscreen )
            switch( eWhat )
            {
            case GLUT_WINDOW_WIDTH:  return ogStructure.Window->State.Width;
            case GLUT_WINDOW_HEIGHT: return ogStructure.Window->State.Height;
            }

        if( ogStructure.Window == NULL )
            return 0;
        XGetWindowAttributes(
            ogDisplay.Display,
            ogStructure.Window->Window.Handle,
            &winAttributes
        );
        switch( eWhat )
        {
        case GLUT_WINDOW_WIDTH:            return winAttributes.width;
        case GLUT_WINDOW_HEIGHT:           return winAttributes.height;
        }
        break;
    }

    /* Not sure if there will be a ogChooseVisual() function for Win32 */
    case GLUT_DISPLAY_MODE_POSSIBLE:
        return !!ogChooseVisual();

    /* This is system-dependant */
    case GLUT_WINDOW_FORMAT_ID:
        if( !ogStructure.Window )
            return 0;
        /*!
            \bug The following returns an unsigned long, but the function
                 is only set to return {int}.
        */
        return ogStructure.Window->Window.VisualInfo->visualid;

#elif TARGET_HOST_WIN32 || TARGET_HOST_WINCE

    /*
     * Handle the OpenGL inquiries
     */
    case GLUT_WINDOW_RGBA:
        glGetBooleanv( GL_RGBA_MODE, &boolValue );
        returnValue = boolValue ? 1 : 0;
        return returnValue;
    case GLUT_WINDOW_DOUBLEBUFFER:
        glGetBooleanv( GL_DOUBLEBUFFER, &boolValue );
        returnValue = boolValue ? 1 : 0;
        return returnValue;
    case GLUT_WINDOW_STEREO:
        glGetBooleanv( GL_STEREO, &boolValue );
        returnValue = boolValue ? 1 : 0;
        return returnValue;

    case GLUT_WINDOW_RED_SIZE:
        glGetIntegerv( GL_RED_BITS, &returnValue );
        return returnValue;
    case GLUT_WINDOW_GREEN_SIZE:
        glGetIntegerv( GL_GREEN_BITS, &returnValue );
        return returnValue;
    case GLUT_WINDOW_BLUE_SIZE:
        glGetIntegerv( GL_BLUE_BITS, &returnValue );
        return returnValue;
    case GLUT_WINDOW_ALPHA_SIZE:
        glGetIntegerv( GL_ALPHA_BITS, &returnValue );
        return returnValue;
    case GLUT_WINDOW_ACCUM_RED_SIZE:
        glGetIntegerv( GL_ACCUM_RED_BITS, &returnValue );
        return returnValue;
    case GLUT_WINDOW_ACCUM_GREEN_SIZE:
        glGetIntegerv( GL_ACCUM_GREEN_BITS, &returnValue );
        return returnValue;
    case GLUT_WINDOW_ACCUM_BLUE_SIZE:
        glGetIntegerv( GL_ACCUM_BLUE_BITS, &returnValue );
        return returnValue;
    case GLUT_WINDOW_ACCUM_ALPHA_SIZE:
        glGetIntegerv( GL_ACCUM_ALPHA_BITS, &returnValue );
        return returnValue;
    case GLUT_WINDOW_DEPTH_SIZE:
        glGetIntegerv( GL_DEPTH_BITS, &returnValue );
        return returnValue;

    case GLUT_WINDOW_BUFFER_SIZE:
        returnValue = 1;                                      /* ????? */
        return returnValue;
    case GLUT_WINDOW_STENCIL_SIZE:
        returnValue = 0;                                      /* ????? */
        return returnValue;

    case GLUT_WINDOW_X:
    case GLUT_WINDOW_Y:
    case GLUT_WINDOW_WIDTH:
    case GLUT_WINDOW_HEIGHT:
    {
        RECT winRect;

        freeglut_return_val_if_fail( ogStructure.Window != NULL, 0 );

        if( ogStructure.Window->State.IsOffscreen )
            switch( eWhat )
            {
            case GLUT_WINDOW_WIDTH:  return ogStructure.Window->State.Width;
            case GLUT_WINDOW_HEIGHT: return ogStructure.Window->State.Height;
            }
        /*
         * We need to call GetWindowRect() first...
         *  (this returns the pixel coordinates of the outside of the window)
         */
        GetWindowRect( ogStructure.Window->Window.Handle, &winRect );

        /* we must correct the results we've just received */
#if !TARGET_HOST_WINCE
        if ( ( ogStructure.GameMode != ogStructure.Window ) &&
             ( ogStructure.Window->Parent == NULL ) &&
             ( ! ogStructure.Window->IsUnmanaged ) )
        {
            winRect.left   += GetSystemMetrics( SM_CXSIZEFRAME );
            winRect.right  -= GetSystemMetrics( SM_CXSIZEFRAME );
            winRect.top    += GetSystemMetrics( SM_CYSIZEFRAME ) +
                GetSystemMetrics( SM_CYCAPTION );
            winRect.bottom -= GetSystemMetrics( SM_CYSIZEFRAME );
        }
#endif

        switch( eWhat )
        {
        case GLUT_WINDOW_X:      return winRect.left;
        case GLUT_WINDOW_Y:      return winRect.top;
        case GLUT_WINDOW_WIDTH:  return winRect.right - winRect.left;
        case GLUT_WINDOW_HEIGHT: return winRect.bottom - winRect.top;
        }
    }
    break;

    case GLUT_WINDOW_BORDER_WIDTH:
#if TARGET_HOST_WINCE
        return 0;
else
        return GetSystemMetrics( SM_CXSIZEFRAME );
#endif

    case GLUT_WINDOW_HEADER_HEIGHT:
#if TARGET_HOST_WINCE
        return 0;
#else
        return GetSystemMetrics( SM_CYCAPTION );
#endif

    case GLUT_DISPLAY_MODE_POSSIBLE:
#if TARGET_HOST_WINCE
        return GL_FALSE;
#else
        return ogSetupPixelFormat( ogStructure.Window, GL_TRUE,
                                    PFD_MAIN_PLANE );
#endif

    case GLUT_WINDOW_FORMAT_ID:
#if !TARGET_HOST_WINCE
        if( ogStructure.Window != NULL )
            return GetPixelFormat( ogStructure.Window->Window.Device );
#endif
        return 0;

#endif

    /*
     * The window structure queries
     */
    case GLUT_WINDOW_PARENT:
        if( ogStructure.Window         == NULL ) return 0;
        if( ogStructure.Window->Parent == NULL ) return 0;
        return ogStructure.Window->Parent->ID;

    case GLUT_WINDOW_NUM_CHILDREN:
        if( ogStructure.Window == NULL )
            return 0;
        return ogListLength( &ogStructure.Window->Children );

    case GLUT_WINDOW_CURSOR:
        if( ogStructure.Window == NULL )
            return 0;
        return ogStructure.Window->State.Cursor;

    case GLUT_MENU_NUM_ITEMS:
        if( ogStructure.Menu == NULL )
            return 0;
        return ogListLength( &ogStructure.Menu->Entries );

    case GLUT_ACTION_ON_WINDOW_CLOSE:
        return ogState.ActionOnWindowClose;

    case GLUT_VERSION :
        return VERSION_MAJOR * 10000 + VERSION_MINOR * 100 + VERSION_PATCH;

    case GLUT_RENDERING_CONTEXT:
        return ogState.UseCurrentContext ?
            GLUT_USE_CURRENT_CONTEXT :
            GLUT_CREATE_NEW_CONTEXT;

    default:
        ogWarning( "glutGet(): missing enum handle %i\n", eWhat );
        break;
    }
    return -1;
}

/*!
    \fn
    \brief    Allows you to get some device state/option variables.
    \ingroup  state
    \param    eWhat    Enumerated parameter ID.

              Retrieves some system-specific information about
              attached devices.  Supported device queries are:

               - \a GLUT_HAS_JOYSTICK
               - \a GLUT_HAS_KEYBOARD
               - \a GLUT_HAS_MOUSE
               - \a GLUT_HAS_SPACEBALL
               - \a GLUT_JOYSTICK_AXES
               - \a GLUT_JOYSTICK_POLL_RATE
               - \a GLUT_NUM_MOUSE_BUTTONS
               - \a GLUT_OWNS_JOYSTICK
               - \a GLUT_DEVICE_IGNORE_KEY_REPEAT
               - \a GLUT_DEVICE_KEY_REPEAT
               - \a GLUT_HAS_DIAL_AND_BUTTON_BOX
               - \a GLUT_HAS_TABLET
               - \a GLUT_NUM_BUTTON_BOX_BUTTONS
               - \a GLUT_NUM_DIALS
               - \a GLUT_NUM_SPACEBALL_BUTTONS
               - \a GLUT_NUM_TABLET_BUTTONS

    \bug      Keyboards are optional, but OpenGLUT doesn't detect
              their absence.
    \bug      Mice are optional, but OpenGLUT only is able to check
              for them under WIN32.
    \bug      Mice can have a varying number of buttons, but OpenGLUT
              assumes exactly 3 on UNIX_X11.
    \bug      Joystick queries are just hard-coded guesses, as are the
              SGI device queries.
    \bug      \a GLUT_DEVICE_KEY_REPEAT returns the key repeat mode,
              but the comment says it returns the <i>rate</i>.
    \see      glutSetOption(), glutGet(), glutGetModifiers(),
              glutLayerGet()
*/
int OGAPIENTRY glutDeviceGet( GLenum eWhat )
{
    freeglut_assert_ready;

    switch( eWhat )
    {
    case GLUT_HAS_KEYBOARD:
        return TRUE;

#if TARGET_HOST_UNIX_X11

    case GLUT_HAS_MOUSE:
        return TRUE;

    case GLUT_NUM_MOUSE_BUTTONS:
        /*
         * Return the number of mouse buttons available. This is a big guess.
         *
         * The present heuristic is to assume that all mice ever
         * produced (future, present, and past) have exactly 3
         * buttons.  This is obviously wrong.  There are some
         * heuristics to use to improve on this:
         *  - Read /var/log/XFree86.0.log (XFree86-specific, but
         *    in practice a pretty good place to peek).
         *  - Read /var/run/dmesg.boot (system-specific, a bit, but
         *    fairly common).
         *  - Support a command-line param and/or env. var. to
         *    inform us.
         */
        return 3;

#elif TARGET_HOST_WIN32 || TARGET_HOST_WINCE

    case GLUT_HAS_MOUSE:
        return GetSystemMetrics( SM_MOUSEPRESENT );

    case GLUT_NUM_MOUSE_BUTTONS:
#if TARGET_HOST_WINCE
        return 1;
#else
        return GetSystemMetrics( SM_CMOUSEBUTTONS );
#endif

#endif

    case GLUT_JOYSTICK_POLL_RATE:
    case GLUT_HAS_JOYSTICK:
    case GLUT_OWNS_JOYSTICK:
    case GLUT_JOYSTICK_BUTTONS:
    case GLUT_JOYSTICK_AXES:
        return 0;

    case GLUT_HAS_SPACEBALL:
    case GLUT_HAS_DIAL_AND_BUTTON_BOX:
    case GLUT_HAS_TABLET:
        return FALSE;

    case GLUT_NUM_SPACEBALL_BUTTONS:
    case GLUT_NUM_BUTTON_BOX_BUTTONS:
    case GLUT_NUM_DIALS:
    case GLUT_NUM_TABLET_BUTTONS:
        return 0;

    case GLUT_DEVICE_IGNORE_KEY_REPEAT:
        return ogStructure.Window ?
            ogStructure.Window->State.IgnoreKeyRepeat :
            0;

    case GLUT_DEVICE_KEY_REPEAT:
        /* XXX WARNING: THIS IS A BIG LIE!  */
        return GLUT_KEY_REPEAT_DEFAULT;  /* XXX Return window repeat rate? */

    default:
        ogWarning( "glutDeviceGet(): missing enum handle %i\n", eWhat );
        break;
    }

    return -1;
}

/*!
    \fn
    \brief    Returns the status of Alt, Shift, and Ctrl keys.
    \ingroup  state

              According to which, if any, modifier keys are held,
              the return value is the logical OR combination
              of any of the following symbolic bitmasks:

               - \a GLUT_ACTIVE_SHIFT
               - \a GLUT_ACTIVE_CTRL
               - \a GLUT_ACTIVE_ALT

    \bug      Complains if not invoked by a client callback.
    \bug      Does not differentiate between left- and right forms
              of the modifiers.
    \see      glutSetOption(), glutGet(), glutDeviceGet(),
              glutLayerGet()
*/
int OGAPIENTRY glutGetModifiers( void )
{
    if( ogState.Modifiers == 0xffffffff )
    {
        ogWarning( "glutGetModifiers() called outside an input callback" );
        return 0;
    }

    return ogState.Modifiers;
}

/*!
    \fn
    \brief    Allows you to get some overlay state/option variables.
    \ingroup  state
    \param    eWhat    Enumerated parameter ID.

              Returns some useful information about layers.
              Or, it would be useful if layers were implemented...
              \a eWhat may be given any of the following values:

               - \a GLUT_HAS_OVERLAY
               - \a GLUT_LAYER_IN_USE
               - \a GLUT_NORMAL_DAMAGED
                 0 unless the window system has told us that
                 the normal layer is damaged (glutPostRedisplay()
                 does not affect this).
               - \a GLUT_OVERLAY_DAMAGED
                 -1 if no layer in use.
               - \a GLUT_OVERLAY_POSSIBLE
               - \a GLUT_TRANSPARENT_INDEX
                 -1 if no layer in use.

              All information relates to the <i>current window</i>
              and any overlay that it may have.

    \see      glutSetOption(), glutGet(), glutDeviceGet(), glutGetModifiers()
*/
int OGAPIENTRY glutLayerGet( GLenum eWhat )
{
    freeglut_assert_ready;

    /*!
        \todo  Probably we should merge the below sections unless
               and until layer support is actually added.
    */
    switch( eWhat )
    {

#if TARGET_HOST_UNIX_X11

    case GLUT_OVERLAY_POSSIBLE:
        return FALSE;

    case GLUT_LAYER_IN_USE:
        return GLUT_NORMAL;

    case GLUT_HAS_OVERLAY:
        return FALSE;

    case GLUT_TRANSPARENT_INDEX:
        return -1;

    case GLUT_OVERLAY_DAMAGED:
        return -1;

#elif TARGET_HOST_WIN32 || TARGET_HOST_WINCE

    case GLUT_OVERLAY_POSSIBLE:
/*      return ogSetupPixelFormat( ogStructure.Window, GL_TRUE,
                                   PFD_OVERLAY_PLANE ); */
      return FALSE;

    case GLUT_LAYER_IN_USE:
        return GLUT_NORMAL;

    case GLUT_HAS_OVERLAY:
        return FALSE;

    case GLUT_TRANSPARENT_INDEX:
        return -1;     /* Must return -1 unless we have a real layer */

    case GLUT_OVERLAY_DAMAGED:
        return -1;
#endif

    case GLUT_NORMAL_DAMAGED:
        /*!
            \todo Should be set when the window is damaged;
                  should not be set just for glutPostRedisplay().
        */
        return FALSE;

    default:
        ogWarning( "glutLayerGet(): missing enum handle %i\n", eWhat );
        break;
    }

    /* And fail. That's good. Programs do love failing. */
    return -1;
}
