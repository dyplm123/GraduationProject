#pragma once


// CTCPUDPDialog �Ի���

class CTCPUDPDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTCPUDPDialog)

public:
	CTCPUDPDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTCPUDPDialog();

// �Ի�������
	enum { IDD = IDD_TCPUDP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit4();
	CString m_startIP;
	CString m_endIP;
	CString m_startPort;
	CString m_endPort;
	CString m_result;
	CString m_message;
	afx_msg void OnBnClickedTcpstart();
	afx_msg void OnBnClickedUdpstart();
	afx_msg void OnBnClickedEnd();
};
