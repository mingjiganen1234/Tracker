#include "stdafx.h"
#include "com.h"

com::com()
{
}

com::com(LPCSTR port)
{
	hCom = CreateFileA(port,//��������
		GENERIC_READ | GENERIC_WRITE,//�����д
		0, //��ռ��ʽ
		NULL,
		OPEN_EXISTING,//�򿪶����Ǵ���
		0,
		NULL);
	if (hCom == (HANDLE)-1)
	{
		hCom == NULL;
		return;
	}
	SetupComm(hCom, 100, 100);//�������������
	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = 57600;//������Ϊ9600bps  
	dcb.ByteSize = 8;//����λ8λ  
	dcb.Parity = NOPARITY;//��У��  
	dcb.StopBits = ONESTOPBIT; //1ֹͣλ
	SetCommState(hCom, &dcb);
	isWork = true;

}

com::~com()
{
}

CString com::sendBuf(byte *buf,int cnt)
{
	OVERLAPPED m_osWrite;
	DWORD dwBytesWrite;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	memset(&m_osWrite, 0, sizeof(OVERLAPPED));
	m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	dwBytesWrite = cnt;
	ClearCommError(hCom, &dwErrorFlags, &ComStat);//�������
	if (!WriteFile(hCom, buf, dwBytesWrite, &dwBytesWrite, &m_osWrite))	//����
	{
		return _T("����ʧ��");
	}
	return _T("Send:") + byte2string(buf,cnt);
}

bool com::close()
{
	isWork = false;
	isTrack = false;
	CloseHandle(hCom);
	hCom = NULL;
	return true;
}

CString com::byte2string(byte *buf, int cnt)
{
	CString s;
	for(int i=0;i<cnt;i++)
		s.Format(_T("%s %02x"), s, buf[i]);
	return s;
}