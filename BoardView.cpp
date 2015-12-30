// BoardView.cpp : implementation file
//

#include "stdafx.h"
#include "HuiReversi.h"
#include "BoardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoardView
const char CBoardView::s_profileHeading[] = "����";
const char CBoardView::s_startMode[]	= "����ģʽ";
const char CBoardView::s_level[] = "��Ϸ�Ѷ�";
const char CBoardView::s_flash[] = "����Ч��";
const char CBoardView::s_showTop[] = "�ϱ߱�־��";
const char CBoardView::s_showLeft[] = "��߱�־��";
const char CBoardView::s_bPlayer1[] = "���ִ����";
const char CBoardView::s_bPlayer2[] = "���ִ����";

// �Ŵ�ı����б�
float CBoardView::Zoom[3] = {1.0, (float)1.2, (float)1.6};
int CBoardView::ZoomCount = 3;

IMPLEMENT_DYNCREATE(CBoardView, CView)

CBoardView::CBoardView()
{
	m_pReversi = new HuiReversiMain();			   // �ڰ���ָ��
	m_pReversiMove     = new HuiReversiMove();	   // �߷�������ָ��
	m_pReversiSearch   = new HuiSearchAlphaBeta(); // ��������ָ��
	m_pReversiGetValue = new HuiReversiGetValue(); // ��ֵ����ָ��
	// ���÷Ŵ���
	m_zoomIndex = 0;
	
	m_bShowTop = TRUE;		// ��ʼʱ�ϱ߱��������ڶ��ɼ�
	m_bShowLeft = TRUE;		// ��ʼʱ��߱��������ڶ��ɼ�
	
	m_bShowBlueX = FALSE;	// ��ʼʱ����ʾ��ɫ�ġ�X��
	m_bShowRedX  = TRUE;	// ��ʼʱ��ʾ��ɫ�ġ�X��
	m_bShowEmpty = FALSE;	// ��ʼʱ����ʾ��Ҫ�ı���ɫ������
	m_nNetPro    = 0;		// ��ʼʱ���������ս
	m_bPlayer1   = TRUE;	// ��ʼʱ�����ִ����
	m_bPlayer2   = FALSE;	// ��ʼʱ�ɵ���ִ����

	m_pBoardDC = NULL;
	m_hWndReceive = NULL;
	m_bThinkExit = FALSE;
	m_bPromptExit = FALSE;
	m_hWndPromptPlan = NULL;
	m_hWndThinkPlan = NULL;
	m_bPromptOver = FALSE;	// ��ʼ��Ϊ����û����������Ҫ��ʾ�������߷�
}

CBoardView::~CBoardView()
{
	if(m_pBoardDC != NULL)
	{
		delete m_pBoardDC;		// ����
		delete m_pInitBoardDC;	// ��ʼʱ������
		delete m_pBlackDC;		// ����ͼƬ
		delete m_pWhiteDC;		// ����ͼƬ
		delete m_pBlackEmptyDC;	// ��ĺ���ͼƬ
		delete m_pWhiteEmptyDC;	// ��İ���ͼƬ
		delete m_pXBlueDC;		// ��ɫ�ġ�X��ͼƬ
		delete m_pXRedDC;		// ��ɫ�ġ�X��ͼƬ
		delete m_pPointDC;		// �������ĸ������ͼƬ
		delete []m_pReversiDC;	// �洢������ͼ��(��20��ͼ��)
	}

	delete m_pReversi;
	delete m_pReversiMove;
	delete m_pReversiSearch;
	delete m_pReversiGetValue;

	CloseHandle(m_hLockEvent);
	CloseHandle(m_hStartThinkEvent);
	CloseHandle(m_hStartPromptEvent);
	CloseHandle(m_hThinkEvent);
	CloseHandle(m_hPromptEvent);
}

