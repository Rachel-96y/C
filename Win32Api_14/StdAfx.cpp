// stdafx.cpp : source file that includes just the standard includes
//	Win32Api_14.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

//////////////////////////////////////////////////////////////////////
void WINAPIV OutputDebugStringF(const char *format, ...)
{
	/*
		���ǵ�����صĺ��� ֻ�� _DEBUG ģʽ������
	*/
    va_list vlArgs;
    char    *strBuffer = (char*)GlobalAlloc(GPTR, 4096);
    va_start(vlArgs, format);
    _vsnprintf(strBuffer, 4096 - 1, format, vlArgs);
    va_end(vlArgs);  
    strcat(strBuffer, "\n");
    OutputDebugStringA(strBuffer);
    GlobalFree(strBuffer);

    return;
}

//////////////////////////////////////////////////////////////////////
HANDLE WINAPI CheckIsExsist(void)
{
	/*
		����Ƿ�ǰ�������������һ��
		�������ִ�гɹ��򷵻�һ���ں˶�����
	*/

	// ��ȡ�ں˶����д˳�����صı�־
	HANDLE g_hMutex = ::OpenMutex(MUTEX_ALL_ACCESS, FALSE, "CHECK_EXSIST_WIN32API_FLAG");

	// ���ڴ洢�´������ں˾��
	HANDLE g_hCHECK_EXSIST_WIN32API_FLAG = NULL;
	
	// ֵΪ0������ǵ�һ������,��OpenMutexִ��ʧ��
	if (!g_hMutex)
	{
		// ����˳����ǵ�һ�������򴴽��ں˶�������ȫ�ֱ�־
		g_hCHECK_EXSIST_WIN32API_FLAG = ::CreateMutex(NULL, FALSE, "CHECK_EXSIST_WIN32API_FLAG");
		if (!g_hCHECK_EXSIST_WIN32API_FLAG)
		{
			_exit(0);
		}
	}
	else
	{
		// ����˳����Ѿ�ִ����ֱ���˳�
		_exit(0);
	}

	// �����ں˶�����
	return g_hCHECK_EXSIST_WIN32API_FLAG;
}

//////////////////////////////////////////////////////////////////////