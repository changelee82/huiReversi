// DlgRule.cpp : implementation file
//

#include "stdafx.h"
#include "HuiReversi.h"
#include "DlgRule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRule dialog


CDlgRule::CDlgRule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRule)
	m_strRule = _T("");
	//}}AFX_DATA_INIT
}


void CDlgRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRule)
	DDX_Text(pDX, IDC_RULE, m_strRule);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRule, CDialog)
	//{{AFX_MSG_MAP(CDlgRule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRule message handlers

BOOL CDlgRule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_strRule = L"\
     ���ȸ�л���Ա������֧�֣��������ʲô�������ӭ\r\n\
 ��Email����OICQ֪ͨ�ҡ�\r\n\r\n\
     ���   Email: lihui_xp@163.com   OICQ: 6545823\r\n\
\r\n\
 ��鼰�������\r\n\
     �ڰ��壬�ֽз���(Reversi)����������(Othello)��\r\n\
 ƻ���壬��ת�塣�ڰ������������ձ������С�\r\n\
     �ڰ����������һ����8*8��������̡�����ʱ������\r\n\
 �ڿո��м䣬��������Χ��һ�����ڽ�����ϡ���ʼʱ����\r\n\
 ��������һ��һ���ĸ����ӽ�����ã����ӵķ����ǣ�����\r\n\
 ����ɫ�����ӷ������̵Ŀո��ϣ������Լ����µ������ں�\r\n\
 ������б�˸��������һ���Լ������ӣ��򱻼����м��ȫ\r\n\
 �����Ϊ�Լ������ӡ����ң�ֻ���ڿ��Է�ת���ӵĵط���\r\n\
 �������ӡ�\r\n\
    ���������û�еط��������ӣ���ö������¡�˫����\r\n\
 û�����ӿ�����ʱ��ֽ��������Ӷ��һ����ʤ��\r\n\
    ���Ĺ�����Ȼ�򵥣����Ǳ仯���ӡ�Ҳ������Ϊ�ڰ���\r\n\
 �ܼ�,���Ƕ��ںڰ��壬��һ��˵���ǣ�ֻ��Ҫ������ѧ\r\n\
 ������ȴ��Ҫһ����ʱ��ȥ��ͨ��(a minute to learn,\r\n\
 a lifetime to master)��";
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
