// stdafx.cpp : source file that includes just the standard includes
//	rc.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


HANDLE hUsart;
CUart uart;
DWORD WINAPI CUart::RxThread(CUart*pUart)
{
	pUart->RxMain();
	return 0;
}
DWORD WINAPI CUart::TaskThread(CUart*pUart)
{
	pUart->TaskLoop();
	return 0;
}

