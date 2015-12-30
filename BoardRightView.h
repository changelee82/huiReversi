#if !defined(_BOARDRIGHTVIEW_H_INCLUDED_)
#define _BOARDRIGHTVIEW_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoardRightView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBoardRightView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CBoardRightView : public CFormView
{
public:
	CBoardRightView();
	virtual ~CBoardRightView();
	DECLARE_DYNCREATE(CBoardRightView)

// Form Data
public:
	//{{AFX_DATA(CBoardRightView)
	enum { IDD = IDD_HUIREVERSI_FORM };
	CProgressCtrl	m_TinkPro;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoardRightView)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CBoardRightView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_BOARDRIGHTVIEW_H_INCLUDED_)
