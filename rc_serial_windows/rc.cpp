// rc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "rc.h"
#include "rcDlg.h"
#include "US.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRcApp

BEGIN_MESSAGE_MAP(CRcApp, CWinApp)
	//{{AFX_MSG_MAP(CRcApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRcApp construction

CRcApp::CRcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRcApp object

CRcApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRcApp initialization
BOOL SelUsart()
{
	CUS dlg;
	return dlg.DoModal()== IDOK;
}

BOOL CRcApp::InitInstance()
{
	if(!SelUsart())return FALSE;

	CRcDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
