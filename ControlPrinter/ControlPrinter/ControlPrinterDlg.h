// ControlPrinterDlg.h : header file
//

#if !defined(AFX_CONTROLPRINTERDLG_H__CED6CAA4_2C76_4177_A38A_8C86A9F2A2CF__INCLUDED_)
#define AFX_CONTROLPRINTERDLG_H__CED6CAA4_2C76_4177_A38A_8C86A9F2A2CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CControlPrinterDlg dialog

class CControlPrinterDlg : public CDialog
{
// Construction
public:
	int m_lRightMargin;
	int m_lLeftMargin;
	CControlPrinterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CControlPrinterDlg)
	enum { IDD = IDD_CONTROLPRINTER_DIALOG };
	CListBox	m_listBox2;
	CListBox	m_listBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlPrinterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ListJobs(LPTSTR szPrinterName);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CControlPrinterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEnumprintters();
	afx_msg void OnSelchangePrinters();
	afx_msg void OnSetprint();
	afx_msg void OnSetuppage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLPRINTERDLG_H__CED6CAA4_2C76_4177_A38A_8C86A9F2A2CF__INCLUDED_)
