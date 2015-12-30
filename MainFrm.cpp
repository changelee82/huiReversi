// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "HuiReversi.h"

#include "MainFrm.h"
#include "DlgGetIP.h"
#include "DlgRule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_QUERYENDSESSION()
	ON_COMMAND(ID_VIEW_TOP, OnViewTop)
	ON_COMMAND(ID_VIEW_LEFT, OnViewLeft)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOP, OnUpdateViewTop)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LEFT, OnUpdateViewLeft)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateViewZoomin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateViewZoomout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_GAME_UNDO, OnGameUndo)
	ON_COMMAND(ID_GAME_REDO, OnGameRedo)
	ON_UPDATE_COMMAND_UI(ID_GAME_UNDO, OnUpdateGameUndo)
	ON_UPDATE_COMMAND_UI(ID_GAME_REDO, OnUpdateGameRedo)
	ON_COMMAND(ID_GAME_COMPUTER_MOVE, OnGameComputerMove)
	ON_COMMAND(IDM_SET_STARTMODE1, OnSetStartmode1)
	ON_UPDATE_COMMAND_UI(IDM_SET_STARTMODE1, OnUpdateSetStartmode1)
	ON_COMMAND(IDM_SET_STARTMODE2, OnSetStartmode2)
	ON_UPDATE_COMMAND_UI(IDM_SET_STARTMODE2, OnUpdateSetStartmode2)
	ON_COMMAND(IDM_SET_STARTMODE3, OnSetStartmode3)
	ON_UPDATE_COMMAND_UI(IDM_SET_STARTMODE3, OnUpdateSetStartmode3)
	ON_COMMAND(IDM_SET_STARTMODE4, OnSetStartmode4)
	ON_UPDATE_COMMAND_UI(IDM_SET_STARTMODE4, OnUpdateSetStartmode4)
	ON_COMMAND(IDM_SET_LEVEL1, OnSetLevel1)
	ON_UPDATE_COMMAND_UI(IDM_SET_LEVEL1, OnUpdateSetLevel1)
	ON_COMMAND(IDM_SET_LEVEL2, OnSetLevel2)
	ON_UPDATE_COMMAND_UI(IDM_SET_LEVEL2, OnUpdateSetLevel2)
	ON_COMMAND(IDM_SET_LEVEL3, OnSetLevel3)
	ON_UPDATE_COMMAND_UI(IDM_SET_LEVEL3, OnUpdateSetLevel3)
	ON_COMMAND(IDM_SET_LEVEL4, OnSetLevel4)
	ON_UPDATE_COMMAND_UI(IDM_SET_LEVEL4, OnUpdateSetLevel4)
	ON_COMMAND(IDM_SET_LEVEL5, OnSetLevel5)
	ON_UPDATE_COMMAND_UI(IDM_SET_LEVEL5, OnUpdateSetLevel5)
	ON_COMMAND(IDM_SET_FLASH, OnSetFlash)
	ON_UPDATE_COMMAND_UI(IDM_SET_FLASH, OnUpdateSetFlash)
	ON_COMMAND(IDM_SET_FIRST_PLAYER, OnSetFirstPlayer)
	ON_UPDATE_COMMAND_UI(IDM_SET_FIRST_PLAYER, OnUpdateSetFirstPlayer)
	ON_COMMAND(IDM_SET_FIRST_COM, OnSetFirstCom)
	ON_UPDATE_COMMAND_UI(IDM_SET_FIRST_COM, OnUpdateSetFirstCom)
	ON_COMMAND(IDM_SET_VS_PLAYER, OnSetVsPlayer)
	ON_UPDATE_COMMAND_UI(IDM_SET_VS_PLAYER, OnUpdateSetVsPlayer)
	ON_COMMAND(IDM_SET_VS_COM, OnSetVsCom)
	ON_UPDATE_COMMAND_UI(IDM_SET_VS_COM, OnUpdateSetVsCom)
	ON_COMMAND(IDM_SET_VS_NET, OnSetVsNet)
	ON_UPDATE_COMMAND_UI(IDM_SET_VS_NET, OnUpdateSetVsNet)
	ON_COMMAND(IDM_GET_IP, OnGetIp)
	ON_COMMAND(IDM_HELP_RULE, OnHelpRule)
	ON_MESSAGE(WM_STATE_CHANGE, OnStateChange)
	ON_MESSAGE(WM_SIZE_CHANGE, OnSizeChange)
	ON_MESSAGE(WM_SEARCH_PLAN, OnSearchPlan)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_GAME_COMPUTER_MOVE, OnUpdateGameComputerMove)
	ON_COMMAND(ID_GAME_STOP_SEARCH, OnGameStopSearch)
	ON_COMMAND(IDM_SET_PROMPT, OnSetPrompt)
	ON_UPDATE_COMMAND_UI(IDM_SET_PROMPT, OnUpdateSetPrompt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	pClientView = NULL;
	memset(title, 31, 0);
	strcpy(title, "    ★魔羯之辉工作室★        ");
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneInfo(0, 0, SBPS_STRETCH, 140);
	m_wndStatusBar.SetPaneInfo(1, 0, 0, 75);
	m_wndStatusBar.SetPaneInfo(2, 0, 0, 130);
	m_wndStatusBar.SetPaneInfo(3, 0, 0, 142);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// 创建黑白棋窗口对象
	theReversiWnd.m_wndBoard->m_hWndReceive = GetSafeHwnd();	// 设置当棋盘内容改变时收到消息的窗口为主框架窗口
	theReversiWnd.m_hWndSizeChange = GetSafeHwnd();	// 设置当棋盘尺寸大小改变时收到消息的窗口为主框架窗口
	theReversiWnd.m_wndBoard->SetThinkPlanWnd(GetSafeHwnd());  // 接收搜索进度信息的窗口为主框架窗口

	theReversiWnd.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, NULL);

	SetTimer(1, 500, 0);	//设置定时器

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED |	WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
	cs.x = 30;
	cs.y = 20;
	cs.cx = 0;
	cs.cy = 0;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnClose() 
{
	if(IDYES==AfxMessageBox("真的要退出吗？",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2))
	{
		theReversiWnd.m_wndBoard->CloseThread();	// 关闭所有线程
		theReversiWnd.m_wndBoard->SetInfoToReg();	// 保存游戏参数到注册表

		CFrameWnd::OnClose();
	}
}

