// huireversisearch.h: interface for the HuiReversiSearch class.
//摩羯之辉黑白棋组件(搜索类的基类)
//////////////////////////////////////////////////////////////////////

#if !defined(_HUIREVERSISEARCH_H_INCLUDED_)
#define _HUIREVERSISEARCH_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_BEST_MOVE_CHANGE	  WM_USER+1050   // 最优走法改变的消息
#define WM_SEARCH_PLAN		  WM_USER+1060   // 当电脑搜索到最优走法的进度消息
// 发送消息时的参数
#define SEARCH_RANGE	1	// 搜索的范围
#define SEARCH_POS		2	// 当前搜索到的值
#define SEARCH_POS_MAX	3	// 最大值


class HuiReversiSearch : public CObject  
{
public:
	HuiReversiSearch();
	virtual ~HuiReversiSearch();
	virtual POINT FindBestStep(HuiReversiMain & reversi) = 0;	//找到一个最好的走法
	inline void SetLayer(int layer) {m_nLayer = layer;}	//设置层数
	inline int  GetLayer() {return m_nLayer;}	//获取层数
	inline void SetGetValue(HuiReversiGetValue * pGetValue) {m_pGetValue = pGetValue;}	//设定估值类指针
	inline void SetMove(HuiReversiMove * pMove) {m_pMove = pMove;}	// 设定走法产生器指针
	inline void SetSearchPlanWnd(HWND hWnd) {m_hWndPlan = hWnd;}	// 设定接收搜索进度信息的窗口句柄
	inline void SetBestMoveWnd(HWND hWnd) {m_hWndBestMove = hWnd;}	// 设定接收最优走法改变的消息的窗口句柄
	inline POINT GetBestStep() {return m_bestStep;}		// 获得最优的走法

public:
	BOOL  m_bExit;			// 停止所搜的标志
protected:
	HWND  m_hWndPlan;		// 接收搜索进度信息的窗口句柄
	HWND  m_hWndBestMove;	// 接收最优走法改变的消息的窗口句柄
	int   m_nLayer;			// 搜索的层数
	int   m_nCurrentLayer;	// 当前搜索的层数
	POINT m_bestStep;		// 记录最优的走法
	HuiReversiMain m_reversi;	// 当前临时的HuiReversiMain类
	HuiReversiMove * m_pMove;	// 走法产生器指针
	HuiReversiGetValue * m_pGetValue;	//估值类的指针

protected:
	int IsGameOver();	//是否游戏结束,没结束返回0,结束返回非0值(极大极小值形式)
	int IsGameOver_Negative();	//是否游戏结束,没结束返回0,结束返回非0值(负极大值形式)
	inline void Move(int x, int y)	//走一步棋
		{m_reversi.NextStep(x, y);}
	inline void ReMove()		//还原一步棋
		{m_reversi.Undo();}
};

#endif // !defined(_HUIREVERSISEARCH_H_INCLUDED_)
