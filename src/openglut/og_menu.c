/*!
    \file  og_menu.c
    \brief Pull-down menu creation and handling.
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

/* -- DEFINITIONS ---------------------------------------------------------- */

/*
 * FREEGLUT_MENU_FONT can be any freeglut/OpenGLUT bitmapped font.
 * (Stroked fonts would not be out of the question, but we'd need to alter
 *  code, since OpenGLUT does not quite unify stroked and
 *  bitmapped font handling.)
 * Old UNIX/X11 GLUT (BSD, UNIX, IRIX, LINUX, HPUX, ...) used a system
 * font best approximated by an 18-pixel HELVETICA, I think.  MS-WINDOWS
 * GLUT used something closest to the 8x13 fixed-width font.  (Old
 * GLUT apparently uses host-system menus rather than building its own.
 * OpenGLUT is building its own menus from scratch.)
 *
 * FREEGLUT_MENU_HEIGHT gives the height of ONE menu box.  This should be
 * the distances between two adjacent menu entries.  It should scale
 * automatically with the font choice, so you needn't alter it---unless you
 * use a stroked font.
 *
 * FREEGLUT_MENU_BORDER says how many pixels to allow around the edge of a
 * menu.  (It also seems to be the same as the number of pixels used as
 * a border around *items* to separate them from neighbors.  John says
 * that that wasn't the original intent...if not, perhaps we need another
 * symbolic constant, FREEGLUT_MENU_ITEM_BORDER, or such.)
 */
/*! \todo Stuff these into global state variables */
/*! \todo Maybe support runtime selection between bitmapped and stroked? */
#if TARGET_HOST_WIN32 || TARGET_HOST_WINCE
#define  FREEGLUT_MENU_FONT    GLUT_BITMAP_8_BY_13
#else
#define  FREEGLUT_MENU_FONT    GLUT_BITMAP_HELVETICA_18
#endif

#define  FREEGLUT_MENU_HEIGHT  (glutBitmapHeight(FREEGLUT_MENU_FONT) + \
                                FREEGLUT_MENU_BORDER)
#define  FREEGLUT_MENU_BORDER   2


/*
 * These variables are for rendering the OpenGLUT menu items.
 *
 * The choices are fore- and background, with and without h for Highlighting.
 * Old GLUT appeared to be system-dependant for its colors (sigh) so we are
 * too.
 */
/*! \todo Stuff these variables into global state; init via glutInit*() */
#if TARGET_HOST_WIN32 || TARGET_HOST_WINCE
static float menu_pen_fore  [4] = {0.0f,  0.0f,  0.0f,  1.0f};
static float menu_pen_back  [4] = {0.85f, 0.85f, 0.85f, 1.0f};
static float menu_pen_hfore [4] = {1.0f,  1.0f,  1.0f,  1.0f};
static float menu_pen_hback [4] = {0.15f, 0.15f, 0.45f, 1.0f};
#else
static float menu_pen_fore  [4] = {0.0f,  0.0f,  0.0f,  1.0f};
static float menu_pen_back  [4] = {0.70f, 0.70f, 0.70f, 1.0f};
static float menu_pen_hfore [4] = {0.0f,  0.0f,  0.0f,  1.0f};
static float menu_pen_hback [4] = {1.0f,  1.0f,  1.0f,  1.0f};
#endif

/* -- PRIVATE FUNCTIONS ---------------------------------------------------- */

/*
 * Private function to find a menu entry by index
 */
static SOG_MenuEntry *oghFindMenuEntry( SOG_Menu *menu, const int index )
{
    SOG_MenuEntry *entry = ( SOG_MenuEntry * )menu->Entries.First;
    int i = 1;

    while( entry && ( index != i ) )
    {
        ++i;
        entry = ( SOG_MenuEntry * )entry->Node.Next;
    }
    return entry;
}

/*
 * Private function to check for the current menu/sub menu activity state
 */
