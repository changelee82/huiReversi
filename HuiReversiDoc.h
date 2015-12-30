// HuiReversiDoc.h : interface of the CHuiReversiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(_HUIREVERSIDOC_H_INCLUDED_)
#define _HUIREVERSIDOC_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "huiReversi\HuiReversiMain.h"	// Added by ClassView

class CHuiReversiDoc : public CDocument
{
protected: // create from serialization only
	CHuiReversiDoc();
	DECLARE_DYNCREATE(CHuiReversiDoc)

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHuiReversiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CHuiReversiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHuiReversiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_HUIREVERSIDOC_H_INCLUDED_)
