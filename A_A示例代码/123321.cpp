// 123321.cpp : Defines the entry point for the console application.
//

/*
// �����Ķ���HelloWorld
int main(int argc, char* argv[])
{
	int i = 0;
	unsigned int a = 4294941587;
	unsigned int b = 2375067792;
	unsigned int c = 2475924151;
	unsigned char* Text = (unsigned char*)&c;
A:
	*((char*)(Text + i)) = ~*((char*)(Text + i));
	if (i++ < 11) goto A;
	printf("%s\n", Text);
	system("pause"); 
	return 0;
}
*/

#include "stdafx.h"
#include <stdlib.h>
#include <Windows.h>

HWND g_hWeChatWindow = NULL;
HWND g_hEdit = NULL;
HMODULE hModuleHandle = NULL;

LRESULT CALLBACK WindowProc(
						IN  HWND hwnd,					// ���ڵľ��
						IN  UINT uMsg,					// ��Ϣ��ʶ��
						IN  WPARAM wParam,				// ��һ����Ϣ����
						IN  LPARAM lParam				// �ڶ�����Ϣ����
						)
{
	switch(uMsg)
	{
	case WM_SIZE:
		{
			// ��С�ı�
			return 0;
		}
	case WM_CREATE:
		{
			// �����༭��
			return 0;
		}
	case WM_DESTROY:
		{
			// ��� (��) ��ť
			PostQuitMessage(0);
			return 0;
		}
	case WM_MOVE:
		{
			// �����ƶ�
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			// ����ƶ�
			return 0;
		}

	case WM_COMMAND:
		{
            // �༭���֪ͨ��Ϣ����
            return 0;
        }
		break;
	}

	// ���Լ�����Ҫ��ע����Ϣ����������ϵͳ
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int main(int argc, char* argv[])
{
	g_hWeChatWindow = FindWindowA("WeChatMainWndForPC", "΢��");
	if (!g_hWeChatWindow)
	{
		return -1;
	}
	hModuleHandle = GetModuleHandleA(NULL);
	if(!hModuleHandle)
	{
		return -2;
	}
	// ����������Ķ���
	// һ��Ҫ�Ƚ����г�Ա(10��)����ֵ
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS | CS_VREDRAW | CS_SAVEBITS;
	wndclass.lpfnWndProc = WindowProc;							// ���ڹ��̺���
	wndclass.cbClsExtra = NULL;
	wndclass.cbWndExtra = NULL;
	wndclass.hInstance = (HINSTANCE)hModuleHandle;				// ���崰�����Ӧ�ó����ʵ�����
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = (HBRUSH)COLOR_MENUTEXT;			// ���ڵı���ɫ
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "ChildWindow";						// �����������
	RegisterClass(&wndclass);									// ������ע���ϵͳ
	// ��������
	HWND hwnd = CreateWindowExA(
		0x02000000L,
		"ChildWindow",											// �����������
		"�Ӵ���",												// ���ڱ���
		WS_CHILD | WS_VISIBLE | WS_CAPTION |\
		WS_SIZEBOX | WS_MAXIMIZEBOX |\
		WS_MINIMIZEBOX  | WS_SYSMENU | WS_CLIPCHILDREN, 		// ������ʽ
		100,													// ����ڸ����ڵ�X����
		100,													// ����ڸ����ڵ�Y����
		400,													// ���ڵĿ��
		400,													// ���ڵĸ߶�
		g_hWeChatWindow,										// �����ھ��,Ϊ NULL
		NULL,													// �˵����,Ϊ NULL
		(HINSTANCE)hModuleHandle,								// ��ǰӦ�ó���ľ��
		NULL);													// ��������һ��ΪNULL
	if(!hwnd)													// �Ƿ񴴽��ɹ�
	{
		return 0;
	}
	// �����༭��
	g_hEdit = CreateWindowExA(
	WS_EX_TOPMOST,                          // ��չ��ʽ
	"Edit",                     // ����
	"�༭��",                   // ���ڱ��⣨Edit�ؼ�û�б��⣩
	WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_MULTILINE | ES_WANTRETURN,
	10,                         // X����
	10,                         // Y����
	380,                        // ���
	300,                        // �߶�
	(HWND)hwnd,					// �����ھ��
	(HMENU)NULL,                // �˵���������û�п���ΪNULL
	(HINSTANCE)hModuleHandle,   // Ӧ�ó���ʵ�����
	NULL);
	if (!g_hEdit)
	{
		MessageBox(hwnd, "�޷������༭��", "����", MB_OK | MB_ICONERROR);
		return -1;
	}
	// ��ʾ����;
	ShowWindow(hwnd, SW_SHOW);
	ShowWindow(g_hEdit, SW_SHOW);
	// ��Ϣѭ��;
	MSG msg = { 0 };  			
	while(GetMessage(&msg, NULL, 0, 0))
	{  			
		TranslateMessage(&msg);									// ������Ϣ(�ӹ���Ϣ);
		DispatchMessage(&msg);									// ���ظ�����ϵͳ;
	}

	return 0;
}
