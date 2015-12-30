#if !defined(_BOARDVIEW_H_INCLUDED_)
#define _BOARDVIEW_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoardView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBoardView view
#include "huiReversi\HuiReversiMain.h"
#include "huiReversi\HuiReversiMove.h"
#include "huiReversi\HuiReversiGetValue.h"
#include "huiReversi\HuiSearchAlphaBeta.h"

#define WM_STATE_CHANGE    WM_USER+1220     // �����̵�״̬�����ı�ʱ���͸��������ڵ���Ϣ
#define WM_FIND_BEST_MOVE  WM_USER+1225     // ������������������߷����͸�������ͼ����Ϣ
#define WM_PROMPT_BEST_MOVE  WM_USER+1230   // ��������ʾ��������߷����͸�������ͼ����Ϣ

// �ڰ��崰�ڳߴ����
#define HEIGHT_TOP		20		// �ϱ߱��������ڸ߶�
#define WIDTH_LEFT		20		// ��߱��������ڿ��
#define WIDTH_BOARD		360		// ���̴��ڿ��(�߶ȺͿ����ͬ)
#define WIDTH_GRID		45		// һ����Ԫ��Ŀ��
#define WIDTH_POINT		5		// �������ĸ�����Ŀ��

class CBoardView : public CView
{
public:
	CBoardView();
	virtual ~CBoardView();
	DECLARE_DYNCREATE(CBoardView)

// ����
public:
	CToolTipCtrl  m_ToolTip;	 // ��ʾ������
	BOOL	m_bShowTop;			 // ���������־���Ƿ�ɼ�
	BOOL	m_bShowLeft;		 // ���������־���Ƿ�ɼ�
	BOOL	m_bFlash;			 // ��ת����ʱ�Ƿ���ʾ����
	BOOL	m_bPlayer1;			 // �Ƿ������ִ����,TRUE�������,FALSE�������
	BOOL	m_bPlayer2;			 // �Ƿ������ִ����,TRUE�������,FALSE�������
	HWND	m_hWndReceive;		 // �����̵�״̬�����ı�ʱ������Ϣ���˴���

protected:
	HuiReversiMain     * m_pReversi;		 // �ڰ�������ָ��
	HuiReversiSearch   * m_pReversiSearch;	 // ��������ָ��
	HuiReversiMove     * m_pReversiMove;	 // �߷�������ָ��
	HuiReversiGetValue * m_pReversiGetValue; // ��ֵ����ָ��

	int		m_nNetPro;			 // �����ս���� (0-���������ս, 1-���ִ����, 2-���ִ����)
	int		m_nStartMode;		 // ����ģʽ (1-4)
	int		m_nLevel;			 // ��Ϸ�Ѷ� (������������ 5-9)
	BOOL	m_bShowBlueX;		 // �Ƿ���ʾ��ɫ�ġ�X��(�������ӵ�λ��)
	BOOL	m_bShowRedX;		 // �Ƿ���ʾ��ɫ�ġ�X��(�������������������ӵ�λ��)
	BOOL	m_bShowEmpty;		 // �Ƿ���ʾ��Ҫ�ı���ɫ������(�����߻�������)
	CPoint	m_curPoint;			 // ��ǰ������ڵ���������

	HANDLE	m_hLockEvent;		 // �������̵��¼�������״̬�򲻴���һЩ�¼�
	CPoint	m_bestPoint;		 // ��¼��ǰ�������������߷�
	// ����ʾ������صĲ���
	HANDLE	m_hStartPromptEvent; // �õ��Կ�ʼ��ʾ�����߷����¼�
	HANDLE	m_hPromptEvent;		 // ����������ʾ�����߷����¼�
	HANDLE	m_hPromptThread;	 // ������ʾ�����߷����߳̾��
	HWND	m_hWndPromptPlan;	 // ������ʾ�����߷��Ľ�����Ϣ�Ĵ��ھ��
	BOOL	m_bPromptExit;		 // ������ʾ�����߷����߳̽����ı�־
	BOOL	m_bPromptOver;		 // �����Ƿ��Ѿ���������Ҫ��ʾ�������߷�
	// �����������صĲ���
	HANDLE	m_hStartThinkEvent;	 // �õ��Կ�ʼ���������߷����¼�
	HANDLE	m_hThinkEvent;		 // �����������������߷����¼�
	HANDLE	m_hThinkThread;		 // �������������߷����߳̾��
	HWND	m_hWndThinkPlan;	 // �������������߷��Ľ�����Ϣ�Ĵ��ھ��
	BOOL	m_bThinkExit;		 // �������������߷����߳̽����ı�־

	int		m_width;		// ����ͼ�Ŀ��
	int		m_height;		// ����ͼ�ĸ߶�
	int		m_zoomIndex;	// ���̵ķŴ���
	static float Zoom[3];	// �Ŵ�ı����б�
	static int ZoomCount;	// �Ŵ�ı����б�Ԫ�ص�����

