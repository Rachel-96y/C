// Win32Api_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	// setlocale(LC_ALL,"");

	// DbgPrintf("Hello\n");

	// HWND result =  FindWindow("Program Manager", 0);

	// DbgPrintf("%x\n", result);

	// MessageBox(0, 0, 0, 0);

	// DWORD Erro = ::GetLastError();

	// DbgPrintf("%d\n", Erro);


	/*
		������ϰ��										
		1���ֱ�ʹ�� wchar_t / wprintf / wcslen / wcscpy / wcscat / wcscmp / wcsstr						
		дһ������.					
		2����MSDN �˽�WinMain����3������������						
	*/
	
	TCHAR name[] = TEXT("����");
	DbgPrintf("%s\n", name);

	wprintf(L"����\n");  // ��Ҫ�ڿ���̨���

	DWORD result = wcslen(L"�Ұ�aa����");
	DbgPrintf("%d\n", result);
	
	wchar_t str1[] = L"�Ұ�aa����";
	CONST WCHAR str2[] = L"123";
	wcscpy(str1, str2);
	DbgPrintf("%s\n", str1);

	wchar_t str3[] = L"3125671";
	wchar_t str4[] = L"567";
	// wcscat(str3, str4);
	int ret = wcscmp(str3, str4);
	if (!ret)
	{
		DbgPrintf("���!");
	}

	wchar_t * answer = wcsstr(str3, str4);
	DbgPrintf("%d\n", *answer);

	// 2����MSDN �˽�WinMain����3������������		
	// hPrevInstance	Ӧ�ó����ǰһ��ʵ���ľ��������һ������Win32��Ӧ�ó��������������Ϊ�ա�
	// lpCmdLine		ָ��һ����β���ַ�����ָ��Ӧ�ó���������У��������������ơ�Ҫ�������������У���ʹ��GetCommandLine������
	// nCmdShow			ָ�����ڵ���ʾ��ʽ

	return 0;
}

