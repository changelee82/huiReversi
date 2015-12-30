#if !defined(_BOARDVIEW_H_INCLUDED_)
#define _BOARDVIEW_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoardView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBoardView view
#include "huiReversi\HuiReversiMain.h"
#include "huiReversi\HuiReversiMove.h"
#include "huiReversi\HuiReversiGetValue.h"
#include "huiReversi\HuiSearchAlphaBeta.h"

#define WM_STATE_CHANGE    WM_USER+1220     // 当棋盘的状态发生改变时发送给其他窗口的消息
#define WM_FIND_BEST_MOVE  WM_USER+1225     // 当电脑搜索完毕最优走法后发送给棋盘视图的消息
#define WM_PROMPT_BEST_MOVE  WM_USER+1230   // 当电脑提示完毕最优走法后发送给棋盘视图的消息

// 黑白棋窗口尺寸参数
#define HEIGHT_TOP		20		// 上边标题栏窗口高度
#define WIDTH_LEFT		20		// 左边标题栏窗口宽度
#define WIDTH_BOARD		360		// 棋盘窗口宽度(高度和宽度相同)
#define WIDTH_GRID		45		// 一个单元格的宽度
#define WIDTH_POINT		5		// 棋盘上四个焦点的宽度

class CBoardView : public CView
{
public:
	CBoardView();
	virtual ~CBoardView();
	DECLARE_DYNCREATE(CBoardView)

// 属性
public:
	CToolTipCtrl  m_ToolTip;	 // 提示工具栏
	BOOL	m_bShowTop;			 // 棋盘上面标志栏是否可见
	BOOL	m_bShowLeft;		 // 棋盘左面标志栏是否可见
	BOOL	m_bFlash;			 // 翻转棋子时是否显示动画
	BOOL	m_bPlayer1;			 // 是否由玩家执黑棋,TRUE代表玩家,FALSE代表电脑
	BOOL	m_bPlayer2;			 // 是否由玩家执白棋,TRUE代表玩家,FALSE代表电脑
	HWND	m_hWndReceive;		 // 当棋盘的状态发生改变时发送消息到此窗口

protected:
	HuiReversiMain     * m_pReversi;		 // 黑白棋对象的指针
	HuiReversiSearch   * m_pReversiSearch;	 // 搜索引擎指针
	HuiReversiMove     * m_pReversiMove;	 // 走法产生器指针
	HuiReversiGetValue * m_pReversiGetValue; // 估值核心指针

	int		m_nNetPro;			 // 网络对战属性 (0-不是网络对战, 1-玩家执黑棋, 2-玩家执白棋)
	int		m_nStartMode;		 // 开局模式 (1-4)
	int		m_nLevel;			 // 游戏难度 (就是搜索层数 5-9)
	BOOL	m_bShowBlueX;		 // 是否显示蓝色的“X”(可以落子的位置)
	BOOL	m_bShowRedX;		 // 是否显示红色的“X”(电脑搜索出的最优落子的位置)
	BOOL	m_bShowEmpty;		 // 是否显示将要改变颜色的棋子(用虚线画的棋子)
	CPoint	m_curPoint;			 // 当前鼠标所在的棋盘坐标

	HANDLE	m_hLockEvent;		 // 锁定棋盘的事件，激发状态则不处理一些事件
	CPoint	m_bestPoint;		 // 记录当前搜索到的最优走法
	// 与提示搜索相关的参数
	HANDLE	m_hStartPromptEvent; // 让电脑开始提示最优走法的事件
	HANDLE	m_hPromptEvent;		 // 电脑正在提示最优走法的事件
	HANDLE	m_hPromptThread;	 // 电脑提示最优走法的线程句柄
	HWND	m_hWndPromptPlan;	 // 接收提示最优走法的进度信息的窗口句柄
	BOOL	m_bPromptExit;		 // 电脑提示最优走法的线程结束的标志
	BOOL	m_bPromptOver;		 // 电脑是否已经搜索到需要提示的最优走法
	// 与电脑走棋相关的参数
	HANDLE	m_hStartThinkEvent;	 // 让电脑开始搜索最优走法的事件
	HANDLE	m_hThinkEvent;		 // 电脑正在搜索最优走法的事件
	HANDLE	m_hThinkThread;		 // 电脑搜索最优走法的线程句柄
	HWND	m_hWndThinkPlan;	 // 接收搜索最优走法的进度信息的窗口句柄
	BOOL	m_bThinkExit;		 // 电脑搜索最优走法的线程结束的标志

	int		m_width;		// 背景图的宽度
	int		m_height;		// 背景图的高度
	int		m_zoomIndex;	// 棋盘的放大倍数
	static float Zoom[3];	// 放大的倍数列表
	static int ZoomCount;	// 放大的倍数列表元素的数量