BOOL CMainFrame::OnQueryEndSession() 
{
	if (!CFrameWnd::OnQueryEndSession())
		return FALSE;

	if(IDNO==AfxMessageBox("真的要退出吗？",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2))
		return FALSE;

	theReversiWnd.m_wndBoard->SetInfoToReg();	// 保存游戏参数到注册表
	return TRUE;
}

void CMainFrame::RecalcLayout(BOOL bNotify) 
{
	CFrameWnd::RecalcLayout(bNotify);
	
	CView*	pView = GetActiveView();
	if(pClientView)
		pView = pClientView;
	CRect rect;
	if(pView)
	{
		// 设置棋盘窗口的位置
		pView->GetWindowRect(&rect);
		ScreenToClient(&rect);
		pView->ShowWindow(SW_HIDE);
		theReversiWnd.MoveWindow(rect);
		pClientView = pView;
	}
}

void CMainFrame::OnViewTop() 
{
	theReversiWnd.ShowTopWindow(!theReversiWnd.m_wndBoard->m_bShowTop);
}

void CMainFrame::OnViewLeft() 
{
	theReversiWnd.ShowLeftWindow(!theReversiWnd.m_wndBoard->m_bShowLeft);
}

void CMainFrame::OnUpdateViewTop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->m_bShowTop);
}

void CMainFrame::OnUpdateViewLeft(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->m_bShowLeft);
}

void CMainFrame::OnViewZoomin()
{
	theReversiWnd.Zoomin();
}

void CMainFrame::OnViewZoomout()
{
	theReversiWnd.Zoomout();
}

void CMainFrame::OnUpdateViewZoomin(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theReversiWnd.m_wndBoard->CanZoomin());
}

void CMainFrame::OnUpdateViewZoomout(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theReversiWnd.m_wndBoard->CanZoomout());
}

// 得到状态栏的高度
int CMainFrame::GetStatusBarHeight()
{
	CRect rect;
	m_wndStatusBar.GetWindowRect(&rect);

	return rect.Height();
}

// 得到工具栏的高度
int CMainFrame::GetToolBarHeight()
{
	CRect rect;
	m_wndToolBar.GetClientRect(&rect);

	// 由于用GetWindowRect得到的高度不正确，所以临时采取下面的方法
	return rect.Height() + GetSystemMetrics(SM_CYEDGE);
}

