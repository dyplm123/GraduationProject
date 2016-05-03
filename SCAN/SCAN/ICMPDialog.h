#pragma once
#include "afxwin.h"
#include "ICMPScan.h"


// CICMPDialog 对话框

class CICMPDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CICMPDialog)

public:
	CICMPDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CICMPDialog();

// 对话框数据
	enum { IDD = IDD_ICMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_startIP;
	CString m_endIP;
	CString m_message;
	CListBox m_result;
	void InitSocket();
	void ClearnSocket();
protected:
//	ICMPScan* pIcmpScan;
public:
	afx_msg void OnBnClickedStart();
protected:
	CWinThread* pThread;
public:
	afx_msg void OnBnClickedEnd();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