	// 下面的变量是存储图片用
	CDC * m_pBoardDC;		// 棋盘
	CDC * m_pInitBoardDC;	// 初始时的棋盘
	CDC * m_pBlackDC;		// 黑棋图片
	CDC * m_pWhiteDC;		// 白棋图片
	CDC * m_pBlackEmptyDC;	// 虚的黑棋图片
	CDC * m_pWhiteEmptyDC;	// 虚的白棋图片
	CDC * m_pXBlueDC;		// 蓝色的“X”图片
	CDC * m_pXRedDC;		// 红色的“X”图片
	CDC * m_pPointDC;		// 棋盘上四个焦点的图片
	CDC * m_pReversiDC;		// 存储动画的图像(共20个图标)

	// 在注册表中保存最后一次游戏时的数据
	static const char s_profileHeading[];	// 参数头
	static const char s_startMode[];		// 开局模式(1-4)
	static const char s_level[];			// 游戏难度(就是搜索层数 5-9)
	static const char s_flash[];			// 动画效果
	static const char s_showTop[];			// 棋盘上边标志栏
	static const char s_showLeft[];			// 棋盘左边标志栏
	static const char s_bPlayer1[];			// 玩家执黑棋
	static const char s_bPlayer2[];			// 玩家执白棋
	
// 操作
public:
	float GetZoom(){return Zoom[m_zoomIndex];};			// 返回放大倍数
	void Zoomin();			// 放大棋盘
	void Zoomout();			// 缩小棋盘
	BOOL CanZoomin();		// 返回是否可以放大棋盘
	BOOL CanZoomout();		// 返回是否可以缩小棋盘
	int  GetCurWidth();		// 返回棋盘窗口当前的有效宽度
	int  GetCurHeight();	// 返回棋盘窗口当前的有效高度

	BOOL Undo();		// 悔棋
	BOOL Redo();		// 撤销悔棋
	BOOL IsCanUndo();	// 是否可以悔棋
	BOOL IsCanRedo();	// 是否可以撤销悔棋
	BOOL SetStartMode(int nMode);	// 设定开局模式(1-4)，参数错误则返回FALSE
	int  GetStartMode() {return m_nStartMode;}	// 获得开局模式
	BOOL SetLevel(int nLevel);		// 设置游戏难度(1-10)，失败则返回FALSE
	int  GetLevel() {return m_nLevel;}			// 获得游戏难度
	int  GetNetPro() {return m_nNetPro;}		// 获得网络对战属性
	BOOL GetPromptInfo() {return m_bShowRedX;}	// 获得提示信息的显示状态
	void ShowPrompt(BOOL bShow)					// 设定提示信息的显示状态
			{m_bShowRedX = bShow;}
	int	 GetStepCount()							// 返回已走棋的步数
			{return m_pReversi->GetStepCount();}

	void GetInfoFromReg();		// 从注册表中读取游戏参数
	void SetInfoToReg();		// 保存游戏参数到注册表
	void ComputerFindMove();	// 让电脑寻找一步棋
	void ComputerMove();		// 让电脑走一步棋
	void StartNewGame();		// 开始一局新的游戏
	void PointToBoard(CPoint & point);			// 将鼠标坐标转换到棋盘坐标(范围1-8)，如果坐标超出范围，则返回(0, 0)
	int  MovePoint(int x, int y);				// 走一步棋
	void ShowFlash(int x, int y, int count);	// 显示动画

	void StartupThread();	// 启动所有线程
	void CloseThread();		// 关闭所有线程
	void SendChangeMsg();	// 当棋盘的状态发生改变时，调用此函数发送消息到指定窗口
	BOOL GetLockState();	// 得到棋盘锁定状态
	void StopSearch();		// 停止搜索最优走法
	void StopSearchPrompt();	// 停止搜索提示信息
	void SetPromptPlanWnd(HWND hWnd) {m_hWndPromptPlan = hWnd;}	// 设定接收提示最优走法的进度信息的窗口句柄
	void SetThinkPlanWnd(HWND hWnd) {m_hWndThinkPlan = hWnd;}	// 设定接收搜索最优走法的进度信息的窗口句柄
	HWND GetPromptPlanWnd() {return m_hWndPromptPlan;}	// 获得接收提示最优走法的进度信息的窗口句柄
	HWND GetThinkPlanWnd() {return m_hWndThinkPlan;}	// 获得接收搜索最优走法的进度信息的窗口句柄

protected:
	void BoardToDc(HuiReversiMain * pReversi=NULL);		// 将黑白棋对象映射到内存DC

	static DWORD WINAPI ThinkThread(LPVOID pParam);		// 电脑搜索最优走法的线程
	static DWORD WINAPI PromptThread(LPVOID pParam);	// 电脑提示最优走法的线程

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoardView)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CBoardView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFindBestMove();		// 电脑搜索到最优走法后的消息处理函数
	afx_msg void OnBestMoveChange();	// 处理最优走法改变的消息
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void Wait(DWORD dwTime);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_BOARDVIEW_H_INCLUDED_)
