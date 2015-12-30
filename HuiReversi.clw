; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "HuiReversi.h"
LastPage=0

ClassCount=10
Class1=CHuiReversiApp
Class2=CHuiReversiDoc
Class3=CHuiReversiView
Class4=CMainFrame

ResourceCount=6
Resource1=IDR_MAINFRAME
Resource2=IDD_DLG_GETIP
Class5=CAboutDlg
Class6=CBoardView
Class7=CBoardRightView
Class8=CReversiWnd
Resource3=IDD_DLG_RULE
Class9=CDlgGetIP
Resource4=IDD_ABOUTBOX
Class10=CDlgRule
Resource5=IDD_HUIREVERSI_FORM
Resource6=IDD_DIALOG1

[CLS:CHuiReversiApp]
Type=0
HeaderFile=HuiReversi.h
ImplementationFile=HuiReversi.cpp
Filter=N
LastObject=ID_FILE_SAVE_AS
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CHuiReversiDoc]
Type=0
HeaderFile=HuiReversiDoc.h
ImplementationFile=HuiReversiDoc.cpp
Filter=N
LastObject=CHuiReversiDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CHuiReversiView]
Type=0
HeaderFile=HuiReversiView.h
ImplementationFile=HuiReversiView.cpp
Filter=D
BaseClass=CView
VirtualFilter=VWC
LastObject=CHuiReversiView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=IDM_SET_PROMPT




[CLS:CAboutDlg]
Type=0
HeaderFile=HuiReversi.cpp
ImplementationFile=HuiReversi.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_LOGO,static,1350569987
Control2=IDC_STATIC,static,1342308480
Control3=IDC_COPYRIGHT,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308364

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_GAME_UNDO
Command6=ID_GAME_REDO
Command7=ID_GAME_COMPUTER_MOVE
Command8=ID_GAME_STOP_SEARCH
Command9=ID_APP_EXIT
Command10=IDM_SET_FIRST_PLAYER
Command11=IDM_SET_FIRST_COM
Command12=IDM_SET_VS_PLAYER
Command13=IDM_SET_VS_COM
Command14=IDM_SET_VS_NET
Command15=IDM_GET_IP
Command16=IDM_SET_DISCONN
Command17=IDM_SET_STARTMODE1
Command18=IDM_SET_STARTMODE2
Command19=IDM_SET_STARTMODE3
Command20=IDM_SET_STARTMODE4
Command21=IDM_SET_LEVEL1
Command22=IDM_SET_LEVEL2
Command23=IDM_SET_LEVEL3
Command24=IDM_SET_LEVEL4
Command25=IDM_SET_LEVEL5
Command26=IDM_SET_FLASH
Command27=IDM_SET_PROMPT
Command28=ID_VIEW_TOOLBAR
Command29=ID_VIEW_STATUS_BAR
Command30=ID_VIEW_TOP
Command31=ID_VIEW_LEFT
Command32=ID_VIEW_ZOOMIN
Command33=ID_VIEW_ZOOMOUT
Command34=IDM_HELP_RULE
Command35=ID_APP_ABOUT
CommandCount=35

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_GAME_UNDO
Command5=ID_GAME_REDO
Command6=ID_GAME_COMPUTER_MOVE
Command7=ID_GAME_STOP_SEARCH
Command8=ID_APP_ABOUT
Command9=ID_APP_EXIT
CommandCount=9

[CLS:CBoardView]
Type=0
HeaderFile=BoardView.h
ImplementationFile=BoardView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CBoardView

[CLS:CReversiWnd]
Type=0
HeaderFile=ReversiWnd.h
ImplementationFile=ReversiWnd.cpp
BaseClass=CWnd
Filter=W
LastObject=CReversiWnd
VirtualFilter=WC

[CLS:CBoardRightView]
Type=0
HeaderFile=BoardRightView.h
ImplementationFile=BoardRightView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=CBoardRightView

[DLG:IDD_HUIREVERSI_FORM]
Type=1
Class=CHuiReversiView
ControlCount=4
Control1=IDC_PROTHINK,msctls_progress32,1350565888
Control2=IDC_CHAT,edit,1352730692
Control3=IDC_MESSAGE,combobox,1478558018
Control4=IDC_SEND,button,1476460545

[DLG:IDD_DLG_GETIP]
Type=1
Class=CDlgGetIP
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_IP,edit,1350633601

[CLS:CDlgGetIP]
Type=0
HeaderFile=DlgGetIP.h
ImplementationFile=DlgGetIP.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgGetIP

[DLG:IDD_DLG_RULE]
Type=1
Class=CDlgRule
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_RULE,edit,1352730628

[CLS:CDlgRule]
Type=0
HeaderFile=DlgRule.h
ImplementationFile=DlgRule.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgRule

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

