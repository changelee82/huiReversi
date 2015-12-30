#if !defined(_REVERSIWND_H_INCLUDED_)
#define _REVERSIWND_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReversiWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReversiWnd window

#include "BoardView.h"
#include "BoardRightView.h"

#define WM_SIZE_CHANGE    WM_USER+1300   // 当棋盘的大小发生改变时发送给其他窗口的消息

// 黑白棋窗口尺寸参数
#define WIDTH_RIGHT		140		// 右边窗口宽度
#define HEIGHT_CAPTION		(GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYFRAME)*2 + 2)

#define USER_TOO_TIP_WIDTH  2000	// 提示工具栏宽度

class CReversiWnd : public CWnd
{
// Construction
public:
	CReversiWnd();

//属性
public:
	CBoardView      * m_wndBoard;		// 棋盘窗口
	CBoardRightView * m_wndBoardRight;	// 棋盘右边窗口
	CRect	m_rectBoard;		// 棋盘大小
	CRect	m_rectRight;		// 棋盘右面操作栏大小
	HWND	m_hWndSizeChange;	// 当棋盘的大小发生改变时需要发送消息通知的窗口句柄
	

// 操作
public:
	void RecalcLayout(BOOL bNotify);
	void PartitionClientRect();		 // 对主窗口客户区分区
	void ShowTopWindow(BOOL nShow);	 // 显示上边标题栏
	void ShowLeftWindow(BOOL nShow); // 显示左边标题栏
	void Zoomin();					 // 放大棋盘
	void Zoomout();					 // 缩小棋盘

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReversiWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReversiWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CReversiWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_REVERSIWND_H_INCLUDED_)
