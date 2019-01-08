// US.cpp : implementation file
//

#include "stdafx.h"
#include "rc.h"
#include "US.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUS dialog


CUS::CUS(CWnd* pParent /*=NULL*/)
	: CDialog(CUS::IDD, pParent)
{
	char bf[256];
	bf[0] = 0;
	GetProfileString("RelayCtrl","COM","",bf,255);
	//{{AFX_DATA_INIT(CUS)
	m_csUsart = bf;
	//}}AFX_DATA_INIT
}


void CUS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUS)
	DDX_Control(pDX, IDC_COMBO1, m_UartList);
	DDX_CBString(pDX, IDC_COMBO1, m_csUsart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUS, CDialog)
	//{{AFX_MSG_MAP(CUS)
	ON_CBN_DROPDOWN(IDC_COMBO1, OnDropdownCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUS message handlers

void CUS::OnOK() 
{
	UpdateData();
	char bf[256],uN[256];
	
	DCB dcb;
	COMMTIMEOUTS TimeOuts;
	
	
	strcpy(bf,m_csUsart);
	
	sprintf(uN,"\\\\.\\%s",m_csUsart);
	
	hUsart = CreateFile(uN, GENERIC_READ | GENERIC_WRITE, 0, NULL,OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	
	if(hUsart != INVALID_HANDLE_VALUE)
	{
		
		if(GetCommState(hUsart, &dcb))
		{
			dcb.fBinary = TRUE;
			dcb.fDtrControl = DTR_CONTROL_ENABLE;
			dcb.fDsrSensitivity = FALSE;
			dcb.fTXContinueOnXoff = FALSE;
			dcb.fOutX = FALSE;
			dcb.fInX = FALSE;
			dcb.fErrorChar = FALSE;
			dcb.fNull = FALSE;
			dcb.fRtsControl = RTS_CONTROL_ENABLE;
			dcb.fAbortOnError = FALSE;
			dcb.fOutxCtsFlow = FALSE;
			dcb.fOutxDsrFlow = FALSE;
			
			dcb.BaudRate = 9600;
			dcb.ByteSize = 8;
			
			dcb.StopBits = ONESTOPBIT;
			
			dcb.Parity = NOPARITY;
			
			if(SetCommState(hUsart, &dcb))
			{
				TimeOuts.ReadIntervalTimeout = 1;
				TimeOuts.ReadTotalTimeoutConstant = 0;
				TimeOuts.ReadTotalTimeoutMultiplier = 0;
				TimeOuts.WriteTotalTimeoutConstant = 0;
				TimeOuts.WriteTotalTimeoutMultiplier = 0;
				SetCommTimeouts(hUsart,&TimeOuts);
				
				SetupComm(hUsart,1024,1024);
				PurgeComm(hUsart, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
				
				
				WriteProfileString("RelayCtrl","COM",bf);
				
				
				CDialog::OnOK();
				return;	
			}
		}
		CloseHandle(hUsart);
	}
	AfxMessageBox("´ò¿ª´®¿ÚÊ§°Ü");
}

void CUS::OnDropdownCombo1() 
{
	// TODO: Add your control notification handler code here
	while(m_UartList.GetCount()>0)m_UartList.DeleteString(0);
	HKEY hKey;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Hardware\\DeviceMap\\SerialComm",NULL,KEY_READ,&hKey) == ERROR_SUCCESS)
	{
		int i=0,id=-1;
		TCHAR portName[256],commName[256];
		DWORD dwLong,dwSize;
		
		while(1)
		{
			dwLong = dwSize = sizeof(portName);
			if(RegEnumValue(hKey, i, portName, &dwLong, NULL, NULL, (LPBYTE)commName, &dwSize ) == ERROR_NO_MORE_ITEMS )break;
			m_UartList.AddString(commName);
			i++;
		}
		RegCloseKey(hKey);
	}
}
