#include "stdafx.h"
#include "ICMPScan.h"


ICMPScan::ICMPScan()
{
}


ICMPScan::~ICMPScan()
{
}


BOOL ICMPScan::InitSocket()
{
	isOverFlag = FALSE;
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
		return FALSE;
	else
		return TRUE;
}


void ICMPScan::ClearSocket()
{
	WSACleanup();
}

BOOL DecodeIcmpResponse(char* pBuf, int iPacketSize,UINT destIP)
{
	//检查数据报大小的合法性
	IPHEADER* pIpHdr = (IPHEADER*)pBuf;
	int iIpHdrLen = 20;
	if (iPacketSize < (int)(iIpHdrLen + sizeof(ICMPHEADER)))
		return FALSE;
	//按照ICMP包类型检查id字段和序列号以确定是否是程序应接收的Icmp包
	ICMPHEADER* pIcmpHdr = (ICMPHEADER*)(pBuf + iIpHdrLen);
	//处理正确收到的ICMP数据报
	if (pIcmpHdr->i_type == 0 && pIpHdr->sourceIP==destIP)
	{
		return TRUE;
	}
	return FALSE;
}

DWORD IcmpRecv(SOCKET s, SOCKADDR_IN *saDest, CListBox *result)
{
	//创建ICMP包接收缓冲区
	char IcmpRecvBuf[1024];
	memset(IcmpRecvBuf, 0, sizeof(IcmpRecvBuf));

	int nRet;
	int nAddrLen = sizeof(struct sockaddr_in);
	SOCKADDR_IN *saFrom=NULL;

	// Receive the echo reply	
	nRet = recvfrom(s,					// socket
		(LPSTR)&IcmpRecvBuf,	// buffer
		1024,	// size of buffer
		0,					// flags
		(LPSOCKADDR)saFrom,	// From address
		&nAddrLen);			// pointer to address len

	//打印输出
	if (nRet != SOCKET_ERROR) //接收没有错误
	{
		//解码得到的数据包，如果解码正确则跳出接收循环发送下一个EchoRequest包
		if (DecodeIcmpResponse(IcmpRecvBuf, nRet, saDest->sin_addr.s_addr))
		{	
			result->AddString(IPIntToStr(saDest->sin_addr.s_addr));
			return 1;
		}
		else
		{
			return 0;
		}

	}
	else if (WSAGetLastError() == WSAETIMEDOUT) //接收超时，打印星号
	{
		return 0;
	}
	else
	{
		return -1;
	}
	return 0;
}

DWORD WINAPI IcmpScan(LPVOID pParament)
{
	SOCKET sockRaw;
	int iResult;
	ICMPTHREADPARAM *pThreadParam = (ICMPTHREADPARAM *)pParament;
	sockaddr_in destAddr = pThreadParam->addrDest;
	destAddr.sin_family = AF_INET;

	sockRaw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	//设置接收超时选项
	int iTimeout = 1000;
	iResult = setsockopt(sockRaw, SOL_SOCKET, SO_RCVTIMEO, (char*)&iTimeout, sizeof(iTimeout));


	int nRet;
	char IcmpSendBuf[sizeof(ICMPHEADER)];

	//填充数据包
	memset(IcmpSendBuf, 0, sizeof(IcmpSendBuf));
	ICMPHEADER *pIcmpHeader = (ICMPHEADER*)IcmpSendBuf;
	pIcmpHeader->i_type = 8; //回写请求消息
	pIcmpHeader->i_code = 0;
	pIcmpHeader->i_id = (USHORT)GetCurrentProcessId();
	pIcmpHeader->i_seq = 0x0;//
	pIcmpHeader->i_cksum = 0;
	pIcmpHeader->timestamp = 0x01020304;//数据，随意，大小也是随意，这里我定义的4B
	pIcmpHeader->i_cksum = CheckSum((USHORT*)pIcmpHeader, sizeof(ICMPHEADER));

	nRet = sendto(sockRaw, IcmpSendBuf, sizeof(IcmpSendBuf), 0, (LPSOCKADDR)&destAddr, sizeof(SOCKADDR_IN));

	if (nRet == SOCKET_ERROR)
	{
		return -1;
	}

	iResult = IcmpRecv(sockRaw,&destAddr, pThreadParam->result);
	return 0;
}

void ICMPScan::Scan(UINT startIP, UINT endIP, CListBox* result)
{
	for (int ip = startIP; ip <= endIP;ip++)
	{
		if (isOverFlag)
			break;
		sockaddr_in destAddr;
		destAddr.sin_family = AF_INET;

		threadParam.result = result;
		threadParam.addrDest.sin_addr.S_un.S_addr = IPIntTurn(ip);
		CreateThread(NULL, 0, IcmpScan, &threadParam, 0, 0);
		Sleep(1000);
	}
	isOverFlag = TRUE;
}


BOOL ICMPScan::GetOverFlag()
{
	return isOverFlag;
}


void ICMPScan::SetOverFlag(bool value)
{
	isOverFlag = value;
}
