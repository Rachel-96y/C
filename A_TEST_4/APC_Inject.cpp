// APC_Inject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>

// LoadLibraryA �����ַ���;
TCHAR g_szBuffer[13] = { 'L', 'o' , 'a', 'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y', 'A', 0};
// �洢ģ���ַ;
TCHAR g_szModulePath[MAX_PATH] = { 0 };
// �洢OpenThread��QueueUserAPCģ����;
HMODULE g_hModule = NULL;
HMODULE g_hModuleAPC = NULL;

BOOL ApcInject(DWORD dwPid)
{
	// ����Ҫʹ�õĺ���ָ�븳ֵ;
	g_hModule = (HMODULE)GetProcAddress(GetModuleHandle("kernel32.dll"), "OpenThread");
	HANDLE (WINAPI *pOpenThread)(DWORD, BOOL, DWORD) = (HANDLE (WINAPI *)(DWORD, BOOL, DWORD))g_hModule;
	g_hModuleAPC = (HMODULE)GetProcAddress(GetModuleHandle("kernel32.dll"), "QueueUserAPC");
	DWORD (WINAPI *pQueueUserAPC)(DWORD, HANDLE, ULONG) = (DWORD (WINAPI *)(DWORD, HANDLE, ULONG))g_hModuleAPC;
	HANDLE hProcess = NULL;
	// ��Ŀ����̻�ȡ���̾��;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, dwPid);
	if (!hProcess)
	{
		return -1;
	}
	// ��Ŀ�����������0xD���ȵĿռ����ڴ洢ģ��·��;
	LPVOID lpImageBuffer = VirtualAllocEx(hProcess, NULL, 0xD, MEM_RESERVE | MEM_COMMIT , PAGE_EXECUTE_READWRITE);
	if (!lpImageBuffer)
	{
		return -2;
	}
	// ��ģ��·��д�뵽Ŀ�����;
	if (!WriteProcessMemory(hProcess, lpImageBuffer, g_szModulePath, 0xD, NULL)) 
	{
		return -3;
	}
	// ����Ŀ����̵�ȫ���߳�;
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwPid);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		return -4;
	}
	THREADENTRY32 stThreadEntry32 = { 0 };
	stThreadEntry32.dwSize = sizeof(THREADENTRY32);
	if (!Thread32First(hThreadSnap, &stThreadEntry32))
	{
		CloseHandle(hThreadSnap);
		return -5;
	}
	do
	{
		// �������̣��õ�ָ�����̵�ȫ���߳̾��;
		if (stThreadEntry32.th32OwnerProcessID == dwPid)
		{
			HANDLE hThread = pOpenThread(THREAD_ALL_ACCESS, NULL, stThreadEntry32.th32ThreadID);
			if (!hThread)
			{
				continue;
			}
			// ���û�ģʽ �첽���̵��� (APC) ������ӵ�ָ���̵߳� APC ����
			pQueueUserAPC((DWORD)LoadLibraryA, hThread, (ULONG)lpImageBuffer);
		}
	} while (Thread32Next(hThreadSnap, &stThreadEntry32));
	CloseHandle(hThreadSnap);
	return 0;
}

int main(int argc, char* argv[])
{
	printf("PID:\n");
	int nPid = NULL;
	scanf("%d", &nPid);
	printf("ModulePath:\n");
	scanf("%s", g_szModulePath);
	ApcInject(nPid);

	system("pause");
	return 0;
}