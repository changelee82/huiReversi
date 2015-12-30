// HuiReversiMove.h: interface for the HuiReversiMove class.
//摩羯之辉黑白棋组件(走法产生器)
//////////////////////////////////////////////////////////////////////

#if !defined(_HUIREVERSIMOVE_H_INCLUDED_)
#define _HUIREVERSIMOVE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class HuiReversiMove : public CObject  
{
public:
	HuiReversiMove();
	virtual ~HuiReversiMove();
	int GetAllMove(HuiReversiMain & reversi, int layer);	//根据传来HuiReversiMain对象，列出所有的走法
	inline POINT GetAMove(int layer, int i)	//返回第layer层，第i个走法(i从0开始)
		{return m_allMove[layer][i];}

private:
	POINT m_allMove[15][30];		//存放所有走法的列队
};

#endif // !defined(_HUIREVERSIMOVE_H_INCLUDED_)