static GLboolean oghCheckMenuStatus( SOG_Window *window, SOG_Menu *menu )
{
    SOG_MenuEntry *menuEntry;
    int x, y;

    /* First of all check any of the active sub menus. */
    for( menuEntry = (SOG_MenuEntry *)menu->Entries.First;
         menuEntry;
         menuEntry = (SOG_MenuEntry *)menuEntry->Node.Next
    )
        if( menuEntry->SubMenu && menuEntry->IsActive )
        {
            /*
             * OK, have the sub-menu checked, too. If it returns GL_TRUE, it
             * will mean that it caught the mouse cursor and we do not need
             * to regenerate the activity list, and so our parents do...
             */
            GLboolean return_status = oghCheckMenuStatus(
                window, menuEntry->SubMenu
            );

            /*
             * Reactivate the submenu as the checkMenuStatus may have turned
             * it off if the mouse is in its parent menu entry.
             */
            menuEntry->SubMenu->IsActive = GL_TRUE;
            if ( return_status )
                return GL_TRUE;
        }

    /* So much for our sub menus; let's check the current menu: */
    x = window->State.MouseX;
    y = window->State.MouseY;

    for( menuEntry = (SOG_MenuEntry *)menu->Entries.First;
         menuEntry;
         menuEntry = (SOG_MenuEntry *)menuEntry->Node.Next )
        menuEntry->IsActive = GL_FALSE;

    menu->IsActive = GL_FALSE;

    /* Check if the mouse cursor is within the current menu box */
    if( ( x >= FREEGLUT_MENU_BORDER ) &&
        ( x < menu->Width  - FREEGLUT_MENU_BORDER ) &&
        ( y >= FREEGLUT_MENU_BORDER ) &&
        ( y < menu->Height - FREEGLUT_MENU_BORDER ) &&
        ( window == menu->Window )
    )
    {
        int menuID = ( y - FREEGLUT_MENU_BORDER ) / FREEGLUT_MENU_HEIGHT;

        /* The mouse cursor is somewhere over our box, check it out. */
        menuEntry = oghFindMenuEntry( menu, menuID + 1 );
        assert( menuEntry );

        menuEntry->IsActive = GL_TRUE;
        menuEntry->Ordinal = menuID;

        /*
         * If this is not the same as the last active menu entry, deactivate
         * the previous entry.  Specifically, if the previous active entry
         * was a submenu then deactivate it.
         */
        if( menu->ActiveEntry && ( menuEntry != menu->ActiveEntry ) )
            if( menu->ActiveEntry->SubMenu )
                ogDeactivateSubMenu( menu->ActiveEntry );

        menu->ActiveEntry = menuEntry;
        menu->IsActive = GL_TRUE;

        /*
         * OKi, we have marked that entry as active, but it would be also
         * nice to have its contents updated, in case it's a sub menu.
         * Also, ignore the return value of the check function:
         */
        if( menuEntry->SubMenu )
        {
            if( ! menuEntry->SubMenu->IsActive )
            {
                SOG_Window *current_window = ogStructure.Window;

                /* Set up the initial menu position now... */
                menuEntry->SubMenu->IsActive = GL_TRUE;

                /* Set up the initial submenu position now: */
                menuEntry->SubMenu->X = menu->X + menu->Width;
                menuEntry->SubMenu->Y = menu->Y +
                    menuEntry->Ordinal * FREEGLUT_MENU_HEIGHT;

                if( menuEntry->SubMenu->X + menuEntry->SubMenu->Width >
                    glutGet( GLUT_SCREEN_WIDTH ) )
                    menuEntry->SubMenu->X = menu->X -
                        menuEntry->SubMenu->Width;

                if( menuEntry->SubMenu->Y + menuEntry->SubMenu->Height >
                    glutGet( GLUT_SCREEN_HEIGHT ) )
                    menuEntry->SubMenu->Y -= ( menuEntry->SubMenu->Height -
                                               FREEGLUT_MENU_HEIGHT -
                                               2 * FREEGLUT_MENU_BORDER );

                ogSetWindow( menuEntry->SubMenu->Window );
                glutPositionWindow( menuEntry->SubMenu->X,
                                    menuEntry->SubMenu->Y );
                glutReshapeWindow( menuEntry->SubMenu->Width,
                                   menuEntry->SubMenu->Height );
                glutPopWindow( );
                glutShowWindow( );
                menuEntry->SubMenu->Window->ActiveMenu = menuEntry->SubMenu;
                ogSetWindow( current_window );
            }

            oghCheckMenuStatus( window, menuEntry->SubMenu );

            /* Activate it because its parent entry is active */
            menuEntry->SubMenu->IsActive = GL_TRUE;
        }
        return GL_TRUE; /* Report back that we have caught the menu cursor */
    }
    return GL_FALSE; /* Looks like the menu cursor is somewhere else... */
}

