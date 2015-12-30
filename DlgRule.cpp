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
     首先感谢您对本软件的支持，如果您有什么意见，欢迎\r\n\
 发Email或用OICQ通知我。\r\n\r\n\
     李辉   Email: lihui_xp@163.com   OICQ: 6545823\r\n\
\r\n\
 简介及下棋规则：\r\n\
     黑白棋，又叫反棋(Reversi)、奥赛罗棋(Othello)，\r\n\
 苹果棋，翻转棋。黑白棋在西方和日本很流行。\r\n\
     黑白棋的棋盘是一个有8*8方格的棋盘。下棋时将棋下\r\n\
 在空格中间，而不是像围棋一样下在交叉点上。开始时在棋\r\n\
 盘正中有一白一黑四个棋子交叉放置，下子的方法是：把自\r\n\
 己颜色的棋子放在棋盘的空格上，而当自己放下的棋子在横\r\n\
 、竖、斜八个方向內有一个自己的棋子，则被夹在中间的全\r\n\
 部会成为自己的棋子。并且，只有在可以翻转棋子的地方才\r\n\
 可以下子。\r\n\
    如果棋盘上没有地方可以下子，则该对手连下。双方都\r\n\
 没有棋子可以下时棋局结束，棋子多的一方获胜。\r\n\
    它的规则虽然简单，但是变化复杂。也许你认为黑白棋\r\n\
 很简单,但是对于黑白棋，有一种说法是：只需要几分钟学\r\n\
 会它，却需要一生的时间去精通它(a minute to learn,\r\n\
 a lifetime to master)。";
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
