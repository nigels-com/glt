# Microsoft Developer Studio Project File - Name="glutm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=glutm - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "glutm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "glutm.mak" CFG="glutm - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "glutm - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "glutm - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "glutm - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../Release"
# PROP BASE Intermediate_Dir "../Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../tmp/glutm/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../src/Inventor" /I "../../src/" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "glutm - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../Debug"
# PROP BASE Intermediate_Dir "../Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../tmp/glutm/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../src/Inventor" /I "../../src/" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "glutm - Win32 Release"
# Name "glutm - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\glutm\axes.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\config.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\input.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\main.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\master.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\menu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\raypp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\robot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\saver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\shape.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\timer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\window.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\winexam.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\winiv.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\glutm\axes.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\glut.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\input.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\main.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\master.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\menu.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\raypp.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\robot.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\saver.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\shape.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\timer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\window.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\winexam.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glutm\winiv.h
# End Source File
# End Group
# End Target
# End Project
