// BoardView.cpp : implementation file
//

#include "stdafx.h"
#include "HuiReversi.h"
#include "BoardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoardView
const char CBoardView::s_profileHeading[] = "参数";
const char CBoardView::s_startMode[]	= "开局模式";
const char CBoardView::s_level[] = "游戏难度";
const char CBoardView::s_flash[] = "动画效果";
const char CBoardView::s_showTop[] = "上边标志栏";
const char CBoardView::s_showLeft[] = "左边标志栏";
const char CBoardView::s_bPlayer1[] = "玩家执黑棋";
const char CBoardView::s_bPlayer2[] = "玩家执白棋";

// 放大的倍数列表
float CBoardView::Zoom[3] = {1.0, (float)1.2, (float)1.6};
int CBoardView::ZoomCount = 3;

IMPLEMENT_DYNCREATE(CBoardView, CView)

CBoardView::CBoardView()
{
	m_pReversi = new HuiReversiMain();			   // 黑白棋指针
	m_pReversiMove     = new HuiReversiMove();	   // 走法产生器指针
	m_pReversiSearch   = new HuiSearchAlphaBeta(); // 搜索引擎指针
	m_pReversiGetValue = new HuiReversiGetValue(); // 估值核心指针
	// 设置放大倍数
	m_zoomIndex = 0;
	
	m_bShowTop = TRUE;		// 初始时上边标题栏窗口都可见
	m_bShowLeft = TRUE;		// 初始时左边标题栏窗口都可见
	
	m_bShowBlueX = FALSE;	// 初始时不显示蓝色的“X”
	m_bShowRedX  = TRUE;	// 初始时显示红色的“X”
	m_bShowEmpty = FALSE;	// 初始时不显示将要改变颜色的棋子
	m_nNetPro    = 0;		// 初始时不是网络对战
	m_bPlayer1   = TRUE;	// 初始时由玩家执黑棋
	m_bPlayer2   = FALSE;	// 初始时由电脑执白棋

	m_pBoardDC = NULL;
	m_hWndReceive = NULL;
	m_bThinkExit = FALSE;
	m_bPromptExit = FALSE;
	m_hWndPromptPlan = NULL;
	m_hWndThinkPlan = NULL;
	m_bPromptOver = FALSE;	// 初始化为电脑没有搜索到需要提示的最优走法
}

CBoardView::~CBoardView()
{
	if(m_pBoardDC != NULL)
	{
		delete m_pBoardDC;		// 棋盘
		delete m_pInitBoardDC;	// 初始时的棋盘
		delete m_pBlackDC;		// 黑棋图片
		delete m_pWhiteDC;		// 白棋图片
		delete m_pBlackEmptyDC;	// 虚的黑棋图片
		delete m_pWhiteEmptyDC;	// 虚的白棋图片
		delete m_pXBlueDC;		// 蓝色的“X”图片
		delete m_pXRedDC;		// 红色的“X”图片
		delete m_pPointDC;		// 棋盘上四个焦点的图片
		delete []m_pReversiDC;	// 存储动画的图像(共20个图标)
	}

	delete m_pReversi;
	delete m_pReversiMove;
	delete m_pReversiSearch;
	delete m_pReversiGetValue;

	CloseHandle(m_hLockEvent);
	CloseHandle(m_hStartThinkEvent);
	CloseHandle(m_hStartPromptEvent);
	CloseHandle(m_hThinkEvent);
	CloseHandle(m_hPromptEvent);
}

