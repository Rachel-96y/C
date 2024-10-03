// Win32Api_15.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

// ���¶�TLS������Ĵ�����VC++6.0�в���֧�� ��Ҫʹ�ø��߰汾 ��VS2010

// ����������,��Ҫʹ��TLS��
#pragma comment(linker, "/INCLUDE:__tls_used")


// TLS��ص�����(���������,һ��TLS�Ļص������ᱻִ��3��)
VOID NTAPI TLS_CALLBACK1(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{
	// ��һ��TLS�ص�����
	if (Reason == DLL_PROCESS_ATTACH)
	{
		MessageBox(0, "��һ��TLS�ص�����ִ�е�һ��", 0, 0);
	}
	if (Reason == DLL_THREAD_ATTACH)
	{
		MessageBox(0, "��һ��TLS�ص�����ִ�еڶ���", 0, 0);
	}
	if (Reason == DLL_THREAD_DETACH)
	{
		MessageBox(0, "��һ��TLS�ص�����ִ�е�����", 0, 0);
	}
	if (Reason == DLL_PROCESS_DETACH)
	{
		MessageBox(0, "��һ��TLS�ص�����ִ�е��Ĵ�", 0, 0);
	}
}

VOID NTAPI TLS_CALLBACK2(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH)
	{
		// �ڶ���TLS�ص�����
		MessageBox(0, "�ڶ���TLS�ص�����ִ�е�һ��", 0, 0);
	}
	if (Reason == DLL_THREAD_ATTACH)
	{
		MessageBox(0, "�ڶ���TLS�ص�����ִ�еڶ���", 0, 0);
	}
	if (Reason == DLL_THREAD_DETACH)
	{
		MessageBox(0, "�ڶ���TLS�ص�����ִ�е�����", 0, 0);
	}
	if (Reason == DLL_PROCESS_DETACH)
	{
		MessageBox(0, "�ڶ���TLS�ص�����ִ�е��Ĵ�", 0, 0);
	}
}


// �洢TLS�����ݻص�����
#pragma data_seg(".CRT$XLX")
PIMAGE_TLS_CALLBACK pIMAGE_TLS_CALLBACKs[] = {TLS_CALLBACK1, TLS_CALLBACK2, NULL};
#pragma data_seg()


typedef struct _FUNC{
	_FUNC()
	{
		MessageBox(0, "ȫ�ֱ���", 0, 0);
	}
}FUNC, *PFUNC;

FUNC flag;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	
	MessageBox(0, "������", 0, 0);
	return 0;
}