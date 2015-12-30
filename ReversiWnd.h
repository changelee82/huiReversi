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

#define WM_SIZE_CHANGE    WM_USER+1300   // �����̵Ĵ�С�����ı�ʱ���͸��������ڵ���Ϣ

// �ڰ��崰�ڳߴ����
#define WIDTH_RIGHT		140		// �ұߴ��ڿ��
#define HEIGHT_CAPTION		(GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYFRAME)*2 + 2)

#define USER_TOO_TIP_WIDTH  2000	// ��ʾ���������

class CReversiWnd : public CWnd
{
// Construction
public:
	CReversiWnd();

//����
public:
	CBoardView      * m_wndBoard;		// ���̴���
	CBoardRightView * m_wndBoardRight;	// �����ұߴ���
	CRect	m_rectBoard;		// ���̴�С
	CRect	m_rectRight;		// ���������������С
	HWND	m_hWndSizeChange;	// �����̵Ĵ�С�����ı�ʱ��Ҫ������Ϣ֪ͨ�Ĵ��ھ��
	

// ����
public:
	void RecalcLayout(BOOL bNotify);
	void PartitionClientRect();		 // �������ڿͻ�������
	void ShowTopWindow(BOOL nShow);	 // ��ʾ�ϱ߱�����
	void ShowLeftWindow(BOOL nShow); // ��ʾ��߱�����
	void Zoomin();					 // �Ŵ�����
	void Zoomout();					 // ��С����

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