/*
 * Displays a menu box and all of its submenus (if they are active)
 */
static void oghDisplayMenuBox( SOG_Menu *menu )
{
    SOG_MenuEntry *menuEntry;
    int i;
    int border = FREEGLUT_MENU_BORDER;

    /*
     * Have the menu box drawn first. The +- values are
     * here just to make it more nice-looking...
     */
    /* a non-black dark version of the below. */
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    glBegin( GL_QUAD_STRIP );
        glVertex2i( menu->Width         , 0                    );
        glVertex2i( menu->Width - border,                border);
        glVertex2i( 0                   , 0                    );
        glVertex2i(               border,                border);
        glVertex2i( 0                   , menu->Height         );
        glVertex2i(               border, menu->Height - border);
    glEnd( );

    /* a non-black dark version of the below. */
    glColor4f( 0.5f, 0.5f, 0.5f, 1.0f );
    glBegin( GL_QUAD_STRIP );
        glVertex2i( 0                   , menu->Height         );
        glVertex2i(               border, menu->Height - border);
        glVertex2i( menu->Width         , menu->Height         );
        glVertex2i( menu->Width - border, menu->Height - border);
        glVertex2i( menu->Width         , 0                    );
        glVertex2i( menu->Width - border,                border);
    glEnd( );

    glColor4fv( menu_pen_back );
    glBegin( GL_QUADS );
        glVertex2i(               border,                border);
        glVertex2i( menu->Width - border,                border);
        glVertex2i( menu->Width - border, menu->Height - border);
        glVertex2i(               border, menu->Height - border);
    glEnd( );

    /* Check if any of the submenus is currently active... */
    for( menuEntry = (SOG_MenuEntry *)menu->Entries.First;
         menuEntry;
         menuEntry = (SOG_MenuEntry *)menuEntry->Node.Next )
        /* Has the menu been marked as active, maybe? */
        if( menuEntry->IsActive )
        {
            /*
             * That's truly right, and we need to have it highlighted.
             * There is an assumption that mouse cursor didn't move
             * since the last check of menu activity state:
             */
            int menuID = menuEntry->Ordinal;

            /* So have the highlight drawn... */
            glColor4fv( menu_pen_hback );
            glBegin( GL_QUADS );
                glVertex2i( border,
                            (menuID + 0)*FREEGLUT_MENU_HEIGHT + border );
                glVertex2i( menu->Width - border,
                            (menuID + 0)*FREEGLUT_MENU_HEIGHT + border );
                glVertex2i( menu->Width - border,
                            (menuID + 1)*FREEGLUT_MENU_HEIGHT + border );
                glVertex2i( border,
                            (menuID + 1)*FREEGLUT_MENU_HEIGHT + border );
            glEnd( );
        }

    /* Print the menu entries now... */
    glColor4fv( menu_pen_fore );
    for( menuEntry = (SOG_MenuEntry *)menu->Entries.First, i = 0;
         menuEntry;
         menuEntry = (SOG_MenuEntry *)menuEntry->Node.Next, ++i )
    {
        /* If the menu entry is active, set the color to white */
        if( menuEntry->IsActive )
            glColor4fv( menu_pen_hfore );

        /* Move the raster into position... */
        /* Try to center the text - JCJ 31 July 2003*/
        glRasterPos2i(
            2 * border,
            ( i + 1 )*FREEGLUT_MENU_HEIGHT -
            ( int )( FREEGLUT_MENU_HEIGHT*0.3 - border )
        );

        /* Have the label drawn, character after character: */
        glutBitmapString( FREEGLUT_MENU_FONT,
                          ( unsigned char * )menuEntry->Text );

        /* If it's a submenu, draw a right arrow */
        if( menuEntry->SubMenu )
        {
            int width = glutBitmapWidth( FREEGLUT_MENU_FONT, '_' );
            int x_base = menu->Width - 2 - width;
            int y_base = i*FREEGLUT_MENU_HEIGHT + border;
            glBegin( GL_TRIANGLES );
                glVertex2i( x_base, y_base + 2*border);
                glVertex2i( menu->Width - 2, y_base +
                            ( FREEGLUT_MENU_HEIGHT + border) / 2 );
                glVertex2i( x_base, y_base + FREEGLUT_MENU_HEIGHT - border );
            glEnd( );
        }

        /* If the menu entry is active, reset the color */
        if( menuEntry->IsActive )
            glColor4fv( menu_pen_fore );
    }

    /* Check if any of our children needs to be redrawn: */
    for( menuEntry = ( SOG_MenuEntry * )menu->Entries.First;
         menuEntry;
         menuEntry = ( SOG_MenuEntry * )menuEntry->Node.Next )
        if( menuEntry->SubMenu && menuEntry->IsActive )
        {
            /* Yeah, indeed. Have it redrawn now: */
            ogSetWindow( menuEntry->SubMenu->Window );
            oghDisplayMenuBox( menuEntry->SubMenu );
            ogSetWindow( menu->Window );
        }
}

