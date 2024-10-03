// Win32Api_10.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

BYTE Thread1 = 0x00;
BYTE Thread2 = 0x00;
BYTE Thread3 = 0x00;

// ���ƽṹ��Ҫ��ȫ�ֵ�
CRITICAL_SECTION csCriticalSection = {0};
CRITICAL_SECTION csCriticalSection_2 = {0};

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc1(LPVOID hwndDlg)
{
	if (Thread1)
	{
		return 0;
	}
	// ���ı�־
	Thread1 = 0x01;
	// ����һ�����������ڴ洢��ȡ�����ı��ַ���
	TCHAR szDATA[0x10] = {0};
	// ���ڴ洢ת���������
	DWORD dwNumber = 0;
	DWORD dwCount = 2000;
	HWND hwndEdit = GetDlgItem((HWND)hwndDlg, IDC_EDIT_1);
	do
	{
		Sleep(3);
		// ��ȡ�ı����е�ֵ
		SendMessage(hwndEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		// ���ַ���ת��Ϊ����
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		// ������ת��Ϊ�ַ���
		sprintf(szDATA, "%d", dwNumber);
		// ���¸��ı���ֵ
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)szDATA);
	}
	while(--dwCount);

	return 0;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc2(LPVOID hwndDlg)
{
	if (Thread2)
	{
		return 0;
	}
	Thread2 = 0x01;
	TCHAR szDATA[0x10] = {0};
	DWORD dwNumber = 0;
	DWORD dwCount = 2000;
	HWND hwndEdit = GetDlgItem((HWND)hwndDlg, IDC_EDIT_1);
	do
	{
		Sleep(3);
		SendMessage(hwndEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)szDATA);
	}
	while(--dwCount);

	return 0;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc3(LPVOID hwndDlg)
{
	if (Thread3)
	{
		return 0;
	}
	Thread3 = 0x01;
	TCHAR szDATA[0x10] = {0};
	DWORD dwNumber = 0;
	DWORD dwCount = 2000;
	HWND hwndEdit = GetDlgItem((HWND)hwndDlg, IDC_EDIT_1);
	do
	{
		Sleep(3);
		SendMessage(hwndEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)szDATA);
	}
	while(--dwCount);

	return 0;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProcNew1(LPVOID hwndDlg)
{
	if (Thread1)
	{
		return 0;
	}
	// ���ı�־
	Thread1 = 0x01;
	// ����һ�����������ڴ洢��ȡ�����ı��ַ���
	TCHAR szDATA[0x10] = {0};
	// ���ڴ洢ת���������
	DWORD dwNumber = 0;
	DWORD dwCount = 2000;
	HWND hwndEdit = GetDlgItem((HWND)hwndDlg, IDC_EDIT_1);
	do
	{
		Sleep(3);
		// ��ȡ����
		EnterCriticalSection(&csCriticalSection);
		// ��ȡ�ı����е�ֵ
		SendMessage(hwndEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		// ���ַ���ת��Ϊ����
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		// ������ת��Ϊ�ַ���
		sprintf(szDATA, "%d", dwNumber);
		// ���¸��ı���ֵ
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)szDATA);
		// �黹����
		LeaveCriticalSection(&csCriticalSection);
	}
	while(--dwCount);

	return 0;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProcNew2(LPVOID hwndDlg)
{
	if (Thread2)
	{
		return 0;
	}
	// ���ı�־
	Thread2 = 0x01;
	TCHAR szDATA[0x10] = {0};
	DWORD dwNumber = 0;
	DWORD dwCount = 2000;
	HWND hwndEdit = GetDlgItem((HWND)hwndDlg, IDC_EDIT_1);
	do
	{
		Sleep(3);
		EnterCriticalSection(&csCriticalSection);
		SendMessage(hwndEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)szDATA);
		LeaveCriticalSection(&csCriticalSection);
	}
	while(--dwCount);

	return 0;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProcNew3(LPVOID hwndDlg)
{
	if (Thread3)
	{
		return 0;
	}
	Thread3 = 0x01;
	TCHAR szDATA[0x10] = {0};
	DWORD dwNumber = 0;
	DWORD dwCount = 2000;
	HWND hwndEdit = GetDlgItem((HWND)hwndDlg, IDC_EDIT_1);
	do
	{
		Sleep(3);
		EnterCriticalSection(&csCriticalSection);
		SendMessage(hwndEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)szDATA);
		LeaveCriticalSection(&csCriticalSection);
	}
	while(--dwCount);

	return 0;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProcErro1(LPVOID hwndDlg)
{
	if (Thread1)
	{
		return 0;
	}
	// ���ı�־
	Thread1 = 0x01;
	EnterCriticalSection(&csCriticalSection_2);
	// ����һ�����������ڴ洢��ȡ�����ı��ַ���
	TCHAR szDATA[0x10] = {0};
	// ���ڴ洢ת���������
	DWORD dwNumber = 0;
	DWORD dwCount = 2000;
	HWND hwndEdit = GetDlgItem((HWND)hwndDlg, IDC_EDIT_2);
	do
	{
		// ��ȡ����
		EnterCriticalSection(&csCriticalSection);
		// ��ȡ�ı����е�ֵ
		SendMessage(hwndEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		// ���ַ���ת��Ϊ����
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		// ������ת��Ϊ�ַ���
		sprintf(szDATA, "%d", dwNumber);
		// ���¸��ı���ֵ
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)szDATA);
		// �黹����
		LeaveCriticalSection(&csCriticalSection);
	}
	while(--dwCount);

	LeaveCriticalSection(&csCriticalSection_2);
	return 0;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProcErro2(LPVOID hwndDlg)
{
	if (Thread2)
	{
		return 0;
	}
	// ���ı�־
	Thread2 = 0x01;
	EnterCriticalSection(&csCriticalSection_2);
	TCHAR szDATA[0x10] = {0};
	DWORD dwNumber = 0;
	DWORD dwCount = 2000;
	HWND hwndEdit = GetDlgItem((HWND)hwndDlg, IDC_EDIT_2);
	do
	{
		EnterCriticalSection(&csCriticalSection);
		SendMessage(hwndEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)szDATA);
		LeaveCriticalSection(&csCriticalSection);
	}
	while(--dwCount);

	LeaveCriticalSection(&csCriticalSection_2);
	return 0;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProcErro3(LPVOID hwndDlg)
{
	if (Thread3)
	{
		return 0;
	}
	// ���ı�־
	Thread3 = 0x01;
	TCHAR szDATA[0x10] = {0};
	DWORD dwNumber = 0;
	DWORD dwCount = 2000;
	HWND hwndEdit = GetDlgItem((HWND)hwndDlg, IDC_EDIT_2);
	do
	{
		EnterCriticalSection(&csCriticalSection);
		SendMessage(hwndEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		sprintf(szDATA, "%d", dwNumber);
		EnterCriticalSection(&csCriticalSection_2);
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)szDATA);
		LeaveCriticalSection(&csCriticalSection_2);
		LeaveCriticalSection(&csCriticalSection);
	}
	while(--dwCount);

	
	return 0;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc_EDIT(LPVOID hwndDlg)
{
	HWND hEdit = (HWND)hwndDlg;
	TCHAR szDATA[0x10] = {0};
	
	do
	{
	Sleep(1000);
	SendMessage(hEdit, WM_SETTEXT, 1, (LPARAM)"�ٽ����ṹ�����:\r\n");
	SendMessage(hEdit, EM_SETSEL, -2, -1);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"DebugInfo:			");
	sprintf(szDATA, "%d",csCriticalSection.DebugInfo);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"LockCount:			");
	sprintf(szDATA, "%d",csCriticalSection.LockCount);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"LockSemaphore:			");
	sprintf(szDATA, "%d",csCriticalSection.LockSemaphore);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"OwningThread:			");
	sprintf(szDATA, "%d",csCriticalSection.OwningThread);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"RecursionCount:			");
	sprintf(szDATA, "%d",csCriticalSection.RecursionCount);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"SpinCount:			");
	sprintf(szDATA, "%08X",csCriticalSection.SpinCount);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	SendMessage(hEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");
	}
	while(TRUE);

	
	return 0;
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
			// Ĭ��ѡ��һ����ѡ��(��ѡ��)
			CheckDlgButton(hwndDlg, IDC_RADIO_1, BST_CHECKED);

			// ���õ�һ��Edit
			SendMessage(GetDlgItem((HWND)hwndDlg, IDC_EDIT_1), WM_SETTEXT, 0, (LPARAM)"0");

			// ���õڶ���Edit
			SendMessage(GetDlgItem((HWND)hwndDlg, IDC_EDIT_2), WM_SETTEXT, 0, (LPARAM)"0");

			// ��ȡ������Edit�ľ��
			HWND hEdit = GetDlgItem((HWND)hwndDlg, IDC_EDIT_Info);

			// ������һ���߳�ʵʱ��ӡ�ṹ���ֵ
			::CreateThread(NULL, 0, ThreadProc_EDIT, hEdit, 0, NULL);

			break;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_BUTTON_RUN_1:
				{
					// �����߳�1
					DWORD dwFlag_1 = IsDlgButtonChecked(hwndDlg, IDC_RADIO_1);
					if (dwFlag_1 == BST_CHECKED)
					{
						::CreateThread(NULL, 0, ThreadProcNew1, hwndDlg, 0, NULL);
					}
					else
					{
						::CreateThread(NULL, 0, ThreadProc1, hwndDlg, 0, NULL);
					}
					break;
				}
			case IDC_BUTTON_RUN_2:
				{
					// �����߳�2
					DWORD dwFlag_2 = IsDlgButtonChecked(hwndDlg, IDC_RADIO_1);
					if (dwFlag_2 == BST_CHECKED)
					{
						::CreateThread(NULL, 0, ThreadProcNew2, hwndDlg, 0, NULL);
					}
					else
					{
						::CreateThread(NULL, 0, ThreadProc2, hwndDlg, 0, NULL);
					}
					break;
				}
			case IDC_BUTTON_RUN_3:
				{
					// �����߳�3
					// �жϵ�ѡ���Ƿ񱻹�ѡ(��ѡ��Ҳ�Ǵ˷���)
					DWORD dwFlag_3 = IsDlgButtonChecked(hwndDlg, IDC_RADIO_1);
					if (dwFlag_3 == BST_CHECKED)
					{
						::CreateThread(NULL, 0, ThreadProcNew3, hwndDlg, 0, NULL);
					}
					else
					{
						::CreateThread(NULL, 0, ThreadProc3, hwndDlg, 0, NULL);
					}
					break;
				}
			case IDC_BUTTON_RUN_4:
				{
					// ͬʱ����3���߳�ʵ������
					// �жϵ�ѡ���Ƿ񱻹�ѡ(��ѡ��Ҳ�Ǵ˷���)
					::CreateThread(NULL, 0, ThreadProcErro1, hwndDlg, 0, NULL);
					::CreateThread(NULL, 0, ThreadProcErro2, hwndDlg, 0, NULL);
					::CreateThread(NULL, 0, ThreadProcErro3, hwndDlg, 0, NULL);
					break;
				}
			case IDC_BUTTON_RUN_Clear:
				{
					// ����ֵ
					SendMessage(GetDlgItem((HWND)hwndDlg, IDC_EDIT_1), WM_SETTEXT, 0, (LPARAM)"0");
					SendMessage(GetDlgItem((HWND)hwndDlg, IDC_EDIT_2), WM_SETTEXT, 0, (LPARAM)"0");
					Thread1 = 0x00;
					Thread2 = 0x00;
					Thread3 = 0x00;
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
 	// TODO: Place code here.
	/*
		������ϰ��	
		ͨ��ʹ���ٽ���ʵ��һ����������.			
	*/

 	// ���ȼ���Ƿ�˳���ֻ������һ��ʵ��
	CheckIsExsist();

	// ��ʼ������
	InitializeCriticalSection(&csCriticalSection);
	InitializeCriticalSection(&csCriticalSection_2);

	// ���öԻ���
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProcMain);

	// ж������
	DeleteCriticalSection(&csCriticalSection);
	DeleteCriticalSection(&csCriticalSection_2);

	return 0;
}