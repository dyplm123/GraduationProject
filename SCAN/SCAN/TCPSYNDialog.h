#pragma once


// CTCPSYNDialog 对话框

class CTCPSYNDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTCPSYNDialog)

public:
	CTCPSYNDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTCPSYNDialog();

// 对话框数据
	enum { IDD = IDD_TCPSYN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
