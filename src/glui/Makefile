C_SRC = \
	glui_img_checkbox_0.c      glui_img_listbox_down.c       glui_img_radiobutton_1_dis.c  glui_img_spinup_1.c \
	glui_img_checkbox_0_dis.c  glui_img_listbox_up.c         glui_img_rightarrow.c         glui_img_spinup_dis.c \
	glui_img_checkbox_1.c      glui_img_listbox_up_dis.c     glui_img_spindown_0.c         glui_img_uparrow.c \
	glui_img_checkbox_1_dis.c  glui_img_radiobutton_0.c      glui_img_spindown_1.c \
	glui_img_downarrow.c       glui_img_radiobutton_0_dis.c  glui_img_spindown_dis.c \
	glui_img_leftarrow.c       glui_img_radiobutton_1.c      glui_img_spinup_0.c

CPP_SRC = \
	algebra3.cpp              glui_checkbox.cpp       glui_node.cpp       glui_spinner.cpp \
	arcball.cpp glui.cpp      glui_column.cpp         glui_panel.cpp      glui_statictext.cpp \
	glui_add_controls.cpp     glui_control.cpp        glui_radio.cpp      glui_translation.cpp \
	glui_bitmap_img_data.cpp  glui_edittext.cpp       glui_rollout.cpp    \
	glui_bitmaps.cpp          glui_listbox.cpp        glui_rotation.cpp   quaternion.cpp \
	glui_button.cpp           glui_mouse_iaction.cpp  glui_separator.cpp

ROOT     = ../..
INCLUDE   = -I$(ROOT)/src/GL 
#EXPAND   = --tabs=2

default: lib

ifdef WINDIR
ARCHIVE = libglui32.a
else
ARCHIVE = libglui.a
endif

include $(ROOT)/gcc/Makefile.inc




