// Win32Api_9.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define CALLBACK_COMPLETED			TRUE
#define CALLBACK_UNCOMPLETED		FALSE

// ��ʼ
BYTE FLAG = 0x00;

// ��ֹ
BYTE FLAG_2 = 0x00;  // ��ʽ1
BYTE FLAG_4 = 0x00;  // ��ʽ2

// ����
BYTE FLAG_3 = 0x00;

// ��ӡ
BYTE FLAG_5 = 0x00;

HANDLE hThread = NULL;

// ���ڴ���������
typedef struct _Args{
	HWND	hEdit;
	LPVOID	lpThread;
} Args, *PArgs;

Args pStArgs = {0};

DWORD WINAPI ThreadProcButton_1(LPVOID hwndEdit)
{
	FLAG = 0x01;

	// ����һ�����������ڴ洢��ȡ�����ı��ַ���
	TCHAR szDATA[0x10] = {0};
	// ���ڴ洢ת���������
	DWORD dwNumber = 0;
	DWORD dwCount = 1000;
	do
	{
		if (FLAG_2 == 0x01)
		{
			break;
		}
		if (FLAG_4 == 0x01)
		{
			FLAG_4 = 0x00;
			FLAG = 0x00;
			FLAG_2 = 0x00;
			SendMessage(GetDlgItem((HWND)hwndEdit, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)"0");
			::ExitThread(222);
		}
		// ��ȡ�ı����е�ֵ
		SendMessage(GetDlgItem((HWND)hwndEdit, IDC_EDIT), WM_GETTEXT, 0x10, (LPARAM)szDATA);
		// ���ַ���ת��Ϊ����
		sscanf(szDATA, "%d", &dwNumber);
		dwNumber++;
		// ÿ��1���һ��
		Sleep(100);
		// ������ת��Ϊ�ַ���
		sprintf(szDATA, "%d", dwNumber);
		// ���¸��ı���ֵ
		SendMessage(GetDlgItem((HWND)hwndEdit, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)szDATA);
	}
	while(--dwCount);

	FLAG = 0x00;
	FLAG_2 = 0x00;
	SendMessage(GetDlgItem((HWND)hwndEdit, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)"0");

	return 111;
}