BEGIN_MESSAGE_MAP(CBoardView, CView)
	//{{AFX_MSG_MAP(CBoardView)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_MESSAGE(WM_FIND_BEST_MOVE, OnFindBestMove)
	ON_MESSAGE(WM_BEST_MOVE_CHANGE, OnBestMoveChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoardView drawing

void CBoardView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CBoardView diagnostics

#ifdef _DEBUG
void CBoardView::AssertValid() const
{
	CView::AssertValid();
}

void CBoardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBoardView message handlers

int CBoardView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 从注册表中读取游戏参数
	GetInfoFromReg();

	m_pReversi->ReStart(m_nStartMode);
	m_pReversiSearch->SetMove(m_pReversiMove);	// 设置走法产生器
	m_pReversiSearch->SetGetValue(m_pReversiGetValue);	//设置估值核心
	SetLevel(m_nLevel);	// 设置难度
	SendChangeMsg();

	BITMAP    bitmap ;
	CBitmap   bmptmp;
	CClientDC pDC(this);
	
	m_pBoardDC = new CDC;	// 棋盘
	bmptmp.LoadBitmap(IDB_BOARD);
	m_pBoardDC->CreateCompatibleDC(&pDC);
	m_pBoardDC->SelectObject(&bmptmp);

	::GetObject ((HBITMAP)bmptmp, sizeof (BITMAP), &bitmap) ;
	// 设置背景图的尺寸
	m_width  = bitmap.bmWidth;
	m_height = bitmap.bmHeight;

	m_pInitBoardDC = new CDC;	// 初始时的棋盘
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_BOARD);
	m_pInitBoardDC->CreateCompatibleDC(&pDC);
	m_pInitBoardDC->SelectObject(&bmptmp);
	m_pBlackDC = new CDC;		// 黑棋
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_BLACK);
	m_pBlackDC->CreateCompatibleDC(&pDC);
	m_pBlackDC->SelectObject(&bmptmp);
	m_pWhiteDC = new CDC;		// 白棋
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_WHITE);
	m_pWhiteDC->CreateCompatibleDC(&pDC);
	m_pWhiteDC->SelectObject(&bmptmp);
	m_pBlackEmptyDC = new CDC;	// 虚的黑棋图片
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_BLACK_EMPTY);
	m_pBlackEmptyDC->CreateCompatibleDC(&pDC);
	m_pBlackEmptyDC->SelectObject(&bmptmp);
	m_pWhiteEmptyDC = new CDC;	// 虚的白棋图片
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_WHITE_EMPTY);
	m_pWhiteEmptyDC->CreateCompatibleDC(&pDC);
	m_pWhiteEmptyDC->SelectObject(&bmptmp);
	m_pXBlueDC = new CDC;		// 蓝色的“X”图片
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_X_BLUE);
	m_pXBlueDC->CreateCompatibleDC(&pDC);
	m_pXBlueDC->SelectObject(&bmptmp);
	m_pXRedDC = new CDC;		// 红色的“X”图片
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_X_RED);
	m_pXRedDC->CreateCompatibleDC(&pDC);
	m_pXRedDC->SelectObject(&bmptmp);
	m_pPointDC = new CDC;		// 棋盘上四个焦点的图片
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_BOARD_POINT);
	m_pPointDC->CreateCompatibleDC(&pDC);
	m_pPointDC->SelectObject(&bmptmp);
	
	m_pReversiDC = new CDC[20];		// 棋子翻转的动画
	for(int i=0; i<20; i++)
	{
		bmptmp.DeleteObject();
		bmptmp.LoadBitmap(IDB_REVERSI_01+i);
		m_pReversiDC[i].CreateCompatibleDC(&pDC);
		m_pReversiDC[i].SelectObject(&bmptmp);
	}

	// 设定提示工具栏参数
	LOGFONT lf;           //字体形状
	CFont fnt;

	lf.lfItalic = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfHeight = 0;
	lf.lfWidth  = 0;
	lf.lfEscapement  = 0;
	lf.lfOrientation = 0;
	lf.lfUnderline   = 0;
	lf.lfStrikeOut   = 0;
	lf.lfCharSet = ANSI_CHARSET;
	lf.lfOutPrecision  = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
	
	strcpy(lf.lfFaceName,"宋体");
    lf.lfItalic  = 0;
	lf.lfHeight  = 12;
	lf.lfWeight  = FW_LIGHT;
	lf.lfCharSet = GB2312_CHARSET;
	
	fnt.CreateFontIndirect(&lf);

	if(!m_ToolTip.Create(this))
	{
		TRACE0("Unable to create Tootips\n");
	}
	else
	{
		m_ToolTip.SetFont(&fnt);
		m_ToolTip.SetTipBkColor(RGB(255, 255, 255));
		m_ToolTip.SetTipTextColor(RGB(0, 0, 0));
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, USER_TOO_TIP_WIDTH);
		m_ToolTip.Activate(FALSE);
	}

	m_pReversiSearch->SetBestMoveWnd(GetSafeHwnd());

	m_hLockEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hStartThinkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hStartPromptEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hThinkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hPromptEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	StartupThread();

	SetTimer(1, 300, 0);	//设置让电脑走棋的定时器
	return 0;
}

// 启动所有线程
void CBoardView::StartupThread()
{
	DWORD threadID;
	m_pReversiSearch->m_bExit = FALSE;
	// 启动电脑搜索最优走法的线程
	m_bThinkExit = FALSE;
	m_hThinkThread = CreateThread(NULL, 0, ThinkThread, this, 0, &threadID);
	// 启动电脑提示最优走法的线程
	m_bPromptExit = FALSE;
	m_hPromptThread = CreateThread(NULL, 0, PromptThread, this, 0, &threadID);
}

