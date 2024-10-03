// Win32Api_4.cpp : Defines the entry point for the application.
//

/*
	DWORD Erro = ::GetLastError();
	DbgPrintf("%d\n", Erro);
*/

#include "stdafx.h"

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
			/*
			SIZE_MAXHIDE		4		������һЩ���ڱ����ʱ����Ϣ�����͵����еĵ������ڡ�
			SIZE_MAXIMIZED		2		�������
			SIZE_MAXSHOW		3		������һЩ���ڻָ�����ǰ�ĳߴ�ʱ����Ϣ�����͵����е���ʽ���ڡ�
			SIZE_MINIMIZED		1		������С��
			SIZE_RESTORED		0		���ڴ�С�仯 ��������󻯻���С��
			*/

			// �ı��Ĵ��ڵĿ�Ⱥ͸߶�
			DWORD SIZE_xPos = (DWORD) LOWORD(lParam);   // �¿��
			DWORD SIZE_yPos = (DWORD) HIWORD(lParam);   // �¸߶�

			if (!wParam)
			{
				DbgPrintf(TEXT("���ڴ�С�ı���!\n�¿��:%d\n�¸߶�:%d\n"), SIZE_xPos, SIZE_yPos);
				return 0;
			}
			if (wParam == 1)
			{
				DbgPrintf(TEXT("������С����!\n"));
				return 0;
			}
			if (wParam == 2)
			{
				DbgPrintf(TEXT("���������!\n"));
				return 0;
			}
			if (wParam == 3)
			{
				DbgPrintf(TEXT("����һЩ���ڻָ�����ǰ�ĳߴ���!\n"));
				return 0;
			}
			if (wParam == 4)
			{
				DbgPrintf(TEXT("������һЩ���ڱ������!\n"));
				return 0;
			}

			return 0;
		}
	case WM_CREATE:
		{
			// ��Ӧ�ó���ͨ������ CreateWindowEx �� CreateWindow �������󴴽�һ������ʱ���ᷢ�� WM_CREATE ��Ϣ
			// wParam ����
			// lParam ָ��CREATESTRUCT�ṹ��ָ�룬�ýṹ�����������ڴ����Ĵ��ڵ���Ϣ��
			LPCREATESTRUCT plParam = (CREATESTRUCT*)lParam;
			DbgPrintf(TEXT("x: %d\n"), plParam -> x);
			DbgPrintf(TEXT("y: %d\n"), plParam -> y);
			DbgPrintf(TEXT("cx: %d\n"), plParam -> cx);
			DbgPrintf(TEXT("cy: %d\n"), plParam -> cy);

			return 0;
		}
	case WM_DESTROY:
		{
			// ��� (��) ��ť
			DbgPrintf(TEXT("WM_DESTROY %d %d\n"), wParam, lParam);
			PostQuitMessage(0);

			return 0;
		}
	case WM_MOVE:
		{
			// �����ƶ�
			DWORD MOVE_xPos = (DWORD) LOWORD(lParam);   // horizontal position 
			DWORD MOVE_yPos = (DWORD) HIWORD(lParam);   // vertical position
			// DbgPrintf(TEXT("MOVE_xPos:%d\nMOVE_yPos:%d\n"), MOVE_xPos, MOVE_yPos);

			return 0;
		}
	case WM_MOUSEMOVE:
		{
			// ����ƶ�
			DWORD MOUSE_xPos = (DWORD) LOWORD(lParam);   // horizontal position 
			DWORD MOUSE_yPos = (DWORD) HIWORD(lParam);   // vertical position
			// DbgPrintf(TEXT("MOUSE_xPos:%d\nMOUSE_yPos:%d\n"), MOUSE_xPos, MOUSE_yPos);

			return 0;
		}

	case WM_COMMAND:
		{
			// ��ť������
			switch (LOWORD(wParam))
			{
			case 0x0001:
				{
					::MessageBox(0, "��ť 1 ��������!\n", 0, 0);
					return 0;
				}
			case 0x0002:
				{
					::MessageBox(0, "��ť 2 ��������!\n", 0, 0);
					return 0;
				}
			case 0x0003:
				{
					::MessageBox(0, "��ť 3 ��������!\n", 0, 0);
					return 0;
				}
			case 0x0004:
				{
					::MessageBox(0, "��ť 4 ��������!\n", 0, 0);
					return 0;
				}
			}
		}
	}

	// ���Լ�����Ҫ��ע����Ϣ����������ϵͳ
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

