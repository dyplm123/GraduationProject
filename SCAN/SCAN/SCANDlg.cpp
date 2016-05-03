
// SCANDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SCAN.h"
#include "SCANDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSCANDlg �Ի���



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


// CSCANDlg ��Ϣ�������

BOOL CSCANDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

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
	//�����ӶԻ����ڸ������е�λ�� 
	rs.top += 20;
	rs.bottom -= 1;
	rs.left += 1;
	rs.right -= 2;

	//�����ӶԻ���ߴ粢�ƶ���ָ��λ�� 
	m_arpDialog.MoveWindow(&rs);
	m_icmpDialog.MoveWindow(&rs);
	m_tcpUdpDialog.MoveWindow(&rs);
	m_tcpSynDialog.MoveWindow(&rs);
	
	//�ֱ��������غ���ʾ 
	m_arpDialog.ShowWindow(true);
	m_icmpDialog.ShowWindow(false);
	m_tcpUdpDialog.ShowWindow(false);
	m_tcpSynDialog.ShowWindow(false);
	//����Ĭ�ϵ�ѡ� 
	m_tab.SetCurSel(0);
	m_arpDialog.InitDevs();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSCANDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSCANDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSCANDlg::OnTcnSelchangeMytab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}
