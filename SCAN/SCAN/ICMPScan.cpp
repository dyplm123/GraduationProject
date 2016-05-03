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
	//������ݱ���С�ĺϷ���
	IPHEADER* pIpHdr = (IPHEADER*)pBuf;
	int iIpHdrLen = 20;
	if (iPacketSize < (int)(iIpHdrLen + sizeof(ICMPHEADER)))
		return FALSE;
	//����ICMP�����ͼ��id�ֶκ����к���ȷ���Ƿ��ǳ���Ӧ���յ�Icmp��
	ICMPHEADER* pIcmpHdr = (ICMPHEADER*)(pBuf + iIpHdrLen);
	//������ȷ�յ���ICMP���ݱ�
	if (pIcmpHdr->i_type == 0 && pIpHdr->sourceIP==destIP)
	{
		return TRUE;
	}
	return FALSE;
}

DWORD IcmpRecv(SOCKET s, SOCKADDR_IN *saDest, CListBox *result)
{
	//����ICMP�����ջ�����
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

	//��ӡ���
	if (nRet != SOCKET_ERROR) //����û�д���
	{
		//����õ������ݰ������������ȷ����������ѭ��������һ��EchoRequest��
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
	else if (WSAGetLastError() == WSAETIMEDOUT) //���ճ�ʱ����ӡ�Ǻ�
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
	//���ý��ճ�ʱѡ��
	int iTimeout = 1000;
	iResult = setsockopt(sockRaw, SOL_SOCKET, SO_RCVTIMEO, (char*)&iTimeout, sizeof(iTimeout));


	int nRet;
	char IcmpSendBuf[sizeof(ICMPHEADER)];

	//������ݰ�
	memset(IcmpSendBuf, 0, sizeof(IcmpSendBuf));
	ICMPHEADER *pIcmpHeader = (ICMPHEADER*)IcmpSendBuf;
	pIcmpHeader->i_type = 8; //��д������Ϣ
	pIcmpHeader->i_code = 0;
	pIcmpHeader->i_id = (USHORT)GetCurrentProcessId();
	pIcmpHeader->i_seq = 0x0;//
	pIcmpHeader->i_cksum = 0;
	pIcmpHeader->timestamp = 0x01020304;//���ݣ����⣬��СҲ�����⣬�����Ҷ����4B
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
