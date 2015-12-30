#if !defined(AFX_DLGGETIP_H__95B2CD4A_48E3_45E8_B1E4_DFCA4E0E31CA__INCLUDED_)
#define AFX_DLGGETIP_H__95B2CD4A_48E3_45E8_B1E4_DFCA4E0E31CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetIP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGetIP dialog

class CDlgGetIP : public CDialog
{
// Construction
public:
	CDlgGetIP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGetIP)
	enum { IDD = IDD_DLG_GETIP };
	CString	m_strIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGetIP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGetIP)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETIP_H__95B2CD4A_48E3_45E8_B1E4_DFCA4E0E31CA__INCLUDED_)