// 得到工具栏的宽度
int CMainFrame::GetToolBarWidth()
{
	CRect rect;
	m_wndToolBar.GetClientRect(&rect);

	return rect.Width() + GetSystemMetrics(SM_CYEDGE);
}

// 开始一局新游戏
void CMainFrame::OnFileNew() 
{
	theReversiWnd.m_wndBoard->StartNewGame();
	SetStatusBarText();
}

// 悔棋
void CMainFrame::OnGameUndo() 
{
	if(theReversiWnd.m_wndBoard->GetLockState())
		return;
	
	theReversiWnd.m_wndBoard->Undo();
	SetStatusBarText();
}

void CMainFrame::OnUpdateGameUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theReversiWnd.m_wndBoard->IsCanUndo() && 
				  !theReversiWnd.m_wndBoard->GetLockState());
}

// 撤销悔棋
void CMainFrame::OnGameRedo() 
{
	if(theReversiWnd.m_wndBoard->GetLockState())
		return;

	theReversiWnd.m_wndBoard->Redo();
	SetStatusBarText();
}

void CMainFrame::OnUpdateGameRedo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(theReversiWnd.m_wndBoard->IsCanRedo() && 
				  !theReversiWnd.m_wndBoard->GetLockState());
}

// 电脑走棋
void CMainFrame::OnGameComputerMove() 
{
	theReversiWnd.m_wndBoard->ComputerFindMove();
}

void CMainFrame::OnUpdateGameComputerMove(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!theReversiWnd.m_wndBoard->GetLockState());
}

// 停止走棋
void CMainFrame::OnGameStopSearch() 
{
	theReversiWnd.m_wndBoard->StopSearch();
}

// 设置走棋模式为玩家先走
void CMainFrame::OnSetFirstPlayer() 
{
	theReversiWnd.m_wndBoard->m_bPlayer1 = TRUE;
	theReversiWnd.m_wndBoard->m_bPlayer2 = FALSE;
	SetStatusBarText();
}

void CMainFrame::OnUpdateSetFirstPlayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!theReversiWnd.m_wndBoard->GetNetPro());
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->m_bPlayer1 && 
					!theReversiWnd.m_wndBoard->m_bPlayer2 && 
					!theReversiWnd.m_wndBoard->GetNetPro());
}

// 设置走棋模式为电脑先走
void CMainFrame::OnSetFirstCom() 
{
	theReversiWnd.m_wndBoard->m_bPlayer1 = FALSE;
	theReversiWnd.m_wndBoard->m_bPlayer2 = TRUE;
	SetStatusBarText();
}

void CMainFrame::OnUpdateSetFirstCom(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!theReversiWnd.m_wndBoard->GetNetPro());
	pCmdUI->SetCheck(!theReversiWnd.m_wndBoard->m_bPlayer1 && 
					theReversiWnd.m_wndBoard->m_bPlayer2 && 
					!theReversiWnd.m_wndBoard->GetNetPro());
}

// 设置走棋模式为双人对战
void CMainFrame::OnSetVsPlayer() 
{
	theReversiWnd.m_wndBoard->m_bPlayer1 = TRUE;
	theReversiWnd.m_wndBoard->m_bPlayer2 = TRUE;
	SetStatusBarText();
}

void CMainFrame::OnUpdateSetVsPlayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!theReversiWnd.m_wndBoard->GetNetPro());
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->m_bPlayer1 && 
					theReversiWnd.m_wndBoard->m_bPlayer2 && 
					!theReversiWnd.m_wndBoard->GetNetPro());
}

// 设置走棋模式为电脑对战
void CMainFrame::OnSetVsCom() 
{
	theReversiWnd.m_wndBoard->m_bPlayer1 = FALSE;
	theReversiWnd.m_wndBoard->m_bPlayer2 = FALSE;
	SetStatusBarText();
}

void CMainFrame::OnUpdateSetVsCom(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!theReversiWnd.m_wndBoard->GetNetPro());
	pCmdUI->SetCheck(!theReversiWnd.m_wndBoard->m_bPlayer1 && 
					!theReversiWnd.m_wndBoard->m_bPlayer2 && 
					!theReversiWnd.m_wndBoard->GetNetPro());
}

// 设置走棋模式为网络对战
void CMainFrame::OnSetVsNet() 
{
	SetStatusBarText();
}

void CMainFrame::OnUpdateSetVsNet(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetNetPro());
}

