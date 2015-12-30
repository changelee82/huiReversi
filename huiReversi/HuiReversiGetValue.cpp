// huireversigetvalue.cpp: implementation of the HuiReversiGetValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\HuiReversi.h"

#include "HuiReversiMain.h"
#include "HuiReversiGetValue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HuiReversiGetValue::HuiReversiGetValue()
{

}

HuiReversiGetValue::~HuiReversiGetValue()
{

}

//������ֵ��ʽ�Ĺ���(�ú�����ʱ���������ð�����ʱ���ظ������Ȱ׺�)
int HuiReversiGetValue::GetValue_Negative(HuiReversiMain & reversi)
{
	int value;

	value=reversi.GetBlackCount()-reversi.GetWhiteCount();
	//���ĸ����ϵĵ���ϸ���ֵ10
	if (reversi.GetChessman(1, 1) == BLACK) value += 10;
	else if (reversi.GetChessman(1, 1) == WHITE) value -= 10;
	if (reversi.GetChessman(1, 8) == BLACK) value += 10;
	else if (reversi.GetChessman(1, 8) == WHITE) value -= 10;
	if (reversi.GetChessman(8, 1) == BLACK) value += 10;
	else if (reversi.GetChessman(8, 1) == WHITE) value -= 10;
	if (reversi.GetChessman(8, 8) == BLACK) value += 10;
	else if (reversi.GetChessman(8, 8) == WHITE) value -= 10;

	if (reversi.GetCurPlayer() == BLACK)
		return value;
	else
		return -value;
}

