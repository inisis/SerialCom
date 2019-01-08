// rcDlg.h : header file
//

#if !defined(AFX_RCDLG_H__F6B58445_9847_445F_881F_EBF321A103B7__INCLUDED_)
#define AFX_RCDLG_H__F6B58445_9847_445F_881F_EBF321A103B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRcDlg dialog

class CRcDlg : public CDialog
{
// Construction
public:
	CRcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRcDlg)
	enum { IDD = IDD_RC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HICON m_hIconRed;
	HICON m_hIconGreen;

	int txFlagCnt;
	int rxFlagCnt;

	LRESULT OnTxMsg(WPARAM,LPARAM);
	LRESULT OnRxMsg(WPARAM,LPARAM);
	LRESULT OnTaskOK(WPARAM,LPARAM);

	afx_msg void OnChk(UINT uID);


	// Generated message map functions
	//{{AFX_MSG(CRcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCDLG_H__F6B58445_9847_445F_881F_EBF321A103B7__INCLUDED_)