	// ����ı����Ǵ洢ͼƬ��
	CDC * m_pBoardDC;		// ����
	CDC * m_pInitBoardDC;	// ��ʼʱ������
	CDC * m_pBlackDC;		// ����ͼƬ
	CDC * m_pWhiteDC;		// ����ͼƬ
	CDC * m_pBlackEmptyDC;	// ��ĺ���ͼƬ
	CDC * m_pWhiteEmptyDC;	// ��İ���ͼƬ
	CDC * m_pXBlueDC;		// ��ɫ�ġ�X��ͼƬ
	CDC * m_pXRedDC;		// ��ɫ�ġ�X��ͼƬ
	CDC * m_pPointDC;		// �������ĸ������ͼƬ
	CDC * m_pReversiDC;		// �洢������ͼ��(��20��ͼ��)

	// ��ע����б������һ����Ϸʱ������
	static const char s_profileHeading[];	// ����ͷ
	static const char s_startMode[];		// ����ģʽ(1-4)
	static const char s_level[];			// ��Ϸ�Ѷ�(������������ 5-9)
	static const char s_flash[];			// ����Ч��
	static const char s_showTop[];			// �����ϱ߱�־��
	static const char s_showLeft[];			// ������߱�־��
	static const char s_bPlayer1[];			// ���ִ����
	static const char s_bPlayer2[];			// ���ִ����
	
// ����
public:
	float GetZoom(){return Zoom[m_zoomIndex];};			// ���طŴ���
	void Zoomin();			// �Ŵ�����
	void Zoomout();			// ��С����
	BOOL CanZoomin();		// �����Ƿ���ԷŴ�����
	BOOL CanZoomout();		// �����Ƿ������С����
	int  GetCurWidth();		// �������̴��ڵ�ǰ����Ч���
	int  GetCurHeight();	// �������̴��ڵ�ǰ����Ч�߶�

	BOOL Undo();		// ����
	BOOL Redo();		// ��������
	BOOL IsCanUndo();	// �Ƿ���Ի���
	BOOL IsCanRedo();	// �Ƿ���Գ�������
	BOOL SetStartMode(int nMode);	// �趨����ģʽ(1-4)�����������򷵻�FALSE
	int  GetStartMode() {return m_nStartMode;}	// ��ÿ���ģʽ
	BOOL SetLevel(int nLevel);		// ������Ϸ�Ѷ�(1-10)��ʧ���򷵻�FALSE
	int  GetLevel() {return m_nLevel;}			// �����Ϸ�Ѷ�
	int  GetNetPro() {return m_nNetPro;}		// ��������ս����
	BOOL GetPromptInfo() {return m_bShowRedX;}	// �����ʾ��Ϣ����ʾ״̬
	void ShowPrompt(BOOL bShow)					// �趨��ʾ��Ϣ����ʾ״̬
			{m_bShowRedX = bShow;}
	int	 GetStepCount()							// ����������Ĳ���
			{return m_pReversi->GetStepCount();}

	void GetInfoFromReg();		// ��ע����ж�ȡ��Ϸ����
	void SetInfoToReg();		// ������Ϸ������ע���
	void ComputerFindMove();	// �õ���Ѱ��һ����
	void ComputerMove();		// �õ�����һ����
	void StartNewGame();		// ��ʼһ���µ���Ϸ
	void PointToBoard(CPoint & point);			// ���������ת������������(��Χ1-8)��������곬����Χ���򷵻�(0, 0)
	int  MovePoint(int x, int y);				// ��һ����
	void ShowFlash(int x, int y, int count);	// ��ʾ����

	void StartupThread();	// ���������߳�
	void CloseThread();		// �ر������߳�
	void SendChangeMsg();	// �����̵�״̬�����ı�ʱ�����ô˺���������Ϣ��ָ������
	BOOL GetLockState();	// �õ���������״̬
	void StopSearch();		// ֹͣ���������߷�
	void StopSearchPrompt();	// ֹͣ������ʾ��Ϣ
	void SetPromptPlanWnd(HWND hWnd) {m_hWndPromptPlan = hWnd;}	// �趨������ʾ�����߷��Ľ�����Ϣ�Ĵ��ھ��
	void SetThinkPlanWnd(HWND hWnd) {m_hWndThinkPlan = hWnd;}	// �趨�������������߷��Ľ�����Ϣ�Ĵ��ھ��
	HWND GetPromptPlanWnd() {return m_hWndPromptPlan;}	// ��ý�����ʾ�����߷��Ľ�����Ϣ�Ĵ��ھ��
	HWND GetThinkPlanWnd() {return m_hWndThinkPlan;}	// ��ý������������߷��Ľ�����Ϣ�Ĵ��ھ��

protected:
	void BoardToDc(HuiReversiMain * pReversi=NULL);		// ���ڰ������ӳ�䵽�ڴ�DC

	static DWORD WINAPI ThinkThread(LPVOID pParam);		// �������������߷����߳�
	static DWORD WINAPI PromptThread(LPVOID pParam);	// ������ʾ�����߷����߳�

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoardView)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CBoardView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFindBestMove();		// ���������������߷������Ϣ������
	afx_msg void OnBestMoveChange();	// ���������߷��ı����Ϣ
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void Wait(DWORD dwTime);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_BOARDVIEW_H_INCLUDED_)
