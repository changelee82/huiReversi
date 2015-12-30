// HuiReversiView.h : interface of the CHuiReversiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(_HUIREVERSIVIEW_H_INCLUDED_)
#define _HUIREVERSIVIEW_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHuiReversiView : public CView
{
protected: // create from serialization only
	CHuiReversiView();
	virtual ~CHuiReversiView();
	DECLARE_DYNCREATE(CHuiReversiView)

public:
	//{{AFX_DATA(CHuiReversiView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CHuiReversiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHuiReversiView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:

	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHuiReversiView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HuiReversiView.cpp
inline CHuiReversiDoc* CHuiReversiView::GetDocument()
   { return (CHuiReversiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_HUIREVERSIVIEW_H_INCLUDED_)