// 开局模式1
void CMainFrame::OnSetStartmode1() 
{
	theReversiWnd.m_wndBoard->SetStartMode(1);
}

void CMainFrame::OnUpdateSetStartmode1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetStartMode() == 1);
}

// 开局模式2
void CMainFrame::OnSetStartmode2() 
{
	theReversiWnd.m_wndBoard->SetStartMode(2);
}

void CMainFrame::OnUpdateSetStartmode2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetStartMode() == 2);
}

// 开局模式3
void CMainFrame::OnSetStartmode3() 
{
	theReversiWnd.m_wndBoard->SetStartMode(3);
}

void CMainFrame::OnUpdateSetStartmode3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetStartMode() == 3);
}

// 开局模式4
void CMainFrame::OnSetStartmode4() 
{
	theReversiWnd.m_wndBoard->SetStartMode(4);
}

void CMainFrame::OnUpdateSetStartmode4(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetStartMode() == 4);
}

// 设置游戏难度为简单
void CMainFrame::OnSetLevel1() 
{
	if(theReversiWnd.m_wndBoard->SetLevel(5))
		SetStatusBarText();
}

void CMainFrame::OnUpdateSetLevel1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetLevel() == 5);
	pCmdUI->Enable(theReversiWnd.m_wndBoard->GetNetPro() == 0 && 
				  !theReversiWnd.m_wndBoard->GetLockState());
}

// 设置游戏难度为初级
void CMainFrame::OnSetLevel2() 
{
	if(theReversiWnd.m_wndBoard->SetLevel(6))
		SetStatusBarText();
}

void CMainFrame::OnUpdateSetLevel2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetLevel() == 6);
	pCmdUI->Enable(theReversiWnd.m_wndBoard->GetNetPro() == 0 && 
				  !theReversiWnd.m_wndBoard->GetLockState());
}

// 设置游戏难度为中级
void CMainFrame::OnSetLevel3() 
{
	if(theReversiWnd.m_wndBoard->SetLevel(7))
		SetStatusBarText();
}

void CMainFrame::OnUpdateSetLevel3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetLevel() == 7);
	pCmdUI->Enable(theReversiWnd.m_wndBoard->GetNetPro() == 0 && 
				  !theReversiWnd.m_wndBoard->GetLockState());
}

// 设置游戏难度为高级
void CMainFrame::OnSetLevel4() 
{
	if(theReversiWnd.m_wndBoard->SetLevel(8))
		SetStatusBarText();
}

void CMainFrame::OnUpdateSetLevel4(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetLevel() == 8);
	pCmdUI->Enable(theReversiWnd.m_wndBoard->GetNetPro() == 0 && 
				  !theReversiWnd.m_wndBoard->GetLockState());
}

// 设置游戏难度为终极
void CMainFrame::OnSetLevel5() 
{
	if(theReversiWnd.m_wndBoard->SetLevel(9))
		SetStatusBarText();
}

void CMainFrame::OnUpdateSetLevel5(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetLevel() == 9);
	pCmdUI->Enable(theReversiWnd.m_wndBoard->GetNetPro() == 0 && 
				  !theReversiWnd.m_wndBoard->GetLockState());
}

// 设置动画效果
void CMainFrame::OnSetFlash() 
{
	theReversiWnd.m_wndBoard->m_bFlash = !theReversiWnd.m_wndBoard->m_bFlash;
}

void CMainFrame::OnUpdateSetFlash(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->m_bFlash);
}

// 设定电脑提示信息
void CMainFrame::OnSetPrompt() 
{
	theReversiWnd.m_wndBoard->ShowPrompt(!theReversiWnd.m_wndBoard->GetPromptInfo());
}

void CMainFrame::OnUpdateSetPrompt(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(theReversiWnd.m_wndBoard->GetPromptInfo());
}

// 得到本机IP
void CMainFrame::OnGetIp() 
{
	CDlgGetIP dlg;
	dlg.DoModal();
}

// 查看游戏规则
void CMainFrame::OnHelpRule() 
{
	CDlgRule dlg;
	dlg.DoModal();
}

