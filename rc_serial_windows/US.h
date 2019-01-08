#if !defined(AFX_US_H__0E0D9A54_1DC7_4C05_8593_80FBFA814D92__INCLUDED_)
#define AFX_US_H__0E0D9A54_1DC7_4C05_8593_80FBFA814D92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// US.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUS dialog

class CUS : public CDialog
{
// Construction
public:
	CUS(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUS)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	m_UartList;
	CString	m_csUsart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUS)
	virtual void OnOK();
	afx_msg void OnDropdownCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_US_H__0E0D9A54_1DC7_4C05_8593_80FBFA814D92__INCLUDED_)
