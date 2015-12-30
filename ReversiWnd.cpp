// ReversiWnd.cpp : implementation file
//

#include "stdafx.h"
#include "HuiReversi.h"
#include "ReversiWnd.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReversiWnd

CReversiWnd::CReversiWnd()
{
	m_wndBoard       = new CBoardView;
	m_wndBoardRight  = new CBoardRightView;
	m_hWndSizeChange = NULL;
}

CReversiWnd::~CReversiWnd()
{
}

BEGIN_MESSAGE_MAP(CReversiWnd, CWnd)
	//{{AFX_MSG_MAP(CReversiWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReversiWnd message handlers

// 消除背景
BOOL CReversiWnd::OnEraseBkgnd(CDC* pDC) 
{
	// 获得整个客户区域
	CRect rect;
	GetClientRect(&rect);

	// 绘制客户区的背景
	HBRUSH	hbrGray = (HBRUSH)CreateSolidBrush(RGB(0xFF,0xFF,0xFF));
	HBRUSH	hbrOld;
	hbrOld = (HBRUSH)pDC->SelectObject(hbrGray);
	pDC->FillRect(&rect, CBrush::FromHandle(hbrGray));
	pDC->SelectObject(hbrOld);
	DeleteObject(hbrGray);

	// 绘制客户区的边框
	pDC->DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
	
	return CWnd::OnEraseBkgnd(pDC);	
}

int CReversiWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// 创建棋盘上边标志栏
	if (!m_wndBoard->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | SS_WHITERECT,
		CRect(0, 0, 0, 0), this, NULL, NULL))
	{
		TRACE0("创建棋盘窗口错误\n");
		return -1;      // fail to create
	}

	// 创建棋盘右边窗口
	if (!m_wndBoardRight->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | SS_WHITERECT,
		CRect(0, 0, 0, 0), this, NULL, NULL))
	{
		TRACE0("创建棋盘右边窗口错误\n");
		return -1;      // fail to create
	}

	return 0;
}

void CReversiWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (nType != SIZE_MINIMIZED)
		RecalcLayout(FALSE);
}

// 对主窗口客户区分区
void CReversiWnd::PartitionClientRect()
{
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(2, 2);

	// 棋盘窗口大小及位置
	m_rectBoard.top     = rect.top;
	m_rectBoard.left    = rect.left;
	m_rectBoard.bottom  = m_rectBoard.top + m_wndBoard->GetCurHeight();
	m_rectBoard.right   = m_rectBoard.left+ m_wndBoard->GetCurWidth();
	// 棋盘右边窗口大小及位置
	m_rectRight.top     = rect.top;
	m_rectRight.left    = m_rectBoard.right;
	m_rectRight.bottom  = m_rectBoard.bottom;
	m_rectRight.right   = rect.right;
}

void CReversiWnd::RecalcLayout(BOOL bNotify)
{
	// 对主窗口进行分区
	PartitionClientRect();

	if(m_wndBoard)
	{
		m_wndBoard->MoveWindow(&m_rectBoard);
	}
	if(m_wndBoardRight)
	{
		m_wndBoardRight->MoveWindow(&m_rectRight);
	}

	if(m_hWndSizeChange)
		::SendMessage(m_hWndSizeChange, WM_SIZE_CHANGE, (WPARAM)m_wndBoard->GetCurWidth(), (LPARAM)m_wndBoard->GetCurHeight());
}

// 显示上边标题栏
void CReversiWnd::ShowTopWindow(BOOL nShow)
{
	m_wndBoard->m_bShowTop = nShow;
	RecalcLayout(FALSE);
}

// 显示左边标题栏
void CReversiWnd::ShowLeftWindow(BOOL nShow)
{
	m_wndBoard->m_bShowLeft = nShow;
	RecalcLayout(FALSE);
}

// 放大棋盘
void CReversiWnd::Zoomin()
{
	m_wndBoard->Zoomin();
	RecalcLayout(FALSE);
}

// 缩小棋盘
void CReversiWnd::Zoomout()
{
	m_wndBoard->Zoomout();
	RecalcLayout(FALSE);
}

void CReversiWnd::OnClose() 
{
	CWnd::OnClose();
}

void CReversiWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);
}
