// Win32Api_11.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

BYTE FLAG = 0x00;
CRITICAL_SECTION csCriticalSection = {0};

/*
//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc_1(LPVOID lpParameter)
{
	// ��һ���߳�

	// ��ȡ�������־
	HANDLE g_hMutex = ::OpenMutex(MUTEX_ALL_ACCESS,FALSE, "g_hWIN32API_THREAD_FLAG");

	// �洢��Ҫת�������κ��ַ���
	DWORD dwNumber = 0;
	TCHAR szDATA[0x10] = {0};

	// �õ�Ŀ��༭�������༭��ľ��
	HWND hEdit_1 = GetDlgItem((HWND)lpParameter, IDC_EDIT_1);
	HWND hEdit_2 = GetDlgItem((HWND)lpParameter, IDC_EDIT_2);
	do
	{
		// �����������Ƿ��ͷ�
		::WaitForSingleObject(g_hMutex,INFINITE);

		// ��Ŀ��༭���е�ֵ
		SendMessage(hEdit_1, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		if (dwNumber < 50)
		{
			FLAG = 0x00;
			break;
		}
		dwNumber -= 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_1, WM_SETTEXT, 0, (LPARAM)szDATA);

		// ������༭���ֵ
		SendMessage(hEdit_2, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber += 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_2, WM_SETTEXT, 0, (LPARAM)szDATA);

		// �ͷŻ������־
		::ReleaseMutex(g_hMutex);

		// ��ʱ50����
		Sleep(50);
	}
	while(TRUE);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc_2(LPVOID lpParameter)
{
	// �ڶ����߳�

	HANDLE g_hMutex = ::OpenMutex(MUTEX_ALL_ACCESS,FALSE, "g_hWIN32API_THREAD_FLAG");
	DWORD dwNumber = 0;
	TCHAR szDATA[0x10] = {0};
	HWND hEdit_1 = GetDlgItem((HWND)lpParameter, IDC_EDIT_1);
	HWND hEdit_3 = GetDlgItem((HWND)lpParameter, IDC_EDIT_3);
	do
	{
		::WaitForSingleObject(g_hMutex,INFINITE);
		SendMessage(hEdit_1, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		if (dwNumber < 50)
		{
			FLAG = 0x00;
			break;
		}
		dwNumber -= 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_1, WM_SETTEXT, 0, (LPARAM)szDATA);
		SendMessage(hEdit_3, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber += 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_3, WM_SETTEXT, 0, (LPARAM)szDATA);
		::ReleaseMutex(g_hMutex);
		Sleep(50);
	}
	while(TRUE);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc_3(LPVOID lpParameter)
{
	// �������߳�

	HANDLE g_hMutex = ::OpenMutex(MUTEX_ALL_ACCESS, FALSE, "g_hWIN32API_THREAD_FLAG");
	DWORD dwNumber = 0;
	TCHAR szDATA[0x10] = {0};
	HWND hEdit_1 = GetDlgItem((HWND)lpParameter, IDC_EDIT_1);
	HWND hEdit_4 = GetDlgItem((HWND)lpParameter, IDC_EDIT_4);
	do
	{
		::WaitForSingleObject(g_hMutex,INFINITE);
		SendMessage(hEdit_1, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		if (dwNumber < 50)
		{
			FLAG = 0x00;
			break;
		}
		dwNumber -= 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_1, WM_SETTEXT, 0, (LPARAM)szDATA);
		SendMessage(hEdit_4, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber += 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_4, WM_SETTEXT, 0, (LPARAM)szDATA);
		::ReleaseMutex(g_hMutex);
		Sleep(50);
	}
	while(TRUE);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	// ���ڴ���3���̲߳��Ҽ�������

	// �����������־
	HANDLE g_hMutex = ::CreateMutex(NULL, FALSE, "g_hWIN32API_THREAD_FLAG");
	if (!g_hMutex)
	{
		return RETURN_FAILED;
	}

	// ���ڴ洢�߳��ں˶�����
	HANDLE hThreadArrays[0x3] = {0};

	// ��ֵ
	hThreadArrays[0] = ::CreateThread(NULL, 0, ThreadProc_1, lpParameter, 0, NULL);
	hThreadArrays[1] = ::CreateThread(NULL, 0, ThreadProc_2, lpParameter, 0, NULL);
	hThreadArrays[2] = ::CreateThread(NULL, 0, ThreadProc_3, lpParameter, 0, NULL);
	
	// �ȴ�ȫ���߳�ִ�����
	::WaitForMultipleObjects(3, hThreadArrays, TRUE, INFINITE);

	// �ͷ��ں˶���ռ�
	::CloseHandle(hThreadArrays[0]);
	::CloseHandle(hThreadArrays[1]);
	::CloseHandle(hThreadArrays[2]);
	::CloseHandle(g_hMutex);

	return RETURN_SUCCESS;
}
*/

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc_1(LPVOID lpParameter)
{
	// �������߳�

	DWORD dwNumber = 0;
	TCHAR szDATA[0x10] = {0};
	HWND hEdit_1 = GetDlgItem((HWND)lpParameter, IDC_EDIT_1);
	HWND hEdit_2 = GetDlgItem((HWND)lpParameter, IDC_EDIT_2);
	do
	{
		EnterCriticalSection(&csCriticalSection);
		SendMessage(hEdit_1, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		if (dwNumber < 50)
		{
			FLAG = 0x00;
			break;
		}
		dwNumber -= 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_1, WM_SETTEXT, 0, (LPARAM)szDATA);
		SendMessage(hEdit_2, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber += 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_2, WM_SETTEXT, 0, (LPARAM)szDATA);
		LeaveCriticalSection(&csCriticalSection);
		Sleep(50);
	}
	while(TRUE);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc_2(LPVOID lpParameter)
{
	// �������߳�

	DWORD dwNumber = 0;
	TCHAR szDATA[0x10] = {0};
	HWND hEdit_1 = GetDlgItem((HWND)lpParameter, IDC_EDIT_1);
	HWND hEdit_3 = GetDlgItem((HWND)lpParameter, IDC_EDIT_3);
	do
	{
		EnterCriticalSection(&csCriticalSection);
		SendMessage(hEdit_1, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		if (dwNumber < 50)
		{
			FLAG = 0x00;
			break;
		}
		dwNumber -= 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_1, WM_SETTEXT, 0, (LPARAM)szDATA);
		SendMessage(hEdit_3, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber += 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_3, WM_SETTEXT, 0, (LPARAM)szDATA);
		LeaveCriticalSection(&csCriticalSection);
		Sleep(50);
	}
	while(TRUE);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc_3(LPVOID lpParameter)
{
	// �������߳�

	DWORD dwNumber = 0;
	TCHAR szDATA[0x10] = {0};
	HWND hEdit_1 = GetDlgItem((HWND)lpParameter, IDC_EDIT_1);
	HWND hEdit_4 = GetDlgItem((HWND)lpParameter, IDC_EDIT_4);
	do
	{
		EnterCriticalSection(&csCriticalSection);
		SendMessage(hEdit_1, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		if (dwNumber < 50)
		{
			FLAG = 0x00;
			break;
		}
		dwNumber -= 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_1, WM_SETTEXT, 0, (LPARAM)szDATA);
		SendMessage(hEdit_4, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber += 50;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit_4, WM_SETTEXT, 0, (LPARAM)szDATA);
		LeaveCriticalSection(&csCriticalSection);
		Sleep(50);
	}
	while(TRUE);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	// ���ڴ���3���̲߳��Ҽ�������

	// ��ʼ������
	InitializeCriticalSection(&csCriticalSection);

	// ���ڴ洢�߳��ں˶�����
	HANDLE hThreadArrays[0x3] = {0};

	// ��ֵ
	hThreadArrays[0] = ::CreateThread(NULL, 0, ThreadProc_1, lpParameter, 0, NULL);
	hThreadArrays[1] = ::CreateThread(NULL, 0, ThreadProc_2, lpParameter, 0, NULL);
	hThreadArrays[2] = ::CreateThread(NULL, 0, ThreadProc_3, lpParameter, 0, NULL);
	
	// �ȴ�ȫ���߳�ִ�����
	::WaitForMultipleObjects(3, hThreadArrays, TRUE, INFINITE);
	
	// �ͷ��ں˶���ռ�
	::CloseHandle(hThreadArrays[0]);
	::CloseHandle(hThreadArrays[1]);
	::CloseHandle(hThreadArrays[2]);

	// ж������
	DeleteCriticalSection(&csCriticalSection);

	// ����ȫ�ֱ�־
	FLAG = 0x00;

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
BOOL CALLBACK DialogProcMain(
						 HWND hwndDlg,
						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam
						 )
{
	/*
		���ڴ���"IDD_DIALOG_MAIN"�Ի���Ļص�����
	*/
	
	switch(uMsg)								
	{
	case WM_CLOSE:
		{
			// �����˳���ť
			EndDialog(hwndDlg, TRUE);
			break;
		}
	case WM_INITDIALOG:
		{
			// �����ʼ��
			SendMessage(GetDlgItem((HWND)hwndDlg, IDC_EDIT_1), WM_SETTEXT, 0, (LPARAM)"1000");
			SendMessage(GetDlgItem((HWND)hwndDlg, IDC_EDIT_2), WM_SETTEXT, 0, (LPARAM)"0");
			SendMessage(GetDlgItem((HWND)hwndDlg, IDC_EDIT_3), WM_SETTEXT, 0, (LPARAM)"0");
			SendMessage(GetDlgItem((HWND)hwndDlg, IDC_EDIT_4), WM_SETTEXT, 0, (LPARAM)"0");
			break;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_BUTTON_1:
				{
					// ���������߳�
					if (!FLAG)
					{
						FLAG = 0x01;
						HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc, hwndDlg, 0, NULL);
						::CloseHandle(hThread);
						break;
					}
					else
					{
						break;
					}
				}
			} // End switch
		return CALLBACK_COMPLETED;
		} 
	}// End switch
	return CALLBACK_UNCOMPLETED;
}

//////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	/*
		�������ϰ��
		��һ�����ڵ�һ���ı���������һ��ֵ������1000
		�ڶ���������������ͬʱ����3���̣߳�ÿ���߳�ѭ������������Ĳ�����ÿ����50
		��������ʹ��Mutex�����߳̿��ƣ�����һ���ı����е�ֵ<50ʱ��������߳̽���.
		�ر�˵����
		1���ĸ��ı����е�ֵ�ܺ�Ӧ��Ϊ1000
		2��������߳�ÿ����ʱ50����.
		3��ʹ��WaitForMultipleObjects���������̣߳����߳�ȫ��������
		   ����CloseHandle�رվ��.
	*/

	// �����ں˶����ֹ�࿪
	HANDLE g_hCHECK_EXSIST_WIN32API_FLAG = CheckIsExsist();

	// ���öԻ���
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProcMain);

	// ������Ҫ����ǰ�ͷ��ں˶���ռ�
	::CloseHandle(g_hCHECK_EXSIST_WIN32API_FLAG);
	
	return 0;
}