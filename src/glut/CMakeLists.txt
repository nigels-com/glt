IF (WIN32)
FILE(GLOB SOURCES .
glut_cindex.c  glut_event.c     glut_gamemode.c  glut_hel18.c
glut_keyctrl.c  glut_modifier.c  glut_space.c   glut_teapot.c     glut_warp.c
win32_menu.c glut_8x13.c     glut_cmap.c    glut_ext.c       glut_get.c  
glut_init.c   glut_keyup.c    glut_mroman.c    glut_stroke.c  
glut_tr10.c       glut_win.c      win32_util.c
glut_9x15.c     glut_cursor.c  glut_fbc.c       glut_input.c
glut_overlay.c   glut_swap.c    glut_tr24.c       glut_winmisc.c  win32_winproc.c
glut_bitmap.c   glut_dials.c   glut_fcb.c       glut_hel10.c     glut_joy.c   
glut_roman.c     glut_swidth.c  glut_util.c
win32_x11.c glut_bwidth.c   glut_dstr.c    glut_fullscrn.c  glut_hel12.c 
glut_key.c    glut_mesa.c     glut_shapes.c    glut_tablet.c  glut_vidresize.c 
win32_glx.c
)
ELSE (WIN32)
FILE(GLOB SOURCES . 
glut_cindex.c  glut_event.c     glut_gamemode.c  glut_hel18.c  glut_keyctrl.c  glut_modifier.c  glut_space.c   glut_teapot.c     glut_warp.c 
glut_8x13.c     glut_cmap.c    glut_ext.c       glut_get.c       glut_init.c   glut_keyup.c    glut_mroman.c    glut_stroke.c  glut_tr10.c       glut_win.c      glut_9x15.c     glut_cursor.c  glut_fbc.c       glut_glxext.c    glut_input.c  glut_menu2.c    glut_overlay.c   glut_swap.c    glut_tr24.c       glut_winmisc.c  glut_bitmap.c   glut_dials.c   glut_fcb.c       glut_hel10.c     glut_joy.c    glut_menu.c     glut_roman.c     glut_swidth.c  glut_util.c       layerutil.c
glut_bwidth.c   glut_dstr.c    glut_fullscrn.c  glut_hel12.c     glut_key.c    glut_mesa.c     glut_shapes.c    glut_tablet.c  glut_vidresize.c
)
ENDIF (WIN32)
ADD_LIBRARY(glut ${SOURCES})