DWORD WINAPI ThreadProcOfEdit(LPVOID pArgs)
{
	FLAG_5 = 0x01;

	// ��ȡ������̵߳ļĴ�����ֵ
	DWORD dwExitCode = 0;
	DWORD dwResult = GetExitCodeThread(((PArgs)pArgs) -> lpThread, &dwExitCode);
	if (!dwResult || dwExitCode != STILL_ACTIVE)
	{
		MessageBox(((PArgs)pArgs) -> hEdit, "�̻߳�û��ִ��", "����Ĳ���", MB_ICONASTERISK);
		return 444;
	}
	if (!FLAG_3)
	{
		MessageBox(((PArgs)pArgs) -> hEdit, "����Ҫ�ȹ����̲߳���׼ȷ��ȡ��ǰֵ", "����Ĳ���", MB_ICONASTERISK);
		return 444;
	}

	// ����context�ṹ
	CONTEXT context;
	memset(&context, 0x00000000, sizeof(CONTEXT));

	// ����Ҫ��ȡ������				
	context.ContextFlags = CONTEXT_DEBUG_REGISTERS | CONTEXT_FULL;

	// ��ȡ
	BOOL ret = ::GetThreadContext(((PArgs)pArgs) -> lpThread, &context);
	if (!ret)
	{
		MessageBox(((PArgs)pArgs) -> hEdit, "��ȡ�Ĵ���ֵʧ��!", "ʧ����", MB_ICONASTERISK);
		return 444;
	}

	// ��ȡ�ı�����
	HWND hwndEdit = GetDlgItem(((PArgs)pArgs) -> hEdit, IDC_EDIT_Register);

	// ���ڴ洢ת������ַ���
	TCHAR szDATA[0x10] = {0};

	// �Ĵ�������
	PTCHAR szName[0x16] = 
	{
		"Dr0",
		"Dr1",
		"Dr2",
		"Dr3",
		"Dr6",
		"Dr7",
		"SegGs",
		"SegFs",
		"SegEs",
		"SegDs",
		"Edi",
		"Esi",
		"Ebx",
		"Edx",
		"Ecx",
		"Eax",
		"Ebp",
		"Eip",
		"SegCs",
		"EFlags",
		"Esp",
		"SegSs",
	};

	// �Ĵ�����Ӧ��ֵ
	DWORD dwDATA[0x16] = 
	{
		context.Dr0,
		context.Dr1,
		context.Dr2,
		context.Dr3,
		context.Dr6,
		context.Dr7,
		context.SegGs,
		context.SegFs,
		context.SegEs,
		context.SegDs,
		context.Edi,
		context.Esi,
		context.Ebx,
		context.Edx,
		context.Ecx,
		context.Eax,
		context.Ebp,
		context.Eip,
		context.SegCs,
		context.EFlags,
		context.Esp,
		context.SegSs,
	};

	// ����
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��ǰ�Ĵ�����ֵ: \r\n\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);
	
	// ���ڼ���
	DWORD dwCount = 0;
	do
	{
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szName[dwCount]);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"				");
		sprintf(szDATA, "%08X", dwDATA[dwCount]);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
	}
	while(++dwCount < 0x16);
	// ����
	// context.Eip = 0x401000;
	// SetThreadContext(hThread,&context);

	return 444;
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
			SendMessage(GetDlgItem(hwndDlg, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)"0");
			break;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_BUTTON_1:
				{
					// ��ʼ
					if (!FLAG)
					{
						SendMessage(GetDlgItem(hwndDlg, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)"0");
						hThread = ::CreateThread(NULL, 0, ThreadProcButton_1, hwndDlg, 0, NULL);
					}
					break;
				}
			case IDC_BUTTON_2:
				{
					// ����
					if (!FLAG_3)
					{
						FLAG_3 = 0x01;
						FLAG_5 = 0x00;
						::SuspendThread(hThread);
					}
					break;
				}
			case IDC_BUTTON_3:
				{
					// ����
					if (FLAG_3)
					{
						FLAG_3 = 0x00;
						::ResumeThread(hThread);
					}
					break;
				}
			case IDC_BUTTON_4:
				{
					// ��ֹ��ʽ1
					DWORD dwExitCode = 0;
					GetExitCodeThread(hThread, &dwExitCode);

					if (!FLAG_2 && dwExitCode == STILL_ACTIVE)
					{
						FLAG_2 = 0x01;
					}
					
					break;
				}
			case IDC_BUTTON_5:
				{
					// ��ֹ��ʽ2
					DWORD dwExitCode = 0;
					GetExitCodeThread(hThread, &dwExitCode);
					if (!FLAG_4 && dwExitCode == STILL_ACTIVE)
					{
						FLAG_4 = 0x01;
					}
					break;
				}
			case IDC_BUTTON_6:
				{
					// ��ֹ��ʽ3
					::TerminateThread(hThread, 333);
					::WaitForSingleObject(hThread, INFINITE);
					FLAG = 0x00;
					FLAG_2 = 0x00;
					SendMessage(GetDlgItem(hwndDlg, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)"0");
					break;
				}
			case IDC_BUTTON_7:
				{
					// �鿴�˳���
					DWORD dwExitCode = 0;
					DWORD dwResult = GetExitCodeThread(hThread, &dwExitCode);
					if (!dwResult)
					{
						MessageBox(hwndDlg, "û���κ��˳���!", 0, MB_ICONWARNING);
						break;
					}
					if (dwExitCode == STILL_ACTIVE)
					{
						MessageBox(hwndDlg, "������������!", 0, MB_ICONWARNING);
						break;
					}
					TCHAR szDATA[0x10] = {0};
					sprintf(szDATA, "%d", dwExitCode);
					MessageBox(hwndDlg, szDATA, "��ʾ�˳���", MB_ICONASTERISK);
					break;
				}
			case IDC_BUTTON_8:
				{
					if (!FLAG_5)
					{
						pStArgs.hEdit = hwndDlg;
						pStArgs.lpThread = hThread;
						::CreateThread(NULL, 0, ThreadProcOfEdit, &pStArgs, 0, NULL);
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
 	// ���ȼ���Ƿ�˳���ֻ������һ��ʵ��
	CheckIsExsist();

	// ���öԻ���
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProcMain);

	return 0;
}