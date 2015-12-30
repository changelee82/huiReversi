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

//�ҵ�һ����õ��߷�
POINT HuiSearchAlphaBeta::FindBestStep(HuiReversiMain & reversi)
{

	m_reversi = reversi;
	m_nCurrentLayer = m_nLayer;
	m_bestStep.x = -1;
	m_bestStep.y = -1;
	Alpha_Beta(-125,125,0);
	if(m_hWndPlan)
		::PostMessage(m_hWndPlan, WM_SEARCH_PLAN, SEARCH_POS_MAX, 0);	// ���ý���Ϊ���ֵ
	m_nCurrentLayer = m_nLayer;	// �����ִ�����������иı��Ѷȣ�����Ҫ�����趨�Ѷ�

	return m_bestStep;
}

//alpha-beta��֦(������ֵ��ʽ)
int HuiSearchAlphaBeta::Alpha_Beta(int alpha, int beta, int layer)
{
	int i,value,count,tvalue;

	value = IsGameOver_Negative();
	if(value!=0) 
		return value;
	if(layer==m_nCurrentLayer) 
		return m_pGetValue->GetValue_Negative(m_reversi);

	count = m_pMove->GetAllMove(m_reversi, layer);
	// �趨�����߷���Ĭ��ֵ
	if(layer==0)
	{
		m_bestStep = m_pMove->GetAMove(layer,0);
		if(m_hWndBestMove)
			::PostMessage(m_hWndBestMove, WM_BEST_MOVE_CHANGE, 0, 0);	// ����Ĭ�������߷�
	}

	if(m_hWndPlan!=NULL && layer==0)
	{
		::PostMessage(m_hWndPlan, WM_SEARCH_PLAN, SEARCH_RANGE, count);	// ����������Χ
		::PostMessage(m_hWndPlan, WM_SEARCH_PLAN, SEARCH_POS, 0);		// ����
	}

	for(i=0; i<count && !m_bExit; i++)
	{
		if(m_hWndPlan!=NULL && layer==0)
			::PostMessage(m_hWndPlan, WM_SEARCH_PLAN, SEARCH_POS, i+1);
		Move(m_pMove->GetAMove(layer,i).x, m_pMove->GetAMove(layer,i).y);
		tvalue = -Alpha_Beta(-beta, -alpha, layer+1);
		ReMove();
		// �Ƿ�ֹͣ����
		if(m_bExit)
			return 0;
		// �õ����õ��߷�
		if(tvalue > alpha)
		{
			alpha = tvalue;
			if(layer==0)
			{
				m_bestStep = m_pMove->GetAMove(layer,i);
				if(m_hWndBestMove)
					::PostMessage(m_hWndBestMove, WM_BEST_MOVE_CHANGE, 0, 0);	// ���������߷��ı����Ϣ
			}
			if(alpha>=beta)
				break;
		}
	}
	
	return alpha;
}
