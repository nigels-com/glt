# Microsoft Developer Studio Project File - Name="glui32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=glui32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "glui32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "glui32.mak" CFG="glui32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "glui32 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "glui32 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "glui32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../Release"
# PROP BASE Intermediate_Dir "../Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../tmp/glui32/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../src/" /I "../../src/GL" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "GLUT_STATIC" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "glui32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../Debug"
# PROP BASE Intermediate_Dir "../Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../tmp/glui32/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../src/" /I "../../src/GL" /D "DEBUG" /D "_LIB" /D "_DEBUG" /D "GLUT_STATIC" /D "WIN32" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "glui32 - Win32 Release"
# Name "glui32 - Win32 Debug"
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\glui\algebra3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\arcball.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_add_controls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_bitmap_img_data.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_bitmaps.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_button.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_checkbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_column.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_control.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_edittext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_checkbox_0.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_checkbox_0_dis.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_checkbox_1.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_checkbox_1_dis.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_downarrow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_leftarrow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_listbox_down.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_listbox_up.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_listbox_up_dis.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_radiobutton_0.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_radiobutton_0_dis.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_radiobutton_1.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_radiobutton_1_dis.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_rightarrow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_spindown_0.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_spindown_1.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_spindown_dis.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_spinup_0.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_spinup_1.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_spinup_dis.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_img_uparrow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_listbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_mouse_iaction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_node.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_panel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_radio.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_rollout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_rotation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_separator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_spinner.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_statictext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\glui_translation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\quaternion.cpp
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\glui\algebra3.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\arcball.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\quaternion.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\stdinc.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glui\viewmodel.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\GL\glui.h
# End Source File
# End Target
# End Project
