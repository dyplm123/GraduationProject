// TCPSYNDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SCAN.h"
#include "TCPSYNDialog.h"
#include "afxdialogex.h"


// CTCPSYNDialog 对话框

IMPLEMENT_DYNAMIC(CTCPSYNDialog, CDialogEx)

CTCPSYNDialog::CTCPSYNDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCPSYNDialog::IDD, pParent)
{

}

CTCPSYNDialog::~CTCPSYNDialog()
{
}

void CTCPSYNDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTCPSYNDialog, CDialogEx)
END_MESSAGE_MAP()


// CTCPSYNDialog 消息处理程序
