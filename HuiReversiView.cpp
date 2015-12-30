// HuiReversiView.cpp : implementation of the CHuiReversiView class
//

#include "stdafx.h"
#include "HuiReversi.h"

#include "HuiReversiDoc.h"
#include "HuiReversiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiView

IMPLEMENT_DYNCREATE(CHuiReversiView, CView)

BEGIN_MESSAGE_MAP(CHuiReversiView, CView)
	//{{AFX_MSG_MAP(CHuiReversiView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiView construction/destruction

CHuiReversiView::CHuiReversiView()
{
	//{{AFX_DATA_INIT(CHuiReversiView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CHuiReversiView::~CHuiReversiView()
{
}

void CHuiReversiView::DoDataExchange(CDataExchange* pDX)
{
	CView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHuiReversiView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CHuiReversiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiView diagnostics

#ifdef _DEBUG
void CHuiReversiView::AssertValid() const
{
	CView::AssertValid();
}

void CHuiReversiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHuiReversiDoc* CHuiReversiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHuiReversiDoc)));
	return (CHuiReversiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiView message handlers

int CHuiReversiView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CHuiReversiView::OnDraw(CDC* pDC) 
{
}