// 关闭所有线程
void CBoardView::CloseThread()
{
	DWORD result;
	m_pReversiSearch->m_bExit = TRUE;	// 退出搜索
	// 关闭电脑搜索最优走法的线程
	m_bThinkExit = TRUE;
	result = WaitForSingleObject(m_hThinkThread, INFINITE);
	CloseHandle(m_hThinkThread);
	// 关闭电脑提示最优走法的线程
	m_bPromptExit = TRUE;
	result = WaitForSingleObject(m_hPromptThread, INFINITE);
	CloseHandle(m_hPromptThread);
}

// 放大棋盘
void CBoardView::Zoomin()
{
	if(m_zoomIndex+1 < ZoomCount)
	{
		m_zoomIndex = m_zoomIndex+1;
	}
}

// 缩小棋盘
void CBoardView::Zoomout()
{
	if(m_zoomIndex-1 >= 0)
	{
		m_zoomIndex = m_zoomIndex-1;
	}
}

// 返回是否可以放大棋盘
BOOL CBoardView::CanZoomin()
{
	return m_zoomIndex+1 < ZoomCount;
}

// 返回是否可以缩小棋盘
BOOL CBoardView::CanZoomout()
{
	return m_zoomIndex > 0;
}

//得到棋盘窗口当前的宽度
int CBoardView::GetCurWidth()
{
	// 得到放大尺寸
	float zoom = GetZoom();
	// 得到是否隐藏左标题
	int x = m_bShowLeft ? WIDTH_LEFT : 0;

	return int((WIDTH_BOARD+x)*zoom)+2;
}

// 得到棋盘窗口当前的高度
int CBoardView::GetCurHeight()
{
	// 得到放大尺寸
	float zoom = GetZoom();
	// 得到是否隐藏上标题
	int y = m_bShowTop ? HEIGHT_TOP : 0;
	
	return int((WIDTH_BOARD+y)*zoom)+2;
}

// 设定开局模式(1-4)
BOOL CBoardView::SetStartMode(int nMode)
{
	// 参数检查
	if(nMode<1 || nMode>4)
		return FALSE;
	
	m_nStartMode = nMode;
	return TRUE;
}

// 设置游戏难度(1-10)
BOOL CBoardView::SetLevel(int nLevel)
{
	// 参数检查
	if(nLevel<1 || nLevel>10)
		return FALSE;

	// 锁定状态不能设置难度
	if(GetLockState())
		return FALSE;

	m_nLevel = nLevel;
	m_pReversiSearch->SetLayer(nLevel);
	return TRUE;
}

// 将鼠标坐标转换到棋盘坐标(范围1-8)，如果坐标超出范围，则返回(0, 0)
void CBoardView::PointToBoard(CPoint & point)
{
	int x, y;
	
	// 得到放大前的尺寸
	float zoom = GetZoom();
	point.x = int(point.x/zoom);
	point.y = int(point.y/zoom);

	if(point.y-(m_bShowTop  ? HEIGHT_TOP : 0) < 0 ||
	   point.x-(m_bShowLeft ? WIDTH_LEFT : 0) < 0)
	{
		point.x = 0;
		point.y = 0;
		return;
	}

	x = (point.y-(m_bShowTop  ? HEIGHT_TOP : 0))/WIDTH_GRID+1;
	y = (point.x-(m_bShowLeft ? WIDTH_LEFT : 0))/WIDTH_GRID+1;
	point.x = x;
	point.y = y;
	if(!m_pReversi->IsRightRange(point.x, point.y))
	{
		point.x = 0;
		point.y = 0;
	}
}

