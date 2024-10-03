// stdafx.cpp : source file that includes just the standard includes
//	Win32Api_9.pch will be the pre-compiled header
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

VOID WINAPI CheckIsExsist(void)
{
	/*
		�˺���ͨ���������� ���ж������Ƿ�࿪
	*/
	
	// ����ɹ����ؽ��̿���ָ��
	LPVOID pSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// �� PROCESSENTRY32 �� dwSize ��ֵ
	PROCESSENTRY32 StructProcessEntry32 = {0};
	StructProcessEntry32.dwSize = sizeof(PROCESSENTRY32);

	// �� MODULEENTRY32 �� dwSize ��ֵ
	MODULEENTRY32 StructModuleEntry32 = {0};
	StructModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	// ��ȡ��һ������ �Ž� StructProcessEntry32.szExeFile ��
	Process32First(pSnapshot, &StructProcessEntry32);

	StructModuleEntry32.th32ProcessID = 0;

	// ����ɹ�����ģ�����ָ��
	HANDLE pModSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, StructProcessEntry32.th32ProcessID);

	// ��ȡ��һ��ģ�� �Ž� StructModuleEntry32.szExeFile ��
	Module32First(pModSnapshot, &StructModuleEntry32);

	// �õ���ǰ��������
	PTCHAR szBaseName = StructModuleEntry32.szModule;

	// ���� �����жϴ˳���(�д����ֵ�exe) �Ƿ���Ψһ��
	DWORD dwCount = 0;
	do
	{
		// �Ƚ������ַ����Ƿ����
		DWORD dwResult = strcmp(szBaseName, StructProcessEntry32.szExeFile);
		if (!dwResult)
		{
			dwCount++;
		}
	}
	// ��û���κν���ʱ����ѭ��
	while(Process32Next(pSnapshot, &StructProcessEntry32));

	if (dwCount == 1)
	{
		// ���ֻ��һ�����������ִ��
		return;
	}
	else
	{
		// ������һ��������ֱ���˳�
		exit(0);
	}
}