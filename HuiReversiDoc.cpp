// HuiReversiDoc.cpp : implementation of the CHuiReversiDoc class
//

#include "stdafx.h"
#include "HuiReversi.h"

#include "HuiReversiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiDoc

IMPLEMENT_DYNCREATE(CHuiReversiDoc, CDocument)

BEGIN_MESSAGE_MAP(CHuiReversiDoc, CDocument)
	//{{AFX_MSG_MAP(CHuiReversiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiDoc construction/destruction

CHuiReversiDoc::CHuiReversiDoc()
{
}

CHuiReversiDoc::~CHuiReversiDoc()
{
}

BOOL CHuiReversiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHuiReversiDoc serialization

void CHuiReversiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiDoc diagnostics

#ifdef _DEBUG
void CHuiReversiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHuiReversiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHuiReversiDoc commands

BOOL CHuiReversiDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CFileException fe;
	CFile* pFile = GetFile(lpszPathName, CFile::modeRead|CFile::shareDenyWrite, &fe);
	if (pFile == NULL)
	{
		ReportSaveLoadException(lpszPathName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}
	DeleteContents();
	
	CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete,4096*8);
	loadArchive.m_pDocument = this;
	loadArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		if (pFile->GetLength() != 0)
		{
			theReversiWnd.m_wndBoard->Serialize(loadArchive);
		}
		loadArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		DeleteContents();   // remove failed contents

		TRY
		{
			ReportSaveLoadException(lpszPathName, e,
				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		}
		END_TRY
		//DELETE_EXCEPTION(e);
		return FALSE;
	}
	END_CATCH_ALL
		
	return TRUE;
}

BOOL CHuiReversiDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	CFileException fe;
	CFile* pFile = NULL;
	pFile = GetFile(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);

	if (pFile == NULL)
	{
		ReportSaveLoadException(lpszPathName, &fe,
			TRUE, AFX_IDP_INVALID_FILENAME);
		return FALSE;
	}

	CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete,4096*8);
	saveArchive.m_pDocument = this;
	saveArchive.m_bForceFlat = FALSE;
	//ÅÐ¶Ï£º

	TRY
	{
		CWaitCursor wait;
		theReversiWnd.m_wndBoard->Serialize(saveArchive);
		saveArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		TRY
		{
			ReportSaveLoadException(lpszPathName, e,
				TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		}
		END_TRY
	//DELETE_EXCEPTION(e);
		return FALSE;
	}
	END_CATCH_ALL	
	return TRUE;
}
