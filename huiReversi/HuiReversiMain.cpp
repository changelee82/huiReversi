// HuiReversiMain.cpp: implementation of the HuiReversiMain class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\HuiReversi.h"
#include "HuiReversiMain.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(HuiReversiMain, CObject, 1)

const char * const HuiReversiMain::ver="摩羯之辉黑白棋组件1.20版  作者:李辉  OICQ:6545823";
const BYTE HuiReversiMain::nVerNum1 = 1;		//主版本号
const BYTE HuiReversiMain::nVerNum2 = 20;		//副版本号


// 构造函数
HuiReversiMain::HuiReversiMain(int startMode)
:m_operStackTop(0), m_curPlayer(BLACK), m_boardLength(BOARD_LENGTH),
 m_chessCount(BOARD_LENGTH*BOARD_LENGTH-4)
{
	int i,j;

	// 清空棋盘
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			m_board[i][j] = NO;

	// 清空历史纪录堆栈
	for(i=0; i<m_chessCount+1; i++)
		m_operStack[i].point.x = NODEF;

	// 根据startMode设定棋盘的开局
	switch(startMode)
	{
	case 1:					// 上黑下白
		m_board[4][4] = BLACK;
		m_board[4][5] = BLACK;
		m_board[5][4] = WHITE;
		m_board[5][5] = WHITE;
		break;
	case 2:					// 上白下黑
		m_board[4][4] = WHITE;
		m_board[4][5] = WHITE;
		m_board[5][4] = BLACK;
		m_board[5][5] = BLACK;
		break;
	case 3:					// 左上右下黑
		m_board[4][4] = BLACK;
		m_board[4][5] = WHITE;
		m_board[5][4] = WHITE;
		m_board[5][5] = BLACK;
		break;
	case 4:					// 左上右下白
		m_board[4][4] = WHITE;
		m_board[4][5] = BLACK;
		m_board[5][4] = BLACK;
		m_board[5][5] = WHITE;
		break;
	default:				// 默认值为左上右下黑
		m_board[4][4] = BLACK;
		m_board[4][5] = WHITE;
		m_board[5][4] = WHITE;
		m_board[5][5] = BLACK;
		break;
	}
}

// 拷贝构造函数
HuiReversiMain::HuiReversiMain (HuiReversiMain & reversi)
:m_operStackTop(reversi.m_operStackTop), m_curPlayer(reversi.m_curPlayer),
 m_boardLength(reversi.m_boardLength), m_chessCount(reversi.m_chessCount)
{
	int i,j;

	// 复制棋盘
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			m_board[i][j] = reversi.m_board[i][j];

	// 复制历史纪录堆栈
	for(i=0; i<m_chessCount+1; i++)
		m_operStack[i] = reversi.m_operStack[i];
}

// 预值操作
HuiReversiMain & HuiReversiMain::operator=(const HuiReversiMain & reversi)
{
	int i,j;

	m_operStackTop = reversi.m_operStackTop;
	m_curPlayer = reversi.m_curPlayer;
	m_boardLength = reversi.m_boardLength;
	m_chessCount = reversi.m_chessCount;

	//复制棋盘
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			m_board[i][j] = reversi.m_board[i][j];

	//复制历史纪录堆栈
	for(i=0; i<m_chessCount+1; i++)
		m_operStack[i] = reversi.m_operStack[i];

	return *this;
}

//析构函数
HuiReversiMain::~HuiReversiMain()
{
}

// 重新开始一个棋局
void HuiReversiMain::ReStart(int startMode)
{
	int i,j;

	m_operStackTop = 0;
	m_curPlayer = BLACK;
	m_boardLength = BOARD_LENGTH;
	m_chessCount = BOARD_LENGTH*BOARD_LENGTH-4;

	// 清空棋盘
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			m_board[i][j] = NO;

	// 清空历史纪录堆栈
	for(i=0; i<m_chessCount+1; i++)
		m_operStack[i].point.x = NODEF;

	// 根据startMode设定棋盘的开局
	switch(startMode)
	{
	case 1:					// 上黑下白
		m_board[4][4] = BLACK;
		m_board[4][5] = BLACK;
		m_board[5][4] = WHITE;
		m_board[5][5] = WHITE;
		break;
	case 2:					// 上白下黑
		m_board[4][4] = WHITE;
		m_board[4][5] = WHITE;
		m_board[5][4] = BLACK;
		m_board[5][5] = BLACK;
		break;
	case 3:					// 左上右下黑
		m_board[4][4] = BLACK;
		m_board[4][5] = WHITE;
		m_board[5][4] = WHITE;
		m_board[5][5] = BLACK;
		break;
	case 4:					// 左上右下白
		m_board[4][4] = WHITE;
		m_board[4][5] = BLACK;
		m_board[5][4] = BLACK;
		m_board[5][5] = WHITE;
		break;
	default:				// 默认值为左上右下黑
		m_board[4][4] = BLACK;
		m_board[4][5] = WHITE;
		m_board[5][4] = WHITE;
		m_board[5][5] = BLACK;
		break;
	}
}

