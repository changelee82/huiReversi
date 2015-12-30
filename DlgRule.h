#if !defined(AFX_DLGRULE_H__62FA5CE2_9250_4855_B0C4_FA10B095567F__INCLUDED_)
#define AFX_DLGRULE_H__62FA5CE2_9250_4855_B0C4_FA10B095567F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRule dialog

class CDlgRule : public CDialog
{
// Construction
public:
	CDlgRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRule)
	enum { IDD = IDD_DLG_RULE };
	CString	m_strRule;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRule)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRULE_H__62FA5CE2_9250_4855_B0C4_FA10B095567F__INCLUDED_)