/*
 * Private static function to set the parent window of a submenu and all
 * of its submenus
 */
static void oghSetSubmenuParentWindow( SOG_Window *window, SOG_Menu *menu )
{
    SOG_MenuEntry *menuEntry;

    menu->ParentWindow = window;

    for( menuEntry = ( SOG_MenuEntry * )menu->Entries.First;
         menuEntry;
         menuEntry = ( SOG_MenuEntry * )menuEntry->Node.Next )
        if( menuEntry->SubMenu )
            oghSetSubmenuParentWindow( window, menuEntry->SubMenu );
}


/*
 * Displays the currently active menu for the current window
 */
void ogDisplayMenu( void )
{
    SOG_Window *window = ogStructure.Window;
    SOG_Menu *menu = NULL;

    freeglut_assert_window;

    /*
     * Check if there is an active menu attached to this window...
     */
    menu = window->ActiveMenu;
    if( menu )
    {
        ogSetWindow( menu->Window );

        glPushAttrib(
            GL_DEPTH_BUFFER_BIT | GL_TEXTURE_BIT | GL_LIGHTING_BIT |
            GL_POLYGON_BIT
        );

        glDisable( GL_DEPTH_TEST );
        glDisable( GL_TEXTURE_2D );
        glDisable( GL_LIGHTING   );
        glDisable( GL_CULL_FACE  );

        glMatrixMode( GL_PROJECTION );
        glPushMatrix( );
        glLoadIdentity( );
        glOrtho(
            0, glutGet( GLUT_WINDOW_WIDTH  ),
            glutGet( GLUT_WINDOW_HEIGHT ), 0,
            -1, 1
        );

        glMatrixMode( GL_MODELVIEW );
        glPushMatrix( );
        glLoadIdentity( );

        oghCheckMenuStatus( window, menu );
        oghDisplayMenuBox( menu );

        glPopAttrib( );

        glMatrixMode( GL_PROJECTION );
        glPopMatrix( );
        glMatrixMode( GL_MODELVIEW );
        glPopMatrix( );

        glutSwapBuffers( );

        ogSetWindow ( window );
    }
}

/*
 * Activates a menu pointed by the function argument
 */
void ogActivateMenu( SOG_Window *window, int button )
{
    /*
     * We'll be referencing this menu a lot, so remember its address:
     */
    SOG_Menu* menu = window->Menu[ button ];

    /*
     * Mark the menu as active, so that it gets displayed:
     */
    window->ActiveMenu = menu;
    menu->IsActive = GL_TRUE;
    ogState.ActiveMenus++;

    /*
     * Set up the initial menu position now:
     */
    menu->X = window->State.MouseX + glutGet( GLUT_WINDOW_X );
    menu->Y = window->State.MouseY + glutGet( GLUT_WINDOW_Y );

    if( menu->X + menu->Width > glutGet ( GLUT_SCREEN_WIDTH ) )
        menu->X -=menu->Width;

    if( menu->Y + menu->Height > glutGet ( GLUT_SCREEN_HEIGHT ) )
        menu->Y -=menu->Height;

    ogSetWindow( menu->Window );
    glutPositionWindow( menu->X, menu->Y );
    glutReshapeWindow( menu->Width, menu->Height );
    glutPopWindow( );
    glutShowWindow( );
    menu->Window->ActiveMenu = menu;
}

/*
 * Check whether an active menu absorbs a mouse click
 */
