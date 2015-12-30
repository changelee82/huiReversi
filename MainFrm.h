// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(_MAINFRM_H_INCLUDED_)
#define _MAINFRM_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
protected:
	CView * pClientView;	//临时存储客户区的视图
	char title[31];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetStatusBarHeight();	// 得到状态栏的高度
	int GetToolBarHeight();		// 得到工具栏的高度
	int GetToolBarWidth();		// 得到工具栏的宽度
	void SetStatusBarText();	// 设置状态栏上的文字

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg BOOL OnQueryEndSession();
	afx_msg void OnViewTop();
	afx_msg void OnViewLeft();
	afx_msg void OnUpdateViewTop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewLeft(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();
	afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnGameUndo();
	afx_msg void OnGameRedo();
	afx_msg void OnUpdateGameUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameRedo(CCmdUI* pCmdUI);
	afx_msg void OnGameComputerMove();
	afx_msg void OnSetStartmode1();
	afx_msg void OnUpdateSetStartmode1(CCmdUI* pCmdUI);
	afx_msg void OnSetStartmode2();
	afx_msg void OnUpdateSetStartmode2(CCmdUI* pCmdUI);
	afx_msg void OnSetStartmode3();
	afx_msg void OnUpdateSetStartmode3(CCmdUI* pCmdUI);
	afx_msg void OnSetStartmode4();
	afx_msg void OnUpdateSetStartmode4(CCmdUI* pCmdUI);
	afx_msg void OnSetLevel1();
	afx_msg void OnUpdateSetLevel1(CCmdUI* pCmdUI);
	afx_msg void OnSetLevel2();
	afx_msg void OnUpdateSetLevel2(CCmdUI* pCmdUI);
	afx_msg void OnSetLevel3();
	afx_msg void OnUpdateSetLevel3(CCmdUI* pCmdUI);
	afx_msg void OnSetLevel4();
	afx_msg void OnUpdateSetLevel4(CCmdUI* pCmdUI);
	afx_msg void OnSetLevel5();
	afx_msg void OnUpdateSetLevel5(CCmdUI* pCmdUI);
	afx_msg void OnSetFlash();
	afx_msg void OnUpdateSetFlash(CCmdUI* pCmdUI);
	afx_msg void OnSetFirstPlayer();
	afx_msg void OnUpdateSetFirstPlayer(CCmdUI* pCmdUI);
	afx_msg void OnSetFirstCom();
	afx_msg void OnUpdateSetFirstCom(CCmdUI* pCmdUI);
	afx_msg void OnSetVsPlayer();
	afx_msg void OnUpdateSetVsPlayer(CCmdUI* pCmdUI);
	afx_msg void OnSetVsCom();
	afx_msg void OnUpdateSetVsCom(CCmdUI* pCmdUI);
	afx_msg void OnSetVsNet();
	afx_msg void OnUpdateSetVsNet(CCmdUI* pCmdUI);
	afx_msg void OnGetIp();
	afx_msg void OnHelpRule();
	afx_msg void OnStateChange(WPARAM wParam, LPARAM lParam);	// 当棋盘状态发生改变时收到消息后的处理函数
	afx_msg void OnSizeChange(WPARAM wParam, LPARAM lParam);	// 当棋盘大小发生改变时收到消息后的处理函数
	afx_msg void OnSearchPlan(WPARAM wParam, LPARAM lParam);	// 搜索引擎发来的搜索进度消息
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateGameComputerMove(CCmdUI* pCmdUI);
	afx_msg void OnGameStopSearch();
	afx_msg void OnSetPrompt();
	afx_msg void OnUpdateSetPrompt(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_MAINFRM_H_INCLUDED_)
