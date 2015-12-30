// huireversigetvalue.h: interface for the HuiReversiGetValue class.
//摩羯之辉黑白棋组件(估值类)
//////////////////////////////////////////////////////////////////////

#if !defined(_HUIREVERSIGETVALUE_H_INCLUDED_)
#define _HUIREVERSIGETVALUE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class HuiReversiGetValue : public CObject  
{
public:
	HuiReversiGetValue();
	virtual ~HuiReversiGetValue();
	int GetValue_Negative(HuiReversiMain & reversi);	//负极大值形式的估价(该黑棋走时返回正，该白棋走时返回负，黑先白后)
	inline int GetValue(HuiReversiMain & reversi)		//极大极小值形式的估价
		{return reversi.GetBlackCount()-reversi.GetWhiteCount();}
};

#endif // !defined(_HUIREVERSIGETVALUE_H_INCLUDED_)
