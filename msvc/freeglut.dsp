# Microsoft Developer Studio Project File - Name="freeeglut" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=freeeglut - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "freeglut.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "freeglut.mak" CFG="freeeglut - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "freeeglut - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "freeeglut - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "freeeglut - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "./tmp/freeeglut/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../src/" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "FREEGLUT_STATIC" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "freeeglut - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "./tmp/freeeglut/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../src/" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "FREEGLUT_STATIC" /YX /FD /GZ /c
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

# Name "freeeglut - Win32 Release"
# Name "freeeglut - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\freeglut\freeglut_callbacks.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_cursor.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_display.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_ext.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_font.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_font_data.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_gamemode.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_geometry.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_glutfont_definitions.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_init.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_joystick.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_main.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_menu.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_misc.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_overlay.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_state.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_stroke_mono_roman.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_stroke_roman.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_structure.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_teapot.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_videoresize.c
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_window.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\GL\freeglut.h
# End Source File
# Begin Source File

SOURCE=..\src\GL\freeglut_ext.h
# End Source File
# Begin Source File

SOURCE=..\src\freeglut\freeglut_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\GL\freeglut_std.h
# End Source File
# End Group
# End Target
# End Project
