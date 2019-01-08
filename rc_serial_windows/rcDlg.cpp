// rcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "rc.h"
#include "rcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRcDlg dialog

CRcDlg::CRcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRcDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIconRed = AfxGetApp()->LoadIcon(IDI_RED);
	m_hIconGreen = AfxGetApp()->LoadIcon(IDI_GREEN);
}

void CRcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRcDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRcDlg, CDialog)
	//{{AFX_MSG_MAP(CRcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED,IDC_CHECK_CH0,IDC_CHECK_ALL,OnChk)

	ON_MESSAGE(WM_RXPACKAGE,OnRxMsg)
	ON_MESSAGE(WM_TXPACKAGE,OnTxMsg)
	ON_MESSAGE(WM_TASKOK,OnTaskOK)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRcDlg message handlers

BOOL CRcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	txFlagCnt = 0;
	rxFlagCnt = 0;
	SetTimer(1232,10,NULL);
	SetTimer(1233,1000,NULL);

	uart.Start(hUsart,m_hWnd);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CRcDlg::OnTaskOK(WPARAM cmd,LPARAM id)
{
	CButton *pBtn;
	UINT uID = IDC_CHECK_CH0 + id -1;
	if(cmd == 0x11)
	{
		pBtn = (CButton*)GetDlgItem(uID);
		if(pBtn)pBtn->SetCheck(FALSE);
	}
	else if(cmd == 0x12)
	{
		pBtn = (CButton*)GetDlgItem(uID);
		if(pBtn)pBtn->SetCheck(TRUE);
	}
	else if(cmd == 0x13)
	{
		for(uID = IDC_CHECK_CH0;uID <= IDC_CHECK_ALL;uID++)
		{
			pBtn = (CButton*)GetDlgItem(uID);
			if(pBtn)pBtn->SetCheck(FALSE);
		}
	}
	else if(cmd == 0x14)
	{
		for(uID = IDC_CHECK_CH0;uID <= IDC_CHECK_ALL;uID++)
		{
			pBtn = (CButton*)GetDlgItem(uID);
			if(pBtn)pBtn->SetCheck(TRUE);
		}
	}
	return 0;
}

LRESULT CRcDlg::OnTxMsg(WPARAM,LPARAM)
{
	if(txFlagCnt == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_TX))->SetIcon(m_hIconGreen);
	}
	txFlagCnt = 10;
	return 0;
}
LRESULT CRcDlg::OnRxMsg(WPARAM,LPARAM)
{
	if(rxFlagCnt == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_RX))->SetIcon(m_hIconGreen);
	}
	rxFlagCnt = 10;
	return 0;
}


void CRcDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 1232)
	{
		if(rxFlagCnt > 0)
		{
			rxFlagCnt--;
			if(rxFlagCnt == 0)
			{
				((CStatic*)GetDlgItem(IDC_STATIC_RX))->SetIcon(m_hIconRed);
			}
		}
		if(txFlagCnt > 0)
		{
			txFlagCnt--;
			if(txFlagCnt == 0)
			{
				((CStatic*)GetDlgItem(IDC_STATIC_TX))->SetIcon(m_hIconRed);
			}
		}
		return;
	}
	if(nIDEvent == 1233)
	{
		if(!((CButton*)GetDlgItem(IDC_CHECK_TEST))->GetCheck())
		{
			return;
		}
		
		return;
	}
	CDialog::OnTimer(nIDEvent);
}

void CRcDlg::OnChk(UINT uID)
{

	UpdateData();
	int chk = ((CButton*)GetDlgItem(uID))->GetCheck();
	int id = 1 + uID - IDC_CHECK_CH0;

	if(uID == IDC_CHECK_ALL)
	{
		uart.CfgTask(chk?0x14:0x13,0);
	}
	else
	{
		uart.CfgTask(chk?0x12:0x11,(unsigned char)id);
	}
}
