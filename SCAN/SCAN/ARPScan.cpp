#include "stdafx.h"
#include "ARPScan.h"

unsigned char *BuildArpPacket(unsigned char* source_mac, unsigned long srcIP, unsigned long destIP)
{
	static struct arp_packet packet;

	//目的MAC地址为广播地址，FF-FF-FF-FF-FF-FF 
	memset(packet.eth.dest_mac, 0xFF, 6);
	//源MAC地址 
	memcpy(packet.eth.source_mac, source_mac, 6);
	//上层协议为ARP协议，0x0806 
	packet.eth.eh_type = htons(0x0806);
	//硬件类型，Ethernet是0x0001 
	packet.arp.hardware_type = htons(0x0001);
	//上层协议类型，IP为0x0800 
	packet.arp.protocol_type = htons(0x0800);
	//硬件地址长度：MAC地址长度为0x06 
	packet.arp.add_len = 0x06;
	//协议地址长度：IP地址长度为0x04 
	packet.arp.pro_len = 0x04;
	//操作：ARP请求为1 
	packet.arp.option = htons(0x0001);
	//源MAC地址 
	memcpy(packet.arp.sour_addr, source_mac, 6);
	//源IP地址 
	packet.arp.sour_ip = srcIP;
	//目的MAC地址，填充0 
	memset(packet.arp.dest_addr, 0, 6);
	//目的IP地址 
	packet.arp.dest_ip = destIP;
	//填充数据，18个字节
	memset(packet.arp.padding, 0, 18);

	return (unsigned char*)&packet;
}

DWORD WINAPI RecvArp(LPVOID pParament)
{
	//pcap_if_t * alldevs;
	pcap_if_t *d;
	pcap_t * adhandle;//定义包捕捉句柄
	char errbuf[PCAP_ERRBUF_SIZE];//错误缓冲最小为256
	pcap_addr_t *pAddr;
	struct bpf_program fcode;
	char packet_filter[] = "arp";
	int res;
	struct pcap_pkthdr * header;
	const u_char * pkt_data;

	unsigned long netmask;         //子网掩码 
	unsigned long srcIP,destIP;
	CListBox* result;
	ARPTHREADPARAM* ThreadParam = (ARPTHREADPARAM*)pParament;
	destIP = ThreadParam->srcIP;
	srcIP = ThreadParam->destIP;
	result = ThreadParam->result;
	/*if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		return -1;
	}*/

	d = ThreadParam->SelectDev;
	if ((adhandle = pcap_open_live(d->name, 65536, 0, 1000, errbuf)) == NULL)
	{
		/* 释放设备列表 */
		//pcap_freealldevs(alldevs);
		return -1;
	}

	pAddr = d->addresses;
	//netmask = ((struct sockaddr_in*)pAddr->next->addr)->sin_addr.S_un.S_addr;
	netmask = ((struct sockaddr_in*)pAddr->next->netmask)->sin_addr.S_un.S_addr;

	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
	{
		//pcap_freealldevs(alldevs);
		return -1;
	}

	//设置过滤器
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		//pcap_freealldevs(alldevs);
		return -1;
	}

	int time = 0;
	//result->AddString(IPIntToStr(srcIP));
	while ((res = pcap_next_ex(adhandle, &header, &pkt_data)) >= 0 && time<20)
	{
		//循环解析ARP数据包

		if (res == 0)//超时 
		{
			time++;
			//result->AddString(_T("."));
			continue;
		}
		//result->AddString(_T("..."));
		arp_packet* arph = (arp_packet *)pkt_data;
		if (arph->arp.sour_ip == srcIP && arph->arp.dest_ip == destIP)
		{
			result->AddString(IPIntToStr(srcIP));
			break;
		}
		time++;
	}
}

DWORD WINAPI ArpScan(LPVOID pParament)
{
	unsigned char *packet;
	ARPTHREADPARAM* ThreadParam = (ARPTHREADPARAM*)pParament;
	UINT srcIP, destIP;
	unsigned char *mac=new unsigned char[6];
	CListBox *result;
	pcap_t *adhandle;
	srcIP = ThreadParam->srcIP;
	destIP = ThreadParam->destIP;
	memcpy(mac, ThreadParam->MAC, 6);
	result = ThreadParam->result;
	adhandle = ThreadParam->adhandle;


	CreateThread(NULL, 0, RecvArp, pParament, 0, 0);

	packet = BuildArpPacket(mac, srcIP, destIP);
	pcap_sendpacket(adhandle, packet, 60);
	//pcap_sendpacket(adhandle, packet, 60);
	return 0;
}