GLboolean ogCheckActiveMenu ( SOG_Window *window, SOG_Menu *menu )
{
    /*
     * XXX See the Menu module discussion for the button
     * XXX policy re. menus.
     */
    /*
     * Since menus can have submenus, we need to check this recursively.
     */
    return oghCheckMenuStatus( window, menu );
}

/*
 * Function to check for menu entry selection on menu deactivation
 */
void ogExecuteMenuCallback( SOG_Menu *menu )
{
    SOG_MenuEntry *menuEntry;

    /*
     * First of all check any of the active sub menus...
     */
    for( menuEntry = (SOG_MenuEntry *)menu->Entries.First;
         menuEntry;
         menuEntry = (SOG_MenuEntry *)menuEntry->Node.Next)
        if( menuEntry->IsActive )
        {
            if( menuEntry->SubMenu )
                ogExecuteMenuCallback( menuEntry->SubMenu );
            else
                if( menu->Callback )
                    menu->Callback( menuEntry->ID );
            return;
        }
}

/*
 * Deactivates a menu pointed by the function argument.
 */
void ogDeactivateMenu( SOG_Window *window )
{
    SOG_Window *current_window = ogStructure.Window;

    /* Check if there is an active menu attached to this window... */
    SOG_Menu* menu = window->ActiveMenu;
    SOG_MenuEntry *menuEntry;

    /* Did we find an active window? */
    if( menu )
    {
        /* Hide the present menu's window */
        ogSetWindow( menu->Window );
        glutHideWindow( );

        /* Forget about having that menu active anymore, now: */
        menu->Window->ActiveMenu = NULL;
        menu->ParentWindow->ActiveMenu = NULL;
        menu->IsActive = GL_FALSE;

        ogState.ActiveMenus--;

        /* Hide all submenu windows, and the root menu's window. */
        for( menuEntry = ( SOG_MenuEntry * )menu->Entries.First;
             menuEntry;
             menuEntry = ( SOG_MenuEntry * )menuEntry->Node.Next )
            /* Is that an active submenu by any case? */
            if( menuEntry->SubMenu )
                ogDeactivateSubMenu( menuEntry );

        ogSetWindow( current_window );
    }
}

/*
 * Deactivates a menu pointed by the function argument.
 */
void ogDeactivateSubMenu( SOG_MenuEntry *menuEntry )
{
    SOG_Window *current_window = ogStructure.Window;
    SOG_MenuEntry *subMenuIter;
    /* Hide the present menu's window */
    ogSetWindow( menuEntry->SubMenu->Window );
    glutHideWindow( );

    /* Forget about having that menu active anymore, now: */
    menuEntry->SubMenu->Window->ActiveMenu = NULL;
    menuEntry->SubMenu->IsActive = GL_FALSE;

    /* Hide all submenu windows, and the root menu's window. */
    for ( subMenuIter = (SOG_MenuEntry *)menuEntry->SubMenu->Entries.First;
          subMenuIter;
          subMenuIter = (SOG_MenuEntry *)subMenuIter->Node.Next )
        /* Is that an active submenu by any case? */
        if( subMenuIter->SubMenu )
            ogDeactivateSubMenu( subMenuIter );

    ogSetWindow( current_window );
}

/*
 * Recalculates current menu's box size
 */
void oghCalculateMenuBoxSize( void )
{
    SOG_MenuEntry *menuEntry;
    int width = 0, height = 0;

    /* Make sure there is a current menu set */
    freeglut_assert_ready;
    if( ogStructure.Menu )
    {
        /* The menu's box size depends on the menu entries: */
        for( menuEntry = ( SOG_MenuEntry * )ogStructure.Menu->Entries.First;
             menuEntry;
             menuEntry = ( SOG_MenuEntry * )menuEntry->Node.Next )
        {
            /* Update the menu entry's width value */
            menuEntry->Width = glutBitmapLength(
                FREEGLUT_MENU_FONT,
                (unsigned char *)menuEntry->Text
            );

            /*
             * If the entry is a submenu, then it needs to be wider to
             * accomodate the arrow. JCJ 31 July 2003
             */
            if (menuEntry->SubMenu )
                menuEntry->Width += glutBitmapLength(
                    FREEGLUT_MENU_FONT,
                    (unsigned char *)"_"
                );

            /* Check if it's the biggest we've found */
            if( menuEntry->Width > width )
                width = menuEntry->Width;

            height += FREEGLUT_MENU_HEIGHT;
        }

        /* Store the menu's box size now: */
        ogStructure.Menu->Height = height + 2 * FREEGLUT_MENU_BORDER;
        ogStructure.Menu->Width  = width  + 4 * FREEGLUT_MENU_BORDER;
    }
}


