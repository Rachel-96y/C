// Win32Api_8.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define CALLBACK_COMPLETED TRUE
#define CALLBACK_UNCOMPLETED FALSE

// �����ж��Ƿ�����δִ�����
BYTE FLAG = 0;

DWORD WINAPI ThreadProcADD(LPVOID hwndEdit)
{

	FLAG = 1;
	// ����һ�����������ڴ洢��ȡ�����ı��ַ���
	TCHAR szDATA[0x10] = {0};
	// ���ڴ洢ת���������
	DWORD dwNumber = 0;
	DWORD dwCount = 15;
	do
	{
		// ��ȡ�ı����е�ֵ
		SendMessage(GetDlgItem((HWND)hwndEdit, IDC_EDIT_ADD), WM_GETTEXT, 0x10, (LPARAM)szDATA);
		// ���ַ���ת��Ϊ����
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber--;
		// ÿ��1���һ��
		Sleep(1000);
		// ������ת��Ϊ�ַ���
		sprintf(szDATA, "%d", dwNumber);
		// ���¸��ı���ֵ
		SendMessage(GetDlgItem((HWND)hwndEdit, IDC_EDIT_ADD), WM_SETTEXT, 0, (LPARAM)szDATA);
	}
	while(--dwCount);

	FLAG = 0;

	return 0;
}

DWORD WINAPI ThreadProcSUB(LPVOID hwndEdit)
{
	// ����һ�����������ڴ洢��ȡ�����ı��ַ���
	TCHAR szDATA[0x10] = {0};
	// ���ڴ洢ת���������
	DWORD dwNumber = 0;
	DWORD dwCount = 15;
	do
	{
		// ��ȡ�ı����е�ֵ
		SendMessage(GetDlgItem((HWND)hwndEdit, IDC_EDIT_SUB), WM_GETTEXT, 0x10, (LPARAM)szDATA);
		// ���ַ���ת��Ϊ����
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		// ÿ��1���һ��
		Sleep(1000);
		// ������ת��Ϊ�ַ���
		sprintf(szDATA, "%d", dwNumber);
		// ���¸��ı���ֵ
		SendMessage(GetDlgItem((HWND)hwndEdit, IDC_EDIT_SUB), WM_SETTEXT, 0, (LPARAM)szDATA);
	}
	while(--dwCount);

	return 0;
}

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
			SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_ADD), WM_SETTEXT, 0, (LPARAM)"15");
			SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_SUB), WM_SETTEXT, 0, (LPARAM)"0");
			break;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_BUTTON_RUN:
				{
				if (!FLAG)
					{
						SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_ADD), WM_SETTEXT, 0, (LPARAM)"15");
						SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_SUB), WM_SETTEXT, 0, (LPARAM)"0");
						FLAG = 1;
						HANDLE hThreadADD = ::CreateThread(NULL, 0, ThreadProcADD, hwndDlg, 0, NULL);
						HANDLE hThreadSUB = ::CreateThread(NULL, 0, ThreadProcSUB, hwndDlg, 0, NULL);
						::CloseHandle(hThreadADD);
						::CloseHandle(hThreadSUB);
					}
				break;
				}
			case IDC_BUTTON_TEST:
				{
					if (FLAG == 1)
					{
						DWORD dwResult = MessageBox(hwndDlg, "���濨����?", "�������", MB_YESNOCANCEL | MB_ICONQUESTION);
						if (dwResult == IDYES)
						{
							MessageBox(hwndDlg, "�ܲ���", "�������", MB_ICONWARNING);
						}
						else if(dwResult == IDNO)
						{
							MessageBox(hwndDlg, "̫����!", "�ɹ�!", MB_ICONINFORMATION | MB_ICONASTERISK);
						}
					}
					else if (!FLAG)
					{
						MessageBox(hwndDlg, "�㻹û�е����ʼ!", "�������", MB_ICONWARNING);
					}
					break;
				}
			case IDC_BUTTON_STOP:
				{
					if (FLAG)
					{
						MessageBox(hwndDlg, "�Ҳ�֪����ôֹͣ���ѩҩn�ѩ�!", "�������", MB_SYSTEMMODAL);
					}
					else
					{
						MessageBox(hwndDlg, "�㻹û�е����ʼ!", "�������", MB_ICONWARNING);
					}
					break;
				}

			} // End switch
		return CALLBACK_COMPLETED;
		} 
	}// End switch
	return CALLBACK_UNCOMPLETED;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	/*
		������ϰ��
			Ҫ��
			�����ʼ�󣬵�һ���ı����ֵ��1000ÿ��1���ּ�1 ֱ��0
			�ڶ����ı����0ÿ��1���Ӽ�1 ֱ��1000
	*/

	// ����Ƿ�ֻ��һ��ͬ������
	CheckIsExsist();

	// ���öԻ���
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProcMain);

	return 0; 
}