BEGIN_MESSAGE_MAP(CBoardView, CView)
	//{{AFX_MSG_MAP(CBoardView)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_MESSAGE(WM_FIND_BEST_MOVE, OnFindBestMove)
	ON_MESSAGE(WM_BEST_MOVE_CHANGE, OnBestMoveChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoardView drawing

void CBoardView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CBoardView diagnostics

#ifdef _DEBUG
void CBoardView::AssertValid() const
{
	CView::AssertValid();
}

void CBoardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBoardView message handlers

int CBoardView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ��ע����ж�ȡ��Ϸ����
	GetInfoFromReg();

	m_pReversi->ReStart(m_nStartMode);
	m_pReversiSearch->SetMove(m_pReversiMove);	// �����߷�������
	m_pReversiSearch->SetGetValue(m_pReversiGetValue);	//���ù�ֵ����
	SetLevel(m_nLevel);	// �����Ѷ�
	SendChangeMsg();

	BITMAP    bitmap ;
	CBitmap   bmptmp;
	CClientDC pDC(this);
	
	m_pBoardDC = new CDC;	// ����
	bmptmp.LoadBitmap(IDB_BOARD);
	m_pBoardDC->CreateCompatibleDC(&pDC);
	m_pBoardDC->SelectObject(&bmptmp);

	::GetObject ((HBITMAP)bmptmp, sizeof (BITMAP), &bitmap) ;
	// ���ñ���ͼ�ĳߴ�
	m_width  = bitmap.bmWidth;
	m_height = bitmap.bmHeight;

	m_pInitBoardDC = new CDC;	// ��ʼʱ������
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_BOARD);
	m_pInitBoardDC->CreateCompatibleDC(&pDC);
	m_pInitBoardDC->SelectObject(&bmptmp);
	m_pBlackDC = new CDC;		// ����
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_BLACK);
	m_pBlackDC->CreateCompatibleDC(&pDC);
	m_pBlackDC->SelectObject(&bmptmp);
	m_pWhiteDC = new CDC;		// ����
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_WHITE);
	m_pWhiteDC->CreateCompatibleDC(&pDC);
	m_pWhiteDC->SelectObject(&bmptmp);
	m_pBlackEmptyDC = new CDC;	// ��ĺ���ͼƬ
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_BLACK_EMPTY);
	m_pBlackEmptyDC->CreateCompatibleDC(&pDC);
	m_pBlackEmptyDC->SelectObject(&bmptmp);
	m_pWhiteEmptyDC = new CDC;	// ��İ���ͼƬ
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_WHITE_EMPTY);
	m_pWhiteEmptyDC->CreateCompatibleDC(&pDC);
	m_pWhiteEmptyDC->SelectObject(&bmptmp);
	m_pXBlueDC = new CDC;		// ��ɫ�ġ�X��ͼƬ
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_X_BLUE);
	m_pXBlueDC->CreateCompatibleDC(&pDC);
	m_pXBlueDC->SelectObject(&bmptmp);
	m_pXRedDC = new CDC;		// ��ɫ�ġ�X��ͼƬ
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_X_RED);
	m_pXRedDC->CreateCompatibleDC(&pDC);
	m_pXRedDC->SelectObject(&bmptmp);
	m_pPointDC = new CDC;		// �������ĸ������ͼƬ
	bmptmp.DeleteObject();
	bmptmp.LoadBitmap(IDB_BOARD_POINT);
	m_pPointDC->CreateCompatibleDC(&pDC);
	m_pPointDC->SelectObject(&bmptmp);
	
	m_pReversiDC = new CDC[20];		// ���ӷ�ת�Ķ���
	for(int i=0; i<20; i++)
	{
		bmptmp.DeleteObject();
		bmptmp.LoadBitmap(IDB_REVERSI_01+i);
		m_pReversiDC[i].CreateCompatibleDC(&pDC);
		m_pReversiDC[i].SelectObject(&bmptmp);
	}

	// �趨��ʾ����������
	LOGFONT lf;           //������״
	CFont fnt;

	lf.lfItalic = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfHeight = 0;
	lf.lfWidth  = 0;
	lf.lfEscapement  = 0;
	lf.lfOrientation = 0;
	lf.lfUnderline   = 0;
	lf.lfStrikeOut   = 0;
	lf.lfCharSet = ANSI_CHARSET;
	lf.lfOutPrecision  = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
	
	strcpy(lf.lfFaceName,"����");
    lf.lfItalic  = 0;
	lf.lfHeight  = 12;
	lf.lfWeight  = FW_LIGHT;
	lf.lfCharSet = GB2312_CHARSET;
	
	fnt.CreateFontIndirect(&lf);

	if(!m_ToolTip.Create(this))
	{
		TRACE0("Unable to create Tootips\n");
	}
	else
	{
		m_ToolTip.SetFont(&fnt);
		m_ToolTip.SetTipBkColor(RGB(255, 255, 255));
		m_ToolTip.SetTipTextColor(RGB(0, 0, 0));
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, USER_TOO_TIP_WIDTH);
		m_ToolTip.Activate(FALSE);
	}

	m_pReversiSearch->SetBestMoveWnd(GetSafeHwnd());

	m_hLockEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hStartThinkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hStartPromptEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hThinkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hPromptEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	StartupThread();

	SetTimer(1, 300, 0);	//�����õ�������Ķ�ʱ��
	return 0;
}

