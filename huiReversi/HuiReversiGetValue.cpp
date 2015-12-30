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

//负极大值形式的估价(该黑棋走时返回正，该白棋走时返回负，黑先白后)
int HuiReversiGetValue::GetValue_Negative(HuiReversiMain & reversi)
{
	int value;

	value=reversi.GetBlackCount()-reversi.GetWhiteCount();
	//给四个角上的点加上附加值10
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

