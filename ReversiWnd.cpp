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

// ��������
BOOL CReversiWnd::OnEraseBkgnd(CDC* pDC) 
{
	// ��������ͻ�����
	CRect rect;
	GetClientRect(&rect);

	// ���ƿͻ����ı���
	HBRUSH	hbrGray = (HBRUSH)CreateSolidBrush(RGB(0xFF,0xFF,0xFF));
	HBRUSH	hbrOld;
	hbrOld = (HBRUSH)pDC->SelectObject(hbrGray);
	pDC->FillRect(&rect, CBrush::FromHandle(hbrGray));
	pDC->SelectObject(hbrOld);
	DeleteObject(hbrGray);

	// ���ƿͻ����ı߿�
	pDC->DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
	
	return CWnd::OnEraseBkgnd(pDC);	
}

int CReversiWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// ���������ϱ߱�־��
	if (!m_wndBoard->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | SS_WHITERECT,
		CRect(0, 0, 0, 0), this, NULL, NULL))
	{
		TRACE0("�������̴��ڴ���\n");
		return -1;      // fail to create
	}

	// ���������ұߴ���
	if (!m_wndBoardRight->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | SS_WHITERECT,
		CRect(0, 0, 0, 0), this, NULL, NULL))
	{
		TRACE0("���������ұߴ��ڴ���\n");
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

// �������ڿͻ�������
void CReversiWnd::PartitionClientRect()
{
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(2, 2);

	// ���̴��ڴ�С��λ��
	m_rectBoard.top     = rect.top;
	m_rectBoard.left    = rect.left;
	m_rectBoard.bottom  = m_rectBoard.top + m_wndBoard->GetCurHeight();
	m_rectBoard.right   = m_rectBoard.left+ m_wndBoard->GetCurWidth();
	// �����ұߴ��ڴ�С��λ��
	m_rectRight.top     = rect.top;
	m_rectRight.left    = m_rectBoard.right;
	m_rectRight.bottom  = m_rectBoard.bottom;
	m_rectRight.right   = rect.right;
}

void CReversiWnd::RecalcLayout(BOOL bNotify)
{
	// �������ڽ��з���
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

// ��ʾ�ϱ߱�����
void CReversiWnd::ShowTopWindow(BOOL nShow)
{
	m_wndBoard->m_bShowTop = nShow;
	RecalcLayout(FALSE);
}

// ��ʾ��߱�����
void CReversiWnd::ShowLeftWindow(BOOL nShow)
{
	m_wndBoard->m_bShowLeft = nShow;
	RecalcLayout(FALSE);
}

// �Ŵ�����
void CReversiWnd::Zoomin()
{
	m_wndBoard->Zoomin();
	RecalcLayout(FALSE);
}

// ��С����
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