/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*!
    \fn
    \brief    Creates a new menu object.
    \ingroup  menus
    \param    callback    Client hook for the new menu.

              Creates a menu with a callback bound to \a callback, and
              returns the menu's integer id.

              When the user makes a selection from this menu,
              \a callback is invoked with the parameter \a value,
              which comes from the (\a label, \a value) pair that
              you define with glutAddMenuEntry().

    \see      glutDestroyMenu(), glutGetMenu(), glutSetMenu(),
              glutAddMenuEntry(), glutAddSubMenu(),
              glutChangeToMenuEntry(), glutChangeToSubMenu(),
              glutRemoveMenuItem(), glutAttachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
int OGAPIENTRY glutCreateMenu( void( *callback )( int value ) )
{
    /* The menu object creation code resides in og_structure.c */
    return ogCreateMenu( callback )->ID;
}

/*!
    \fn
    \brief    Destroys menu object.
    \ingroup  menus
    \param    menuID    The menu to destroy.

              Destroys a given menu object by its ID.

    \see      glutCreateMenu(), glutGetMenu(), glutSetMenu(),
              glutAddMenuEntry(), glutAddSubMenu(),
              glutChangeToMenuEntry(), glutChangeToSubMenu(),
              glutRemoveMenuItem(), glutAttachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
void OGAPIENTRY glutDestroyMenu( int menuID )
{
    SOG_Menu* menu = ogMenuByID( menuID );

    freeglut_assert_ready;
    if( menu )
        /* The menu object destruction code resides in og_structure.c */
        ogDestroyMenu( menu );
}

/*!
    \fn
    \brief    Gets current menu ID.
    \ingroup  menus

              Returns the integer ID of the current menu.

    \see      glutCreateMenu(), glutDestroyMenu(), glutSetMenu(),
              glutAddMenuEntry(), glutAddSubMenu(),
              glutChangeToMenuEntry(), glutChangeToSubMenu(),
              glutRemoveMenuItem(), glutAttachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
int OGAPIENTRY glutGetMenu( void )
{
    freeglut_assert_ready;

    if( ogStructure.Menu )
        return ogStructure.Menu->ID;

    return 0;
}

/*!
    \fn
    \brief    Sets current menu ID.
    \ingroup  menus
    \param    menuID    Selected menu.

              Tells OpenGLUT to select the menu given by the
              \a menuID.

    \see      glutCreateMenu(), glutDestroyMenu(), glutGetMenu(),
              glutAddMenuEntry(), glutAddSubMenu(),
              glutChangeToMenuEntry(), glutChangeToSubMenu(),
              glutRemoveMenuItem(), glutAttachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
void OGAPIENTRY glutSetMenu( int menuID )
{
    SOG_Menu* menu = ogMenuByID( menuID );

    freeglut_assert_ready;
    if( menu )
        ogStructure.Menu = menu;
}

/*!
    \fn
    \brief    Appends an item to the current menu.
    \ingroup  menus
    \param    label    Text of the menu item.
    \param    value    Integer to bind to the menu item.

              Inserts a given (\a label, \a value) pair
              into the current menu.  \a label is the text used for
              the item in the menu; \a value is what your program will
              receive (via the menu's registered callback)
              whenever the user selects this item.

              The new entry is added at the bottem of the menu.

    \see      glutCreateMenu(), glutDestroyMenu(), glutGetMenu(),
              glutSetMenu(), glutAddSubMenu(),
              glutChangeToMenuEntry(), glutChangeToSubMenu(),
              glutRemoveMenuItem(), glutAttachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
void OGAPIENTRY glutAddMenuEntry( const char *label, int value )
{
    SOG_MenuEntry *menuEntry =
        ( SOG_MenuEntry * )calloc( sizeof( SOG_MenuEntry ), 1 );

    freeglut_assert_ready;
    if( ogStructure.Menu )
    {
        menuEntry->Text = strdup( label );
        menuEntry->ID   = value;

        /* Have the new menu entry attached to the current menu */
        ogListAppend( &ogStructure.Menu->Entries, &menuEntry->Node );

        oghCalculateMenuBoxSize( );
    }
}

