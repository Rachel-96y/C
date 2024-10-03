// Win32Api_14.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

// �ź�����־
HANDLE g_hSemaphore = {0};
HANDLE g_hEnd = {0};
// �¼���־
HANDLE g_hTop = {0};
HANDLE g_hUnder = {0};
// �߳̽�����־
BYTE g_bFLAG = 0x00;
// �洢�̶߳�Ӧ�Ĵ��ھ��
HWND g_hThread[0x7] = {0};

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProcTop(LPVOID lpParameter)
{
	// TOP�̴߳�����
	// ���ڴ�Ż�ȡ�����ַ���������
	TCHAR szDATA[0x20] = {0};
	TCHAR szNum[0x10] = {0};
	// ���ڵ�����Ҫ���õ��ַ���,��������
	TCHAR szSetText[0x2] = {0};
	// ��ȡ�ı�������ݲ����õ�szDATA��
	SendMessage(g_hThread[0], WM_GETTEXT, 0x10, (LPARAM)szDATA);
	// ��ȡ�ַ�����������ѭ��
	DWORD dwCount = strlen(szDATA);
	// �ַ�������ָ��
	DWORD dwPStr = 0;
	do
	{
		// �ȴ�TOP�¼���־�л�Ϊ��֪ͨ״̬
		::WaitForSingleObject(g_hTop, INFINITE);
		Sleep(1000);
		// ��ֵ��ַ��õ������ַ��ı���
		memcpy(szSetText, szDATA + dwPStr++, 0x1);
		// ��ȡ�������ı�������,��˭��ֵ��0
		SendMessage(g_hThread[1], WM_GETTEXT, 0x10, (LPARAM)szNum);
		if (!strcmp(szNum, "0"))
		{
			// ���õ�һ��������
			SendMessage(g_hThread[1], WM_SETTEXT, 0, (LPARAM)szSetText);
		}
		else
		{
			// ���õڶ���������
			SendMessage(g_hThread[2], WM_SETTEXT, 0, (LPARAM)szSetText);
		}
		// ����g_hUnder��־,�������̼߳�������
		::SetEvent(g_hUnder);
	}
	while(--dwCount);
	// ����ȫ�ֱ�־
	g_bFLAG = 0x01;
	// �ȴ��ź�����־�л�Ϊ��֪ͨ״̬
	::WaitForSingleObject(g_hEnd, INFINITE);
	// ������־
	g_bFLAG = 0x02;
	return 0xFF;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProcUnder(LPVOID lpParameter)
{
	// UNDER���̴߳�����
	// ת���±�
	DWORD dwIndex = (DWORD)lpParameter;
	// ���ڴ�Ż�ȡ�����ַ���������
	TCHAR szDATA[0x10] = {0};
	// ƴ�ӵ��ַ���
	TCHAR szString[0x10] = {0};
	do
	{
		// �ȴ��ź�����־�л�Ϊ��֪ͨ״̬
		::WaitForSingleObject(g_hSemaphore, INFINITE);
		// �ȴ�UNDER�¼���־�л�Ϊ��֪ͨ״̬
		::WaitForSingleObject(g_hUnder, INFINITE);
		Sleep(1000);
		// �ж��߳̽�����־
		if (g_bFLAG == 0x02)
		{
			::ReleaseSemaphore(g_hSemaphore, 1, NULL);
			::SetEvent(g_hUnder);
			break;
		}
		// ��ȡ������1��ֵ�������ֵ
		SendMessage(g_hThread[1], WM_GETTEXT, 0x10, (LPARAM)szDATA);
		SendMessage(g_hThread[dwIndex], WM_GETTEXT, 0x10, (LPARAM)szString);
		// ����ֵ�Ļ�������ֵ�Ž��Լ��ı༭��,����0������
		if (strcmp(szDATA, "0"))
		{
			// ��ֵ�򽫵�1����������ֵ,����ԭ����ֵ,���õ��Լ��ı༭����
			strcat(szString, szDATA);
			strcat(szString, "-");
			SendMessage(g_hThread[dwIndex], WM_SETTEXT, 0, (LPARAM)szString);
			// ��0������
			SendMessage(g_hThread[1], WM_SETTEXT, 0, (LPARAM)"0");
		}
		else
		{
			// û��ֵ�򽫵�2����������ֵ������,����ԭ����ֵ,���õ��Լ��ı༭����
			SendMessage(g_hThread[2], WM_GETTEXT, 0x10, (LPARAM)szDATA);
			strcat(szString, szDATA);
			strcat(szString, "-");
			SendMessage(g_hThread[dwIndex], WM_SETTEXT, 0, (LPARAM)szString);
			// ��0������
			SendMessage(g_hThread[2], WM_SETTEXT, 0, (LPARAM)"0");
		}

		// �ͷ�1���ź�
		::ReleaseSemaphore(g_hSemaphore, 1, NULL);
		// ����g_hTop��־,����һ���̼߳�������
		::SetEvent(g_hTop);
		if (g_bFLAG== 0x01)
		{
			::ReleaseSemaphore(g_hEnd, 1, NULL);
			::SetEvent(g_hUnder);
		}
	}
	while(TRUE);

	return dwIndex;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	// �������߳�
	// �����ź����ں˶���
	g_hSemaphore = ::CreateSemaphore(NULL, 0, 4, NULL);
	g_hEnd = ::CreateSemaphore(NULL, 0, 1, NULL);
	// �����¼��ں˶���
	g_hTop = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	g_hUnder = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	// �����洢�߳��ں˶�����������
	HANDLE hThreadArrays[0x5] = {0};
	// ����1��TOP�߳�
	hThreadArrays[0] = ::CreateThread(NULL, 0, ThreadProcTop, NULL, 0, NULL);
	// ����4��UNDER�߳�
	hThreadArrays[1] = ::CreateThread(NULL, 0, ThreadProcUnder, (LPVOID)3, 0, NULL);
	hThreadArrays[2] = ::CreateThread(NULL, 0, ThreadProcUnder, (LPVOID)4, 0, NULL);
	hThreadArrays[3] = ::CreateThread(NULL, 0, ThreadProcUnder, (LPVOID)5, 0, NULL);
	hThreadArrays[4] = ::CreateThread(NULL, 0, ThreadProcUnder, (LPVOID)6, 0, NULL);
	// �ͷ��ź�,����UNDER�߳�
	ReleaseSemaphore(g_hSemaphore, 2, NULL);
	// �����¼���־,����TOP�߳�
	::SetEvent(g_hTop);
	// �ȴ�ȫ���߳�ִ�����
	::WaitForMultipleObjects(5, hThreadArrays, TRUE, INFINITE);
	// �����־λ
	g_bFLAG = 0x00;
	// �ͷ��߳��ں˶���ռ�
	::CloseHandle(hThreadArrays[0]);
	::CloseHandle(hThreadArrays[1]);
	::CloseHandle(hThreadArrays[2]);
	::CloseHandle(hThreadArrays[3]);
	::CloseHandle(hThreadArrays[4]);
	// �ͷ��ź����ں˶���
	::CloseHandle(g_hSemaphore);
	::CloseHandle(g_hEnd);
	// �ͷ��¼��ں˶���
	::CloseHandle(g_hTop);
	::CloseHandle(g_hUnder);
	return 0xEE;
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
			// �洢���ھ����ȫ�ֱ�����
			g_hThread[0] = GetDlgItem((HWND)hwndDlg, IDC_EDIT_1);
			g_hThread[1] = GetDlgItem((HWND)hwndDlg, IDC_EDIT_2);
			g_hThread[2] = GetDlgItem((HWND)hwndDlg, IDC_EDIT_3);
			g_hThread[3] = GetDlgItem((HWND)hwndDlg, IDC_EDIT_4);
			g_hThread[4] = GetDlgItem((HWND)hwndDlg, IDC_EDIT_5);
			g_hThread[5] = GetDlgItem((HWND)hwndDlg, IDC_EDIT_6);
			g_hThread[6] = GetDlgItem((HWND)hwndDlg, IDC_EDIT_7);
			// �����ʼ��
			SendMessage(g_hThread[0], WM_SETTEXT, 0, (LPARAM)"0");
			SendMessage(g_hThread[1], WM_SETTEXT, 0, (LPARAM)"0");
			SendMessage(g_hThread[2], WM_SETTEXT, 0, (LPARAM)"0");
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