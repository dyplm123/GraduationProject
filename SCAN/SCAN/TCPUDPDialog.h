#pragma once


// CTCPUDPDialog 对话框

class CTCPUDPDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTCPUDPDialog)

public:
	CTCPUDPDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTCPUDPDialog();

// 对话框数据
	enum { IDD = IDD_TCPUDP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
