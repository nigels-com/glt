# Microsoft Developer Studio Project File - Name="glt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=glt - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "glt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "glt.mak" CFG="glt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "glt - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "glt - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "glt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../Release"
# PROP BASE Intermediate_Dir "../Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../tmp/glt/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../src/zlib/" /I "../../src/png/" /I "../../src/" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "glt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../Debug"
# PROP BASE Intermediate_Dir "../Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../tmp/glt/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../src/zlib/" /I "../../src/png/" /I "../../src/" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "glt - Win32 Release"
# Name "glt - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\glt\buffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\colmap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\color.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\config.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\countsrf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\cursor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\dlcache.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\error.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\font.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\fontasci.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\fonttex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\fontunic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\frame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\info.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\light.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\lightm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\material.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\matrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\mcubes.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\project.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\raster.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\rgb.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\texture.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\viewport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\zplane.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\zvis.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\glt\buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\colmap.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\color.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\countsrf.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\cursor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\dlcache.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\error.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\font.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\fontasci.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\fonttex.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\fontunic.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\frame.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\gl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\glu.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\info.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\light.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\lightm.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\material.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\matrix.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\mcubes.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\project.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\raster.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\rgb.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\texture.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\viewport.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\zplane.h
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\zvis.h
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\doc\doxygen.cfg
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\doxygen.dox
# End Source File
# Begin Source File

SOURCE=..\..\src\glt\rgb.dox
# End Source File
# End Group
# End Target
# End Project
