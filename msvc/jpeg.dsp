# Microsoft Developer Studio Project File - Name="jpeg" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=jpeg - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "jpeg.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "jpeg.mak" CFG="jpeg - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "jpeg - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "jpeg - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "jpeg - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../Release"
# PROP BASE Intermediate_Dir "../Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "tmp/jpeg/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../src/" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "NO_MIN_MAX" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "jpeg - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../Debug"
# PROP BASE Intermediate_Dir "../Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "tmp/jpeg/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../src/" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "NO_MIN_MAX" /YX /FD /GZ /c
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

# Name "jpeg - Win32 Release"
# Name "jpeg - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\jpeg\cdjpeg.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcapimin.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcapistd.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jccoefct.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jccolor.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcdctmgr.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jchuff.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcinit.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcmainct.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcmarker.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcmaster.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcomapi.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcparam.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcphuff.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcprepct.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jcsample.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jctrans.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdapimin.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdapistd.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdatadst.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdatasrc.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdcoefct.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdcolor.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jddctmgr.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdhuff.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdinput.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdmainct.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdmarker.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdmaster.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdmerge.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdphuff.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdpostct.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdsample.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdtrans.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jerror.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jfdctflt.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jfdctfst.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jfdctint.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jidctflt.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jidctfst.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jidctint.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jidctred.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jmemansi.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jmemmgr.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jquant1.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jquant2.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jutils.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\rdbmp.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\rdcolmap.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\rdgif.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\rdppm.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\rdrle.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\rdswitch.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\rdtarga.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\transupp.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\wrbmp.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\wrgif.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\wrppm.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\wrrle.c
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\wrtarga.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\jpeg\cderror.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\cdjpeg.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jchuff.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jconfig.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdct.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jdhuff.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jerror.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jinclude.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jmemsys.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jmorecfg.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jpegint.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jpeglib.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\jversion.h
# End Source File
# Begin Source File

SOURCE=..\src\jpeg\transupp.h
# End Source File
# End Group
# End Target
# End Project
