# Microsoft Developer Studio Project File - Name="misc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=misc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "misc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "misc.mak" CFG="misc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "misc - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "misc - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "misc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../Release"
# PROP BASE Intermediate_Dir "../Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../tmp/misc/Release"
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

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../Debug"
# PROP BASE Intermediate_Dir "../Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../tmp/misc/Debug"
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

# Name "misc - Win32 Release"
# Name "misc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\misc\bmp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\buffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\compress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\endian.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\hex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\jpeg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\observer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\png.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\ppm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\string.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\text2src.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\tga.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\timer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\misc\buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\cbuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\compress.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\endian.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\hex.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\image.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\lru.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\observer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\refcount.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\stlutil.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\string.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\text2src.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\timer.h
# End Source File
# End Group
# Begin Group "Internal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\misc\internal\lzf.h
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\internal\lzf_c.c
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\internal\lzf_d.c
# End Source File
# Begin Source File

SOURCE=..\..\src\misc\internal\lzfP.h
# End Source File
# End Group
# End Target
# End Project
