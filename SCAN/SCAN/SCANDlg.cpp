
// SCANDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SCAN.h"
#include "SCANDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSCANDlg 对话框



CSCANDlg::CSCANDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSCANDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSCANDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYTAB, m_tab);
}

BEGIN_MESSAGE_MAP(CSCANDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MYTAB, &CSCANDlg::OnTcnSelchangeMytab)
END_MESSAGE_MAP()


// CSCANDlg 消息处理程序

BOOL CSCANDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	m_tab.InsertItem(0,_T("ARP"));
	m_tab.InsertItem(1, _T("ICMP"));
	m_tab.InsertItem(2, _T("TCP/UDP"));
	m_tab.InsertItem(3, _T("TCP_SYN"));

	m_arpDialog.Create(IDD_ARP, GetDlgItem(IDC_MYTAB));
	m_icmpDialog.Create(IDD_ICMP, GetDlgItem(IDC_MYTAB));
	m_tcpUdpDialog.Create(IDD_TCPUDP, GetDlgItem(IDC_MYTAB));
	m_tcpSynDialog.Create(IDD_TCPSYN, GetDlgItem(IDC_MYTAB));

	CRect rs;
	m_tab.GetClientRect(&rs);
	//调整子对话框在父窗口中的位置 
	rs.top += 20;
	rs.bottom -= 1;
	rs.left += 1;
	rs.right -= 2;

	//设置子对话框尺寸并移动到指定位置 
	m_arpDialog.MoveWindow(&rs);
	m_icmpDialog.MoveWindow(&rs);
	m_tcpUdpDialog.MoveWindow(&rs);
	m_tcpSynDialog.MoveWindow(&rs);
	
	//分别设置隐藏和显示 
	m_arpDialog.ShowWindow(true);
	m_icmpDialog.ShowWindow(false);
	m_tcpUdpDialog.ShowWindow(false);
	m_tcpSynDialog.ShowWindow(false);
	//设置默认的选项卡 
	m_tab.SetCurSel(0);
	m_arpDialog.InitDevs();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}





void CSCANDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSCANDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSCANDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSCANDlg::OnTcnSelchangeMytab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	int CulSel = m_tab.GetCurSel();
	switch (CulSel)
	{
	case 0:
		m_arpDialog.ShowWindow(true);
		m_icmpDialog.ShowWindow(false);
		m_tcpUdpDialog.ShowWindow(false);
		m_tcpSynDialog.ShowWindow(false);
		m_arpDialog.InitDevs();
		m_icmpDialog.ClearnSocket();
		break;
	case 1:
		m_arpDialog.ShowWindow(false);
		m_icmpDialog.ShowWindow(true);
		m_tcpUdpDialog.ShowWindow(false);
		m_tcpSynDialog.ShowWindow(false);
		m_arpDialog.FreeDevs();
		m_icmpDialog.InitSocket();
		break;
	case 2:
		m_arpDialog.ShowWindow(false);
		m_icmpDialog.ShowWindow(false);
		m_tcpUdpDialog.ShowWindow(true);
		m_tcpSynDialog.ShowWindow(false);
		m_arpDialog.FreeDevs();
		m_icmpDialog.ClearnSocket();
		break;
	case 3:
		m_arpDialog.ShowWindow(false);
		m_icmpDialog.ShowWindow(false);
		m_tcpUdpDialog.ShowWindow(false);
		m_tcpSynDialog.ShowWindow(true);
		m_arpDialog.FreeDevs();
		m_icmpDialog.ClearnSocket();
		break;
	default:
		m_arpDialog.FreeDevs();
		break;
	}
	*pResult = 0;
}


void CSCANDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
