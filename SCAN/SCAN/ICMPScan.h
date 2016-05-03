#pragma once
#include "tool.h"
class ICMPScan
{
public:
	ICMPScan();
	~ICMPScan();
	BOOL InitSocket();
	void ClearSocket();
	void Scan(UINT startIP, UINT endIP, CListBox* result);
protected:
	ICMPTHREADPARAM threadParam;
	BOOL isOverFlag;
public:
	BOOL GetOverFlag();
	void SetOverFlag(bool value);
};

