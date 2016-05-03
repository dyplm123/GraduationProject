// TCPUDPDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SCAN.h"
#include "TCPUDPDialog.h"
#include "afxdialogex.h"


// CTCPUDPDialog 对话框

IMPLEMENT_DYNAMIC(CTCPUDPDialog, CDialogEx)

CTCPUDPDialog::CTCPUDPDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCPUDPDialog::IDD, pParent)
{

}

CTCPUDPDialog::~CTCPUDPDialog()
{
}

void CTCPUDPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTCPUDPDialog, CDialogEx)
END_MESSAGE_MAP()


// CTCPUDPDialog 消息处理程序
