
// SCANDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include"ARPDialog.h"
#include "ICMPDialog.h"
#include "TCPUDPDialog.h"
#include "TCPSYNDialog.h"


// CSCANDlg �Ի���
class CSCANDlg : public CDialogEx
{
// ����
public:
	CSCANDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CARPDialog m_arpDialog;
	CICMPDialog m_icmpDialog;
	CTCPUDPDialog m_tcpUdpDialog;
	CTCPSYNDialog m_tcpSynDialog;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeMytab(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_tab;
	virtual void OnOK();
};
