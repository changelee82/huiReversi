// HuiReversiMain.h: interface for the HuiReversiMain class.
//Ħ��֮�Ժڰ������
//////////////////////////////////////////////////////////////////////

#if !defined(_HUIREVERSIMAIN_H_INCLUDED_)
#define _HUIREVERSIMAIN_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BOARD_LENGTH	8	//���̵ı߳�

#define	NODEF	-1		//û�ж���
#define	NO		 0		//û������
#define	BLACK	 1		//��ɫ����
#define	WHITE	 2		//��ɫ����


struct SOperate		//������¼
{
	POINT point;		//���ӵ�
	int curPlayer;		//���ӵ���ɫ
	int changeCount[8];	//8�������ϱ�ת����ɫ������
};

//POINT����������ĳһ���ӵ������
const POINT offset[8]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};	//�˸������λ������


class HuiReversiMain : public CObject  
{
	DECLARE_SERIAL(HuiReversiMain)
// ���졢��������
public:
	HuiReversiMain (int = 1);						//1ΪĬ�Ͽ��֣�(1:�Ϻ��°�,2:�ϰ��º�,3:�������º�,4:�������°�)
	HuiReversiMain (HuiReversiMain &);				//�������캯��
	HuiReversiMain & operator=(const HuiReversiMain &);	//Ԥֵ����
	virtual	~HuiReversiMain();						//��������

// ����
protected:
	int	m_boardLength;		//���̵ı߳�
	int	m_chessCount;		//�����ϵ���������
	int	m_curPlayer;		//��ǰ��˭������
	int	m_operStackTop;		//ָ��������λ�õĶ�ջ����λ��
	int	m_board[BOARD_LENGTH+1][BOARD_LENGTH+1];	//��������
	SOperate	m_operStack [BOARD_LENGTH * BOARD_LENGTH - 3];		//�����ʷ��¼�Ķ�ջ
public:
	static	const char * const ver;		//�汾��Ϣ
	static	const BYTE nVerNum1;		//���汾��
	static	const BYTE nVerNum2;		//���汾��

//����
public:
	virtual	void	Serialize(CArchive& ar);	// ���л�����,��ȡ����
	inline	int	GetCurPlayer() {return m_curPlayer;}		// ���ص�ǰ��˭����(black��white)
	inline	int	GetBoardLength() {return m_boardLength;}	// �������̵ı߳�
	void	ReStart(int startMode);			// ���¿�ʼһ�����
    int		NextStep(int, int);				// ��һ����,����ֵ:�õ�����(-1);����(0);��һ����ʤ(1);û�������(2)
	int		IsRight(int, int);				// ��ǰ���Ƿ�Ϸ�,���Ϸ�����0���Ϸ�������ת���ӵĸ���
	BOOL	GetLastStep(POINT * point);		// �õ����һ���ߵ�λ�ã������û�߷���FALSE
	BOOL	Undo();		//���壬����ɹ��򷵻�TRUE
	BOOL	Redo();		//�������壬����ɹ��򷵻�TRUE
	BOOL	IsCanUndo() {return (m_operStackTop != 0);}		// �Ƿ���Ի���
	BOOL	IsCanRedo() {return (m_operStack[m_operStackTop].point.x != NODEF);}	//�Ƿ���Գ�������
	int		GetBlackCount();		//���ص�ǰ��������
	int		GetWhiteCount();		//���ص�ǰ��������
	int		GetStepCount() {return m_operStackTop;}		// �������ߵĲ���
	BOOL	IsNoStep();		//��ǰ�����һ���Ƿ��Ѿ�û�������
	BOOL	IsGameOver();	//��Ϸ�Ƿ��Ѿ�����
	void	GetChangePoint(int x, int y, POINT * point);	//����һ���x,y���꣬���ؽ�Ҫ�ı�ĵ��ָ���жӺ͵����Ŀ
	void	GetStepPoint(int step, POINT * point) 	//�õ���step�����ߵĵ�
				{point->x=m_operStack[step].point.x; point->y=m_operStack[step].point.y; }
	inline	BOOL IsRightRange(int x,int y)		//��Χ�Ƿ���ȷ
				{return x>=1 && x<=m_boardLength && y>=1 && y<=m_boardLength;}	//������λ���Ƿ���ȷ:��ȷ(true)
	inline	int GetChessman(int x, int y)		//���ظ���λ�������ӵ���ɫ(BLACK,WHITE,NO����NODEF)
				{return IsRightRange(x,y) ? m_board[x][y] : NODEF;}	
};

#endif // !defined(_HUIREVERSIMAIN_H_INCLUDED_)
