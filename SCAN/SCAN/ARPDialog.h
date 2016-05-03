#pragma once
#include "ARPScan.h"
#include "afxwin.h"

// CARPDialog �Ի���

class CARPDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CARPDialog)

public:
	CARPDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CARPDialog();

// �Ի�������
	enum { IDD = IDD_ARP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
