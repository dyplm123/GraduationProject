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
};
