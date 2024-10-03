// Win32Api_2.cpp : Defines the entry point for the application.
//

/*
	DWORD Erro = ::GetLastError();
	DbgPrintf("%d\n", Erro);
*/

#include "stdafx.h"

/*
	��ϰ��
	1�� ����һ�����ڳ���ѧϰ��β�ѯ�ĵ�
	2�� ��һ�� Windows �ж�������Ϣ����Ҫ�˽�һ��ÿ����Ϣ������.
	3�� NDCLASS wndclass = {0};
		WNDCLASS wndclass;	(������ʲô)

	// 2�� Windows �� 400 ������Ϣ
	// 3�� �����ǣ�ֵû�б���ʼ��
*/

LRESULT CALLBACK WindowProc(
						IN  HWND hwnd,					// ���ڵľ��
						IN  UINT uMsg,					// ��Ϣ��ʶ��
						IN  WPARAM wParam,				// ��һ����Ϣ����
						IN  LPARAM lParam				// �ڶ�����Ϣ����
						)
{
	switch(uMsg)
	{

	case WM_DESTROY:
		{
			// ��� (��) ��ť
			DbgPrintf("WM_DESTROY %d %d\n", wParam, lParam);
			PostQuitMessage(0);

			return 0;
		}
	case WM_MOVE:
		{
			// �����ƶ�
			DWORD MOVE_xPos = (DWORD) LOWORD(lParam);   // horizontal position 
			DWORD MOVE_yPos = (DWORD) HIWORD(lParam);   // vertical position
			DbgPrintf(TEXT("MOVE_xPos:%d\nMOVE_yPos:%d\n"), MOVE_xPos, MOVE_yPos);

			return 0;
		}
	case WM_MOUSEMOVE:
		{
			// ����ƶ�
			DWORD MOUSE_xPos = (DWORD) LOWORD(lParam);   // horizontal position 
			DWORD MOUSE_yPos = (DWORD) HIWORD(lParam);   // vertical position
			DbgPrintf(TEXT("MOUSE_xPos:%d\nMOUSE_yPos:%d\n"), MOUSE_xPos, MOUSE_yPos);

			return 0;
		}
	}

	// ���Լ�����Ҫ��ע����Ϣ����������ϵͳ
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	// ����������Ķ���
	// һ��Ҫ�Ƚ����г�Ա(10��)����ֵ
	WNDCLASS wndclass;
	wndclass.style = NULL;
	wndclass.lpfnWndProc = WindowProc;						// ���ڹ��̺���
	wndclass.cbClsExtra = NULL;
	wndclass.cbWndExtra = NULL;
	wndclass.hInstance = hInstance;							// ���崰�����Ӧ�ó����ʵ�����
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = (HBRUSH)COLOR_MENUTEXT;		// ���ڵı���ɫ
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = TEXT("My_First_Window");		// �����������
	

	RegisterClass(&wndclass);								// ������ע���ϵͳ

	// ��������
	HWND hwnd = CreateWindow( 
	TEXT("My_First_Window"),								// �����������
	TEXT("�ҵĵ�һ������"),									// ���ڱ���
	WS_SYSMENU | WS_MAXIMIZEBOX |\
	WS_MINIMIZEBOX | WS_THICKFRAME,												// ���������ʽ
	20,														// ����ڸ����ڵ�X����
	20,														// ����ڸ����ڵ�Y����
	800,													// ���ڵĿ��
	800,													// ���ڵĸ߶�
	NULL,													// �����ھ��,Ϊ NULL
	NULL,													// �˵����,Ϊ NULL
	hInstance,												// ��ǰӦ�ó���ľ��
	NULL);													// ��������һ��ΪNULL

	if(!hwnd)												// �Ƿ񴴽��ɹ�
		return 0;

	// ��ʾ����
	ShowWindow(hwnd, SW_SHOW);  

	// ��Ϣѭ��
	MSG msg = {0};  			
	while(GetMessage(&msg, NULL, 0, 0))
	{  			
		TranslateMessage(&msg);								// ������Ϣ(�ӹ���Ϣ)
		DispatchMessage(&msg);								// ���ظ�����ϵͳ
	}

	return 0;
}
