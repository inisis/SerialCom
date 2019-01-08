// rc.h : main header file for the RC application
//

#if !defined(AFX_RC_H__C33FD666_FA30_4954_AE0B_BFB45C18994C__INCLUDED_)
#define AFX_RC_H__C33FD666_FA30_4954_AE0B_BFB45C18994C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRcApp:
// See rc.cpp for the implementation of this class
//

class CRcApp : public CWinApp
{
public:
	CRcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RC_H__C33FD666_FA30_4954_AE0B_BFB45C18994C__INCLUDED_)
