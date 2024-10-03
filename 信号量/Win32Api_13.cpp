// Win32Api_13.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

// �ź�����־
HANDLE g_hSemaphore = {0};

// ���ڴ洢�༭����
HWND hEditAll[0x3] = {0};

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProcAll(LPVOID lpParameter)
{
	// ���̴߳�����
	
	// ת����Ҫ������ֵ���±�
	DWORD dwIndex = (DWORD)lpParameter;

	// �洢��Ҫת�������κ��ַ���
	DWORD dwNumber = 0;
	TCHAR szDATA[0x10] = {0};

	// ���յ��źź��ź���-1
	WaitForSingleObject(g_hSemaphore, INFINITE);
	do
	{
		// ��ȡ�ı����е�ֵ
		SendMessage(hEditAll[dwIndex], WM_GETTEXT, 0x10, (LPARAM)szDATA);

		// ת�������޸�
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		
		// ת����д��
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEditAll[dwIndex], WM_SETTEXT, 0, (LPARAM)szDATA);

		// ˯��10�������ڹ۲�
		Sleep(10);
	}
	while(dwNumber != 1000);

	// ���ź���+1
	ReleaseSemaphore(g_hSemaphore, 1, NULL);

	return dwIndex;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	// �������߳�

	// �����ź����ں˶���
	g_hSemaphore = CreateSemaphore(NULL, 0, 3, NULL);

	// ���ڴ洢�߳��ں˶�����
	HANDLE hThreadArrays[0x3] = {0};

	// ����3���̶߳���
	hThreadArrays[0] = ::CreateThread(NULL, 0, ThreadProcAll, (LPVOID)0, 0, NULL);
	hThreadArrays[1] = ::CreateThread(NULL, 0, ThreadProcAll, (LPVOID)1, 0, NULL);
	hThreadArrays[2] = ::CreateThread(NULL, 0, ThreadProcAll, (LPVOID)2, 0, NULL);

	// ��ȡ��һ���༭��ľ��
	HWND hEdit_1 = GetDlgItem((HWND)lpParameter, IDC_EDIT_1);

	// ���õ�һ���༭�����Ϣ(ģ��)
	Sleep(1000);
	SendMessage(hEdit_1, WM_SETTEXT, 0, (LPARAM)"200");
	Sleep(1000);
	SendMessage(hEdit_1, WM_SETTEXT, 0, (LPARAM)"500");
	Sleep(1000);
	SendMessage(hEdit_1, WM_SETTEXT, 0, (LPARAM)"1000");
	Sleep(1000);

	// �ͷ��ź�(�����ͷ�2��)
	ReleaseSemaphore(g_hSemaphore, 2, NULL);

	// �ȴ�ȫ���߳�ִ�����
	::WaitForMultipleObjects(3, hThreadArrays, TRUE, INFINITE);

	// �ͷ��߳��ں˶���ռ�
	::CloseHandle(hThreadArrays[0]);
	::CloseHandle(hThreadArrays[1]);
	::CloseHandle(hThreadArrays[2]);

	// �ͷ��ź����ں˶���
	::CloseHandle(g_hSemaphore);

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
	// ���ڴ���"IDD_DIALOG_MAIN"�Ի���Ļص�����
	// ���߳�

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
			// Ϊ�༭�������鸳ֵ
			hEditAll[0] = GetDlgItem((HWND)hwndDlg, IDC_EDIT_2);
			hEditAll[1] = GetDlgItem((HWND)hwndDlg, IDC_EDIT_3);
			hEditAll[2] = GetDlgItem((HWND)hwndDlg, IDC_EDIT_4);

			// �����ʼ��
			SendMessage(GetDlgItem((HWND)hwndDlg, IDC_EDIT_1), WM_SETTEXT, 0, (LPARAM)"0");
			SendMessage(hEditAll[0], WM_SETTEXT, 0, (LPARAM)"0");
			SendMessage(hEditAll[1], WM_SETTEXT, 0, (LPARAM)"0");
			SendMessage(hEditAll[2], WM_SETTEXT, 0, (LPARAM)"0");
			break;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_BUTTON_1:
				{
					// �����������߳�
					HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc, hwndDlg, 0, NULL);
					::CloseHandle(hThread);
					break;
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
 	// �߳�ͬ��

	// ���û������ֹ�࿪
	HANDLE g_hCHECK_EXSIST_WIN32API_FLAG = CheckIsExsist();

	// ���öԻ���
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProcMain);

	// ������Ҫ����ǰ�ر��ں˾��
	::CloseHandle(g_hCHECK_EXSIST_WIN32API_FLAG);

	return 0;
}