SET(SOURCES
algebra3.cpp              glui_button.cpp       glui.cpp              glui_mouse_iaction.cpp  glui_rotation.cpp    glui_string.cpp       glui_window.cpp
arcball.cpp               glui_checkbox.cpp     glui_edittext.cpp     glui_node.cpp           glui_scrollbar.cpp   glui_textbox.cpp     
glui_add_controls.cpp     glui_column.cpp       glui_filebrowser.cpp  glui_panel.cpp          glui_separator.cpp   glui_translation.cpp  ppm.cpp
glui_bitmap_img_data.cpp  glui_commandline.cpp  glui_listbox.cpp      glui_radio.cpp          glui_spinner.cpp     glui_tree.cpp         quaternion.cpp
glui_bitmaps.cpp          glui_control.cpp      glui_list.cpp         glui_rollout.cpp        glui_statictext.cpp  glui_treepanel.cpp    viewmodel.cpp
)

ADD_LIBRARY(glui ${SOURCES})
