#include "stdafx.h"
#include"tool.h"

CString IPIntToStr(UINT IPINT)
{
	CString IPStr;
	UNIONIP IP;
	IP.uInt = IPINT;
	IPStr.Format(_T("%d.%d.%d.%d"), IP.ucByte[0], IP.ucByte[1], IP.ucByte[2], IP.ucByte[3]);
	return IPStr;
}

UINT IPStrToInt(CString IPStr)
{
	UNIONIP IP;
	int i, j = 0;
	IPStr.TrimLeft();
	IPStr.TrimRight();
	i = 0;
	IPStr += ".";
	CString temp;
	for (int m = 0; m < 4; m++)
	{
		temp = "";
		while (IPStr.GetAt(i) != '.')
		{
			temp += IPStr.GetAt(i);
			i++;
		}
		i++;
		IP.ucByte[m] = _ttoi(temp);
	}
	return IP.uInt;
}

BOOL IsRightIP(CString strIP)
{
	int i, j = 0;
	strIP.TrimLeft();
	strIP.TrimRight();
	for (i = 0; i < strIP.GetLength(); i++)
	{
		if (strIP.GetAt(i)<'0' || strIP.GetAt(i)>'9')
		if (strIP.GetAt(i) == '.')
			j++;
		else
		{
			return FALSE;
		}
	}
	if (j != 3)
	{
		return FALSE;
	}
	i = 0;
	strIP += ".";
	CString temp;
	for (int m = 0; m < 4; m++)
	{
		temp = "";
		while (strIP.GetAt(i) != '.')
		{
			temp += strIP.GetAt(i);
			i++;
		}
		i++;
		if (temp == "" || _ttoi(temp)>0xff)
		{
			return FALSE;
		}
	}
	return TRUE;
}

UINT IPIntTurn(UINT IPINT)
{
	UNIONIP IP,t;
	UINT result;
	IP.uInt = IPINT;
	t.cByte[0] = IP.cByte[3];
	t.cByte[1] = IP.cByte[2];
	t.cByte[2] = IP.cByte[1];
	t.cByte[3] = IP.cByte[0];
	result = t.uInt;
	return result;
}

USHORT CheckSum(USHORT *buffer, int size)
{
	unsigned long cksum = 0;
	while (size > 1)
	{
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}
	if (size)
	{
		cksum += *(UCHAR*)buffer;
	}
	while (cksum >> 16)
		cksum = (cksum >> 16) + (cksum & 0xffff);
	return (USHORT)(~cksum);
}