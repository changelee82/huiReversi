// huireversigetvalue.h: interface for the HuiReversiGetValue class.
//Ħ��֮�Ժڰ������(��ֵ��)
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
	int GetValue_Negative(HuiReversiMain & reversi);	//������ֵ��ʽ�Ĺ���(�ú�����ʱ���������ð�����ʱ���ظ������Ȱ׺�)
	inline int GetValue(HuiReversiMain & reversi)		//����Сֵ��ʽ�Ĺ���
		{return reversi.GetBlackCount()-reversi.GetWhiteCount();}
};

#endif // !defined(_HUIREVERSIGETVALUE_H_INCLUDED_)
