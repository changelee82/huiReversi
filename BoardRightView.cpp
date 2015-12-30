// BoardRightView.cpp : implementation file
//

#include "stdafx.h"
#include "HuiReversi.h"
#include "BoardRightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoardRightView

IMPLEMENT_DYNCREATE(CBoardRightView, CFormView)

CBoardRightView::CBoardRightView()
	: CFormView(CBoardRightView::IDD)
{
	//{{AFX_DATA_INIT(CBoardRightView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CBoardRightView::~CBoardRightView()
{
}

void CBoardRightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoardRightView)
	DDX_Control(pDX, IDC_PROTHINK, m_TinkPro);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBoardRightView, CFormView)
	//{{AFX_MSG_MAP(CBoardRightView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoardRightView diagnostics

#ifdef _DEBUG
void CBoardRightView::AssertValid() const
{
	CFormView::AssertValid();
}

void CBoardRightView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBoardRightView message handlers

BOOL CBoardRightView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{	
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
