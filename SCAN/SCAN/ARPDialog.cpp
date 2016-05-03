// ARPDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SCAN.h"
#include "ARPDialog.h"
#include "afxdialogex.h"

ARPScan * pArpScan;
// CARPDialog 对话框

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


// CARPDialog 消息处理程序

void CARPDialog::InitDevs()
{
	m_result.AddString(_T("扫描结果："));
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
			MessageBox(_T("获取网卡错误，程序结束！"));
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

//选中一个设备之后
void CARPDialog::OnCbnSelchangeSelinterface()
{
	// TODO:  在此添加控件通知处理程序代码
	int t;
	pArpScan->SetCulDev(m_devs.GetCurSel());
	m_message =_T("当前选中的网络设备:")+ pArpScan->GetCulDev();

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
	// TODO:  在此添加控件通知处理程序代码

	if (m_devs.GetCurSel()==-1)
	{
		MessageBox(_T("请选择一个网络设备！"));
	}
	else
	{
		UpdateData(TRUE);
		if (!pArpScan->OpenDev())
			MessageBox(_T("打开网络设备失败！！"));
		else
		{
			if (m_startIP == "" || m_endIP == "")
				MessageBox(_T("请输入IP范围！"));
			else
			{
				if (!IsRightIP(m_startIP) || !IsRightIP(m_endIP))
					MessageBox(_T("IP格式错误！"));

				else
				{
					unsigned long sIP, eIP;
					//UNIONIP uIPBegin, uIPEnd;
					sIP = IPStrToInt(m_startIP);
					eIP = IPStrToInt(m_endIP);
					if (IPIntTurn(sIP) > IPIntTurn(eIP))
					{
						MessageBox(_T("起始IP应该比结束IP小!"));
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
						m_message = _T("正在扫描........");
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
	// TODO:  在此添加控件通知处理程序代码
	pArpScan->SetOverFlag(TRUE);
	GetDlgItem(IDC_ARPSTART)->EnableWindow(TRUE);
	m_message = _T("已停止");
	UpdateData(FALSE);
}



void CARPDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (pArpScan->GetOverFlag())
	{
		GetDlgItem(IDC_ARPSTART)->EnableWindow(TRUE);
		m_message = _T("已完成");
		UpdateData(FALSE);
		KillTimer(1);
	}

	CDialogEx::OnTimer(nIDEvent);
}
