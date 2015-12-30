// HuiReversi.h : main header file for the HUIREVERSI application
//

#if !defined(_HUIREVERSI_H_INCLUDED_)
#define _HUIREVERSI_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ReversiWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiApp:
// See HuiReversi.cpp for the implementation of this class
//
extern CReversiWnd	theReversiWnd;	//黑白棋窗口对象

class CHuiReversiApp : public CWinApp
{
public:
	CHuiReversiApp();
	CDocument * GetCurrentDoc();	// 得到文档类对象指针

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHuiReversiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHuiReversiApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_HUIREVERSI_H_INCLUDED_)
