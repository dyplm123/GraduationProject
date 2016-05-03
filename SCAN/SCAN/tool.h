#pragma once
#define HAVE_REMOTE
#include"pcap.h"
#include"packet32.h"
#include "ntddndis.h"

#include"winsock2.h"
#pragma comment(lib,"ws2_32")
#include "mstcpip.h"


struct ethernet_head
{
	unsigned char dest_mac[6];
	unsigned char source_mac[6];
	unsigned short eh_type;
}; 

struct arp_head
{
	unsigned short hardware_type;
	unsigned short protocol_type;
	unsigned char add_len;
	unsigned char pro_len;
	unsigned short option;
	unsigned char sour_addr[6];
	unsigned long sour_ip;
	unsigned char dest_addr[6];
	unsigned long dest_ip;
	unsigned char padding[18];
};

struct arp_packet
{
	ethernet_head eth;
	arp_head arp;
};

typedef union MultiByteStruct
{
	int iInt;
	float fFloat;
	UINT uInt;
	ULONG uLong;
	DWORD dwDword;
	WORD wWord[2];
	UCHAR ucByte[4];
	char cByte[4];
}UNIONIP,*PUNIONIP;

CString IPIntToStr(UINT IPINT);


UINT IPStrToInt(CString IPStr);

BOOL IsRightIP(CString strIP);

UINT IPIntTurn(UINT IPINT);

typedef struct ARPThreadParam
{
	UINT srcIP;
	UINT destIP;
	CHAR MAC[6];
	pcap_t* adhandle;
	CListBox* result;
	pcap_if_t *SelectDev;
}ARPTHREADPARAM;

typedef struct ARPDialogThreadParam
{
	UINT startIP;
	UINT endIP;
	CListBox* result;
}ARPDIALOGTHREADPARAM;

typedef struct ICMPThreadParam
{
	sockaddr_in addrDest;
	CListBox * result;
}ICMPTHREADPARAM;

typedef struct ICMPDialogThreadParam
{
	UINT startIP;
	UINT endIP;
	CListBox * result;
}ICMPDIALOGTHREADPARAM;

typedef struct _iphdr
{
	unsigned char h_lenver;
	unsigned char tos;
	unsigned short total_len;
	unsigned short ident;
	unsigned short frag_and_flags;
	unsigned char ttl;
	unsigned char proto;
	unsigned short checksum;
	unsigned int sourceIP;
	unsigned int destIP;
}IPHEADER;

typedef struct psd_hdr
{
	unsigned long saddr;
	unsigned long daddr;
	char mbz;
	char ptcl;
	unsigned short tcpl;
}PSDHEADER;

typedef struct _tcphdr
{
	USHORT th_sport;
	USHORT th_dport;
	unsigned int th_seq;
	unsigned int th_ack;
	unsigned char th_lenres;
	unsigned char th_flag;
	USHORT th_win;
	USHORT th_sum;
	USHORT th_urp;
}TCPHEADER;

typedef struct _udphdr
{
	unsigned short uh_sport;
	unsigned short uh_dport;
	unsigned short uh_len;
	unsigned short uh_sum;
}UDPHEADER;

//icmp不同用途的包头不一样，只有类型，代码，校验和一样，这里请参考回送请求和回送响应icmp包格式
typedef struct _icmphdr
{
	BYTE i_type;
	BYTE i_code;
	USHORT i_cksum;
	USHORT i_id;
	USHORT i_seq;
	ULONG timestamp;
}ICMPHEADER;

//计算检验和函数
USHORT CheckSum(USHORT *buffer, int size);