ARPScan::ARPScan()
{
	IsOver = TRUE;
}


ARPScan::~ARPScan()
{
	if (alldevs)
	{
		pcap_freealldevs(alldevs);
	}
}

//初始化设备
bool ARPScan::InitInternet()
{
	pcap_if_t* d;
	//获取本机网卡列表
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		return false;
	}
	for (d = alldevs; d; d = d->next)
	{
		CString temp;
		temp=d->description+d->flags;
		alldevsName.push_back(temp);
	}
	return true;
}

//获取错误信息
CString ARPScan::GetErrBuf()
{
	CString temp;
	temp.Format(_T("%s"), errbuf);
	return temp;
}

//返回所有的设备名称
vector<CString> ARPScan::GetAlldevsName()
{
	return alldevsName;
}

//获取选中的设备
void ARPScan::SetCulDev(int value)
{
	int i = 0;
	for (culDev = alldevs; i < value; culDev = culDev->next, i++);
	GetMac(culDev->name);
}

//返回选中的设备信息
CString ARPScan::GetCulDev()
{
	CString t,t1,t2;
	t2 = culDev->description;
	t1.Format(_T("%.2x-%.2x-%.2x-%.2x-%.2x-%.2x"), culMac[0], culMac[1], culMac[2], culMac[3], culMac[4], culMac[5]);
	t = t2 + t1;
	
	return t;
}

//获取当前设备的mac地址
void ARPScan::GetMac(char* devName)
{
	static u_char mac[6];
	LPADAPTER lpAdapter = PacketOpenAdapter(devName);
	if (!lpAdapter || (lpAdapter->hFile == INVALID_HANDLE_VALUE))
		return ;
	PPACKET_OID_DATA OidData = (PPACKET_OID_DATA)malloc(6 + sizeof(PACKET_OID_DATA));
	if (OidData == NULL)
	{
		PacketCloseAdapter(lpAdapter);
		return ;
	}

	OidData->Oid = OID_802_3_CURRENT_ADDRESS;
	OidData->Length = 6;
	memset(OidData->Data, 0, 6);
	BOOLEAN Status = PacketRequest(lpAdapter, FALSE, OidData);
	if (Status)
		memcpy(mac, (u_char*)(OidData->Data), 6);
	free(OidData);
	PacketCloseAdapter(lpAdapter);
	culMac = mac;
}


void ARPScan::Scan(UINT IPBegin, UINT IPEnd, CListBox *result)
{
	pcap_addr_t *pAddr;
	startIP = IPBegin;
	endIP = IPEnd;
	pAddr = culDev->addresses;
	culIP = ((struct sockaddr_in*)pAddr->next->addr)->sin_addr.S_un.S_addr;
	culNetmask = ((struct sockaddr_in*)pAddr->next->netmask)->sin_addr.S_un.S_addr;

	for (UINT ip = startIP; ip <= endIP; ip++)
	{
		if (IsOver)
			return;
		UINT tIP = IPIntTurn(culIP);
		UINT tMask = IPIntTurn(culNetmask);
		if ((tIP&tMask) < (ip&tMask))
			return;
		else if ((tIP&tMask) > (ip&tMask))
		{
			ip = (ip | (~tMask)) + 1;
		}
		else if (tIP==ip || !(ip&~tMask))
		{
			continue;
		}
		else
		{	
			threadParam.srcIP = culIP;
			threadParam.destIP = IPIntTurn(ip);
			memcpy(threadParam.MAC, culMac, 6);
			threadParam.result = result;
			threadParam.adhandle = adhandle;
			//result->AddString(IPIntToStr(IPIntTurn(ip)));
			threadParam.SelectDev = culDev;

			CreateThread(NULL, 0, ArpScan, &threadParam, 0, 0);
			Sleep(1000);
		}
	}
	IsOver = TRUE;
	//Sleep(10000);
}

BOOL ARPScan::OpenDev()
{
	if ((adhandle = pcap_open_live(culDev->name, 65536, 0, 1000, errbuf)) == NULL)
	{
		return FALSE;
	}
	return TRUE;
}


void ARPScan::SetOverFlag(bool value)
{
	IsOver = value;
}


BOOL ARPScan::GetOverFlag()
{
	return IsOver;
}
