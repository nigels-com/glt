# Microsoft Developer Studio Project File - Name="mesh" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mesh - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mesh.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mesh.mak" CFG="mesh - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mesh - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mesh - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mesh - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../Release"
# PROP BASE Intermediate_Dir "../Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../tmp/mesh/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../src/" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "mesh - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../Debug"
# PROP BASE Intermediate_Dir "../Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../tmp/mesh/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../src/" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "mesh - Win32 Release"
# Name "mesh - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\mesh\md3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\mesh.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\quad.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\read3dsb.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\sweep.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\triangle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\vrml.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\vrmlpars.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\vrmlscan.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\mesh\md3.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\mesh.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\quad.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\read3dsb.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\sweep.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\triangle.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\vrml.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\vrmlpars.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\vrmlscan.h
# End Source File
# End Group
# Begin Group "Parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\mesh\vrmlpars.y
# End Source File
# Begin Source File

SOURCE=..\..\src\mesh\vrmlscan.l
# End Source File
# End Group
# End Target
# End Project
