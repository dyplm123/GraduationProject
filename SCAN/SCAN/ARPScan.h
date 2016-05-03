#pragma once
#include"tool.h"
#include <vector>
using namespace std;

class ARPScan
{
public:
	ARPScan();
	~ARPScan();
	
protected:
	pcap_if_t* alldevs;
	char errbuf[256];
public:
	bool InitInternet();
	
	CString GetErrBuf();
protected:
	vector<CString> alldevsName;
public:
	vector<CString> GetAlldevsName();
protected:
	pcap_if_t* culDev;
public:
	void SetCulDev(int value);
	CString GetCulDev();
protected:
	unsigned char* culMac;
	unsigned long culNetmask;
	unsigned long culIP;
	unsigned long startIP;
	unsigned long endIP;
public:
	void GetMac(char* devName);
	void Scan(UINT IPBegin, UINT IPEnd, CListBox* result);
protected:
	pcap_t* adhandle;
	ARPTHREADPARAM threadParam;
public:
	BOOL OpenDev();
protected:
	BOOL IsOver;
public:
	void SetOverFlag(bool value);
	BOOL GetOverFlag();
};