// ���������߳�
void CBoardView::StartupThread()
{
	DWORD threadID;
	m_pReversiSearch->m_bExit = FALSE;
	// �����������������߷����߳�
	m_bThinkExit = FALSE;
	m_hThinkThread = CreateThread(NULL, 0, ThinkThread, this, 0, &threadID);
	// ����������ʾ�����߷����߳�
	m_bPromptExit = FALSE;
	m_hPromptThread = CreateThread(NULL, 0, PromptThread, this, 0, &threadID);
}

// �ر������߳�
void CBoardView::CloseThread()
{
	DWORD result;
	m_pReversiSearch->m_bExit = TRUE;	// �˳�����
	// �رյ������������߷����߳�
	m_bThinkExit = TRUE;
	result = WaitForSingleObject(m_hThinkThread, INFINITE);
	CloseHandle(m_hThinkThread);
	// �رյ�����ʾ�����߷����߳�
	m_bPromptExit = TRUE;
	result = WaitForSingleObject(m_hPromptThread, INFINITE);
	CloseHandle(m_hPromptThread);
}

// �Ŵ�����
void CBoardView::Zoomin()
{
	if(m_zoomIndex+1 < ZoomCount)
	{
		m_zoomIndex = m_zoomIndex+1;
	}
}

// ��С����
void CBoardView::Zoomout()
{
	if(m_zoomIndex-1 >= 0)
	{
		m_zoomIndex = m_zoomIndex-1;
	}
}

// �����Ƿ���ԷŴ�����
BOOL CBoardView::CanZoomin()
{
	return m_zoomIndex+1 < ZoomCount;
}

// �����Ƿ������С����
BOOL CBoardView::CanZoomout()
{
	return m_zoomIndex > 0;
}

//�õ����̴��ڵ�ǰ�Ŀ��
int CBoardView::GetCurWidth()
{
	// �õ��Ŵ�ߴ�
	float zoom = GetZoom();
	// �õ��Ƿ����������
	int x = m_bShowLeft ? WIDTH_LEFT : 0;

	return int((WIDTH_BOARD+x)*zoom)+2;
}

// �õ����̴��ڵ�ǰ�ĸ߶�
int CBoardView::GetCurHeight()
{
	// �õ��Ŵ�ߴ�
	float zoom = GetZoom();
	// �õ��Ƿ������ϱ���
	int y = m_bShowTop ? HEIGHT_TOP : 0;
	
	return int((WIDTH_BOARD+y)*zoom)+2;
}

// �趨����ģʽ(1-4)
BOOL CBoardView::SetStartMode(int nMode)
{
	// �������
	if(nMode<1 || nMode>4)
		return FALSE;
	
	m_nStartMode = nMode;
	return TRUE;
}

// ������Ϸ�Ѷ�(1-10)
BOOL CBoardView::SetLevel(int nLevel)
{
	// �������
	if(nLevel<1 || nLevel>10)
		return FALSE;

	// ����״̬���������Ѷ�
	if(GetLockState())
		return FALSE;

	m_nLevel = nLevel;
	m_pReversiSearch->SetLayer(nLevel);
	return TRUE;
}

// ���������ת������������(��Χ1-8)��������곬����Χ���򷵻�(0, 0)
void CBoardView::PointToBoard(CPoint & point)
{
	int x, y;
	
	// �õ��Ŵ�ǰ�ĳߴ�
	float zoom = GetZoom();
	point.x = int(point.x/zoom);
	point.y = int(point.y/zoom);

	if(point.y-(m_bShowTop  ? HEIGHT_TOP : 0) < 0 ||
	   point.x-(m_bShowLeft ? WIDTH_LEFT : 0) < 0)
	{
		point.x = 0;
		point.y = 0;
		return;
	}

	x = (point.y-(m_bShowTop  ? HEIGHT_TOP : 0))/WIDTH_GRID+1;
	y = (point.x-(m_bShowLeft ? WIDTH_LEFT : 0))/WIDTH_GRID+1;
	point.x = x;
	point.y = y;
	if(!m_pReversi->IsRightRange(point.x, point.y))
	{
		point.x = 0;
		point.y = 0;
	}
}

