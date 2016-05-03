#pragma once
#include "afxwin.h"
#include "ICMPScan.h"


// CICMPDialog �Ի���

class CICMPDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CICMPDialog)

public:
	CICMPDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CICMPDialog();

// �Ի�������
	enum { IDD = IDD_ICMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
