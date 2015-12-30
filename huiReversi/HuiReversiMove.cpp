// HuiReversiMove.cpp: implementation of the HuiReversiMove class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\HuiReversi.h"

#include "HuiReversiMain.h"
#include "HuiReversiMove.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HuiReversiMove::HuiReversiMove()
{

}

HuiReversiMove::~HuiReversiMove()
{

}

int HuiReversiMove::GetAllMove(HuiReversiMain & reversi, int layer)
{
	int i, j, count;

	count = 0;
	for (i=1; i<=reversi.GetBoardLength(); i++)
		for (j=1; j<=reversi.GetBoardLength(); j++)
		{
			if(reversi.IsRight(i, j)) 
			{
				m_allMove[layer][count].x = i;
				m_allMove[layer][count].y = j;
				count++;
			}
		}

	return count;
}