// 将黑白棋对象映射到内存DC
void CBoardView::BoardToDc(HuiReversiMain * pReversi)
{
	if(pReversi==NULL)
		pReversi = m_pReversi;

	// 首先画黑棋，白棋和可以落子的标志(蓝色的“X”)
	int i, j;
	m_pBoardDC->BitBlt(0, 0, WIDTH_LEFT+WIDTH_BOARD, HEIGHT_TOP+WIDTH_BOARD, m_pInitBoardDC, 0, 0, SRCCOPY);
	for(i=1; i<=8; i++)
		for(j=1; j<=8; j++)
		{
			if(pReversi->GetChessman(i, j)==BLACK)
				m_pBoardDC->BitBlt((j-1)*WIDTH_GRID+WIDTH_LEFT, (i-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, m_pBlackDC, 0, 0, SRCCOPY);
			else if(pReversi->GetChessman(i, j)==WHITE)
				m_pBoardDC->BitBlt((j-1)*WIDTH_GRID+WIDTH_LEFT, (i-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, m_pWhiteDC, 0, 0, SRCCOPY);
			else if(pReversi->IsRight(i,j) && m_bShowBlueX)
			{	// 画蓝色的“X”和红色的“X”(最优走法)
				if(m_bShowRedX && m_pReversiSearch->GetBestStep().x == i && m_pReversiSearch->GetBestStep().y == j)
					m_pBoardDC->BitBlt((j-1)*WIDTH_GRID+WIDTH_LEFT, (i-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, m_pXRedDC, 0, 0, SRCCOPY);
				else
					m_pBoardDC->BitBlt((j-1)*WIDTH_GRID+WIDTH_LEFT, (i-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, m_pXBlueDC, 0, 0, SRCCOPY);
			}
				
		}

	// 画将要改变颜色的棋子(用虚线画的棋子)
	int count;
	CPoint * pArray;
	CDC * playerDC;
	if(m_bShowEmpty && (count=pReversi->IsRight(m_curPoint.x, m_curPoint.y)))
	{
		pArray = new CPoint[count];
		pReversi->GetChangePoint(m_curPoint.x, m_curPoint.y, pArray);
		if(pReversi->GetCurPlayer()==BLACK)
			playerDC = m_pBlackEmptyDC;
		else
			playerDC = m_pWhiteEmptyDC;
		m_pBoardDC->BitBlt((m_curPoint.y-1)*WIDTH_GRID+WIDTH_LEFT, (m_curPoint.x-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, playerDC, 0, 0, SRCCOPY);
		for(i=0; i<count; i++)
			m_pBoardDC->BitBlt((pArray[i].y-1)*WIDTH_GRID+WIDTH_LEFT, (pArray[i].x-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, playerDC, 0, 0, SRCCOPY);	
		delete []pArray;
	}

	// 在最后落的子上画一个黄色正方形
	CBrush * brush;
	CPoint point;
	CPen pen;
	CPen * pOldPen;
	pen.CreatePen(PS_SOLID, 2, RGB(255,255,0));	//画黄色正方形的画笔
	if(pReversi->GetLastStep(&point))
	{
		brush = (CBrush *)m_pBoardDC->SelectStockObject(NULL_BRUSH);
		pOldPen = (CPen *)m_pBoardDC->SelectObject(&pen);
		m_pBoardDC->Rectangle(CRect((point.y-1)*WIDTH_GRID+WIDTH_LEFT+2, (point.x-1)*WIDTH_GRID+HEIGHT_TOP+2, (point.y-1)*WIDTH_GRID+WIDTH_LEFT+WIDTH_GRID-1, (point.x-1)*WIDTH_GRID+HEIGHT_TOP+WIDTH_GRID-1));
		m_pBoardDC->SelectObject(brush);
		m_pBoardDC->SelectObject(pOldPen);
	}

	// 绘制棋盘上四个焦点
	m_pBoardDC->BitBlt(2*WIDTH_GRID+WIDTH_LEFT-WIDTH_POINT/2-1, 2*WIDTH_GRID+HEIGHT_TOP-WIDTH_POINT/2-1, WIDTH_POINT, WIDTH_POINT, m_pPointDC, 0, 0, SRCCOPY);
	m_pBoardDC->BitBlt(2*WIDTH_GRID+WIDTH_LEFT-WIDTH_POINT/2-1, 6*WIDTH_GRID+HEIGHT_TOP-WIDTH_POINT/2-1, WIDTH_POINT, WIDTH_POINT, m_pPointDC, 0, 0, SRCCOPY);
	m_pBoardDC->BitBlt(6*WIDTH_GRID+WIDTH_LEFT-WIDTH_POINT/2-1, 2*WIDTH_GRID+HEIGHT_TOP-WIDTH_POINT/2-1, WIDTH_POINT, WIDTH_POINT, m_pPointDC, 0, 0, SRCCOPY);
	m_pBoardDC->BitBlt(6*WIDTH_GRID+WIDTH_LEFT-WIDTH_POINT/2-1, 6*WIDTH_GRID+HEIGHT_TOP-WIDTH_POINT/2-1, WIDTH_POINT, WIDTH_POINT, m_pPointDC, 0, 0, SRCCOPY);
}

void CBoardView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// 得到放大尺寸
	float zoom = Zoom[m_zoomIndex];
	
	// 得到是否隐藏上标题和左标题
	int x, y;
	x = m_bShowLeft ? 0 : WIDTH_LEFT;
	y = m_bShowTop  ? 0 : HEIGHT_TOP;
	
	//首先画黑色的边框
	CBrush * brush;
	CPen pen;
	CPen * pOldPen;
	pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	brush=(CBrush *)dc.SelectStockObject(NULL_BRUSH);
	pOldPen=(CPen *)dc.SelectObject(&pen);
	dc.Rectangle(0, 0, int((m_width-x)*zoom)+2, int((m_height-y)*zoom)+2);
	dc.SelectObject(brush);
	dc.SelectObject(pOldPen);

	BoardToDc(m_pReversi);
	// 绘制背景框
	dc.StretchBlt(1, 1, int(m_width*zoom), int(m_height*zoom), m_pBoardDC, 
				  x, y, m_width, m_height, SRCCOPY);
}

// 显示动画
void CBoardView::ShowFlash(int x, int y, int count)
{
	int i, n;
	CPoint * pArray;
	CClientDC dc(this);

	// 得到放大尺寸
	float zoom = Zoom[m_zoomIndex];
	// 得到是否隐藏上标题和左标题
	int xOrigin, yOrigin;
	xOrigin = (m_bShowLeft ? int(WIDTH_LEFT*zoom) : 0) + 1;
	yOrigin = (m_bShowTop  ? int(HEIGHT_TOP*zoom) : 0) + 1;

	if (count<1) return;
	pArray = new CPoint[count];
	m_pReversi->GetChangePoint(x, y, pArray);
	if(m_pReversi->GetCurPlayer()==BLACK)
	{
		dc.StretchBlt(int((y-1)*WIDTH_GRID*zoom)+xOrigin, int((x-1)*WIDTH_GRID*zoom)+yOrigin, int(WIDTH_GRID*zoom), int(WIDTH_GRID*zoom), m_pBlackDC, 0, 0, WIDTH_GRID, WIDTH_GRID, SRCCOPY);
		for(i=15; i>=0; i--)
		{
			for(n=0; n<count; n++)
				dc.StretchBlt(int((pArray[n].y-1)*WIDTH_GRID*zoom)+xOrigin, int((pArray[n].x-1)*WIDTH_GRID*zoom)+yOrigin, int(WIDTH_GRID*zoom), int(WIDTH_GRID*zoom), &m_pReversiDC[i], 0, 0, WIDTH_GRID, WIDTH_GRID, SRCCOPY);
	//		::Sleep(40);
			Wait(40);
		}
	}
	else
	{
		dc.StretchBlt(int((y-1)*WIDTH_GRID*zoom)+xOrigin, int((x-1)*WIDTH_GRID*zoom)+yOrigin, int(WIDTH_GRID*zoom), int(WIDTH_GRID*zoom), m_pWhiteDC, 0, 0, WIDTH_GRID, WIDTH_GRID, SRCCOPY);
		for(i=5; i<20; i++)
		{
			for(n=0; n<count; n++)
				dc.StretchBlt(int((pArray[n].y-1)*WIDTH_GRID*zoom)+xOrigin, int((pArray[n].x-1)*WIDTH_GRID*zoom)+yOrigin, int(WIDTH_GRID*zoom), int(WIDTH_GRID*zoom), &m_pReversiDC[i], 0, 0, WIDTH_GRID, WIDTH_GRID, SRCCOPY);
	//		::Sleep(40);
			Wait(40);
		}
	}
	delete []pArray;
}

// 走一步棋
int CBoardView::MovePoint(int x, int y)
{
	int count, isWin;
	int curPlayer;
	CString strWin, strTemp;
	
	curPlayer = m_pReversi->GetCurPlayer();
	count = m_pReversi->IsRight(x, y);
	if(m_bFlash)
		ShowFlash(x, y, count);		//显示动画
	isWin = m_pReversi->NextStep(x, y);
	Invalidate(FALSE);
	UpdateWindow();

	// 如果游戏结束则给出提示
	if(isWin==1)
	{
		if(m_pReversi->GetBlackCount() > m_pReversi->GetWhiteCount())
		{
			strTemp.LoadString(IDS_BLACK_WIN);
			strWin.Format(strTemp.GetBuffer(16), m_pReversi->GetBlackCount()-m_pReversi->GetWhiteCount());
		}
		else if(m_pReversi->GetBlackCount() < m_pReversi->GetWhiteCount())
		{
			strTemp.LoadString(IDS_WHITE_WIN);
			strWin.Format(strTemp.GetBuffer(16), m_pReversi->GetWhiteCount()-m_pReversi->GetBlackCount());
		}
		else
			strWin.LoadString(IDS_DOGFALL);
		AfxMessageBox(strWin, 0, 0);
		return isWin;
	}
	// 如果落子后，对方没棋可走，则给出提示
	if(curPlayer==m_pReversi->GetCurPlayer())
	{
		if(curPlayer==BLACK)
			strWin.LoadString(IDS_WHITE_STOP);
		else
			strWin.LoadString(IDS_BLACK_STOP);
		AfxMessageBox(strWin, 0, 0);
	}
	
	m_bPromptOver = FALSE;	// 当棋盘上发生变化时重新设置电脑没有搜索到需要提示的最优走法

	return isWin;
}

// 开始一局新的游戏
void CBoardView::StartNewGame()
{
	if(GetLockState())
		return;

	StopSearchPrompt();			// 停止搜索提示信息
	
	m_pReversi->ReStart(m_nStartMode);
	Invalidate(FALSE);
	m_bPromptOver = FALSE;
}

void CBoardView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CString strTip="";
	CPoint p = point;
	// 得到放大前的尺寸
	float zoom = GetZoom();
	p.x = int(p.x/zoom);
	p.y = int(p.y/zoom);
	if(m_bShowTop)
		if(p.x-(m_bShowLeft ? WIDTH_LEFT : 0)>=0 && p.y<=HEIGHT_TOP)
			strTip = "上面标题";
	if(m_bShowLeft)
		if(p.y-(m_bShowTop  ? HEIGHT_TOP : 0)>=0 && p.x<=WIDTH_LEFT)
			strTip = "左边标题";
	if(strTip!="")
	{
		m_ToolTip.Activate(TRUE);
		m_ToolTip.AddTool(this, strTip);
	}
	else
		m_ToolTip.Activate(FALSE);

	//如果当前坐标和移动前的坐标不同，则更新当前坐标
	CPoint tmpPoint = point;
	PointToBoard(tmpPoint);
	if(tmpPoint!=m_curPoint)
	{
		m_curPoint = tmpPoint;
		if(m_bShowEmpty)
			Invalidate(FALSE);
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CBoardView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(GetLockState())
		return;
	
	SetCapture();
	m_bShowEmpty = TRUE;
	Invalidate(FALSE);
	
	CView::OnLButtonDown(nFlags, point);
}

void CBoardView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	if(m_bShowEmpty == FALSE)	// 解决打开文件时误点鼠标的问题加入的判断
		return;
	m_bShowEmpty = FALSE;
	
	if(GetLockState())
		return;

	int count;
	CPoint tmpPoint = point;
	PointToBoard(tmpPoint);
	if(count=m_pReversi->IsRight(tmpPoint.x, tmpPoint.y))
	{
		StopSearchPrompt();			// 停止搜索提示信息
		SetEvent(m_hLockEvent);		// 锁定棋盘
		MovePoint(tmpPoint.x, tmpPoint.y);
		Invalidate(FALSE);
		SendChangeMsg();
		ResetEvent(m_hLockEvent);	// 解锁棋盘
	}
	else
		MessageBeep(1);

	CView::OnLButtonUp(nFlags, point);
}

void CBoardView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	m_bShowBlueX = TRUE;
	Invalidate(FALSE);

	CView::OnRButtonDown(nFlags, point);
}

void CBoardView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	m_bShowBlueX = FALSE;
	Invalidate(FALSE);

	CView::OnRButtonUp(nFlags, point);
}

BOOL CBoardView::Undo()
{
	if(!m_pReversi->IsCanUndo())
		return FALSE;

	StopSearchPrompt();			// 停止搜索提示信息
	m_pReversi->Undo();
	// 如果是电脑走棋则连续撤销
	while(m_pReversi->GetCurPlayer()==BLACK && !m_bPlayer1 ||
		  m_pReversi->GetCurPlayer()==WHITE && !m_bPlayer2)
	{
		m_pReversi->Undo();
	}
	Invalidate(FALSE);
	m_bPromptOver = FALSE;
	return TRUE;
}

// 是否可以悔棋
BOOL CBoardView::IsCanUndo()
{
	return m_pReversi->IsCanUndo();
}

BOOL CBoardView::Redo()
{
	if(!m_pReversi->IsCanRedo())
		return FALSE;

	StopSearchPrompt();			// 停止搜索提示信息
	m_pReversi->Redo();
	Invalidate(FALSE);
	m_bPromptOver = FALSE;
	return TRUE;
}

// 是否可以撤销悔棋
BOOL CBoardView::IsCanRedo()
{
	return m_pReversi->IsCanRedo();
}

// 计时器，控制电脑走棋
void CBoardView::OnTimer(UINT nIDEvent) 
{
	if(GetLockState())
		return;
	if(m_pReversi->IsGameOver())
		return;
	// 让电脑找出最优走法，用红色的“X”提示用户
	if(m_pReversi->GetCurPlayer()==BLACK && m_bPlayer1 ||
	   m_pReversi->GetCurPlayer()==WHITE && m_bPlayer2)
	{
		DWORD result = WaitForSingleObject(m_hPromptEvent, 0);
		if(!m_bPromptOver && result == WAIT_TIMEOUT)
			SetEvent(m_hStartPromptEvent);	// 让电脑提示线程开始运行
		return;
	}

	ComputerFindMove();

	CView::OnTimer(nIDEvent);
}

// 让电脑寻找一步棋
void CBoardView::ComputerFindMove()
{
	if(GetLockState())
		return;

	StopSearchPrompt();			// 停止搜索提示信息
//	::SetCursor (LoadCursor (NULL, IDC_WAIT));
	SetEvent(m_hLockEvent);			// 锁定棋盘
	SetEvent(m_hStartThinkEvent);	// 让电脑搜索线程开始运行
}

// 电脑搜索到最优走法后的消息处理函数
void CBoardView::OnFindBestMove()
{
	// 当前是电脑思考
	ComputerMove();
}

// 让电脑走一步棋
void CBoardView::ComputerMove()
{	
	MovePoint(m_bestPoint.x, m_bestPoint.y);
	SendChangeMsg();
	::SetCursor (LoadCursor (NULL, IDC_ARROW));
	ResetEvent(m_hLockEvent);	// 解锁棋盘
}

// 处理最优走法改变的消息
void CBoardView::OnBestMoveChange()
{
	Invalidate(FALSE);
}

// 当棋盘的状态发生改变时，调用此函数发送消息到指定窗口
void CBoardView::SendChangeMsg()
{
	if(m_hWndReceive)
		::SendMessage(m_hWndReceive, WM_STATE_CHANGE, 0, 0);
}

// 得到棋盘锁定状态
BOOL CBoardView::GetLockState()
{
	DWORD result = WaitForSingleObject(m_hLockEvent, 0);
	if(result == WAIT_OBJECT_0)
		return TRUE;
	else
		return FALSE;
}

// 停止搜索最优走法
void CBoardView::StopSearch()
{
	if(!GetLockState())
		return;

	m_pReversiSearch->m_bExit = TRUE;
}

// 停止搜索提示信息
void CBoardView::StopSearchPrompt()
{
	if(WaitForSingleObject(m_hPromptEvent, 0) == WAIT_OBJECT_0)
	{
		m_pReversiSearch->m_bExit = TRUE;
		while(WaitForSingleObject(m_hPromptEvent, 0) != WAIT_TIMEOUT)
			Sleep(40);
	}
}

// 电脑搜索最优走法的线程
DWORD WINAPI CBoardView::ThinkThread(LPVOID pParam)
{
	CBoardView * pView = (CBoardView *)pParam;

	DWORD result;
	while(!pView->m_bThinkExit)
	{
		result = WaitForSingleObject(pView->m_hStartThinkEvent, 1000);
		if(result == WAIT_OBJECT_0)
		{		
			// 先停止提示线程的搜索
			pView->m_pReversiSearch->m_bExit = TRUE;
			if(WaitForSingleObject(pView->m_hPromptEvent, 0)==WAIT_TIMEOUT)
			{
				SetEvent(pView->m_hThinkEvent);
				ResetEvent(pView->m_hStartThinkEvent);
				pView->m_pReversiSearch->SetSearchPlanWnd(pView->m_hWndThinkPlan);
				pView->m_pReversiSearch->m_bExit = FALSE;
				pView->m_bestPoint = pView->m_pReversiSearch->FindBestStep(*(pView->m_pReversi));
				ResetEvent(pView->m_hThinkEvent);
				// 发送搜索完毕的消息
				pView->PostMessage(WM_FIND_BEST_MOVE, 0, 0);
			}
		}
	}

	return 0;
}

// 电脑提示最优走法的线程
DWORD WINAPI CBoardView::PromptThread(LPVOID pParam)
{
	CBoardView * pView = (CBoardView *)pParam;

	DWORD result;
	while(!pView->m_bPromptExit)
	{
		result = WaitForSingleObject(pView->m_hStartPromptEvent, 1000);
		if(result == WAIT_OBJECT_0)
		{
			SetEvent(pView->m_hPromptEvent);
			ResetEvent(pView->m_hStartPromptEvent);
			pView->m_pReversiSearch->SetSearchPlanWnd(pView->m_hWndPromptPlan);
			pView->m_pReversiSearch->m_bExit = FALSE;
			pView->m_bestPoint = pView->m_pReversiSearch->FindBestStep(*(pView->m_pReversi));
			pView->m_bPromptOver = TRUE;
			ResetEvent(pView->m_hPromptEvent);
			// 发送搜索完毕的消息
			pView->PostMessage(WM_PROMPT_BEST_MOVE, 0, 0);
		}
	}

	return 0;
}

// 从注册表中读取游戏参数
void CBoardView::GetInfoFromReg()
{
	m_nLevel = AfxGetApp()->GetProfileInt(s_profileHeading, s_level, 6);			// 难度
	m_nStartMode = AfxGetApp()->GetProfileInt(s_profileHeading, s_startMode, 3);	// 开局模式
	m_bFlash = AfxGetApp()->GetProfileInt(s_profileHeading, s_flash, 1);			// 是否显示动画
	m_bShowTop = AfxGetApp()->GetProfileInt(s_profileHeading, s_showTop, 1);		// 是否显示上边标题
	m_bShowLeft = AfxGetApp()->GetProfileInt(s_profileHeading, s_showLeft, 1);		// 是否显示左边标题
	m_bPlayer1 = AfxGetApp()->GetProfileInt(s_profileHeading, s_bPlayer1, 1);		// 玩家是否执黑棋
	m_bPlayer2 = AfxGetApp()->GetProfileInt(s_profileHeading, s_bPlayer2, 0);		// 玩家是否执白棋
}

// 保存游戏参数到注册表
void CBoardView::SetInfoToReg()
{
	AfxGetApp()->WriteProfileInt(s_profileHeading, s_level, m_nLevel);			// 难度
	AfxGetApp()->WriteProfileInt(s_profileHeading, s_startMode, m_nStartMode);	// 开局模式
	AfxGetApp()->WriteProfileInt(s_profileHeading, s_flash, m_bFlash);			// 是否显示动画
	AfxGetApp()->WriteProfileInt(s_profileHeading, s_showTop, m_bShowTop);		// 是否显示上边标题
	AfxGetApp()->WriteProfileInt(s_profileHeading, s_showLeft, m_bShowLeft);	// 是否显示左边标题
	if(m_nNetPro == 0)
	{
		AfxGetApp()->WriteProfileInt(s_profileHeading, s_bPlayer1, m_bPlayer1);
		AfxGetApp()->WriteProfileInt(s_profileHeading, s_bPlayer2, m_bPlayer2);
	}
	else
	{
		AfxGetApp()->WriteProfileInt(s_profileHeading, s_bPlayer1, 1);
		AfxGetApp()->WriteProfileInt(s_profileHeading, s_bPlayer2, 1);	
	}
}

void CBoardView::Serialize(CArchive& ar) 
{
	BOOL bPlayer1, bPlayer2;
	if (ar.IsStoring())
	{
		bPlayer1 = m_bPlayer1;
		bPlayer2 = m_bPlayer2;
		if(m_nNetPro != 0)
		{
			bPlayer1 = TRUE;
			bPlayer2 = TRUE;
		}
		ar << m_bFlash << m_nStartMode << m_nLevel << bPlayer1 << bPlayer2;
	}
	else
	{
		ar >> m_bFlash >> m_nStartMode >> m_nLevel >> m_bPlayer1 >> m_bPlayer2;
	}

	m_pReversi->Serialize(ar);
	
	if (!ar.IsStoring())
		m_bPromptOver = FALSE;
}

void Wait(DWORD dwTime)
{
	MSG msg;
	DWORD dwOrgTick = GetTickCount();
	while((GetTickCount() - dwOrgTick) < dwTime)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

BOOL CBoardView::PreTranslateMessage(MSG* pMsg) 
{
	if(m_ToolTip.m_hWnd) m_ToolTip.RelayEvent(pMsg);
	return CView::PreTranslateMessage(pMsg);
}