/*!
    \fn
    \brief    Attaches a submenu to the current menu.
    \ingroup  menus
    \param    label     Text of the submenu.
    \param    subMenuID The menuID of the submenu.

              Attaches a previously defined menu as a submenu
              to the current menu.  \a label is the text used for the
              item in the menu.  \a subMenuID is the menu ID returned
              by a previous call to glutCreateMenu() for the attached
              menu.

              The submenu is attached just as a non-submenu item
              is added: At the current bottom of the list.

    \see      glutCreateMenu(), glutDestroyMenu(), glutGetMenu(),
              glutSetMenu(), glutAddMenuEntry(),
              glutChangeToMenuEntry(), glutChangeToSubMenu(),
              glutRemoveMenuItem(), glutAttachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
void OGAPIENTRY glutAddSubMenu( const char *label, int subMenuID )
{
    SOG_MenuEntry *menuEntry =
        ( SOG_MenuEntry * )calloc( sizeof( SOG_MenuEntry ), 1 );
    SOG_Menu *subMenu = ogMenuByID( subMenuID );

    freeglut_assert_ready;
    if( ogStructure.Menu && subMenu )
    {
        menuEntry->Text    = strdup( label );
        menuEntry->SubMenu = subMenu;
        menuEntry->ID      = -1;

        /* Make the submenu's parent window be the menu's parent window */
        oghSetSubmenuParentWindow( ogStructure.Menu->ParentWindow, subMenu );

        ogListAppend( &ogStructure.Menu->Entries, &menuEntry->Node );
        oghCalculateMenuBoxSize( );
    }
}

/*!
    \fn
    \brief    Replaces a given menu entry with an item.
    \ingroup  menus
    \param    item    Integer position down the list.
    \param    label   Text of the submenu.
    \param    value   The menuID of the submenu.

              Walks the list of the menu items and replaces
              the numbered \a item in the list with the
              given definition.  Except that it replaces a
              pre-existing \a item, this function is much like
              glutAddMenuEntry().

    \see      glutCreateMenu(), glutDestroyMenu(), glutGetMenu(),
              glutSetMenu(), glutAddMenuEntry(), glutAddSubMenu(),
              glutChangeToSubMenu(),
              glutRemoveMenuItem(), glutAttachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
void OGAPIENTRY glutChangeToMenuEntry( int item, const char *label, int value )
{
    SOG_MenuEntry *menuEntry = NULL;

    freeglut_assert_ready;
    if( ogStructure.Menu )
    {
        /* Get n-th menu entry in the current menu, starting from one: */
        menuEntry = oghFindMenuEntry( ogStructure.Menu, item );
        if( menuEntry )
        {
            
            /* We want it to become a normal menu entry, so: */
            if( menuEntry->Text )
                free( menuEntry->Text );

            menuEntry->Text    = strdup( label );
            menuEntry->ID      = value;
            menuEntry->SubMenu = NULL;
            oghCalculateMenuBoxSize( );
        }
    }
}

/*!
    \fn
    \brief    Replaces a given menu entry with a submenu.
    \ingroup  menus
    \param    item      Integer position down the list.
    \param    label     Text of the submenu.
    \param    subMenuID The menuID of the submenu.

              Walks the list of the menu items and replaces
              the numbered \a item in the list with the
              given submenu.

    \see      glutCreateMenu(), glutDestroyMenu(), glutGetMenu(),
              glutSetMenu(), glutAddMenuEntry(), glutAddSubMenu(),
              glutChangeToMenuEntry(),
              glutRemoveMenuItem(), glutAttachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
void OGAPIENTRY glutChangeToSubMenu( int item, const char *label,
                                     int subMenuID )
{
    SOG_Menu        *subMenu = ogMenuByID( subMenuID );
    SOG_MenuEntry *menuEntry = NULL;

    freeglut_assert_ready;
    if( ogStructure.Menu && subMenu )
    {
        /* Get n-th menu entry in the current menu, starting from one: */
        menuEntry = oghFindMenuEntry( ogStructure.Menu, item );
        if( menuEntry )
        {
            /* We want it to become a sub menu entry, so: */
            if( menuEntry->Text )
                free( menuEntry->Text );

            menuEntry->Text    = strdup( label );
            menuEntry->SubMenu = subMenu;
            menuEntry->ID      = -1;
            oghCalculateMenuBoxSize( );
        }
    }
}

