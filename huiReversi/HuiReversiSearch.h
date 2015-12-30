// huireversisearch.h: interface for the HuiReversiSearch class.
//Ħ��֮�Ժڰ������(������Ļ���)
//////////////////////////////////////////////////////////////////////

#if !defined(_HUIREVERSISEARCH_H_INCLUDED_)
#define _HUIREVERSISEARCH_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_BEST_MOVE_CHANGE	  WM_USER+1050   // �����߷��ı����Ϣ
#define WM_SEARCH_PLAN		  WM_USER+1060   // �����������������߷��Ľ�����Ϣ
// ������Ϣʱ�Ĳ���
#define SEARCH_RANGE	1	// �����ķ�Χ
#define SEARCH_POS		2	// ��ǰ��������ֵ
#define SEARCH_POS_MAX	3	// ���ֵ


class HuiReversiSearch : public CObject  
{
public:
	HuiReversiSearch();
	virtual ~HuiReversiSearch();
	virtual POINT FindBestStep(HuiReversiMain & reversi) = 0;	//�ҵ�һ����õ��߷�
	inline void SetLayer(int layer) {m_nLayer = layer;}	//���ò���
	inline int  GetLayer() {return m_nLayer;}	//��ȡ����
	inline void SetGetValue(HuiReversiGetValue * pGetValue) {m_pGetValue = pGetValue;}	//�趨��ֵ��ָ��
	inline void SetMove(HuiReversiMove * pMove) {m_pMove = pMove;}	// �趨�߷�������ָ��
	inline void SetSearchPlanWnd(HWND hWnd) {m_hWndPlan = hWnd;}	// �趨��������������Ϣ�Ĵ��ھ��
	inline void SetBestMoveWnd(HWND hWnd) {m_hWndBestMove = hWnd;}	// �趨���������߷��ı����Ϣ�Ĵ��ھ��
	inline POINT GetBestStep() {return m_bestStep;}		// ������ŵ��߷�

public:
	BOOL  m_bExit;			// ֹͣ���ѵı�־
protected:
	HWND  m_hWndPlan;		// ��������������Ϣ�Ĵ��ھ��
	HWND  m_hWndBestMove;	// ���������߷��ı����Ϣ�Ĵ��ھ��
	int   m_nLayer;			// �����Ĳ���
	int   m_nCurrentLayer;	// ��ǰ�����Ĳ���
	POINT m_bestStep;		// ��¼���ŵ��߷�
	HuiReversiMain m_reversi;	// ��ǰ��ʱ��HuiReversiMain��
	HuiReversiMove * m_pMove;	// �߷�������ָ��
	HuiReversiGetValue * m_pGetValue;	//��ֵ���ָ��

protected:
	int IsGameOver();	//�Ƿ���Ϸ����,û��������0,�������ط�0ֵ(����Сֵ��ʽ)
	int IsGameOver_Negative();	//�Ƿ���Ϸ����,û��������0,�������ط�0ֵ(������ֵ��ʽ)
	inline void Move(int x, int y)	//��һ����
		{m_reversi.NextStep(x, y);}
	inline void ReMove()		//��ԭһ����
		{m_reversi.Undo();}
};

#endif // !defined(_HUIREVERSISEARCH_H_INCLUDED_)
