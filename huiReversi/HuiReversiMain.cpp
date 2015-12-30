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

const char * const HuiReversiMain::ver="Ħ��֮�Ժڰ������1.20��  ����:���  OICQ:6545823";
const BYTE HuiReversiMain::nVerNum1 = 1;		//���汾��
const BYTE HuiReversiMain::nVerNum2 = 20;		//���汾��


// ���캯��
HuiReversiMain::HuiReversiMain(int startMode)
:m_operStackTop(0), m_curPlayer(BLACK), m_boardLength(BOARD_LENGTH),
 m_chessCount(BOARD_LENGTH*BOARD_LENGTH-4)
{
	int i,j;

	// �������
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			m_board[i][j] = NO;

	// �����ʷ��¼��ջ
	for(i=0; i<m_chessCount+1; i++)
		m_operStack[i].point.x = NODEF;

	// ����startMode�趨���̵Ŀ���
	switch(startMode)
	{
	case 1:					// �Ϻ��°�
		m_board[4][4] = BLACK;
		m_board[4][5] = BLACK;
		m_board[5][4] = WHITE;
		m_board[5][5] = WHITE;
		break;
	case 2:					// �ϰ��º�
		m_board[4][4] = WHITE;
		m_board[4][5] = WHITE;
		m_board[5][4] = BLACK;
		m_board[5][5] = BLACK;
		break;
	case 3:					// �������º�
		m_board[4][4] = BLACK;
		m_board[4][5] = WHITE;
		m_board[5][4] = WHITE;
		m_board[5][5] = BLACK;
		break;
	case 4:					// �������°�
		m_board[4][4] = WHITE;
		m_board[4][5] = BLACK;
		m_board[5][4] = BLACK;
		m_board[5][5] = WHITE;
		break;
	default:				// Ĭ��ֵΪ�������º�
		m_board[4][4] = BLACK;
		m_board[4][5] = WHITE;
		m_board[5][4] = WHITE;
		m_board[5][5] = BLACK;
		break;
	}
}

// �������캯��
HuiReversiMain::HuiReversiMain (HuiReversiMain & reversi)
:m_operStackTop(reversi.m_operStackTop), m_curPlayer(reversi.m_curPlayer),
 m_boardLength(reversi.m_boardLength), m_chessCount(reversi.m_chessCount)
{
	int i,j;

	// ��������
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			m_board[i][j] = reversi.m_board[i][j];

	// ������ʷ��¼��ջ
	for(i=0; i<m_chessCount+1; i++)
		m_operStack[i] = reversi.m_operStack[i];
}

// Ԥֵ����
HuiReversiMain & HuiReversiMain::operator=(const HuiReversiMain & reversi)
{
	int i,j;

	m_operStackTop = reversi.m_operStackTop;
	m_curPlayer = reversi.m_curPlayer;
	m_boardLength = reversi.m_boardLength;
	m_chessCount = reversi.m_chessCount;

	//��������
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			m_board[i][j] = reversi.m_board[i][j];

	//������ʷ��¼��ջ
	for(i=0; i<m_chessCount+1; i++)
		m_operStack[i] = reversi.m_operStack[i];

	return *this;
}

//��������
HuiReversiMain::~HuiReversiMain()
{
}

// ���¿�ʼһ�����
void HuiReversiMain::ReStart(int startMode)
{
	int i,j;

	m_operStackTop = 0;
	m_curPlayer = BLACK;
	m_boardLength = BOARD_LENGTH;
	m_chessCount = BOARD_LENGTH*BOARD_LENGTH-4;

	// �������
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			m_board[i][j] = NO;

	// �����ʷ��¼��ջ
	for(i=0; i<m_chessCount+1; i++)
		m_operStack[i].point.x = NODEF;

	// ����startMode�趨���̵Ŀ���
	switch(startMode)
	{
	case 1:					// �Ϻ��°�
		m_board[4][4] = BLACK;
		m_board[4][5] = BLACK;
		m_board[5][4] = WHITE;
		m_board[5][5] = WHITE;
		break;
	case 2:					// �ϰ��º�
		m_board[4][4] = WHITE;
		m_board[4][5] = WHITE;
		m_board[5][4] = BLACK;
		m_board[5][5] = BLACK;
		break;
	case 3:					// �������º�
		m_board[4][4] = BLACK;
		m_board[4][5] = WHITE;
		m_board[5][4] = WHITE;
		m_board[5][5] = BLACK;
		break;
	case 4:					// �������°�
		m_board[4][4] = WHITE;
		m_board[4][5] = BLACK;
		m_board[5][4] = BLACK;
		m_board[5][5] = WHITE;
		break;
	default:				// Ĭ��ֵΪ�������º�
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

//��һ����,����ֵ:�õ�����(-1);����(0);��һ����ʤ(1);û�������(2)
int HuiReversiMain::NextStep(int x,int y)
{
	int i, count;
	int tx, ty;			
	int rivalPlayer;	//��ǰû���������ҵ���ɫ

	//�����λ�ò��Ϸ�,�򷵻�
	if (!IsRight(x,y)) return -1;

	rivalPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;
	m_board[x][y] = m_curPlayer;

	for(i=0; i<8; i++)		//��8�������ϲ鿴�ܷ�ת��Է�������
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
	if(IsNoStep())			//����Է��Ѿ�û������ˣ����������
	{
		m_curPlayer = (m_curPlayer==BLACK) ? WHITE : BLACK;
		if(IsNoStep())		// ����Լ�Ҳû������ˣ������һ����
		 	return 1;
		else
		 	return 2;	
	}
	return 0;
}

// ��ǰ���Ƿ�Ϸ�,���Ϸ�����0���Ϸ�������ת���ӵĸ���
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

//��ǰ�����һ���Ƿ��Ѿ�û�������
BOOL HuiReversiMain::IsNoStep()
{
	int i,j;

	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			if (m_board[i][j] == NO) 
				if(IsRight(i,j)) return FALSE;
	return true;
}

//��Ϸ�Ƿ��Ѿ�����
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

//����
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

//��������
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

//���ص�ǰ��������
int HuiReversiMain::GetBlackCount()
{
	int i, j, count;

	count = 0;
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<= m_boardLength; j++)
			if (m_board[i][j]==BLACK) count++;
	return count;
}

//���ص�ǰ��������
int HuiReversiMain::GetWhiteCount()
{
	int i, j, count;

	count = 0;
	for(i=1; i<=m_boardLength; i++)
		for(j=1; j<=m_boardLength; j++)
			if (m_board[i][j]==WHITE) count++;
	return count;
}

//�õ����һ���ߵ�λ�ã������û�߷���FALSE
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

//����һ���x,y���꣬���ؽ�Ҫ�ı�ĵ��ָ���жӺ͵����Ŀ
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