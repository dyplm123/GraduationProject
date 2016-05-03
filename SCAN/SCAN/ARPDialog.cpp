// ARPDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SCAN.h"
#include "ARPDialog.h"
#include "afxdialogex.h"

ARPScan * pArpScan;
// CARPDialog �Ի���

IMPLEMENT_DYNAMIC(CARPDialog, CDialogEx)

CARPDialog::CARPDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CARPDialog::IDD, pParent)
	, m_startIP(_T(""))
	, m_endIP(_T(""))
	, m_message(_T(""))
	, pThread(NULL)
{

}

CARPDialog::~CARPDialog()
{
}

void CARPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STARTIP, m_startIP);
	DDX_Text(pDX, IDC_ENDIP, m_endIP);
	DDX_Control(pDX, IDC_SELINTERFACE, m_devs);
	DDX_Text(pDX, IDC_TIP, m_message);
	DDX_Control(pDX, IDC_RESULT, m_result);
}


BEGIN_MESSAGE_MAP(CARPDialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_SELINTERFACE, &CARPDialog::OnCbnSelchangeSelinterface)
	ON_BN_CLICKED(IDC_ARPSTART, &CARPDialog::OnBnClickedArpstart)
	ON_BN_CLICKED(IDC_ARPEND, &CARPDialog::OnBnClickedArpend)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CARPDialog ��Ϣ�������

void CARPDialog::InitDevs()
{
	m_result.AddString(_T("ɨ������"));
	GetDlgItem(IDC_ARPSTART)->EnableWindow(TRUE);
	
	if (pArpScan == NULL)
	{
		pArpScan = new ARPScan();
		if (pArpScan->InitInternet())
		{
			vector <CString> name;
			name = pArpScan->GetAlldevsName();
			for (int i = 0; i < name.size(); i++)
			{
				m_devs.AddString(name[i]);
			}
		}
		else
		{
			MessageBox(_T("��ȡ�������󣬳��������"));
			exit(1);
		}
	}
	
}


void CARPDialog::FreeDevs()
{
	if (pArpScan != NULL)
	{
		delete(pArpScan);
		pArpScan = NULL;
	}
	m_devs.ResetContent();
	m_result.ResetContent();
}

//ѡ��һ���豸֮��
void CARPDialog::OnCbnSelchangeSelinterface()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int t;
	pArpScan->SetCulDev(m_devs.GetCurSel());
	m_message =_T("��ǰѡ�е������豸:")+ pArpScan->GetCulDev();

	UpdateData(FALSE);
}


UINT StartScan(LPVOID pParament)
{
	ARPDIALOGTHREADPARAM* ThreadParam = (ARPDIALOGTHREADPARAM*)pParament;
	pArpScan->Scan(ThreadParam->startIP, ThreadParam->endIP, ThreadParam->result);
	return 0;
}

void CARPDialog::OnBnClickedArpstart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (m_devs.GetCurSel()==-1)
	{
		MessageBox(_T("��ѡ��һ�������豸��"));
	}
	else
	{
		UpdateData(TRUE);
		if (!pArpScan->OpenDev())
			MessageBox(_T("�������豸ʧ�ܣ���"));
		else
		{
			if (m_startIP == "" || m_endIP == "")
				MessageBox(_T("������IP��Χ��"));
			else
			{
				if (!IsRightIP(m_startIP) || !IsRightIP(m_endIP))
					MessageBox(_T("IP��ʽ����"));

				else
				{
					unsigned long sIP, eIP;
					//UNIONIP uIPBegin, uIPEnd;
					sIP = IPStrToInt(m_startIP);
					eIP = IPStrToInt(m_endIP);
					if (IPIntTurn(sIP) > IPIntTurn(eIP))
					{
						MessageBox(_T("��ʼIPӦ�ñȽ���IPС!"));
					}
					else
					{
						ARPDIALOGTHREADPARAM ThreadParam;
						ThreadParam.startIP = IPIntTurn(sIP);
						ThreadParam.endIP = IPIntTurn(eIP);
						ThreadParam.result = &m_result;
						pThread = AfxBeginThread(StartScan, &ThreadParam);
						pArpScan->SetOverFlag(FALSE);
						GetDlgItem(IDC_ARPSTART)->EnableWindow(FALSE);
						m_message = _T("����ɨ��........");
						UpdateData(FALSE);
						SetTimer(1,500,NULL);
					}
				}

			}
		}
		
	}
}

void CARPDialog::OnBnClickedArpend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	pArpScan->SetOverFlag(TRUE);
	GetDlgItem(IDC_ARPSTART)->EnableWindow(TRUE);
	m_message = _T("��ֹͣ");
	UpdateData(FALSE);
}



void CARPDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (pArpScan->GetOverFlag())
	{
		GetDlgItem(IDC_ARPSTART)->EnableWindow(TRUE);
		m_message = _T("�����");
		UpdateData(FALSE);
		KillTimer(1);
	}

	CDialogEx::OnTimer(nIDEvent);
}