void HuiReversiMain::Serialize(CArchive &ar)
{
	int i, curPlayer;
	int totalSize = (BOARD_LENGTH+1) * (BOARD_LENGTH+1);

	if (ar.IsStoring())
	{
		ar << m_boardLength << m_chessCount << m_operStackTop << m_curPlayer;
		ar.Write(m_board, totalSize*sizeof(int));
		for(i=0; i<BOARD_LENGTH*BOARD_LENGTH-3; i++)
		{
			curPlayer = m_operStack[i].curPlayer;
			ar << m_operStack[i].point.x << m_operStack[i].point.y << curPlayer;
			ar.Write(m_operStack[i].changeCount, 8*sizeof(int));
		}
	}
	else
	{
		ar>>m_boardLength>>m_chessCount>>m_operStackTop>>m_curPlayer;
		ar.Read(m_board, totalSize*sizeof(int));
		for(i=0; i<BOARD_LENGTH*BOARD_LENGTH-3; i++)
		{
			ar >> m_operStack[i].point.x >> m_operStack[i].point.y >> curPlayer;
			m_operStack[i].curPlayer = curPlayer;
			ar.Read(m_operStack[i].changeCount, 8*sizeof(int));
		}
	}
}

//走一步棋,返回值:该点有子(-1);正常(0);有一方得胜(1);没棋可走了(2)
int HuiReversiMain::NextStep(int x,int y)
{
	int i, count;
	int tx, ty;			
	int rivalPlayer;	//当前没有走棋的玩家的颜色

	//如果该位置不合法,则返回
	if (!IsRight(x,y)) return -1;

	rivalPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;
	m_board[x][y] = m_curPlayer;

	for(i=0; i<8; i++)		//在8个方向上查看能否转变对方的棋子
	{
		tx = x + offset[i].x;
		ty = y + offset[i].y;
		if (IsRightRange(tx, ty) && m_board[tx][ty]==rivalPlayer)
		{
			do
			{
				tx = tx + offset[i].x;
				ty = ty + offset[i].y;
			}while(IsRightRange(tx, ty) && m_board[tx][ty]==rivalPlayer);

			if(IsRightRange(tx, ty) && m_board[tx][ty]==m_curPlayer)
			{
				count = 0;
				tx = tx - offset[i].x;
				ty = ty - offset[i].y;
				while(!(tx==x && ty==y))
				{
					count++;
					m_board[tx][ty] = m_curPlayer;
					tx = tx - offset[i].x;
					ty = ty - offset[i].y;
				}
				m_operStack[m_operStackTop].changeCount[i] = count;
			}
			else
				m_operStack[m_operStackTop].changeCount[i] = 0;
		}
		else
			m_operStack[m_operStackTop].changeCount[i] = 0;
	}
	m_operStack[m_operStackTop].curPlayer = m_curPlayer;
	m_operStack[m_operStackTop].point.x = x;
	m_operStack[m_operStackTop].point.y = y;
	++m_operStackTop;
	m_operStack[m_operStackTop].point.x = NODEF;
	m_curPlayer = rivalPlayer;
	if (m_operStackTop >= m_boardLength*m_boardLength-4) return 1;
	if(IsNoStep())			//如果对方已经没棋可走了，则继续走棋
	{
		m_curPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;
		if(IsNoStep())		// 如果自己也没棋可走了，则结束一盘棋
		 	return 1;
		else
		 	return 2;	
	}
	return 0;
}

// 当前点是否合法,不合法返回0，合法返回能转变子的个数
int HuiReversiMain::IsRight(int x, int y)
{
	int i, tx, ty, changeCount, totalCount=0;

	if(GetChessman(x, y) != NO) return 0;
	int rivalPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;

	for(i=0; i<8; i++)
	{
		changeCount = 0;
		tx = x + offset[i].x;
		ty = y + offset[i].y;
		if (IsRightRange(tx, ty) && m_board[tx][ty]==rivalPlayer)
		{	
			changeCount++;
			do
			{
				changeCount++;
				tx = tx + offset[i].x;
				ty = ty + offset[i].y;
			}while(IsRightRange(tx,ty) && m_board[tx][ty]==rivalPlayer);
			if(IsRightRange(tx,ty) && m_board[tx][ty]==m_curPlayer)
				totalCount += changeCount - 1;
		}
	}
	return totalCount;
}

