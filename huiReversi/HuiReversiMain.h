// HuiReversiMain.h: interface for the HuiReversiMain class.
//摩羯之辉黑白棋组件
//////////////////////////////////////////////////////////////////////

#if !defined(_HUIREVERSIMAIN_H_INCLUDED_)
#define _HUIREVERSIMAIN_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BOARD_LENGTH	8	//棋盘的边长

#define	NODEF	-1		//没有定义
#define	NO		 0		//没有棋子
#define	BLACK	 1		//黑色棋子
#define	WHITE	 2		//白色棋子


struct SOperate		//操作记录
{
	POINT point;		//落子点
	int curPlayer;		//落子的颜色
	int changeCount[8];	//8个方向上被转变颜色的子数
};

//POINT代表棋盘上某一落子点的坐标
const POINT offset[8]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};	//八个方向的位置增量


class HuiReversiMain : public CObject  
{
	DECLARE_SERIAL(HuiReversiMain)
// 构造、析构函数
public:
	HuiReversiMain (int = 1);						//1为默认开局，(1:上黑下白,2:上白下黑,3:左上右下黑,4:左上右下白)
	HuiReversiMain (HuiReversiMain &);				//拷贝构造函数
	HuiReversiMain & operator=(const HuiReversiMain &);	//预值操作
	virtual	~HuiReversiMain();						//析构函数

// 属性
protected:
	int	m_boardLength;		//棋盘的边长
	int	m_chessCount;		//棋盘上的棋子总数
	int	m_curPlayer;		//当前该谁走子了
	int	m_operStackTop;		//指向存放落子位置的堆栈顶的位置
	int	m_board[BOARD_LENGTH+1][BOARD_LENGTH+1];	//棋盘数组
	SOperate	m_operStack [BOARD_LENGTH * BOARD_LENGTH - 3];		//存放历史纪录的堆栈
public:
	static	const char * const ver;		//版本信息
	static	const BYTE nVerNum1;		//主版本号
	static	const BYTE nVerNum2;		//副版本号

//操作
public:
	virtual	void	Serialize(CArchive& ar);	// 序列化操作,存取数据
	inline	int	GetCurPlayer() {return m_curPlayer;}		// 返回当前该谁走棋(black或white)
	inline	int	GetBoardLength() {return m_boardLength;}	// 返回棋盘的边长
	void	ReStart(int startMode);			// 重新开始一个棋局
    int		NextStep(int, int);				// 走一步棋,返回值:该点有子(-1);正常(0);有一方得胜(1);没棋可走了(2)
	int		IsRight(int, int);				// 当前点是否合法,不合法返回0，合法返回能转变子的个数
	BOOL	GetLastStep(POINT * point);		// 得到最后一步走的位置，如果还没走返回FALSE
	BOOL	Undo();		//悔棋，如果成功则返回TRUE
	BOOL	Redo();		//撤销悔棋，如果成功则返回TRUE
	BOOL	IsCanUndo() {return (m_operStackTop != 0);}		// 是否可以悔棋
	BOOL	IsCanRedo() {return (m_operStack[m_operStackTop].point.x != NODEF);}	//是否可以撤销悔棋
	int		GetBlackCount();		//返回当前黑棋子数
	int		GetWhiteCount();		//返回当前白棋子数
	int		GetStepCount() {return m_operStackTop;}		// 返回已走的步数
	BOOL	IsNoStep();		//当前走棋的一方是否已经没棋可走了
	BOOL	IsGameOver();	//游戏是否已经结束
	void	GetChangePoint(int x, int y, POINT * point);	//给出一点的x,y坐标，返回将要改变的点的指针列队和点的数目
	void	GetStepPoint(int step, POINT * point) 	//得到第step步所走的点
				{point->x=m_operStack[step].point.x; point->y=m_operStack[step].point.y; }
	inline	BOOL IsRightRange(int x,int y)		//范围是否正确
				{return x>=1 && x<=m_boardLength && y>=1 && y<=m_boardLength;}	//给出的位置是否正确:正确(true)
	inline	int GetChessman(int x, int y)		//返回给定位置上棋子的颜色(BLACK,WHITE,NO或是NODEF)
				{return IsRightRange(x,y) ? m_board[x][y] : NODEF;}	
};

#endif // !defined(_HUIREVERSIMAIN_H_INCLUDED_)
