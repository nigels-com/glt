# Microsoft Developer Studio Project File - Name="glut32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=glut32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "glut32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "glut32.mak" CFG="glut32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "glut32 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "glut32 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "glut32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "./tmp/glut32/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../src/" /D "NDEBUG" /D "WIN32" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "glut32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "./tmp/glut32/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../src/" /D "_DEBUG" /D "WIN32" /D "_MBCS" /YX /FD /GZ /c
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

# Name "glut32 - Win32 Release"
# Name "glut32 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\glut\glut.rc
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_8x13.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_9x15.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_bitmap.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_bwidth.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_cindex.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_cmap.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_cursor.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_dials.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_dstr.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_event.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_ext.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_fcb.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_fullscrn.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_gamemode.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_get.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_hel10.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_hel12.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_hel18.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_init.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_input.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_joy.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_key.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_keyctrl.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_keyup.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_mesa.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_modifier.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_mroman.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_overlay.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_roman.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_shapes.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_space.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_stroke.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_swap.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_swidth.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_tablet.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_teapot.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_tr10.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_tr24.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_util.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_vidresize.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_warp.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_win.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut_winmisc.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\glutbitmap.h
# End Source File
# Begin Source File

SOURCE=..\src\glut\glutint.h
# End Source File
# Begin Source File

SOURCE=..\src\glut\glutstroke.h
# End Source File
# Begin Source File

SOURCE=..\src\glut\glutwin32.h
# End Source File
# Begin Source File

SOURCE=..\src\glut\stroke.h
# End Source File
# Begin Source File

SOURCE=..\src\glut\win32_glx.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\win32_glx.h
# End Source File
# Begin Source File

SOURCE=..\src\glut\win32_menu.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\win32_util.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\win32_winproc.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\win32_x11.c
# End Source File
# Begin Source File

SOURCE=..\src\glut\win32_x11.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\gl\glut.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\glut\glut.def
# End Source File
# Begin Source File

SOURCE=..\src\glut\glut.ico
# End Source File
# End Target
# End Project
