
// SCANDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include"ARPDialog.h"
#include "ICMPDialog.h"
#include "TCPUDPDialog.h"
#include "TCPSYNDialog.h"


// CSCANDlg 对话框
class CSCANDlg : public CDialogEx
{
// 构造
public:
	CSCANDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SCAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CARPDialog m_arpDialog;
	CICMPDialog m_icmpDialog;
	CTCPUDPDialog m_tcpUdpDialog;
	CTCPSYNDialog m_tcpSynDialog;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
