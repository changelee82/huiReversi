// HuiSearchAlphaBeta.cpp: implementation of the HuiSearchAlphaBeta class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\HuiReversi.h"
#include "HuiReversiMain.h"
#include "HuiReversiMove.h"
#include "HuiReversiGetValue.h"
#include "HuiSearchAlphaBeta.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HuiSearchAlphaBeta::HuiSearchAlphaBeta()
{

}

HuiSearchAlphaBeta::~HuiSearchAlphaBeta()
{

}

//找到一个最好的走法
POINT HuiSearchAlphaBeta::FindBestStep(HuiReversiMain & reversi)
{

	m_reversi = reversi;
	m_nCurrentLayer = m_nLayer;
	m_bestStep.x = -1;
	m_bestStep.y = -1;
	Alpha_Beta(-125,125,0);
	if(m_hWndPlan)
		::PostMessage(m_hWndPlan, WM_SEARCH_PLAN, SEARCH_POS_MAX, 0);	// 设置进度为最大值
	m_nCurrentLayer = m_nLayer;	// 如果在执行搜索过程中改变难度，则需要重新设定难度

	return m_bestStep;
}

//alpha-beta剪枝(负极大值形式)
int HuiSearchAlphaBeta::Alpha_Beta(int alpha, int beta, int layer)
{
	int i,value,count,tvalue;

	value = IsGameOver_Negative();
	if(value!=0) 
		return value;
	if(layer==m_nCurrentLayer) 
		return m_pGetValue->GetValue_Negative(m_reversi);

	count = m_pMove->GetAllMove(m_reversi, layer);
	// 设定最优走法的默认值
	if(layer==0)
	{
		m_bestStep = m_pMove->GetAMove(layer,0);
		if(m_hWndBestMove)
			::PostMessage(m_hWndBestMove, WM_BEST_MOVE_CHANGE, 0, 0);	// 设置默认最优走法
	}

	if(m_hWndPlan!=NULL && layer==0)
	{
		::PostMessage(m_hWndPlan, WM_SEARCH_PLAN, SEARCH_RANGE, count);	// 设置搜索范围
		::PostMessage(m_hWndPlan, WM_SEARCH_PLAN, SEARCH_POS, 0);		// 清零
	}

	for(i=0; i<count && !m_bExit; i++)
	{
		if(m_hWndPlan!=NULL && layer==0)
			::PostMessage(m_hWndPlan, WM_SEARCH_PLAN, SEARCH_POS, i+1);
		Move(m_pMove->GetAMove(layer,i).x, m_pMove->GetAMove(layer,i).y);
		tvalue = -Alpha_Beta(-beta, -alpha, layer+1);
		ReMove();
		// 是否停止搜索
		if(m_bExit)
			return 0;
		// 得到更好的走法
		if(tvalue > alpha)
		{
			alpha = tvalue;
			if(layer==0)
			{
				m_bestStep = m_pMove->GetAMove(layer,i);
				if(m_hWndBestMove)
					::PostMessage(m_hWndBestMove, WM_BEST_MOVE_CHANGE, 0, 0);	// 发出最优走法改变的消息
			}
			if(alpha>=beta)
				break;
		}
	}
	
	return alpha;
}