// 搜索引擎发来的搜索进度消息
void CMainFrame::OnSearchPlan(WPARAM wParam, LPARAM lParam)
{
	if(wParam==SEARCH_RANGE)	// 设置范围
	{
		theReversiWnd.m_wndBoardRight->m_TinkPro.SetRange(0, (int)lParam);
		theReversiWnd.m_wndBoardRight->m_TinkPro.SetPos((int)lParam);
	}
	else if(wParam==SEARCH_POS)	// 设置进度值
	{
		theReversiWnd.m_wndBoardRight->m_TinkPro.SetPos((int)lParam);
	}
	else if(wParam==SEARCH_POS_MAX)	// 设置进度值为最大值
	{
		int nLower, nUpper;
		theReversiWnd.m_wndBoardRight->m_TinkPro.GetRange(nLower, nUpper);
		theReversiWnd.m_wndBoardRight->m_TinkPro.SetPos(nUpper);
	}
}

// 当棋盘大小发生改变时收到消息后的处理函数，设置主框架窗口尺寸
void CMainFrame::OnSizeChange(WPARAM wParam, LPARAM lParam)
{
//	int nWidth = (int)wParam;	// 棋盘窗口的高度和宽度，暂时不用
//	int nHeight = (int)lParam;

	int nToolBarWidth, nToolBarHeight, nStatusBarHeight;
	DWORD style;

	nToolBarWidth = 0;
	nToolBarHeight = 0;
	// 如果工具栏可见，并且为停靠状态，则计算工具栏尺寸
	if(!m_wndToolBar.IsFloating() && m_wndToolBar.IsWindowVisible())
	{
		style = m_wndToolBar.GetBarStyle();
		if((style & CBRS_ALIGN_TOP) || (style & CBRS_ALIGN_BOTTOM))	// 上面，下面
			nToolBarHeight = GetToolBarHeight();
		else if((style & CBRS_ALIGN_LEFT) || (style & CBRS_ALIGN_RIGHT)) // 左边，右边
			nToolBarWidth = GetToolBarWidth();
	}
	
	nStatusBarHeight = 0;
	// 如果状态可见，则计算状态栏高度
	if(m_wndStatusBar.IsWindowVisible())
		nStatusBarHeight = GetStatusBarHeight();

	RECT rect;
	GetWindowRect(&rect);
	MoveWindow(rect.left, rect.top,
		nToolBarWidth + WIDTH_RIGHT + theReversiWnd.m_wndBoard->GetCurWidth(),
		nToolBarHeight + nStatusBarHeight + HEIGHT_CAPTION + theReversiWnd.m_wndBoard->GetCurHeight());
}

// 当棋盘状态发生改变时收到消息后的处理函数
void CMainFrame::OnStateChange(WPARAM wParam, LPARAM lParam)
{
	// 重新设置状态栏上的文字
	SetStatusBarText();
}

// 设置状态栏上的文字
void CMainFrame::SetStatusBarText()
{
	CString str, strLevel;
	CBoardView * pView = theReversiWnd.m_wndBoard;
	str.Format("  共走了%d手", pView->GetStepCount());
	m_wndStatusBar.SetPaneText(1, str);

	switch (pView->GetLevel())
	{
	case 5:
		strLevel = "简单难度";
		break;
	case 6:
		strLevel = "初级难度";
		break;
	case 7:
		strLevel = "中级难度";
		break;
	case 8:
		strLevel = "高级难度";
		break;
	case 9:
		strLevel = "终级难度";
		break;
	default:
		AfxMessageBox("游戏难度设置出现错误!");
		break;
	}

	if(pView->GetNetPro() == 1)
		str = "  网络对战  您执黑棋";
	else if(pView->GetNetPro() == 2)
		str = "  网络对战  您执白棋";
	else if(pView->m_bPlayer1 && pView->m_bPlayer2)
		str = "  双人对战";
	else if(pView->m_bPlayer1 && !pView->m_bPlayer2)
		str = "  您执黑棋  " + strLevel;
	else if(!pView->m_bPlayer1 && pView->m_bPlayer2)
		str = "  您执白棋  " + strLevel;
	else if(!pView->m_bPlayer1 && !pView->m_bPlayer2)
		str = "  电脑对战  " + strLevel;
	m_wndStatusBar.SetPaneText(2, str);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==1)	// 设置状态栏上的移动图标
	{
		char tmp[2];
		int stepLen = strlen(title)-2;
		memcpy(tmp, title, 2);
		memcpy(title, title+2, stepLen);
		memcpy(title+stepLen, tmp, 2);
		m_wndStatusBar.SetPaneText(3, title);
	}

	CFrameWnd::OnTimer(nIDEvent);
}
