# Microsoft Developer Studio Project File - Name="ptypes" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ptypes - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ptypes.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ptypes.mak" CFG="ptypes - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ptypes - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ptypes - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ptypes - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../Release"
# PROP BASE Intermediate_Dir "../Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../tmp/ptypes/Release"
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

!ELSEIF  "$(CFG)" == "ptypes - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../Debug"
# PROP BASE Intermediate_Dir "../Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../tmp/ptypes/Debug"
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

# Name "ptypes - Win32 Release"
# Name "ptypes - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cpp;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\ptypes\pasync.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\patomic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pcomponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pcset.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pcsetdbg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pexcept.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pfatal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pfdxstm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pinfile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pinfilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pinmem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pinstm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pintee.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\piobase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pipbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pipmsg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pipmsgsv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pipstm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pipstmsv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pipsvbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pmd5.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pmem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pmsgq.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pmtxtable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pnpipe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pnpserver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pobjlist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\poutfile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\poutfilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\poutmem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\poutstm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\ppipe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pputf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\prwlock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\psemaphore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pstdio.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pstrcase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pstrconv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pstring.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pstrlist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pstrmanip.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pstrtoi.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pstrutils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pthread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\ptime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\ptimedsem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\ptrigger.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\punit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\punknown.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pvariant.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pvarray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pversion.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\ptypes\pasync.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pinet.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pport.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\pstreams.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\ptime.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ptypes\ptypes.h
# End Source File
# End Group
# End Target
# End Project
