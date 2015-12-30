// huireversisearch.cpp: implementation of the HuiReversiSearch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\HuiReversi.h"

#include "HuiReversiMain.h"
#include "HuiReversiMove.h"
#include "HuiReversiGetValue.h"
#include "HuiReversiSearch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HuiReversiSearch::HuiReversiSearch()
{
	m_hWndPlan = NULL;
	m_hWndBestMove = NULL;
	m_bExit = FALSE;
}

HuiReversiSearch::~HuiReversiSearch()
{

}

//是否游戏结束,没结束返回0,结束返回非0值(极大极小值形式)
int HuiReversiSearch::IsGameOver()
{
	int value;

	value = m_reversi.GetBlackCount()-m_reversi.GetWhiteCount();
	if(m_reversi.IsNoStep())
	{
		if(value > 0)
			return value + 60;
		else if(value < 0)
			return value - 60;
		else
		{
			if(m_reversi.GetCurPlayer() == BLACK)
				return 1;
			else
				return -1;
		}
	}
	else
		return 0;
}

//是否游戏结束,没结束返回0,结束返回非0值(负极大值形式)
int HuiReversiSearch::IsGameOver_Negative()
{
	int value;

	value = m_reversi.GetBlackCount()-m_reversi.GetWhiteCount();
	if(m_reversi.IsNoStep())
	{
		if(value > 0)
			value += 60;
		else if(value < 0)
			value -= 60;
		else
		{
			if(m_reversi.GetCurPlayer() == BLACK)
				value = 1;
			else
				value = -1;
		}
		if(m_reversi.GetCurPlayer() == BLACK)
			return value;
		else
			return -value;
	}
	else
		return 0;
}
