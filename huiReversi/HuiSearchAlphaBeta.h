// HuiSearchAlphaBeta.h: interface for the HuiSearchAlphaBeta class.
//摩羯之辉黑白棋组件(搜索类:alpha-beta剪枝)
//////////////////////////////////////////////////////////////////////

#if !defined(_HUISEARCHALPHABETA_H_INCLUDED_)
#define _HUISEARCHALPHABETA_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "HuiReversiSearch.h"
class HuiSearchAlphaBeta : public HuiReversiSearch  
{
public:
	HuiSearchAlphaBeta();
	virtual ~HuiSearchAlphaBeta();
	virtual POINT FindBestStep(HuiReversiMain & reversi);	//找到一个最好的走法
protected:
	int Alpha_Beta(int alpha,int beta,int layer);
};

#endif // !defined(_HUISEARCHALPHABETA_H_INCLUDED_)
