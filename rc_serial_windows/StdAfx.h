// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3C25F178_8232_4461_80CE_C4E7E7C06CC5__INCLUDED_)
#define AFX_STDAFX_H__3C25F178_8232_4461_80CE_C4E7E7C06CC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define WM_RXPACKAGE	(WM_USER+101)
#define WM_TXPACKAGE	(WM_USER+102)

#define WM_TASKOK		(WM_USER+103)

extern HANDLE hUsart;


typedef unsigned short u16;
typedef unsigned char u8;


class CUart
{
private:

	HANDLE m_TaskEvt;
	HANDLE m_RxOKEvt;
	

	CRITICAL_SECTION	m_cs;
	HWND	m_msgHwnd;	
	HANDLE	m_hCom;
	

	HANDLE m_ovEvtRx;
	OVERLAPPED m_ovRx;
	HANDLE m_ovEvtTx;
	OVERLAPPED m_ovTx;

	void Lock(){EnterCriticalSection(&m_cs);}
	void Unlock(){LeaveCriticalSection(&m_cs);}


	unsigned char txPut,txGet;
	unsigned char txQue[256][2];

	


	unsigned char uiRxLen;
	unsigned char rxData[256];

	void OnRxChar(unsigned char c)
	{
		/*
		if(c == 0x22)
		{
			TRACE("Rx:");
		}
		TRACE("0x%02X ",c);
		*/
		if(uiRxLen == 0 && c != 0x22)
		{
			return;
		}
		rxData[uiRxLen++] = c;
		if(uiRxLen >= 8)
		{
			unsigned char csum,i;
			csum = 0;
			for(i = 0; i < 7 ; i++)
			{
				csum += rxData[i];
			}
			if(csum == rxData[7])
			{//ok
				//TRACE(" -- \r\n");
				PostMessage(m_msgHwnd,WM_TASKOK,rxData[2],rxData[6]);
			}

			uiRxLen = 0;

			
		}
	}

	

	void RxLoop()
	{
		unsigned char rxChar[256];
		DWORD n,ret;
		
		uiRxLen = 0;

		while(1)
		{
			memset(&m_ovRx, 0, sizeof(OVERLAPPED));
			m_ovRx.hEvent = m_ovEvtRx;
			int a =ReadFile(m_hCom,rxChar,256,(unsigned long*)&n,&m_ovRx);
			if(ReadFile(m_hCom,rxChar,256,(unsigned long*)&n,&m_ovRx))
			{
				if(n == 0)break;
				for(ret=0;ret<n;ret++)
				{
					OnRxChar(rxChar[ret]);
				}
				PostMessage(m_msgHwnd,WM_RXPACKAGE,0,0);
			}
			else
			{
				if(GetLastError() == ERROR_IO_PENDING)
				{
					if(!GetOverlappedResult(m_hCom, &m_ovRx, (unsigned long*)&n, TRUE))
					{
						ret = GetLastError();
						if(ret == ERROR_SUCCESS)
						{
							break;
						}
						if(ret == ERROR_IO_INCOMPLETE)
						{
							break;
						}
						return;
					}
					if(n == 0)
					{
						return;
					}
					for(ret=0;ret<n;ret++)
					{
						OnRxChar(rxChar[ret]);
					}						
					PostMessage(m_msgHwnd,WM_RXPACKAGE,0,0);
				}
				else
				{
					return;
				}
			}
		}
	}

	int DoTxing(const u8 *pd,unsigned int dl)
	{
		unsigned long n,ret;
		
		memset(&m_ovTx, 0, sizeof(OVERLAPPED));
		m_ovTx.hEvent = m_ovEvtTx;
		n = 0;
		if(!WriteFile(m_hCom,pd,dl,(unsigned long*)&n,&m_ovTx))
		{
			if(GetLastError() == ERROR_IO_PENDING)
			{
				WaitForSingleObject(m_ovEvtTx,1000);
				if(!GetOverlappedResult(m_hCom, &m_ovTx, (unsigned long*)&n, FALSE))
				{
					ret = GetLastError();
					if(ret != ERROR_SUCCESS && ret != ERROR_IO_INCOMPLETE)
					{
						dl = 0;
					}
				}
			}
			else
			{
				dl = 0;
			}
		}
		PostMessage(m_msgHwnd,WM_TXPACKAGE,0,0);
		if(dl == 0)return 0;
		return 1;
	}



	void TaskLoop()
	{
		unsigned char cmd[16]={0x33,0x01,0x11,0,0,0,0,0};
		unsigned char *pc,c,i;
		while(1)
		{
			while(txGet != txPut)
			{
				cmd[2] = txQue[txGet][0];
				cmd[6] = txQue[txGet][1];
				//TRACE("txcmd:0x%02X 0x%02X\r\n",cmd[2],cmd[6]);
				pc = cmd;				
				c = 0;
				for(i = 0;i < 7;i++)   //a loop for transimitting data
				{
					c +=*pc++;
				}
				*pc = c;         //pointer add the numbers in total
				DoTxing(cmd,8);
				txGet++;
			}
			
			ResetEvent(m_TaskEvt);
			WaitForSingleObject(m_TaskEvt,INFINITE);
		}
	}

public:
	CUart()
	{
		InitializeCriticalSection(&m_cs);
				
		m_ovEvtRx = CreateEvent(NULL, TRUE, FALSE, NULL);		
		m_ovEvtTx = CreateEvent(NULL, TRUE, FALSE, NULL);

		m_TaskEvt = CreateEvent(NULL, TRUE, FALSE, NULL);

		m_RxOKEvt = CreateEvent(NULL, TRUE, FALSE, NULL);

		txPut = 0;
		txGet = 0;
	}

	void RxMain()
	{
		RxLoop();
		AfxMessageBox("´®¿Ú¶ÁÈ¡Òì³£");
	}

	void TaskMain()
	{
		TaskLoop();
	}
	
	static DWORD WINAPI RxThread(CUart*pUart);
	static DWORD WINAPI TaskThread(CUart*pUart);

	void Start(HANDLE hCom, HWND msgToWin)
	{
		DWORD dwThreadId;
		
		m_msgHwnd = msgToWin;
		m_hCom = hCom;
	
		CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)(CUart::RxThread),(void*)this,0,&dwThreadId);
		CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)(CUart::TaskThread),(void*)this,0,&dwThreadId);		
	}
	

	void CfgTask(unsigned char cmd,unsigned char id)
	{
		Lock();
		txQue[txPut][0] = cmd;
		txQue[txPut][1] = id;
		txPut++;
		Unlock();
		SetEvent(m_TaskEvt);
	}

};


extern CUart uart;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_STDAFX_H__3C25F178_8232_4461_80CE_C4E7E7C06CC5__INCLUDED_)
