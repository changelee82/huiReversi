# Microsoft Developer Studio Project File - Name="HuiReversi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HuiReversi - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HuiReversi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HuiReversi.mak" CFG="HuiReversi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HuiReversi - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HuiReversi - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HuiReversi - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "HuiReversi - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Output"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "HuiReversi - Win32 Release"
# Name "HuiReversi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BoardRightView.cpp
# End Source File
# Begin Source File

SOURCE=.\BoardView.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetIP.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRule.cpp
# End Source File
# Begin Source File

SOURCE=.\HuiReversi.cpp
# End Source File
# Begin Source File

SOURCE=.\HuiReversi.rc
# End Source File
# Begin Source File

SOURCE=.\HuiReversiDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\huiReversi\HuiReversiGetValue.cpp
# End Source File
# Begin Source File

SOURCE=.\huiReversi\HuiReversiMain.cpp
# End Source File
# Begin Source File

SOURCE=.\huiReversi\HuiReversiMove.cpp
# End Source File
# Begin Source File

SOURCE=.\huiReversi\HuiReversiSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\HuiReversiView.cpp
# End Source File
# Begin Source File

SOURCE=.\huiReversi\HuiSearchAlphaBeta.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ReversiWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BoardRightView.h
# End Source File
# Begin Source File

SOURCE=.\BoardView.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetIP.h
# End Source File
# Begin Source File

SOURCE=.\DlgRule.h
# End Source File
# Begin Source File

SOURCE=.\HuiReversi.h
# End Source File
# Begin Source File

SOURCE=.\HuiReversiDoc.h
# End Source File
# Begin Source File

SOURCE=.\huiReversi\HuiReversiGetValue.h
# End Source File
# Begin Source File

SOURCE=.\huiReversi\HuiReversiMain.h
# End Source File
# Begin Source File

SOURCE=.\huiReversi\HuiReversiMove.h
# End Source File
# Begin Source File

SOURCE=.\huiReversi\HuiReversiSearch.h
# End Source File
# Begin Source File

SOURCE=.\HuiReversiView.h
# End Source File
# Begin Source File

SOURCE=.\huiReversi\HuiSearchAlphaBeta.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ReversiWnd.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\black_empty.bmp
# End Source File
# Begin Source File

SOURCE=.\res\board.bmp
# End Source File
# Begin Source File

SOURCE=.\res\board_left.bmp
# End Source File
# Begin Source File

SOURCE=.\res\board_top.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HuiReversi.ico
# End Source File
# Begin Source File

SOURCE=.\res\HuiReversi.rc2
# End Source File
# Begin Source File

SOURCE=.\res\HuiReversiDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\point.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_01.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_02.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_03.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_04.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_05.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_06.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_07.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_08.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_09.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_14.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_15.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_17.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_18.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_19.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reversi_20.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\white.bmp
# End Source File
# Begin Source File

SOURCE=.\res\white_empty.bmp
# End Source File
# Begin Source File

SOURCE=.\res\X_blue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\X_red.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\HuiReversi.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
