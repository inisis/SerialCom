; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUS
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "rc.h"

ClassCount=4
Class1=CRcApp
Class2=CRcDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_RC_DIALOG
Class4=CUS
Resource4=IDD_DIALOG1

[CLS:CRcApp]
Type=0
HeaderFile=rc.h
ImplementationFile=rc.cpp
Filter=N

[CLS:CRcDlg]
Type=0
HeaderFile=rcDlg.h
ImplementationFile=rcDlg.cpp
Filter=D
LastObject=IDC_CHECK_CH7
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=rcDlg.h
ImplementationFile=rcDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_RC_DIALOG]
Type=1
Class=CRcDlg
ControlCount=12
Control1=IDC_STATIC_TX,static,1342177283
Control2=IDC_STATIC_RX,static,1342177283
Control3=IDC_CHECK_CH0,button,1342242819
Control4=IDC_CHECK_CH1,button,1342242819
Control5=IDC_CHECK_CH2,button,1342242819
Control6=IDC_CHECK_CH3,button,1342242819
Control7=IDC_CHECK_CH4,button,1342242819
Control8=IDC_CHECK_CH5,button,1342242819
Control9=IDC_CHECK_CH6,button,1342242819
Control10=IDC_CHECK_CH7,button,1342242819
Control11=IDC_CHECK_ALL,button,1342242819
Control12=IDC_CHECK_TEST,button,1342242819

[DLG:IDD_DIALOG1]
Type=1
Class=CUS
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_COMBO1,combobox,1344339970

[CLS:CUS]
Type=0
HeaderFile=US.h
ImplementationFile=US.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CUS

