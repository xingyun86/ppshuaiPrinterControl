// ControlPrinterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ControlPrinter.h"
#include "ControlPrinterDlg.h"
#include <winspool.h>

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
// CControlPrinterDlg dialog

CControlPrinterDlg::CControlPrinterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlPrinterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlPrinterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CControlPrinterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlPrinterDlg)
	DDX_Control(pDX, ID_JOBS, m_listBox2);
	DDX_Control(pDX, ID_PRINTERS, m_listBox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CControlPrinterDlg, CDialog)
	//{{AFX_MSG_MAP(CControlPrinterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENUMPRINTTERS, OnEnumprintters)
	ON_LBN_SELCHANGE(ID_PRINTERS, OnSelchangePrinters)
	ON_BN_CLICKED(IDC_SETPRINT, OnSetprint)
	ON_BN_CLICKED(IDC_SETUPPAGE, OnSetuppage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlPrinterDlg message handlers

BOOL CControlPrinterDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CControlPrinterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CControlPrinterDlg::OnPaint() 
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
HCURSOR CControlPrinterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CControlPrinterDlg::OnEnumprintters() 
{
	// TODO: Add your control notification handler code here
	
	DWORD dwSize = 0;
	DWORD dwIndex = 0;
	DWORD dwPrinters = 0;
	BYTE * pBuffer = NULL;
	PRINTER_INFO_5 * pPrinterInfo5 = NULL;

	m_listBox.ResetContent();

	::EnumPrinters (PRINTER_ENUM_LOCAL, NULL, 5, NULL, 0, &dwSize, &dwPrinters); 	
	pBuffer = (BYTE *)malloc(dwSize * sizeof(BYTE));
	if (pBuffer)
	{
		::EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 5, pBuffer, dwSize, &dwSize, &dwPrinters);
		if (dwPrinters != 0)
		{

			pPrinterInfo5 = (PRINTER_INFO_5*)pBuffer;
			for (dwIndex = 0; dwIndex < dwPrinters; dwIndex++) 
			{
				m_listBox.AddString(pPrinterInfo5->pPrinterName);
				pPrinterInfo5++;
			}
		}
		free(pBuffer);
		pBuffer = NULL;
	}
}

void CControlPrinterDlg::OnSelchangePrinters() 
{
	// TODO: Add your control notification handler code here
	CString strPrinterName(_T(""));
	int nIndex = m_listBox.GetCurSel();
	
	if (nIndex != CB_ERR)
	{
		m_listBox.GetText(nIndex, strPrinterName);
		if (!strPrinterName.IsEmpty())
		{
			ListJobs((LPTSTR)(LPCSTR)strPrinterName);
		}
	}
}

BOOL CControlPrinterDlg::ListJobs(LPTSTR szPrinterName)
{
	HANDLE hPrinter;
	DWORD dwNeeded, dwReturned, i;
	JOB_INFO_1 *pJobInfo;
	// You need a printer handle, open the printer
	if (!OpenPrinter(szPrinterName, &hPrinter, NULL))
	{
		return FALSE;
	}
	// First you call EnumJobs() to find out how much memory you need
	if( ! EnumJobs( hPrinter, 0, 0xFFFFFFFF, 1, NULL, 0, &dwNeeded, &dwReturned ) )
	{
		// It should have failed, but if it failed for any reason other
		// than "not enough memory", you should bail out
		if( GetLastError() != ERROR_INSUFFICIENT_BUFFER )
		{
			ClosePrinter( hPrinter );
			return FALSE;
		}
	}
	// Allocate enough memory for the JOB_INFO_1 structures plus
	// the extra data - dwNeeded from the previous call tells you
	// the total size needed
	if( (pJobInfo = (JOB_INFO_1 *)malloc( dwNeeded )) == NULL )
	{
		ClosePrinter( hPrinter );
		return FALSE;
	}
	// Call EnumJobs() again and let it fill out our structures
	if( ! EnumJobs( hPrinter, 0, 0xFFFFFFFF, 1, (LPBYTE)pJobInfo,
		dwNeeded, &dwNeeded, &dwReturned ) )
	{
		ClosePrinter( hPrinter );
		free( pJobInfo );
		return FALSE;
	}
	// You're done with the printer handle, close it
	ClosePrinter( hPrinter );

	// dwReturned tells how many jobs there are
	// Here, you'll simply display the number of jobs found
	// It's easy to loop through the jobs and access each one
	for(i=0;i<dwReturned;i++)
	{
		// pJobInfo[i] is a JOB_INFO_1 struct for that job
		// so here you could do whatever you want for each job
		m_listBox2.AddString( pJobInfo[i].pDocument );
	}
	// Clean up
	free( pJobInfo );
	pJobInfo = NULL;

	return TRUE;
}

void CControlPrinterDlg::OnSetprint() 
{
	// TODO: Add your control notification handler code here
	CSize size;
	CString strBuffer(_T(""));
	DWORD dwFlags = PD_PAGENUMS | PD_HIDEPRINTTOFILE | PD_SELECTION;
	CPrintDialog dlgPrint(FALSE, dwFlags, NULL);
	dlgPrint.m_pd.nCopies = 2;
	dlgPrint.m_pd.nMinPage = 1;
	dlgPrint.m_pd.nMaxPage = 2;
	dlgPrint.m_pd.nFromPage = 1;
	dlgPrint.m_pd.nToPage =2;
	if( dlgPrint.DoModal() == IDOK )
	{
		CDC dcPrint;
		dcPrint.Attach( dlgPrint.GetPrinterDC() );
		size.cy = dcPrint.GetDeviceCaps(VERTSIZE);
		size.cx = dcPrint.GetDeviceCaps(HORZSIZE);
		strBuffer.Format(_T("印刷页的长%d毫米\n印刷页的高%d毫米"), size.cx, size.cy);
		AfxMessageBox(strBuffer);
		dcPrint.DeleteDC();
	}
}

void CControlPrinterDlg::OnSetuppage() 
{
	// TODO: Add your control notification handler code here
	CPageSetupDialog dlgPage(PSD_MARGINS, NULL);
	CRect rcMax, rcMin;
	if ( dlgPage.DoModal() == IDOK )//使用默认的A4纸
	{
		dlgPage.GetMargins(&rcMax, &rcMin);
		m_lLeftMargin = rcMax.left / 100; //返回左边距单位是毫米
		m_lRightMargin = rcMax.right / 100; //返回右边距单位是毫米
	}
}