// ���ڰ������ӳ�䵽�ڴ�DC
void CBoardView::BoardToDc(HuiReversiMain * pReversi)
{
	if(pReversi==NULL)
		pReversi = m_pReversi;

	// ���Ȼ����壬����Ϳ������ӵı�־(��ɫ�ġ�X��)
	int i, j;
	m_pBoardDC->BitBlt(0, 0, WIDTH_LEFT+WIDTH_BOARD, HEIGHT_TOP+WIDTH_BOARD, m_pInitBoardDC, 0, 0, SRCCOPY);
	for(i=1; i<=8; i++)
		for(j=1; j<=8; j++)
		{
			if(pReversi->GetChessman(i, j)==BLACK)
				m_pBoardDC->BitBlt((j-1)*WIDTH_GRID+WIDTH_LEFT, (i-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, m_pBlackDC, 0, 0, SRCCOPY);
			else if(pReversi->GetChessman(i, j)==WHITE)
				m_pBoardDC->BitBlt((j-1)*WIDTH_GRID+WIDTH_LEFT, (i-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, m_pWhiteDC, 0, 0, SRCCOPY);
			else if(pReversi->IsRight(i,j) && m_bShowBlueX)
			{	// ����ɫ�ġ�X���ͺ�ɫ�ġ�X��(�����߷�)
				if(m_bShowRedX && m_pReversiSearch->GetBestStep().x == i && m_pReversiSearch->GetBestStep().y == j)
					m_pBoardDC->BitBlt((j-1)*WIDTH_GRID+WIDTH_LEFT, (i-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, m_pXRedDC, 0, 0, SRCCOPY);
				else
					m_pBoardDC->BitBlt((j-1)*WIDTH_GRID+WIDTH_LEFT, (i-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, m_pXBlueDC, 0, 0, SRCCOPY);
			}
				
		}

	// ����Ҫ�ı���ɫ������(�����߻�������)
	int count;
	CPoint * pArray;
	CDC * playerDC;
	if(m_bShowEmpty && (count=pReversi->IsRight(m_curPoint.x, m_curPoint.y)))
	{
		pArray = new CPoint[count];
		pReversi->GetChangePoint(m_curPoint.x, m_curPoint.y, pArray);
		if(pReversi->GetCurPlayer()==BLACK)
			playerDC = m_pBlackEmptyDC;
		else
			playerDC = m_pWhiteEmptyDC;
		m_pBoardDC->BitBlt((m_curPoint.y-1)*WIDTH_GRID+WIDTH_LEFT, (m_curPoint.x-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, playerDC, 0, 0, SRCCOPY);
		for(i=0; i<count; i++)
			m_pBoardDC->BitBlt((pArray[i].y-1)*WIDTH_GRID+WIDTH_LEFT, (pArray[i].x-1)*WIDTH_GRID+HEIGHT_TOP, WIDTH_GRID, WIDTH_GRID, playerDC, 0, 0, SRCCOPY);	
		delete []pArray;
	}

	// �����������ϻ�һ����ɫ������
	CBrush * brush;
	CPoint point;
	CPen pen;
	CPen * pOldPen;
	pen.CreatePen(PS_SOLID, 2, RGB(255,255,0));	//����ɫ�����εĻ���
	if(pReversi->GetLastStep(&point))
	{
		brush = (CBrush *)m_pBoardDC->SelectStockObject(NULL_BRUSH);
		pOldPen = (CPen *)m_pBoardDC->SelectObject(&pen);
		m_pBoardDC->Rectangle(CRect((point.y-1)*WIDTH_GRID+WIDTH_LEFT+2, (point.x-1)*WIDTH_GRID+HEIGHT_TOP+2, (point.y-1)*WIDTH_GRID+WIDTH_LEFT+WIDTH_GRID-1, (point.x-1)*WIDTH_GRID+HEIGHT_TOP+WIDTH_GRID-1));
		m_pBoardDC->SelectObject(brush);
		m_pBoardDC->SelectObject(pOldPen);
	}

	// �����������ĸ�����
	m_pBoardDC->BitBlt(2*WIDTH_GRID+WIDTH_LEFT-WIDTH_POINT/2-1, 2*WIDTH_GRID+HEIGHT_TOP-WIDTH_POINT/2-1, WIDTH_POINT, WIDTH_POINT, m_pPointDC, 0, 0, SRCCOPY);
	m_pBoardDC->BitBlt(2*WIDTH_GRID+WIDTH_LEFT-WIDTH_POINT/2-1, 6*WIDTH_GRID+HEIGHT_TOP-WIDTH_POINT/2-1, WIDTH_POINT, WIDTH_POINT, m_pPointDC, 0, 0, SRCCOPY);
	m_pBoardDC->BitBlt(6*WIDTH_GRID+WIDTH_LEFT-WIDTH_POINT/2-1, 2*WIDTH_GRID+HEIGHT_TOP-WIDTH_POINT/2-1, WIDTH_POINT, WIDTH_POINT, m_pPointDC, 0, 0, SRCCOPY);
	m_pBoardDC->BitBlt(6*WIDTH_GRID+WIDTH_LEFT-WIDTH_POINT/2-1, 6*WIDTH_GRID+HEIGHT_TOP-WIDTH_POINT/2-1, WIDTH_POINT, WIDTH_POINT, m_pPointDC, 0, 0, SRCCOPY);
}

void CBoardView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// �õ��Ŵ�ߴ�
	float zoom = Zoom[m_zoomIndex];
	
	// �õ��Ƿ������ϱ���������
	int x, y;
	x = m_bShowLeft ? 0 : WIDTH_LEFT;
	y = m_bShowTop  ? 0 : HEIGHT_TOP;
	
	//���Ȼ���ɫ�ı߿�
	CBrush * brush;
	CPen pen;
	CPen * pOldPen;
	pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	brush=(CBrush *)dc.SelectStockObject(NULL_BRUSH);
	pOldPen=(CPen *)dc.SelectObject(&pen);
	dc.Rectangle(0, 0, int((m_width-x)*zoom)+2, int((m_height-y)*zoom)+2);
	dc.SelectObject(brush);
	dc.SelectObject(pOldPen);

	BoardToDc(m_pReversi);
	// ���Ʊ�����
	dc.StretchBlt(1, 1, int(m_width*zoom), int(m_height*zoom), m_pBoardDC, 
				  x, y, m_width, m_height, SRCCOPY);
}

// ��ʾ����
void CBoardView::ShowFlash(int x, int y, int count)
{
	int i, n;
	CPoint * pArray;
	CClientDC dc(this);

	// �õ��Ŵ�ߴ�
	float zoom = Zoom[m_zoomIndex];
	// �õ��Ƿ������ϱ���������
	int xOrigin, yOrigin;
	xOrigin = (m_bShowLeft ? int(WIDTH_LEFT*zoom) : 0) + 1;
	yOrigin = (m_bShowTop  ? int(HEIGHT_TOP*zoom) : 0) + 1;

	if (count<1) return;
	pArray = new CPoint[count];
	m_pReversi->GetChangePoint(x, y, pArray);
	if(m_pReversi->GetCurPlayer()==BLACK)
	{
		dc.StretchBlt(int((y-1)*WIDTH_GRID*zoom)+xOrigin, int((x-1)*WIDTH_GRID*zoom)+yOrigin, int(WIDTH_GRID*zoom), int(WIDTH_GRID*zoom), m_pBlackDC, 0, 0, WIDTH_GRID, WIDTH_GRID, SRCCOPY);
		for(i=15; i>=0; i--)
		{
			for(n=0; n<count; n++)
				dc.StretchBlt(int((pArray[n].y-1)*WIDTH_GRID*zoom)+xOrigin, int((pArray[n].x-1)*WIDTH_GRID*zoom)+yOrigin, int(WIDTH_GRID*zoom), int(WIDTH_GRID*zoom), &m_pReversiDC[i], 0, 0, WIDTH_GRID, WIDTH_GRID, SRCCOPY);
	//		::Sleep(40);
			Wait(40);
		}
	}
	else
	{
		dc.StretchBlt(int((y-1)*WIDTH_GRID*zoom)+xOrigin, int((x-1)*WIDTH_GRID*zoom)+yOrigin, int(WIDTH_GRID*zoom), int(WIDTH_GRID*zoom), m_pWhiteDC, 0, 0, WIDTH_GRID, WIDTH_GRID, SRCCOPY);
		for(i=5; i<20; i++)
		{
			for(n=0; n<count; n++)
				dc.StretchBlt(int((pArray[n].y-1)*WIDTH_GRID*zoom)+xOrigin, int((pArray[n].x-1)*WIDTH_GRID*zoom)+yOrigin, int(WIDTH_GRID*zoom), int(WIDTH_GRID*zoom), &m_pReversiDC[i], 0, 0, WIDTH_GRID, WIDTH_GRID, SRCCOPY);
	//		::Sleep(40);
			Wait(40);
		}
	}
	delete []pArray;
}

// ��һ����
int CBoardView::MovePoint(int x, int y)
{
	int count, isWin;
	int curPlayer;
	CString strWin, strTemp;
	
	curPlayer = m_pReversi->GetCurPlayer();
	count = m_pReversi->IsRight(x, y);
	if(m_bFlash)
		ShowFlash(x, y, count);		//��ʾ����
	isWin = m_pReversi->NextStep(x, y);
	Invalidate(FALSE);
	UpdateWindow();

	// �����Ϸ�����������ʾ
	if(isWin==1)
	{
		if(m_pReversi->GetBlackCount() > m_pReversi->GetWhiteCount())
		{
			strTemp.LoadString(IDS_BLACK_WIN);
			strWin.Format(strTemp.GetBuffer(16), m_pReversi->GetBlackCount()-m_pReversi->GetWhiteCount());
		}
		else if(m_pReversi->GetBlackCount() < m_pReversi->GetWhiteCount())
		{
			strTemp.LoadString(IDS_WHITE_WIN);
			strWin.Format(strTemp.GetBuffer(16), m_pReversi->GetWhiteCount()-m_pReversi->GetBlackCount());
		}
		else
			strWin.LoadString(IDS_DOGFALL);
		AfxMessageBox(strWin, 0, 0);
		return isWin;
	}
	// ������Ӻ󣬶Է�û����ߣ��������ʾ
	if(curPlayer==m_pReversi->GetCurPlayer())
	{
		if(curPlayer==BLACK)
			strWin.LoadString(IDS_WHITE_STOP);
		else
			strWin.LoadString(IDS_BLACK_STOP);
		AfxMessageBox(strWin, 0, 0);
	}
	
	m_bPromptOver = FALSE;	// �������Ϸ����仯ʱ�������õ���û����������Ҫ��ʾ�������߷�

	return isWin;
}

// ��ʼһ���µ���Ϸ
void CBoardView::StartNewGame()
{
	if(GetLockState())
		return;

	StopSearchPrompt();			// ֹͣ������ʾ��Ϣ
	
	m_pReversi->ReStart(m_nStartMode);
	Invalidate(FALSE);
	m_bPromptOver = FALSE;
}

void CBoardView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CString strTip="";
	CPoint p = point;
	// �õ��Ŵ�ǰ�ĳߴ�
	float zoom = GetZoom();
	p.x = int(p.x/zoom);
	p.y = int(p.y/zoom);
	if(m_bShowTop)
		if(p.x-(m_bShowLeft ? WIDTH_LEFT : 0)>=0 && p.y<=HEIGHT_TOP)
			strTip = "�������";
	if(m_bShowLeft)
		if(p.y-(m_bShowTop  ? HEIGHT_TOP : 0)>=0 && p.x<=WIDTH_LEFT)
			strTip = "��߱���";
	if(strTip!="")
	{
		m_ToolTip.Activate(TRUE);
		m_ToolTip.AddTool(this, strTip);
	}
	else
		m_ToolTip.Activate(FALSE);

	//�����ǰ������ƶ�ǰ�����겻ͬ������µ�ǰ����
	CPoint tmpPoint = point;
	PointToBoard(tmpPoint);
	if(tmpPoint!=m_curPoint)
	{
		m_curPoint = tmpPoint;
		if(m_bShowEmpty)
			Invalidate(FALSE);
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CBoardView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(GetLockState())
		return;
	
	SetCapture();
	m_bShowEmpty = TRUE;
	Invalidate(FALSE);
	
	CView::OnLButtonDown(nFlags, point);
}

void CBoardView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	if(m_bShowEmpty == FALSE)	// ������ļ�ʱ����������������ж�
		return;
	m_bShowEmpty = FALSE;
	
	if(GetLockState())
		return;

	int count;
	CPoint tmpPoint = point;
	PointToBoard(tmpPoint);
	if(count=m_pReversi->IsRight(tmpPoint.x, tmpPoint.y))
	{
		StopSearchPrompt();			// ֹͣ������ʾ��Ϣ
		SetEvent(m_hLockEvent);		// ��������
		MovePoint(tmpPoint.x, tmpPoint.y);
		Invalidate(FALSE);
		SendChangeMsg();
		ResetEvent(m_hLockEvent);	// ��������
	}
	else
		MessageBeep(1);

	CView::OnLButtonUp(nFlags, point);
}

void CBoardView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	m_bShowBlueX = TRUE;
	Invalidate(FALSE);

	CView::OnRButtonDown(nFlags, point);
}

void CBoardView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	m_bShowBlueX = FALSE;
	Invalidate(FALSE);

	CView::OnRButtonUp(nFlags, point);
}

BOOL CBoardView::Undo()
{
	if(!m_pReversi->IsCanUndo())
		return FALSE;

	StopSearchPrompt();			// ֹͣ������ʾ��Ϣ
	m_pReversi->Undo();
	// ����ǵ�����������������
	while(m_pReversi->GetCurPlayer()==BLACK && !m_bPlayer1 ||
		  m_pReversi->GetCurPlayer()==WHITE && !m_bPlayer2)
	{
		m_pReversi->Undo();
	}
	Invalidate(FALSE);
	m_bPromptOver = FALSE;
	return TRUE;
}

// �Ƿ���Ի���
BOOL CBoardView::IsCanUndo()
{
	return m_pReversi->IsCanUndo();
}

BOOL CBoardView::Redo()
{
	if(!m_pReversi->IsCanRedo())
		return FALSE;

	StopSearchPrompt();			// ֹͣ������ʾ��Ϣ
	m_pReversi->Redo();
	Invalidate(FALSE);
	m_bPromptOver = FALSE;
	return TRUE;
}

// �Ƿ���Գ�������
BOOL CBoardView::IsCanRedo()
{
	return m_pReversi->IsCanRedo();
}

// ��ʱ�������Ƶ�������
void CBoardView::OnTimer(UINT nIDEvent) 
{
	if(GetLockState())
		return;
	if(m_pReversi->IsGameOver())
		return;
	// �õ����ҳ������߷����ú�ɫ�ġ�X����ʾ�û�
	if(m_pReversi->GetCurPlayer()==BLACK && m_bPlayer1 ||
	   m_pReversi->GetCurPlayer()==WHITE && m_bPlayer2)
	{
		DWORD result = WaitForSingleObject(m_hPromptEvent, 0);
		if(!m_bPromptOver && result == WAIT_TIMEOUT)
			SetEvent(m_hStartPromptEvent);	// �õ�����ʾ�߳̿�ʼ����
		return;
	}

	ComputerFindMove();

	CView::OnTimer(nIDEvent);
}

// �õ���Ѱ��һ����
void CBoardView::ComputerFindMove()
{
	if(GetLockState())
		return;

	StopSearchPrompt();			// ֹͣ������ʾ��Ϣ
//	::SetCursor (LoadCursor (NULL, IDC_WAIT));
	SetEvent(m_hLockEvent);			// ��������
	SetEvent(m_hStartThinkEvent);	// �õ��������߳̿�ʼ����
}

// ���������������߷������Ϣ������
void CBoardView::OnFindBestMove()
{
	// ��ǰ�ǵ���˼��
	ComputerMove();
}

// �õ�����һ����
void CBoardView::ComputerMove()
{	
	MovePoint(m_bestPoint.x, m_bestPoint.y);
	SendChangeMsg();
	::SetCursor (LoadCursor (NULL, IDC_ARROW));
	ResetEvent(m_hLockEvent);	// ��������
}

// ���������߷��ı����Ϣ
void CBoardView::OnBestMoveChange()
{
	Invalidate(FALSE);
}

// �����̵�״̬�����ı�ʱ�����ô˺���������Ϣ��ָ������
void CBoardView::SendChangeMsg()
{
	if(m_hWndReceive)
		::SendMessage(m_hWndReceive, WM_STATE_CHANGE, 0, 0);
}

// �õ���������״̬
BOOL CBoardView::GetLockState()
{
	DWORD result = WaitForSingleObject(m_hLockEvent, 0);
	if(result == WAIT_OBJECT_0)
		return TRUE;
	else
		return FALSE;
}

// ֹͣ���������߷�
void CBoardView::StopSearch()
{
	if(!GetLockState())
		return;

	m_pReversiSearch->m_bExit = TRUE;
}

// ֹͣ������ʾ��Ϣ
void CBoardView::StopSearchPrompt()
{
	if(WaitForSingleObject(m_hPromptEvent, 0) == WAIT_OBJECT_0)
	{
		m_pReversiSearch->m_bExit = TRUE;
		while(WaitForSingleObject(m_hPromptEvent, 0) != WAIT_TIMEOUT)
			Sleep(40);
	}
}

// �������������߷����߳�
DWORD WINAPI CBoardView::ThinkThread(LPVOID pParam)
{
	CBoardView * pView = (CBoardView *)pParam;

	DWORD result;
	while(!pView->m_bThinkExit)
	{
		result = WaitForSingleObject(pView->m_hStartThinkEvent, 1000);
		if(result == WAIT_OBJECT_0)
		{		
			// ��ֹͣ��ʾ�̵߳�����
			pView->m_pReversiSearch->m_bExit = TRUE;
			if(WaitForSingleObject(pView->m_hPromptEvent, 0)==WAIT_TIMEOUT)
			{
				SetEvent(pView->m_hThinkEvent);
				ResetEvent(pView->m_hStartThinkEvent);
				pView->m_pReversiSearch->SetSearchPlanWnd(pView->m_hWndThinkPlan);
				pView->m_pReversiSearch->m_bExit = FALSE;
				pView->m_bestPoint = pView->m_pReversiSearch->FindBestStep(*(pView->m_pReversi));
				ResetEvent(pView->m_hThinkEvent);
				// ����������ϵ���Ϣ
				pView->PostMessage(WM_FIND_BEST_MOVE, 0, 0);
			}
		}
	}

	return 0;
}

// ������ʾ�����߷����߳�
DWORD WINAPI CBoardView::PromptThread(LPVOID pParam)
{
	CBoardView * pView = (CBoardView *)pParam;

	DWORD result;
	while(!pView->m_bPromptExit)
	{
		result = WaitForSingleObject(pView->m_hStartPromptEvent, 1000);
		if(result == WAIT_OBJECT_0)
		{
			SetEvent(pView->m_hPromptEvent);
			ResetEvent(pView->m_hStartPromptEvent);
			pView->m_pReversiSearch->SetSearchPlanWnd(pView->m_hWndPromptPlan);
			pView->m_pReversiSearch->m_bExit = FALSE;
			pView->m_bestPoint = pView->m_pReversiSearch->FindBestStep(*(pView->m_pReversi));
			pView->m_bPromptOver = TRUE;
			ResetEvent(pView->m_hPromptEvent);
			// ����������ϵ���Ϣ
			pView->PostMessage(WM_PROMPT_BEST_MOVE, 0, 0);
		}
	}

	return 0;
}

// ��ע����ж�ȡ��Ϸ����
void CBoardView::GetInfoFromReg()
{
	m_nLevel = AfxGetApp()->GetProfileInt(s_profileHeading, s_level, 6);			// �Ѷ�
	m_nStartMode = AfxGetApp()->GetProfileInt(s_profileHeading, s_startMode, 3);	// ����ģʽ
	m_bFlash = AfxGetApp()->GetProfileInt(s_profileHeading, s_flash, 1);			// �Ƿ���ʾ����
	m_bShowTop = AfxGetApp()->GetProfileInt(s_profileHeading, s_showTop, 1);		// �Ƿ���ʾ�ϱ߱���
	m_bShowLeft = AfxGetApp()->GetProfileInt(s_profileHeading, s_showLeft, 1);		// �Ƿ���ʾ��߱���
	m_bPlayer1 = AfxGetApp()->GetProfileInt(s_profileHeading, s_bPlayer1, 1);		// ����Ƿ�ִ����
	m_bPlayer2 = AfxGetApp()->GetProfileInt(s_profileHeading, s_bPlayer2, 0);		// ����Ƿ�ִ����
}

// ������Ϸ������ע���
void CBoardView::SetInfoToReg()
{
	AfxGetApp()->WriteProfileInt(s_profileHeading, s_level, m_nLevel);			// �Ѷ�
	AfxGetApp()->WriteProfileInt(s_profileHeading, s_startMode, m_nStartMode);	// ����ģʽ
	AfxGetApp()->WriteProfileInt(s_profileHeading, s_flash, m_bFlash);			// �Ƿ���ʾ����
	AfxGetApp()->WriteProfileInt(s_profileHeading, s_showTop, m_bShowTop);		// �Ƿ���ʾ�ϱ߱���
	AfxGetApp()->WriteProfileInt(s_profileHeading, s_showLeft, m_bShowLeft);	// �Ƿ���ʾ��߱���
	if(m_nNetPro == 0)
	{
		AfxGetApp()->WriteProfileInt(s_profileHeading, s_bPlayer1, m_bPlayer1);
		AfxGetApp()->WriteProfileInt(s_profileHeading, s_bPlayer2, m_bPlayer2);
	}
	else
	{
		AfxGetApp()->WriteProfileInt(s_profileHeading, s_bPlayer1, 1);
		AfxGetApp()->WriteProfileInt(s_profileHeading, s_bPlayer2, 1);	
	}
}

void CBoardView::Serialize(CArchive& ar) 
{
	BOOL bPlayer1, bPlayer2;
	if (ar.IsStoring())
	{
		bPlayer1 = m_bPlayer1;
		bPlayer2 = m_bPlayer2;
		if(m_nNetPro != 0)
		{
			bPlayer1 = TRUE;
			bPlayer2 = TRUE;
		}
		ar << m_bFlash << m_nStartMode << m_nLevel << bPlayer1 << bPlayer2;
	}
	else
	{
		ar >> m_bFlash >> m_nStartMode >> m_nLevel >> m_bPlayer1 >> m_bPlayer2;
	}

	m_pReversi->Serialize(ar);
	
	if (!ar.IsStoring())
		m_bPromptOver = FALSE;
}

void Wait(DWORD dwTime)
{
	MSG msg;
	DWORD dwOrgTick = GetTickCount();
	while((GetTickCount() - dwOrgTick) < dwTime)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

BOOL CBoardView::PreTranslateMessage(MSG* pMsg) 
{
	if(m_ToolTip.m_hWnd) m_ToolTip.RelayEvent(pMsg);
	return CView::PreTranslateMessage(pMsg);
}
