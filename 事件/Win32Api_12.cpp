// Win32Api_12.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

// �¼�����
HANDLE g_hSet = 0;
HANDLE g_hClear = 0;

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc_1(LPVOID lpParameter)
{
	// ��һ���߳�(ÿ��ѭ�����ı����е�ֵ��2��д��,��Ҫ���߳�2����ִ��)

	// �洢��Ҫת�������κ��ַ���
	DWORD dwNumber = 0;
	TCHAR szDATA[0x10] = {0};

	// ת��
	HWND hEdit = (HWND)lpParameter;

	do
	{
		// ����g_hSet�Ƿ�����֪ͨ״̬(����WaitForSingleObjectִ����Ϻ���Զ���Ϊδ֪ͨ״̬)
		::WaitForSingleObject(g_hSet, INFINITE);

		// ��Ŀ��༭���е�ֵ
		SendMessage(hEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		if (!dwNumber)
		{
			break;
		}
		dwNumber -= 2;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)szDATA);

		// ��ʱ1��
		Sleep(1000);

		// ����g_hClear��־,����һ���̼߳�������
		::SetEvent(g_hClear);
	}
	while(TRUE);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc_2(LPVOID lpParameter)
{
	// �ڶ����߳�(ÿ��ѭ�����ı����е�ֵ��3��д��,��Ҫ���߳�1����ִ��)

	// �洢��Ҫת�������κ��ַ���
	DWORD dwNumber = 0;
	TCHAR szDATA[0x10] = {0};

	// ת��
	HWND hEdit = (HWND)lpParameter;

	do
	{
		// ����g_hSet�Ƿ�����֪ͨ״̬(����WaitForSingleObjectִ����Ϻ���Զ���Ϊδ֪ͨ״̬)
		::WaitForSingleObject(g_hClear, INFINITE);

		// ��Ŀ��༭���е�ֵ
		SendMessage(hEdit, WM_GETTEXT, 0x10, (LPARAM)szDATA);
		sscanf(szDATA, "%d", &dwNumber);
		if (!dwNumber)
		{
			break;
		}
		dwNumber -= 3;
		sprintf(szDATA, "%d", dwNumber);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)szDATA);

		// ��ʱ1��
		Sleep(1000);

		// ����g_hClear��־,����һ���̼߳�������
		::SetEvent(g_hSet);
	}
	while(TRUE);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	// ���ڴ���2���̲߳��Ҽ�������

	// �õ��ı���ľ��
	HWND hEdit = GetDlgItem((HWND)lpParameter, IDC_EDIT_1);

	// ���ڴ洢�߳��ں˶�����
	HANDLE hThreadArrays[0x2] = {0};

	// �����¼��ں˶��󲢸�ֵ
	// �ڶ���������ʾ:ÿ��wait����,Ҫ�޸�״̬Ϊδ֪ͨ
	// ������������ʾ:�Ƿ��¼�һ�����������ͻᱻwait��
	g_hSet = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	g_hClear = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	// ���ں˶������鸳ֵ
	hThreadArrays[0] = ::CreateThread(NULL, 0, ThreadProc_1, hEdit, 0, NULL);
	hThreadArrays[1] = ::CreateThread(NULL, 0, ThreadProc_2, hEdit, 0, NULL);

	// ���߳��ȸ��ı���ֵ(��ʱ���������߳�����)
	SendMessage((HWND)hEdit, WM_SETTEXT, 0, (LPARAM)"20");

	// �ӳ�2�����ڸ��õ���ʾ����״̬
	Sleep(2000);

	// ��Ҫ��ִ�е��߳�����Ϊ��֪ͨ״̬
	::SetEvent(g_hSet);

	// �ȴ�ȫ���߳�ִ�����
	::WaitForMultipleObjects(2, hThreadArrays, TRUE, INFINITE);

	// �ͷ��ں˶���ռ�
	::CloseHandle(hThreadArrays[0]);
	::CloseHandle(hThreadArrays[1]);

	// �����¼��ں˶���
    ::CloseHandle(g_hSet);  		
    ::CloseHandle(g_hClear);  		

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
			// �����ʼ��(�Ȳ��������ʼ���ı���,���ڲ����߳�)
			SendMessage(GetDlgItem((HWND)hwndDlg, IDC_EDIT_1), WM_SETTEXT, 0, (LPARAM)"0");
			break;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_BUTTON_1:
				{
					// ���������߳�
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
 	// TODO: Place code here.

	// ���û������ֹ�࿪
	HANDLE g_hCHECK_EXSIST_WIN32API_FLAG = CheckIsExsist();

	// ���öԻ���
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProcMain);

	// ������Ҫ����ǰ�ر��ں˾��
	::CloseHandle(g_hCHECK_EXSIST_WIN32API_FLAG);

	return 0;
}