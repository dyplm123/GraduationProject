#pragma once


// CTCPSYNDialog �Ի���

class CTCPSYNDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTCPSYNDialog)

public:
	CTCPSYNDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTCPSYNDialog();

// �Ի�������
	enum { IDD = IDD_TCPSYN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
