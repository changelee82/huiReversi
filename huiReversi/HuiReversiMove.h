// HuiReversiMove.h: interface for the HuiReversiMove class.
//Ħ��֮�Ժڰ������(�߷�������)
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
	int GetAllMove(HuiReversiMain & reversi, int layer);	//���ݴ���HuiReversiMain�����г����е��߷�
	inline POINT GetAMove(int layer, int i)	//���ص�layer�㣬��i���߷�(i��0��ʼ)
		{return m_allMove[layer][i];}

private:
	POINT m_allMove[15][30];		//��������߷����ж�
};

#endif // !defined(_HUIREVERSIMOVE_H_INCLUDED_)