//当前走棋的一方是否已经没棋可走了
BOOL HuiReversiMain::IsNoStep()
{
	int i,j;

	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			if (m_board[i][j] == NO) 
				if(IsRight(i,j)) return FALSE;
	return true;
}

//游戏是否已经结束
BOOL HuiReversiMain::IsGameOver()
{
	if (!IsNoStep())
		return false;
	m_curPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;

	if(!IsNoStep())
	{
		m_curPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;
		return false;
	}
	else
	{
		m_curPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;
		return true;
	}
}

//悔棋
BOOL HuiReversiMain::Undo()
{
	int i, j, x, y, tx, ty;
	int rivalPlayer;

	if (m_operStackTop==0) return false;
	--m_operStackTop;
	x = m_operStack[m_operStackTop].point.x;
	y = m_operStack[m_operStackTop].point.y;
	m_board[x][y] = NO;
	rivalPlayer = (m_operStack[m_operStackTop].curPlayer == BLACK) ? WHITE : BLACK;

	for(i=0; i<8; i++)
	{
		tx = x;
		ty = y;
		for(j=0; j<m_operStack[m_operStackTop].changeCount[i]; j++)
		{
			tx = tx + offset[i].x;
			ty = ty + offset[i].y;
			m_board[tx][ty] = rivalPlayer;
		}
	}
	m_curPlayer = m_operStack[m_operStackTop].curPlayer;
	return true;
}

//撤销悔棋
BOOL HuiReversiMain::Redo()
{
	int i, j, x, y, tx, ty;

	if (m_operStack[m_operStackTop].point.x == NODEF) return false;
	x = m_operStack[m_operStackTop].point.x;
	y = m_operStack[m_operStackTop].point.y;
	m_curPlayer = m_operStack[m_operStackTop].curPlayer;
	m_board[x][y] = m_curPlayer;

	for(i=0; i<8; i++)
	{
		tx=x;
		ty=y;
		for(j=0;j<m_operStack[m_operStackTop].changeCount[i];j++)
		{
			tx = tx + offset[i].x;
			ty = ty + offset[i].y;
			m_board[tx][ty] = m_curPlayer;
		}
	}
	m_operStackTop++;
	m_curPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;
	if (IsNoStep())
		m_curPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;
	return true;
}

//返回当前黑棋子数
int HuiReversiMain::GetBlackCount()
{
	int i, j, count;

	count = 0;
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<= m_boardLength; j++)
			if (m_board[i][j]==BLACK) count++;
	return count;
}

//返回当前白棋子数
int HuiReversiMain::GetWhiteCount()
{
	int i, j, count;

	count = 0;
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			if (m_board[i][j]==WHITE) count++;
	return count;
}

//得到最后一步走的位置，如果还没走返回FALSE
BOOL HuiReversiMain::GetLastStep(POINT * point)
{
	if(m_operStackTop>0)
	{
		point->x = m_operStack[m_operStackTop-1].point.x;
		point->y = m_operStack[m_operStackTop-1].point.y;
		return TRUE;
	}
	return FALSE;
}

//给出一点的x,y坐标，返回将要改变的点的指针列队和点的数目
void HuiReversiMain::GetChangePoint(int x, int y, POINT * point)
{
	int i, tx, ty, changeCount, index;
	int rivalPlayer;

	index = 0;
	rivalPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;

	for(i=0; i<8; i++)
	{
		changeCount = 0;
		tx = x + offset[i].x;
		ty = y + offset[i].y;
		if (IsRightRange(tx, ty) && m_board[tx][ty]==rivalPlayer)
		{	
			changeCount++;
			do
			{
				changeCount++;
				tx = tx + offset[i].x;
				ty = ty + offset[i].y;
			}while(IsRightRange(tx, ty) && m_board[tx][ty]==rivalPlayer);
			if(IsRightRange(tx, ty) && m_board[tx][ty]==m_curPlayer)
			{
				for(changeCount--; changeCount>0; changeCount--)
				{
					tx = tx - offset[i].x;
					ty = ty - offset[i].y;
					point[index].x = tx;
					point[index].y = ty;
					index++;
				}
			}
		}
	}
}