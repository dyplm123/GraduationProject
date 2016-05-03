#pragma once
#include "ARPScan.h"
#include "afxwin.h"

// CARPDialog 对话框

class CARPDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CARPDialog)

public:
	CARPDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CARPDialog();

// 对话框数据
	enum { IDD = IDD_ARP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_startIP;
	CString m_endIP;
//	ARPScan * pArpScan;
	
	void InitDevs();
	CComboBox m_devs;
	void FreeDevs();
	afx_msg void OnCbnSelchangeSelinterface();
	CString m_message;
	afx_msg void OnBnClickedArpstart();
	CListBox m_result;
protected:
	CWinThread* pThread;
public:
	afx_msg void OnBnClickedArpend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
