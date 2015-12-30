// HuiReversi.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HuiReversi.h"

#include "MainFrm.h"
#include "HuiReversiDoc.h"
#include "HuiReversiView.h"
#include "ReversiWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiApp

BEGIN_MESSAGE_MAP(CHuiReversiApp, CWinApp)
	//{{AFX_MSG_MAP(CHuiReversiApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiApp construction

CHuiReversiApp::CHuiReversiApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHuiReversiApp object

CHuiReversiApp	theApp;
CReversiWnd		theReversiWnd;	//黑白棋窗口对象

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiApp initialization

BOOL CHuiReversiApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("魔羯之辉黑白棋0.6版"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHuiReversiDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CHuiReversiView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CHuiReversiApp message handlers

// 得到文档类对象指针
CDocument* CHuiReversiApp::GetCurrentDoc()
{
	POSITION pos = theApp.GetFirstDocTemplatePosition();
	if(pos)
	{
		CDocTemplate * pDocTemplate = theApp.GetNextDocTemplate(pos);
		POSITION pos1 = pDocTemplate->GetFirstDocPosition();
		if(pos1)
			return pDocTemplate->GetNextDoc(pos1);
	}
	return NULL;
}

// 载入文件
void CHuiReversiApp::OnFileOpen() 
{
	if(theReversiWnd.m_wndBoard->GetLockState())
		return;

	char szOpenFilter[] = "黑白棋文件 (.rvs)|*.rvs|所有文件 (*.*)|*.*||";
	CFileDialog FileDlg(TRUE, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szOpenFilter);

	if (FileDlg.DoModal() == IDOK)
 		OpenDocumentFile(FileDlg.m_ofn.lpstrFile);
}

void CHuiReversiApp::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!theReversiWnd.m_wndBoard->GetLockState());
}

// 保存文件
void CHuiReversiApp::OnFileSave() 
{
	if(theReversiWnd.m_wndBoard->GetLockState())
		return;

	CHuiReversiDoc * pDoc = (CHuiReversiDoc *)GetCurrentDoc();
	if(pDoc)
		pDoc->DoFileSave();
}

void CHuiReversiApp::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!theReversiWnd.m_wndBoard->GetLockState());
}

// 另存为文件
void CHuiReversiApp::OnFileSaveAs() 
{
	if(theReversiWnd.m_wndBoard->GetLockState())
		return;

	CHuiReversiDoc * pDoc = (CHuiReversiDoc *)GetCurrentDoc();
	if(pDoc)
	{
		if (!pDoc->DoSave(NULL))
			TRACE0("Warning: File save-as failed.\n");
	}
}

void CHuiReversiApp::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!theReversiWnd.m_wndBoard->GetLockState());
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_strHide;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int nCount;		// 隐藏要素的计数器
	int count[4];	// 记录最近4秒钟点击鼠标左键的次数
	BOOL bShow;		// 是否已经显示隐藏要素

	//{{AFX_MSG(CAboutDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_strHide = _T("李辉  版权所有 (C) 2005");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_COPYRIGHT, m_strHide);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	nCount = 0;
	bShow = FALSE;
	for(int i=0; i<5; i++)
		count[i] = 0;
	SetTimer(1, 1000, 0);	//设置隐藏要素的计时器

	return 0;
}

void CAboutDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 1)
	{
		if(!bShow)
		{
			for(int i=1; i<4; i++)		
				count[i-1] = count[i];
			count[3] = nCount;
			nCount = 0;
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(!bShow)
	{
		CRect rc;
		POINT pt;
		// 必须在图标上点击鼠标才能触发隐藏要素
		CStatic *pIcon = (CStatic*)GetDlgItem(IDC_LOGO);
		pIcon->GetWindowRect(&rc);
		::GetCursorPos(&pt);

		if(rc.PtInRect(pt))
		{
			nCount++;
			int total = 0;
			for(int i=0; i<4; i++)		
				total += count[i];
			total += nCount;
			if(total > 25)	// 如果5秒钟内点击鼠标次数大于25次，则出发隐藏要素
			{
				bShow = TRUE;
				m_strHide = "李辉,你究竟想要什么? 我想,我知道答案了!";
				UpdateData(FALSE);
				KillTimer(1);
			}
		}
	}
	
	CDialog::OnLButtonUp(nFlags, point);
}

// App command to run the dialog
void CHuiReversiApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