VOID Button_1(HINSTANCE hInstance, HWND hwnd)
{
	HWND e_hwnd = CreateWindow(
		TEXT("button"),											// ��ť�Ĺ̶����������
		TEXT("�ҵĵ�һ����ť"),									// ��ť����
		WS_CHILD | WS_VISIBLE |\
		BS_PUSHBUTTON | BS_DEFPUSHBUTTON,						// ��ť�����ʽ
		10,														// ����ڸ����ڵ�X����
		10,														// ����ڸ����ڵ�Y����
		200,													// ��ť�Ŀ��
		40,														// ��ť�ĸ߶�
		hwnd,													// �����ھ��
		(HMENU)0x0001,											// ��ť���͵� ID
		hInstance,												// ��ǰӦ�ó���ľ��
		NULL);													// ��������һ��ΪNULL
}

VOID Button_2(HINSTANCE hInstance, HWND hwnd)
{
	HWND e_hwnd = CreateWindow(
		TEXT("button"),											// ��ť�Ĺ̶����������
		TEXT("�ҵĵڶ�����ť"),									// ��ť����
		WS_CHILD | WS_VISIBLE |\
		BS_CHECKBOX |BS_AUTOCHECKBOX,							// ��ť�����ʽ
		210,													// ����ڸ����ڵ�X����
		10,														// ����ڸ����ڵ�Y����
		200,													// ��ť�Ŀ��
		40,														// ��ť�ĸ߶�
		hwnd,													// �����ھ��
		(HMENU)0x0002,											// ��ť���͵� ID
		hInstance,												// ��ǰӦ�ó���ľ��
		NULL);													// ��������һ��ΪNULL
}

VOID Button_3(HINSTANCE hInstance, HWND hwnd)
{
	HWND e_hwnd = CreateWindow(
		TEXT("button"),											// ��ť�Ĺ̶����������
		TEXT("�ҵĵ�������ť"),									// ��ť����
		WS_CHILD | WS_VISIBLE |\
		BS_AUTORADIOBUTTON,										// ��ť�����ʽ
		410,													// ����ڸ����ڵ�X����
		10,														// ����ڸ����ڵ�Y����
		200,													// ��ť�Ŀ��
		40,														// ��ť�ĸ߶�
		hwnd,													// �����ھ��
		(HMENU)0x0003,											// ��ť���͵� ID
		hInstance,												// ��ǰӦ�ó���ľ��
		NULL);													// ��������һ��ΪNULL
}

VOID Button_4(HINSTANCE hInstance, HWND hwnd)
{
	HWND e_hwnd = CreateWindow(
		TEXT("button"),											// ��ť�Ĺ̶����������
		TEXT("�ҵĵ��ĸ���ť"),									// ��ť����
		WS_CHILD | WS_VISIBLE |\
		BS_AUTORADIOBUTTON,										// ��ť�����ʽ
		610,													// ����ڸ����ڵ�X����
		10,														// ����ڸ����ڵ�Y����
		200,													// ��ť�Ŀ��
		40,														// ��ť�ĸ߶�
		hwnd,													// �����ھ��
		(HMENU)0x0004,											// ��ť���͵� ID
		hInstance,												// ��ǰӦ�ó���ľ��
		NULL);													// ��������һ��ΪNULL
}

int APIENTRY _tWinMain(HINSTANCE hInstance,				// ImageBase
                     HINSTANCE hPrevInstance,			// һ��Ϊ NULL
                     LPSTR     lpCmdLine,				// lpCmdLine �����������������ֵ��ָ��
                     int       nCmdShow)				// ������ʾ��ʽ
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
	WS_MINIMIZEBOX | WS_THICKFRAME,							// ���������ʽ
	20,														// ����ڸ����ڵ�X����
	20,														// ����ڸ����ڵ�Y����
	800,													// ���ڵĿ��
	800,													// ���ڵĸ߶�
	NULL,													// �����ھ��,Ϊ NULL
	NULL,													// �˵����,Ϊ NULL
	hInstance,												// ��ǰӦ�ó���ľ��
	NULL);													// ��������һ��ΪNULL

	if(!hwnd)												// �Ƿ񴴽��ɹ�
	{
		return 0;
	}

	// ��ʾ����
	ShowWindow(hwnd, SW_SHOW);  
	
	Button_1(hInstance, hwnd);
	Button_2(hInstance, hwnd);
	Button_3(hInstance, hwnd);
	Button_4(hInstance, hwnd);

	// ��Ϣѭ��
	MSG msg = {0};  			
	while(GetMessage(&msg, NULL, 0, 0))
	{  			
		TranslateMessage(&msg);								// ������Ϣ(�ӹ���Ϣ)
		DispatchMessage(&msg);								// ���ظ�����ϵͳ
	}

	return 0;
}

