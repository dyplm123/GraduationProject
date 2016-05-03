// ICMPDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SCAN.h"
#include "ICMPDialog.h"
#include "afxdialogex.h"

ICMPScan *pIcmpScan;
// CICMPDialog �Ի���

IMPLEMENT_DYNAMIC(CICMPDialog, CDialogEx)

CICMPDialog::CICMPDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CICMPDialog::IDD, pParent)
	, m_startIP(_T(""))
	, m_endIP(_T(""))
	, m_message(_T(""))
{

}

CICMPDialog::~CICMPDialog()
{
}

void CICMPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_startIP);
	DDX_Text(pDX, IDC_EDIT2, m_endIP);
	DDX_Text(pDX, IDC_MESSAGE, m_message);
	DDX_Control(pDX, IDC_LIST1, m_result);
}


BEGIN_MESSAGE_MAP(CICMPDialog, CDialogEx)
	ON_BN_CLICKED(IDC_START, &CICMPDialog::OnBnClickedStart)
	ON_BN_CLICKED(IDC_END, &CICMPDialog::OnBnClickedEnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CICMPDialog ��Ϣ�������


void CICMPDialog::InitSocket()
{
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	if (pIcmpScan==NULL)
		pIcmpScan = new ICMPScan();
	if (!pIcmpScan->InitSocket())
	{
		MessageBox(_T("Socket��ʼ��ʧ�ܣ�"));
		exit(1);
	}
}


void CICMPDialog::ClearnSocket()
{
	if (pIcmpScan != NULL)
	{
		pIcmpScan->ClearSocket();
		delete(pIcmpScan);
		pIcmpScan = NULL;
	}
}

UINT IcmpStartScan(LPVOID pParament)
{
	UINT sIP, eIP;
	CListBox * result;
	ICMPDIALOGTHREADPARAM* threadParam = (ICMPDIALOGTHREADPARAM*)pParament;
	sIP = threadParam->startIP;
	eIP = threadParam->endIP;
	result = threadParam->result;
	pIcmpScan->Scan(sIP, eIP, result);
	return 0;
}

void CICMPDialog::OnBnClickedStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_startIP == "" || m_endIP == "")
	{
		MessageBox(_T("������IP��Χ��"));

	}
	else if (!IsRightIP(m_startIP) || !IsRightIP(m_endIP))
	{
		MessageBox(_T("�����IP��ʽ���Ϸ���"));
	}
	else
	{
		unsigned long sIP, eIP;
		sIP = IPStrToInt(m_startIP);
		eIP = IPStrToInt(m_endIP);
		if (IPIntTurn(sIP) > IPIntTurn(eIP))
		{
			MessageBox(_T("��ʼIPӦ�ñȽ���IPС!"));
		}
		else
		{
			ICMPDIALOGTHREADPARAM ThreadParam;
			ThreadParam.startIP = IPIntTurn(sIP);
			ThreadParam.endIP = IPIntTurn(eIP);
			ThreadParam.result = &m_result;
			pThread = AfxBeginThread(IcmpStartScan, &ThreadParam);
			GetDlgItem(IDC_START)->EnableWindow(FALSE);
			m_message = _T("����ɨ��........");
			UpdateData(FALSE);
			SetTimer(1, 500, NULL);
		}
	}
}


void CICMPDialog::OnBnClickedEnd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	pIcmpScan->SetOverFlag(TRUE);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	m_message = _T("��ֹͣ");
	UpdateData(FALSE);
}


void CICMPDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (pIcmpScan->GetOverFlag())
	{
		GetDlgItem(IDC_START)->EnableWindow(TRUE);
		m_message = _T("�����");
		UpdateData(FALSE);
		KillTimer(1);
	}

	CDialogEx::OnTimer(nIDEvent);
}