/*!
    \fn
    \brief    Removes a given menu entry.
    \ingroup  menus
    \param    item    Integer position down the list.

              Walks the list of the menu items and deletes
              the numbered \a item in the list.

    \see      glutCreateMenu(), glutDestroyMenu(), glutGetMenu(),
              glutSetMenu(), glutAddMenuEntry(), glutAddSubMenu(),
              glutChangeToMenuEntry(), glutChangeToSubMenu(),
              glutAttachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
void OGAPIENTRY glutRemoveMenuItem( int item )
{
    SOG_MenuEntry *menuEntry;

    freeglut_assert_ready;
    if( ogStructure.Menu )
    {
        /* Get n-th menu entry in the current menu, starting from one: */
        menuEntry = oghFindMenuEntry( ogStructure.Menu, item );
        if( menuEntry )
        {
            ogListRemove( &ogStructure.Menu->Entries, &menuEntry->Node );
            if ( menuEntry->Text )
                free( menuEntry->Text );

            free( menuEntry );
            oghCalculateMenuBoxSize( );
        }
    }
}

/*!
    \fn
    \brief    Attaches the current menu to the current window.
    \ingroup  menus
    \param    button    Binds the menu to this mouse button.

              Associates the \a button with the current menu
              in the current window.

    \bug      Assumes 3 mouse buttons.  (Actually \a FREEGLUT_MAX_MENUS
              holds the assumed number of buttons.)  Cannot bind to more
              buttons.  Will not issue any warnings or errors if the user
              does not have enough buttons to reach your menu.
    \see      glutCreateMenu(), glutDestroyMenu(), glutGetMenu(),
              glutSetMenu(), glutAddMenuEntry(), glutAddSubMenu(),
              glutChangeToMenuEntry(), glutChangeToSubMenu(),
              glutDetachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
void OGAPIENTRY glutAttachMenu( int button )
{
    freeglut_assert_ready;

    if(
        ogStructure.Window &&
        ogStructure.Menu &&
        ( button >= 0 ) &&
        ( button < FREEGLUT_MAX_MENUS )
    )
    {
        ogStructure.Window->Menu[ button ] = ogStructure.Menu;

        /*
         * Make the parent window of the menu (and all submenus) the
         * current window
         *
         * XXX Is this wise?  It seems that a (sub)menu can have multiple
         * XXX parents...  Parents also do not get dis-associated when
         * XXX we detach the menu.
         */
        oghSetSubmenuParentWindow( ogStructure.Window, ogStructure.Menu );
    }
}

/*!
    \fn
    \brief    Detaches from menu from the current window.
    \ingroup  menus
    \param    button    Unbinds the menu on this mouse button.

              If the given \a button has a menu bound to it,
              this breaks the assocation.

    \see      glutCreateMenu(), glutDestroyMenu(), glutGetMenu(),
              glutSetMenu(), glutAddMenuEntry(), glutAddSubMenu(),
              glutChangeToMenuEntry(), glutChangeToSubMenu(),
              glutAttachMenu(),
              glutSetMenuData(), glutGetMenuData()
*/
void OGAPIENTRY glutDetachMenu( int button )
{
    freeglut_assert_ready;

    if(
        ogStructure.Window &&
        ogStructure.Menu &&
        ( button >= 0 ) &&
        ( button < FREEGLUT_MAX_MENUS )
    )
        ogStructure.Window->Menu[ button ] = NULL;
}

/*!
    \fn
    \brief    Rerieves user data from a menu.
    \ingroup  menus

              Retrieves a previously stored arbitrary user
              data pointer from the current menu.

    \see      glutSetMenuData()
*/
void* OGAPIENTRY glutGetMenuData( void )
{
    return ogStructure.Menu->UserData;
}

/*!
    \fn
    \brief    Store user data in a menu.
    \ingroup  menus
    \param    data    An arbitrary client pointer.

              Stores an arbitrary user data pointer.  OpenGLUT
              does not interpret this pointer in any way, but
              merely stores it for you in the menu structure.

    \see      glutGetMenuData()
*/
void OGAPIENTRY glutSetMenuData(void *data)
{
    ogStructure.Menu->UserData=data;
}
