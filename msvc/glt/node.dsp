# Microsoft Developer Studio Project File - Name="node" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=node - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "node.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "node.mak" CFG="node - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "node - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "node - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "node - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../Release"
# PROP BASE Intermediate_Dir "../Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../tmp/node/Release"
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

!ELSEIF  "$(CFG)" == "node - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../Debug"
# PROP BASE Intermediate_Dir "../Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../tmp/node/Debug"
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

# Name "node - Win32 Release"
# Name "node - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\node\blend.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\dlist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\fade.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\field.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\fieldmen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\fields.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\histogrm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\interp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\line.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\polygon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\registry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\shape.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\shapes.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\skybox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\skyspher.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\slides.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\sprite.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\starfld.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\text.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\node\tiled.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\node\blend.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\dlist.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\fade.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\field.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\fieldmen.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\fields.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\histogrm.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\interp.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\line.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\polygon.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\registry.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\shape.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\shapes.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\skybox.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\skyspher.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\slides.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\sprite.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\starfld.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\text.h
# End Source File
# Begin Source File

SOURCE=..\..\src\node\tiled.h
# End Source File
# End Group
# End Target
# End Project
