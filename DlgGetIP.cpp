// DlgGetIP.cpp : implementation file
//

#include "stdafx.h"
#include "HuiReversi.h"
#include "DlgGetIP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGetIP dialog


CDlgGetIP::CDlgGetIP(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGetIP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGetIP)
	m_strIP = _T("");
	//}}AFX_DATA_INIT
}


void CDlgGetIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGetIP)
	DDX_Text(pDX, IDC_IP, m_strIP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGetIP, CDialog)
	//{{AFX_MSG_MAP(CDlgGetIP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGetIP message handlers

void CDlgGetIP::OnOK() 
{
	CDialog::OnOK();
}

BOOL CDlgGetIP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// 设置IP地址
	char szHostName[128];
	struct hostent * pHost;	
	if( gethostname(szHostName, 128) == 0 )
	{
		pHost = gethostbyname(szHostName); 
		m_strIP = inet_ntoa (*(struct in_addr *)pHost->h_addr_list[0]);
		UpdateData(FALSE);
	}
	// 设定焦点，选中IP地址字符串
	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_IP);
	pEdit->SetFocus();
	pEdit->SetSel(0, -1);

	return FALSE;  // return TRUE unless you set the focus to a control
	               // EXCEPTION: OCX Property Pages should return FALSE
}
