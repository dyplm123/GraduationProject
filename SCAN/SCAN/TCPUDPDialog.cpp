// TCPUDPDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SCAN.h"
#include "TCPUDPDialog.h"
#include "afxdialogex.h"


// CTCPUDPDialog �Ի���

IMPLEMENT_DYNAMIC(CTCPUDPDialog, CDialogEx)

CTCPUDPDialog::CTCPUDPDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCPUDPDialog::IDD, pParent)
	, m_startIP(_T(""))
	, m_endIP(_T(""))
	, m_startPort(_T(""))
	, m_endPort(_T(""))
	, m_result(_T(""))
	, m_message(_T(""))
{

}

CTCPUDPDialog::~CTCPUDPDialog()
{
}

void CTCPUDPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_startIP);
	DDX_Text(pDX, IDC_EDIT2, m_endIP);
	DDX_Text(pDX, IDC_EDIT3, m_startPort);
	DDX_Text(pDX, IDC_EDIT4, m_endPort);
	DDX_LBString(pDX, IDC_LIST1, m_result);
	DDX_Text(pDX, IDC_MESSAGE, m_message);
}


BEGIN_MESSAGE_MAP(CTCPUDPDialog, CDialogEx)
	ON_BN_CLICKED(IDC_TCPSTART, &CTCPUDPDialog::OnBnClickedTcpstart)
	ON_BN_CLICKED(IDC_UDPSTART, &CTCPUDPDialog::OnBnClickedUdpstart)
	ON_BN_CLICKED(IDC_END, &CTCPUDPDialog::OnBnClickedEnd)
END_MESSAGE_MAP()


// CTCPUDPDialog ��Ϣ�������


void CTCPUDPDialog::OnBnClickedTcpstart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTCPUDPDialog::OnBnClickedUdpstart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTCPUDPDialog::OnBnClickedEnd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
