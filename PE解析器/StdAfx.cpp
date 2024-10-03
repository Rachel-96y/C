// stdafx.cpp : source file that includes just the standard includes
//	WIN32API_7.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "PeFiles.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

//////////////////////////////////////////////////////////////////////
// ���ļ��ṩ�������̺�ģ�鼰���湦�ܺ���
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// _TLS_Directory

WINAPI TLSDirectory::_TLSDirectory()
{
	/*
		��ʼ��ȫ����Ա
	*/
	
	// ȫ�ֱ�־
	this -> m_dwGlobalFlag = 0x00000000;

	// �ļ�������ָ��
	this -> m_fpFileBuffer = 0;

	// ���ڴ洢�����ģ���� 
	this -> m_hAppInstance = 0;

	// ��ʼ�����洢��·���Ŀռ��С
	this -> m_szFileName = (LPTSTR)malloc(sizeof(CHAR) * 0x100);
	memset(this -> m_szFileName, 0x00000000, sizeof(CHAR) * 0x100);

}

WINAPI TLSDirectory::_TLSDirectory(IN DWORD dwNumber)
{
	/*
		��ʼ��ȫ����Ա
		��������洢�ַ����Ļ�������С
	*/
	
	// ȫ�ֱ�־
	this -> m_dwGlobalFlag = 0x00000000;

	// �ļ�������ָ��
	this -> m_fpFileBuffer = 0;

	// ���ڴ洢�����ģ���� 
	this -> m_hAppInstance = 0;

	// ��ʼ�����洢��·���Ŀռ��С
	this -> m_szFileName = (LPTSTR)malloc(sizeof(CHAR) * dwNumber);
	memset(this -> m_szFileName, 0x00000000, sizeof(CHAR) * dwNumber);
}

WINAPI TLSDirectory::~_TLSDirectory()
{
	/*
		�ͷſռ�
	*/
	free(this -> m_szFileName);
	this -> m_szFileName = NULL;
	this -> m_fpFileBuffer = NULL;
	this -> m_hAppInstance = NULL;
	this -> m_dwGlobalFlag = NULL;
}

// END _TLS_Directory
//////////////////////////////////////////////////////////////////////

void WINAPIV OutputDebugStringF(const char *format, ...)  
{
	/*
		���ǵ�����صĺ��� ֻ�� _DEBUG ģʽ������
	*/
    va_list vlArgs;  
    char    *strBuffer = (char*)GlobalAlloc(GPTR, 4096);  

    va_start(vlArgs, format);  
    _vsnprintf(strBuffer, 4096 - 1, format, vlArgs);  
    va_end(vlArgs);  
    strcat(strBuffer, "\n");  
    OutputDebugStringA(strBuffer);  
    GlobalFree(strBuffer); 

    return;  
}

//////////////////////////////////////////////////////////////////////

VOID WINAPI CheckIsExsist(void)
{
	/*
		�˺���ͨ���������� ���ж������Ƿ�࿪
	*/
	
	// ����ɹ����ؽ��̿���ָ��
	LPVOID pSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// �� PROCESSENTRY32 �� dwSize ��ֵ
	PROCESSENTRY32 StructProcessEntry32 = {0};
	StructProcessEntry32.dwSize = sizeof(PROCESSENTRY32);

	// �� MODULEENTRY32 �� dwSize ��ֵ
	MODULEENTRY32 StructModuleEntry32 = {0};
	StructModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	// ��ȡ��һ������ �Ž� StructProcessEntry32.szExeFile ��
	Process32First(pSnapshot, &StructProcessEntry32);

	StructModuleEntry32.th32ProcessID = 0;

	// ����ɹ�����ģ�����ָ��
	HANDLE pModSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, StructProcessEntry32.th32ProcessID);

	// ��ȡ��һ��ģ�� �Ž� StructModuleEntry32.szExeFile ��
	Module32First(pModSnapshot, &StructModuleEntry32);

	// �õ���ǰ��������
	PTCHAR szBaseName = StructModuleEntry32.szModule;

	// ���� �����жϴ˳���(�д����ֵ�exe) �Ƿ���Ψһ��
	DWORD dwCount = 0;
	do
	{
		// �Ƚ������ַ����Ƿ����
		DWORD dwResult = strcmp(szBaseName, StructProcessEntry32.szExeFile);
		if (!dwResult)
		{
			dwCount++;
		}
	}
	// ��û���κν���ʱ����ѭ��
	while(Process32Next(pSnapshot, &StructProcessEntry32));

	if (dwCount == 1)
	{
		// ���ֻ��һ�����������ִ��
		return;
	}
	else
	{
		// ������һ��������ֱ���˳�
		exit(0);
	}
}

//////////////////////////////////////////////////////////////////////

VOID WINAPI SetListViewText(IN HWND hListProcess, 
							IN DWORD Count, 
							IN PTCHAR szNumber, 
							IN PTCHAR szString, 
							IN PTCHAR szProcessID, 
							IN PTCHAR szImageBase, 
							IN PTCHAR szSizeOfImage
							)
{
	/*
		���õ��ĸ�������д�뵽IDC_LIST_PROCESS_UPPER��
	*/

	// �����ò���ϵͳ��ʾֵ�Ľṹ
	LV_ITEM vitem = {0};

	// ��Ա pszText ��Ч�������д��
	vitem.mask = LVIF_TEXT;

	// ���
	vitem.pszText = TEXT(szNumber);
	vitem.iItem = Count;
	vitem.iSubItem = 0;
	SendMessage(hListProcess, LVM_INSERTITEM, 0, (DWORD)&vitem);

	// ��������
	vitem.pszText = TEXT(szString);
	vitem.iSubItem = 1;
	SendMessage(hListProcess, LVM_SETITEM, 0, (DWORD)&vitem);

	// PID
	vitem.pszText = TEXT(szProcessID);	
	vitem.iSubItem = 2;
	SendMessage(hListProcess, LVM_SETITEM, 0, (DWORD)&vitem);

	// �����ַ
	vitem.pszText = TEXT(szImageBase);	
	vitem.iSubItem = 3;
	SendMessage(hListProcess, LVM_SETITEM, 0, (DWORD)&vitem);

	// �����С
	vitem.pszText = TEXT(szSizeOfImage);	
	vitem.iSubItem = 4;
	SendMessage(hListProcess, LVM_SETITEM, 0, (DWORD)&vitem);

	return;
}

//////////////////////////////////////////////////////////////////////

VOID WINAPI SetListViewTextLow(IN HWND hListProcess, 
							   IN DWORD Count, 
							   IN PTCHAR szNumber, 
							   IN PTCHAR szName, 
							   IN PTCHAR szModBaseAddr, 
							   IN PTCHAR szModBaseSize, 
							   IN PTCHAR szLocal
							   )
{
	/*
		���õ��ĸ�������д�뵽IDC_LIST_PROCESS_LOWER��
	*/

	// �����ò���ϵͳ��ʾֵ�Ľṹ
	LV_ITEM vitem = {0};

	// ��Ա pszText ��Ч�������д��
	vitem.mask = LVIF_TEXT;

	// ���
	vitem.pszText = TEXT(szNumber);
	vitem.iItem = Count;
	vitem.iSubItem = 0;
	SendMessage(hListProcess, LVM_INSERTITEM, 0, (DWORD)&vitem);

	// ģ������
	vitem.pszText = TEXT(szName);
	vitem.iSubItem = 1;
	SendMessage(hListProcess, LVM_SETITEM, 0, (DWORD)&vitem);

	// ģ��ImageBase
	vitem.pszText = TEXT(szModBaseAddr);
	vitem.iSubItem = 2;
	SendMessage(hListProcess, LVM_SETITEM, 0, (DWORD)&vitem);

	// ģ��ImageBase
	vitem.pszText = TEXT(szModBaseSize);
	vitem.iSubItem = 3;
	SendMessage(hListProcess, LVM_SETITEM, 0, (DWORD)&vitem);

	// ģ��λ��
	vitem.pszText = TEXT(szLocal);	
	vitem.iSubItem = 4;
	SendMessage(hListProcess, LVM_SETITEM, 0, (DWORD)&vitem);

	return;
}

//////////////////////////////////////////////////////////////////////

VOID WINAPI SetListViewTextOfSection(IN HWND hListSection, 
									 IN DWORD Count, 
									 IN PTCHAR szNumber, 
									 IN PTCHAR szName, 
									 IN PTCHAR szVirtualSize, 
									 IN PTCHAR szVirtualAddress, 
									 IN PTCHAR szSizeOfRawData, 
									 IN PTCHAR szPointerToRawData, 
									 IN PTCHAR szCharacteristics
									 )
{
	/*
		���õ��ĸ�������д�뵽IDC_LIST_Section��
	*/

	// �����ò���ϵͳ��ʾֵ�Ľṹ
	LV_ITEM vitem = {0};

	// ��Ա pszText ��Ч�������д��
	vitem.mask = LVIF_TEXT;

	// ���
	vitem.pszText = TEXT(szNumber);
	vitem.iItem = Count;
	vitem.iSubItem = 0;
	SendMessage(hListSection, LVM_INSERTITEM, 0, (DWORD)&vitem);

	// ����
	vitem.pszText = TEXT(szName);
	vitem.iSubItem = 1;
	SendMessage(hListSection, LVM_SETITEM, 0, (DWORD)&vitem);

	// �ڴ��С
	vitem.pszText = TEXT(szVirtualSize);
	vitem.iSubItem = 2;
	SendMessage(hListSection, LVM_SETITEM, 0, (DWORD)&vitem);

	// �ڴ�ƫ��
	vitem.pszText = TEXT(szVirtualAddress);
	vitem.iSubItem = 3;
	SendMessage(hListSection, LVM_SETITEM, 0, (DWORD)&vitem);

	// �ļ���С
	vitem.pszText = TEXT(szSizeOfRawData);	
	vitem.iSubItem = 4;
	SendMessage(hListSection, LVM_SETITEM, 0, (DWORD)&vitem);

	// �ļ�ƫ��
	vitem.pszText = TEXT(szPointerToRawData);	
	vitem.iSubItem = 5;
	SendMessage(hListSection, LVM_SETITEM, 0, (DWORD)&vitem);

	// ������
	vitem.pszText = TEXT(szCharacteristics);	
	vitem.iSubItem = 6;
	SendMessage(hListSection, LVM_SETITEM, 0, (DWORD)&vitem);

	return;
}
//////////////////////////////////////////////////////////////////////

BOOL WINAPI GetPidByListViewText(IN HWND hwndDlg, OUT PTCHAR szResult)
{
	/*
		�����û�����������õ����е�pid��ֵ
	*/

	// �����˽ṹ���ڴ洢��ȡ����ֵ
	LV_ITEM vitem = {0};

	// ����û��������һ��
	DWORD dwResult = SendMessage(hwndDlg, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	if (dwResult == ERROR_CLICK)
	{
		// û�е����ָ��λ��
		return RETURN_FAILURE;
	}

	vitem.iSubItem = 2;				// Ҫ��ȡ����
	vitem.pszText = szResult;		// pid��ֵ�洢���洢��λ��
	vitem.cchTextMax = 0x10;		// ָ���������Ĵ�С

	// ��ȡ PID �е�ֵ(������)
	SendMessage(hwndDlg, LVM_GETITEMTEXT, dwResult, (LPARAM)&vitem);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

VOID WINAPI EnumMoudelByProcID(IN HWND hListViewLower, IN DWORD ProcessID)
{
	/*
		���ݽ��� PID �����˽�����ȫ����ģ��
	*/
	
	// ����һ�� MODULEENTRY32 �ṹ
	MODULEENTRY32 StructModuleEntry32 = {0};
	
	// �� MODULEENTRY32 �� dwSize ��ֵ
	StructModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	// ��ȡģ�����
	LPVOID pModuleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
	if (pModuleSnapshot == INVALID_HANDLE_VALUE)
	{
		// ������� -1 �����ʧ�� ��:û��Ȩ��
		return;
	}

	// ������������Ľ��� ID ����ģ��
	StructModuleEntry32.th32ProcessID = ProcessID;

	// ��һ�α���
	Module32First(pModuleSnapshot, &StructModuleEntry32);

	// ����
	DWORD dwListNumber = NULL;

	// ���ڴ洢 ��� ת������ַ���
	TCHAR szNumber[0x10] = {0};

	// ���ڴ洢ģ�� ImageBase ת������ַ���
	TCHAR szBaseAddr[0x10] = {0};

	// ���ڴ洢ģ�� ��С ת������ַ���
	TCHAR szBaseSize[0x10] = {0};

	// ��ȡ��һ��ģ�� �Ž� StructModuleEntry32.szExeFile ��
	Module32First(pModuleSnapshot, &StructModuleEntry32);

	do
	{
		// ����ʽ������ת��Ϊ�ַ���
		sprintf(szNumber, "%8d", dwListNumber);
		sprintf(szBaseAddr, "%08X", StructModuleEntry32.modBaseAddr);
		sprintf(szBaseSize, "%08X", StructModuleEntry32.modBaseSize);


		if (pModuleSnapshot != INVALID_HANDLE_VALUE)
		{
			// �� ListView д������(��Ȩ�޵����)
			SetListViewTextLow(
				hListViewLower, 
				dwListNumber, 
				szNumber, 
				StructModuleEntry32.szModule, 
				szBaseAddr, 
				szBaseSize, 
				StructModuleEntry32.szExePath
				);
		}

		dwListNumber++;
	}
	// ��ȡ��һ��ģ��
	while(Module32Next(pModuleSnapshot, &StructModuleEntry32));

	return;
}

//////////////////////////////////////////////////////////////////////

VOID WINAPI EnumProcByWinApi(IN HWND hListViewUpper)
{
	/*
		��ϵͳ�е����н��̱�������
	*/

	// ����ɹ����ؽ��̿���ָ��
	HANDLE pSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// �� PROCESSENTRY32 �� dwSize ��ֵ
	PROCESSENTRY32 StructProcessEntry32 = {0};
	StructProcessEntry32.dwSize = sizeof(PROCESSENTRY32);

	// �� MODULEENTRY32 �� dwSize ��ֵ
	MODULEENTRY32 StructModuleEntry32 = {0};
	StructModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	// ��ȡ��һ������ �Ž� StructProcessEntry32.szExeFile ��
	Process32First(pSnapshot, &StructProcessEntry32);

	// �ڼ���
	DWORD dwListNumber = 0;

	// ���ڴ洢 ��� ת������ַ���
	TCHAR szNumber[0x10] = {0};

	// ���ڴ洢 PID ת������ַ���
	TCHAR szBufferPID[0x10] = {0};

	// ���ڴ洢 ImageBase ת������ַ���
	TCHAR szBufferImageBase[0x10] = {0};

	// ���ڴ洢 SizeOfImage ת������ַ���
	TCHAR szBufferSizeOfImage[0x10] = {0};

	do
	{
		// ����ɹ�����ģ�����ָ��
		HANDLE pModSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, StructProcessEntry32.th32ProcessID);

		// ��ȡ��һ��ģ�� �Ž� StructModuleEntry32.szExeFile ��
		Module32First(pModSnapshot, &StructModuleEntry32);

		// ����ʽ������ת��Ϊ�ַ���
		sprintf(szNumber, "%8d", dwListNumber);
		sprintf(szBufferPID, "%8d", StructProcessEntry32.th32ProcessID);
		sprintf(szBufferImageBase, "%08X", StructModuleEntry32.modBaseAddr);
		sprintf(szBufferSizeOfImage, "%08X", StructModuleEntry32.modBaseSize);

		if (pModSnapshot != INVALID_HANDLE_VALUE)
		{
			// �� ListView д������
			SetListViewText(
				hListViewUpper, 
				dwListNumber, 
				szNumber, 
				StructProcessEntry32.szExeFile, 
				szBufferPID, 
				szBufferImageBase, 
				szBufferSizeOfImage
				);
		}
		else
		{
			// �� ListView д������ (û��Ȩ�޵����)
			SetListViewText(
				hListViewUpper, 
				dwListNumber, 
				szNumber, 
				StructProcessEntry32.szExeFile, 
				szBufferPID, 
				"��32λ����", 
				"��32λ����"
				);
		}
		
		dwListNumber++;
	}
	// ��û���κν���ʱ����ѭ��
	while(Process32Next(pSnapshot, &StructProcessEntry32));

	return;
}

//////////////////////////////////////////////////////////////////////

VOID WINAPI InitProcessListViewUpper(IN HWND hwndDlg)
{
	/*
		���� ListView ��ʽ
	*/

	LV_COLUMN lv = {0};
	HWND hListProcess = {0};

	// ��ȡIDC_LIST_PROCESS���
	hListProcess = GetDlgItem(hwndDlg, IDC_LIST_PROCESS_UPPER);

	// ��������ѡ��
	SendMessage(hListProcess, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	// ��������
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	
	// �� 0 ��
	lv.pszText = TEXT("���");
	lv.cx = 100;
	lv.iSubItem = 0;
	SendMessage(hListProcess, LVM_INSERTCOLUMN, 0, (DWORD)&lv);

	// �� 1 ��
	lv.pszText = TEXT("����");
	lv.cx = 300;
	lv.iSubItem = 1;
	SendMessage(hListProcess, LVM_INSERTCOLUMN, 1, (DWORD)&lv);

	// �� 2 ��
	lv.pszText = TEXT("PID");
	lv.cx = 100;
	lv.iSubItem = 2;
	SendMessage(hListProcess, LVM_INSERTCOLUMN, 2, (DWORD)&lv);


	// �� 3 ��
	lv.pszText = TEXT("�����ַ");
	lv.cx = 200;
	lv.iSubItem = 3;
	SendMessage(hListProcess, LVM_INSERTCOLUMN, 3, (DWORD)&lv);

	// �� 4 ��
	lv.pszText = TEXT("�����С");
	lv.cx = 200;
	lv.iSubItem = 4;
	SendMessage(hListProcess, LVM_INSERTCOLUMN, 4, (DWORD)&lv);
}

//////////////////////////////////////////////////////////////////////

VOID WINAPI InitProcessListViewLower(HWND hwndDlg)
{
	/*
		���õڶ����� ListView ��ʽ
	*/

	LV_COLUMN lv = {0};
	HWND hListProcess = {0};

	// ��ȡIDC_LIST_PROCESS���
	hListProcess = GetDlgItem(hwndDlg, IDC_LIST_PROCESS_LOWER);

	// ��������ѡ��
	SendMessage(hListProcess, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	
	// ��������
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

	// ��0��
	lv.pszText = TEXT("���");
	lv.cx = 100;
	lv.iSubItem = 0;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 0, (DWORD)&lv);

	// ��1��
	lv.pszText = TEXT("ģ������");
	lv.cx = 300;
	lv.iSubItem = 1;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 1, (DWORD)&lv);

	// ��2��
	lv.pszText = TEXT("ģ���ַ");
	lv.cx = 200;
	lv.iSubItem = 2;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 2, (DWORD)&lv);

	// ��3��
	lv.pszText = TEXT("ģ���С");
	lv.cx = 200;
	lv.iSubItem = 3;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 3, (DWORD)&lv);


	// ��4��
	lv.pszText = TEXT("ģ��λ��");
	lv.cx = 800;
	lv.iSubItem = 4;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 4, (DWORD)&lv);
}

//////////////////////////////////////////////////////////////////////

VOID WINAPI InitSectionListView(HWND hwndDlg)
{
	/*
		����IDD_DIALOG_Section��ListView����ʽ
	*/

	LV_COLUMN lv = {0};
	HWND hListProcess = {0};

	// ��ȡIDC_LIST_PROCESS���
	hListProcess = GetDlgItem(hwndDlg, IDC_LIST_Section);

	// ��������ѡ��
	SendMessage(hListProcess, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	
	// ��������
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

	// ��0��
	lv.pszText = TEXT("���");
	lv.cx = 100;
	lv.iSubItem = 0;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 0, (DWORD)&lv);

	// ��1��
	lv.pszText = TEXT("����");
	lv.cx = 200;
	lv.iSubItem = 1;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 1, (DWORD)&lv);

	// ��2��
	lv.pszText = TEXT("�ڴ��С");
	lv.cx = 200;
	lv.iSubItem = 2;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 2, (DWORD)&lv);

	// ��3��
	lv.pszText = TEXT("�ڴ�ƫ��");
	lv.cx = 200;
	lv.iSubItem = 3;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 3, (DWORD)&lv);


	// ��4��
	lv.pszText = TEXT("�ļ���С");
	lv.cx = 200;
	lv.iSubItem = 4;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 4, (DWORD)&lv);

	// ��5��
	lv.pszText = TEXT("�ļ�ƫ��");
	lv.cx = 200;
	lv.iSubItem = 5;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 5, (DWORD)&lv);

	// ��6��
	lv.pszText = TEXT("������");
	lv.cx = 200;
	lv.iSubItem = 6;
	SendMessage(hListProcess,LVM_INSERTCOLUMN, 6, (DWORD)&lv);

	return;

}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI SetIcon(IN HINSTANCE hAppInstance, IN HWND hwndDlg, IN DWORD IconSmall, IN DWORD IconBig)
{
	/*
		����ͼ��
		��Ҫģ���� hAppInstance
		���� hwnd �ı�ָ���Ĵ��ڵ�ͼ��
		IconSmall Сͼ����Դ���
		IconBig ��ͼ����Դ���
	*/

	HICON hIcon_SMALL = LoadIcon(hAppInstance, MAKEINTRESOURCE(IconSmall));
	HICON hIcon_BIG = LoadIcon(hAppInstance, MAKEINTRESOURCE(IconBig));
	SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (DWORD)hIcon_SMALL);
	SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (DWORD)hIcon_BIG);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI PushViewButton(IN HWND hwndDlg, IN LPTSTR TEXT(szFileName), IN PTCHAR TEXT(szTitle))
{
	/* 
		�˺������ڴ��� ���û����"�鿴"��ťʱӦ�ý��еĲ���
		����û�ѡ��ɹ��򷵻ط�0
	*/

	// ��ʼ�� OPENFILENAME �ṹ ���ڻ�ȡ�ļ�·���Ľṹ
	OPENFILENAME stOpenFile = {0};

	// ָ���ṹ�ĳ���
	stOpenFile.lStructSize = sizeof(OPENFILENAME);

	// ָ�����ĸ�������(�����򴰿�)
	stOpenFile.hwndOwner = hwndDlg;

	// ��Ҫ���˵��ļ���չ�� | exe��dll��sys��vxd��vdm
	stOpenFile.lpstrFilter = TEXT("exe;dll;sys;vxd;vdm;\0*exe;*dll;*sys;*vxd;*vdm;\0exe;\0*.exe;\0dll;\0*.dll\0sys;\0*.sys\0vxd;\0*.vxd;\0vdm;\0*vdm\0All Files(*.*)\0*.*\0\0");

	// ָ�� lpstrFile ��ָ��Ļ������Ĵ�С �� TCHAR Ϊ��λ
	stOpenFile.nMaxFile = MAX_PATH;
	
	// д��·���洢��ַ
	stOpenFile.lpstrFile = szFileName;

	// Ҫ��ʾ�ı���
	stOpenFile.lpstrTitle = TEXT(szTitle);

	// �ļ���ʾ��ʽ������
	stOpenFile.Flags = OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;
	

	return GetOpenFileName(&stOpenFile);
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisOfPEData32(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS)
{
	/*
		���ʹ�ô˺���,��֤���򿪵��ļ��Ѿ�ͨ��PE�ļ����
		����PE�ļ�,�������õ����ݷֱ�д�뵽IDD_DIALOG_DOS_HEADER�ϵĸ���Edit��
		������32λPE�ļ�������

		��Ҫ��ȡ��ֵ��:

		������ڵ�	(IDC_EDIT_EntryPoint)			��ϵͳ		(IDC_EDIT_SubSystem)
		�����ַ	(IDC_EDIT_ImageBase)			������Ŀ	(IDC_EDIT_NumberOfSections)
		�����С	(IDC_EDIT_SizeOfImage)			ʱ���		(IDC_EDIT_TimeDateStamp)
		�����ַ	(IDC_EDIT_BaseOfCode)			PEͷ��С	(IDC_EDIT_SizeOfHeaders)
		���ݻ�ַ	(IDC_EDIT_BaseOfData)			����ֵ		(IDC_EDIT_Magic)
		�ڴ����	(IDC_EDIT_SectionAlignment)		У���		(IDC_EDIT_CheckSum)
		�ļ�����	(IDC_EDIT_FileAlignment)		��ѡPEͷ	(IDC_EDIT_SizeOfOptionalHeader)
		��־��		(IDC_EDIT_Characteristics)		Ŀ¼��Ŀ��	(IDC_EDIT_NumberOfRvaAndSizes)
	*/
	
	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ���ڴ洢����Edit�ı��
	DWORD ElementalArrays[0x10] =
	{
		IDC_EDIT_EntryPoint,
		IDC_EDIT_ImageBase,
		IDC_EDIT_SizeOfImage,
		IDC_EDIT_BaseOfCode,
		IDC_EDIT_BaseOfData,
		IDC_EDIT_SectionAlignment,
		IDC_EDIT_FileAlignment,
		IDC_EDIT_Characteristics,
		IDC_EDIT_SubSystem,
		IDC_EDIT_NumberOfSections,
		IDC_EDIT_TimeDateStamp,
		IDC_EDIT_SizeOfHeaders,
		IDC_EDIT_Magic,
		IDC_EDIT_CheckSum,
		IDC_EDIT_SizeOfOptionalHeader,
		IDC_EDIT_NumberOfRvaAndSizes,
	};

	// ���ڴ洢��ӦElementalArrays����Ľ���������ֵ
	DWORD dwDATA[0x10] = 
	{
		pIMAGE_OPTIONAL_HEADER32 -> AddressOfEntryPoint,
		pIMAGE_OPTIONAL_HEADER32 -> ImageBase,
		pIMAGE_OPTIONAL_HEADER32 -> SizeOfImage,
		pIMAGE_OPTIONAL_HEADER32 -> BaseOfCode,
		pIMAGE_OPTIONAL_HEADER32 -> BaseOfData,
		pIMAGE_OPTIONAL_HEADER32 -> SectionAlignment,
		pIMAGE_OPTIONAL_HEADER32 -> FileAlignment,
		pIMAGE_FILE_HEADER -> Characteristics,
		pIMAGE_OPTIONAL_HEADER32 -> Subsystem,
		pIMAGE_FILE_HEADER -> NumberOfSections,
		pIMAGE_FILE_HEADER -> TimeDateStamp,
		pIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders,
		pIMAGE_OPTIONAL_HEADER32 -> Magic,
		pIMAGE_OPTIONAL_HEADER32 -> CheckSum,
		pIMAGE_FILE_HEADER -> SizeOfOptionalHeader,
		pIMAGE_OPTIONAL_HEADER32 -> NumberOfRvaAndSizes,
	};

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};
	
	// ����ָ��ѭ������
	DWORD dwTempNumber = 0xF;
	do
	{
		// �ҵ����ݲ�����ת��Ϊ�ַ�������
		sprintf(szDATA, "%08X", dwDATA[dwTempNumber]);
		SendMessage(GetDlgItem(hwndDlg, ElementalArrays[dwTempNumber]), WM_SETTEXT, 0, (LPARAM)TEXT(szDATA));
	}
	while(dwTempNumber--);
		
	return RETURN_SUCCESS;
}


//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisOfPEData64(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS)
{
	/*
		���ʹ�ô˺���,��֤���򿪵��ļ��Ѿ�ͨ��PE�ļ����
		����PE�ļ�,�������õ����ݷֱ�д�뵽IDD_DIALOG_DOS_HEADER�ϵĸ���Edit��
		������64λPE�ļ�������
		��Ҫ��ȡ��ֵ��:
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS64 pIMAGE_NT_HEADERS64 = (IMAGE_NT_HEADERS64*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS64 + sizeof(pIMAGE_NT_HEADERS64 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 
	PIMAGE_OPTIONAL_HEADER64 pIMAGE_OPTIONAL_HEADER64 = (IMAGE_OPTIONAL_HEADER64*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ���ڴ洢����Edit�ı��
	DWORD ElementalArrays[0xE] = 
	{
		IDC_EDIT_EntryPoint,
		IDC_EDIT_SizeOfImage,
		IDC_EDIT_BaseOfCode,
		IDC_EDIT_SectionAlignment,
		IDC_EDIT_FileAlignment,
		IDC_EDIT_Characteristics,
		IDC_EDIT_SubSystem,
		IDC_EDIT_NumberOfSections,
		IDC_EDIT_TimeDateStamp,
		IDC_EDIT_SizeOfHeaders,
		IDC_EDIT_Magic,
		IDC_EDIT_CheckSum,
		IDC_EDIT_SizeOfOptionalHeader,
		IDC_EDIT_NumberOfRvaAndSizes,
	};


	// ���ڴ洢��ӦElementalArrays����Ľ���������ֵ
	DWORD dwDATA[0xE] = 
	{
		pIMAGE_OPTIONAL_HEADER64 -> AddressOfEntryPoint,
		pIMAGE_OPTIONAL_HEADER64 -> SizeOfImage,
		pIMAGE_OPTIONAL_HEADER64 -> BaseOfCode,
		pIMAGE_OPTIONAL_HEADER64 -> SectionAlignment,
		pIMAGE_OPTIONAL_HEADER64 -> FileAlignment,
		pIMAGE_FILE_HEADER -> Characteristics,
		pIMAGE_OPTIONAL_HEADER64 -> Subsystem,
		pIMAGE_FILE_HEADER -> NumberOfSections,
		pIMAGE_FILE_HEADER -> TimeDateStamp,
		pIMAGE_OPTIONAL_HEADER64 -> SizeOfHeaders,
		pIMAGE_OPTIONAL_HEADER64 -> Magic,
		pIMAGE_OPTIONAL_HEADER64 -> CheckSum,
		pIMAGE_FILE_HEADER -> SizeOfOptionalHeader,
		pIMAGE_OPTIONAL_HEADER64 -> NumberOfRvaAndSizes,
	};

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};
	
	// ����ָ��ѭ������
	DWORD dwTempNumber = 0xD;
	do
	{
		// �ҵ����ݲ�����ת��Ϊ�ַ�������
		sprintf(szDATA, "%08X", dwDATA[dwTempNumber]);
		SendMessage(GetDlgItem(hwndDlg, ElementalArrays[dwTempNumber]), WM_SETTEXT, 0, (LPARAM)TEXT(szDATA));
	}
	while(dwTempNumber--);

	// ���ݻ�ַ(BaseOfData)ʹ��32λ����
	sprintf(szDATA,"%08X", pIMAGE_OPTIONAL_HEADER32 -> BaseOfData);
	SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_BaseOfData), WM_SETTEXT, 0, (LPARAM)TEXT(szDATA));

	// 64λ��ImageBase������ֵ(ULONGLONG����)
	sprintf(szDATA,"%I64X", pIMAGE_OPTIONAL_HEADER64 -> ImageBase);
	SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_ImageBase), WM_SETTEXT, 0, (LPARAM)TEXT(szDATA));

	return RETURN_SUCCESS;
}
	

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDirectoryOfPEData32(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS)
{
	/*
		��һ������32λPE�ļ�������Ŀ¼

		"������", "�����", "��Դ��", "�쳣��Ϣ��", 
		"��ȫ֤���", "�ض�λ��", "������Ϣ��", "��Ȩ���б�", 
		"ȫ��ָ���", "TLS��", "�������ñ�", "�󶨵����",
		"IAT��", "�ӳٵ����", "COM��Ϣ��", "������δʹ�õı�",
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER32 -> DataDirectory);

	// ���ڴ洢����Edit�ı��
	DWORD ElementalArrays[0x30] = 
	{
		IDC_EDIT_D_Export_FOA,
		IDC_EDIT_D_Export_RVA,
		IDC_EDIT_D_Export_SIZE,
		IDC_EDIT_D_Import_FOA,
		IDC_EDIT_D_Import_RVA,
		IDC_EDIT_D_Import_SIZE,
		IDC_EDIT_D_Resource_FOA,
		IDC_EDIT_D_Resource_RVA,
		IDC_EDIT_D_Resource_SIZE,
		IDC_EDIT_D_Exception_FOA,
		IDC_EDIT_D_Exception_RVA,
		IDC_EDIT_D_Exception_SIZE,
		IDC_EDIT_D_Security_FOA,
		IDC_EDIT_D_Security_RVA,
		IDC_EDIT_D_Security_SIZE,
		IDC_EDIT_D_BaseReloc_FOA,
		IDC_EDIT_D_BaseReloc_RVA,
		IDC_EDIT_D_BaseReloc_SIZE,
		IDC_EDIT_D_Debug_FOA,
		IDC_EDIT_D_Debug_RVA,
		IDC_EDIT_D_Debug_SIZE,
		IDC_EDIT_D_CopyRight_FOA,
		IDC_EDIT_D_CopyRight_RVA,
		IDC_EDIT_D_CopyRight_SIZE,
		IDC_EDIT_D_GlobalPtr_FOA,
		IDC_EDIT_D_GlobalPtr_RVA,
		IDC_EDIT_D_GlobalPtr_SIZE,
		IDC_EDIT_D_TLS_FOA,
		IDC_EDIT_D_TLS_RVA,
		IDC_EDIT_D_TLS_SIZE,
		IDC_EDIT_D_LoadConfig_FOA,
		IDC_EDIT_D_LoadConfig_RVA,
		IDC_EDIT_D_LoadConfig_SIZE,
		IDC_EDIT_D_BoundImport_FOA,
		IDC_EDIT_D_BoundImport_RVA,
		IDC_EDIT_D_BoundImport_SIZE,
		IDC_EDIT_D_IAT_FOA,
		IDC_EDIT_D_IAT_RVA,
		IDC_EDIT_D_IAT_SIZE,
		IDC_EDIT_D_DelayImport_FOA,
		IDC_EDIT_D_DelayImport_RVA,
		IDC_EDIT_D_DelayImport_SIZE,
		IDC_EDIT_D_ComDescriptor_FOA,
		IDC_EDIT_D_ComDescriptor_RVA,
		IDC_EDIT_D_ComDescriptor_SIZE,
		IDC_EDIT_D_Retain_FOA,
		IDC_EDIT_D_Retain_RVA,
		IDC_EDIT_D_Retain_SIZE,
	};

	// ���ڴ洢��ӦElementalArrays����Ľ���������ֵ
	DWORD dwDATA[0x30] = {0};

	// ��Ҫѭ���Ĵ���+1
	DWORD dwTempNumber = 0x30;

	// ����Ŀ¼�±�
	DWORD dwDIRECTORY = 0xF;

	do
	{
		// ѭ���洢��Ҫ��ֵ
		dwTempNumber--;
		dwDATA[dwTempNumber--] = (pIMAGE_DATA_DIRECTORY + dwDIRECTORY) -> Size;
		dwDATA[dwTempNumber--] = (pIMAGE_DATA_DIRECTORY + dwDIRECTORY) -> VirtualAddress;
		dwDATA[dwTempNumber] = ChangeRvaToFoa32((pIMAGE_DATA_DIRECTORY + dwDIRECTORY--) -> VirtualAddress, g_pStTLS -> m_fpFileBuffer);
	}
	while(dwTempNumber);

	// ���¸�dwTempNumber��ֵ
	dwTempNumber = 0x2F;

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	do
	{
		// �ҵ����ݲ�����ת��Ϊ�ַ�������
		sprintf(szDATA, "%08X", dwDATA[dwTempNumber]);
		SendMessage(GetDlgItem(hwndDlg, ElementalArrays[dwTempNumber]), WM_SETTEXT, 0, (LPARAM)TEXT(szDATA));
	}
	while(dwTempNumber--);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDirectoryOfPEData64(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS)
{
	/*
		��һ������64λPE�ļ�������Ŀ¼
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS64 pIMAGE_NT_HEADERS64 = (IMAGE_NT_HEADERS64*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS64 + sizeof(pIMAGE_NT_HEADERS64 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER64 pIMAGE_OPTIONAL_HEADER64 = (IMAGE_OPTIONAL_HEADER64*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER64 -> DataDirectory);

	// ���ڴ洢����Edit�ı��
	DWORD ElementalArrays[0x30] = 
	{
		IDC_EDIT_D_Export_FOA,
		IDC_EDIT_D_Export_RVA,
		IDC_EDIT_D_Export_SIZE,
		IDC_EDIT_D_Import_FOA,
		IDC_EDIT_D_Import_RVA,
		IDC_EDIT_D_Import_SIZE,
		IDC_EDIT_D_Resource_FOA,
		IDC_EDIT_D_Resource_RVA,
		IDC_EDIT_D_Resource_SIZE,
		IDC_EDIT_D_Exception_FOA,
		IDC_EDIT_D_Exception_RVA,
		IDC_EDIT_D_Exception_SIZE,
		IDC_EDIT_D_Security_FOA,
		IDC_EDIT_D_Security_RVA,
		IDC_EDIT_D_Security_SIZE,
		IDC_EDIT_D_BaseReloc_FOA,
		IDC_EDIT_D_BaseReloc_RVA,
		IDC_EDIT_D_BaseReloc_SIZE,
		IDC_EDIT_D_Debug_FOA,
		IDC_EDIT_D_Debug_RVA,
		IDC_EDIT_D_Debug_SIZE,
		IDC_EDIT_D_CopyRight_FOA,
		IDC_EDIT_D_CopyRight_RVA,
		IDC_EDIT_D_CopyRight_SIZE,
		IDC_EDIT_D_GlobalPtr_FOA,
		IDC_EDIT_D_GlobalPtr_RVA,
		IDC_EDIT_D_GlobalPtr_SIZE,
		IDC_EDIT_D_TLS_FOA,
		IDC_EDIT_D_TLS_RVA,
		IDC_EDIT_D_TLS_SIZE,
		IDC_EDIT_D_LoadConfig_FOA,
		IDC_EDIT_D_LoadConfig_RVA,
		IDC_EDIT_D_LoadConfig_SIZE,
		IDC_EDIT_D_BoundImport_FOA,
		IDC_EDIT_D_BoundImport_RVA,
		IDC_EDIT_D_BoundImport_SIZE,
		IDC_EDIT_D_IAT_FOA,
		IDC_EDIT_D_IAT_RVA,
		IDC_EDIT_D_IAT_SIZE,
		IDC_EDIT_D_DelayImport_FOA,
		IDC_EDIT_D_DelayImport_RVA,
		IDC_EDIT_D_DelayImport_SIZE,
		IDC_EDIT_D_ComDescriptor_FOA,
		IDC_EDIT_D_ComDescriptor_RVA,
		IDC_EDIT_D_ComDescriptor_SIZE,
		IDC_EDIT_D_Retain_FOA,
		IDC_EDIT_D_Retain_RVA,
		IDC_EDIT_D_Retain_SIZE,
	};

	// ���ڴ洢��ӦElementalArrays����Ľ���������ֵ
	DWORD dwDATA[0x30] = {0};

	// ��Ҫѭ���Ĵ���+1
	DWORD dwTempNumber = 0x30;

	// ����Ŀ¼�±�
	DWORD dwDIRECTORY = 0xF;

	do
	{
		// ѭ���洢��Ҫ��ֵ
		dwTempNumber--;
		dwDATA[dwTempNumber--] = (pIMAGE_DATA_DIRECTORY + dwDIRECTORY) -> Size;
		dwDATA[dwTempNumber--] = (pIMAGE_DATA_DIRECTORY + dwDIRECTORY) -> VirtualAddress;
		dwDATA[dwTempNumber] = ChangeRvaToFoa64((pIMAGE_DATA_DIRECTORY + dwDIRECTORY--) -> VirtualAddress, g_pStTLS -> m_fpFileBuffer);
	}
	while(dwTempNumber);

	// ���¸�dwTempNumber��ֵ
	dwTempNumber = 0x2F;

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	do
	{
		// �ҵ����ݲ�����ת��Ϊ�ַ�������
		sprintf(szDATA, "%08X", dwDATA[dwTempNumber]);
		SendMessage(GetDlgItem(hwndDlg, ElementalArrays[dwTempNumber]), WM_SETTEXT, 0, (LPARAM)TEXT(szDATA));
	}
	while(dwTempNumber--);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisSectionOfPEData32(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS)
{
	/*
		��һ������32λPE�ļ�������
		�����ڱ���Ϣ��ʾ��IDD_DIALOG_Section��ListView��
	*/
	
	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pIMAGE_OPTIONAL_HEADER32 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);
	
	// �����ж�ѭ������
	DWORD dwTempNumber = 0;

	// ���ڴ洢ת����õ����ַ���
	TCHAR szNumber[0x10] = {0};
	TCHAR szName[0x10] = {0};
	TCHAR szVirtualSize[0x10] = {0};
	TCHAR szVirtualAddress[0x10] = {0};
	TCHAR szSizeOfRawData[0x10] = {0};
	TCHAR szPointerToRawData[0x10] = {0};
	TCHAR szCharacteristics[0x10] = {0};

	do
	{
		// ���ڱ����ƿ���������Ŀռ��Է�ֹ���Ƹպ�8���ֽڵ����
		memcpy(szName, &pIMAGE_SECTION_HEADER -> Name, 0x8);

		// �ҵ����ݲ�����ת��Ϊ�ַ�������
		sprintf(szNumber, "%8d", dwTempNumber);
		sprintf(szVirtualSize, "%08X", pIMAGE_SECTION_HEADER -> Misc.VirtualSize);
		sprintf(szVirtualAddress, "%08X", pIMAGE_SECTION_HEADER -> VirtualAddress);
		sprintf(szSizeOfRawData, "%08X", pIMAGE_SECTION_HEADER -> SizeOfRawData);
		sprintf(szPointerToRawData, "%08X", pIMAGE_SECTION_HEADER -> PointerToRawData);
		sprintf(szCharacteristics, "%08X", pIMAGE_SECTION_HEADER -> Characteristics);
		
		// ����Ҫ��ʾ���ַ������뵽IDD_DIALOG_Section��ListView��
		SetListViewTextOfSection(
			GetDlgItem(hwndDlg, IDC_LIST_Section), 
			dwTempNumber++, 
			szNumber, 
			szName, 
			szVirtualSize, 
			szVirtualAddress, 
			szSizeOfRawData, 
			szPointerToRawData, 
			szCharacteristics
			);

		// ��ת����һ���ڱ�
		pIMAGE_SECTION_HEADER++;
	}
	while(dwTempNumber < pIMAGE_FILE_HEADER -> NumberOfSections);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisSectionOfPEData64(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS)
{
	/*
		��һ������64λPE�ļ�������
		�����ڱ���Ϣ��ʾ��IDD_DIALOG_Section��ListView��
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS64 pIMAGE_NT_HEADERS64 = (IMAGE_NT_HEADERS64*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS64 + sizeof(pIMAGE_NT_HEADERS64 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER64 pIMAGE_OPTIONAL_HEADER64 = (IMAGE_OPTIONAL_HEADER64*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pIMAGE_OPTIONAL_HEADER64 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// �����ж�ѭ������
	DWORD dwTempNumber = 0;

	// ���ڴ洢ת����õ����ַ���
	TCHAR szNumber[0x10] = {0};
	TCHAR szName[0x10] = {0};
	TCHAR szVirtualSize[0x10] = {0};
	TCHAR szVirtualAddress[0x10] = {0};
	TCHAR szSizeOfRawData[0x10] = {0};
	TCHAR szPointerToRawData[0x10] = {0};
	TCHAR szCharacteristics[0x10] = {0};

	do
	{
		// ���ڱ����ƿ���������Ŀռ��Է�ֹ���Ƹպ�8���ֽڵ����
		memcpy(szName, &pIMAGE_SECTION_HEADER -> Name, 0x8);

		// �ҵ����ݲ�����ת��Ϊ�ַ�������
		sprintf(szNumber, "%8d", dwTempNumber);
		sprintf(szVirtualSize, "%08X", pIMAGE_SECTION_HEADER -> Misc.VirtualSize);
		sprintf(szVirtualAddress, "%08X", pIMAGE_SECTION_HEADER -> VirtualAddress);
		sprintf(szSizeOfRawData, "%08X", pIMAGE_SECTION_HEADER -> SizeOfRawData);
		sprintf(szPointerToRawData, "%08X", pIMAGE_SECTION_HEADER -> PointerToRawData);
		sprintf(szCharacteristics, "%08X", pIMAGE_SECTION_HEADER -> Characteristics);
		
		// ����Ҫ��ʾ���ַ������뵽IDD_DIALOG_Section��ListView��
		SetListViewTextOfSection(
			GetDlgItem(hwndDlg, IDC_LIST_Section), 
			dwTempNumber++, 
			szNumber, 
			szName, 
			szVirtualSize, 
			szVirtualAddress, 
			szSizeOfRawData, 
			szPointerToRawData, 
			szCharacteristics
			);

		// ��ת����һ���ڱ�
		pIMAGE_SECTION_HEADER++;
	}
	while(dwTempNumber < pIMAGE_FILE_HEADER -> NumberOfSections);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI DsEditHandle(IN PTLSDirectory g_pStTLS, IN HWND hwndDlg, IN DWORD dwCallBackFunction, IN DWORD dwFlag)
{
	/*
		���ݵ���Ĳ�ͬ��ť���Ĳ���ͬ��־λ
		ͳһ������DialogProcDS_ALL�ص�����������
		��˿ɼ�����Դ�ļ���ʹ��
	*/

	// ��ʼ��DS��־λ
	CLICK_DS_INIT(g_pStTLS -> m_dwGlobalFlag);

	// ��ָ���ı�־λ,��1
	switch (dwFlag)
	{
	case 0:
		CLICK_DS_SELECT_EXPORT(g_pStTLS -> m_dwGlobalFlag);
		break;
	case 1:
		CLICK_DS_SELECT_IMPORT(g_pStTLS -> m_dwGlobalFlag);
		break;
	case 2:
		CLICK_DS_SELECT_RESOURCE(g_pStTLS -> m_dwGlobalFlag);
		break;
	case 3:
		CLICK_DS_SELECT_BASERELOC(g_pStTLS -> m_dwGlobalFlag);
		break;
	case 4:
		CLICK_DS_SELECT_BOUNDIMPORT(g_pStTLS -> m_dwGlobalFlag);
		break;
	case 5:
		CLICK_DS_SELECT_IAT(g_pStTLS -> m_dwGlobalFlag);
		break;
	}
	
	// ����DialogProcDS_ALL
	DialogBox(g_pStTLS -> m_hAppInstance, 
		MAKEINTRESOURCE(IDD_DIALOG_DS_ALL), 
		hwndDlg,
		(int (WINAPI*)(struct HWND__*, unsigned int, unsigned int, long))dwCallBackFunction);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsExportOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	/*
		����32λ��PE�ļ��ĵ���������������ʾ��IDC_EDIT_DS_ALL��
	*/
	
	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER32 -> DataDirectory);

	// �����ж�PE�ļ��Ƿ��е�����
	if (!pIMAGE_DATA_DIRECTORY -> VirtualAddress)
	{
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��PE�ļ�û�е�����");
		return RETURN_FAILURE;
	}

	// ���嵼����ṹ��ָ��
	PIMAGE_EXPORT_DIRECTORY pIMAGE_EXPORT_DIRECTORY = (IMAGE_EXPORT_DIRECTORY*)(ChangeRvaToFoa32(pIMAGE_DATA_DIRECTORY -> VirtualAddress, g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	
	// ����д��
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��������Ϣ:\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);

	// �ָ���
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"------------------------------------------------\r\n");

	// ���ڴ洢����
	PTCHAR ElementalArrays[0x8] =
	{
		"\r\nTimeDateStamp\r\t\t[ʱ���]\r\t\t\t",
		"\r\nName\r\t\t\t[ģ������]\r\t\t\t",
		"\r\nBase\r\t\t\t[����������ʼ���]\r\t\t",
		"\r\nNumberOfFunctions\r\t[������������]\r\t\t",
		"\r\nNumberOfNames\r\t\t[�����ֵ����ĺ�������]\r\t",
		"\r\nAddressOfFunctions\r\t[����������ַ��RVA]\r\t",
		"\r\nAddressOfNames\r\t\t[�����������Ʊ�RVA]\r\t",
		"\r\nAddressOfNameOrdinals\r\t[����������ű�RVA]\r\t",
	};

	// ���ڴ洢����
	DWORD dwDATA[0x8] =
	{
		pIMAGE_EXPORT_DIRECTORY -> TimeDateStamp,
		pIMAGE_EXPORT_DIRECTORY -> Name,
		pIMAGE_EXPORT_DIRECTORY -> Base,
		pIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions,
		pIMAGE_EXPORT_DIRECTORY -> NumberOfNames,
		pIMAGE_EXPORT_DIRECTORY -> AddressOfFunctions,
		pIMAGE_EXPORT_DIRECTORY -> AddressOfNames,
		pIMAGE_EXPORT_DIRECTORY -> AddressOfNameOrdinals,
	};

	// ��ʱ����
	DWORD dwTempNumber = 0;
	
	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	// ��д��ģ������
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"ģ������:\r\t");
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)(ChangeRvaToFoa32(pIMAGE_EXPORT_DIRECTORY -> Name, g_pStTLS -> m_fpFileBuffer)) + (DWORD)g_pStTLS -> m_fpFileBuffer);

	do
	{
		// ת��Ϊ�ַ������Ͳ�ѭ��д��
		sprintf(szDATA, "%08X", dwDATA[dwTempNumber]);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)ElementalArrays[dwTempNumber]);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	}
	while(dwTempNumber++ < 0x7);

	// �ָ���
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n------------------------------------------------\r\n");

	// �õ�����������ַ��/���Ʊ�/��ű��ʵ�����ڵ�ַ
	LPDWORD pExportFunctions = (LPDWORD)(ChangeRvaToFoa32(pIMAGE_EXPORT_DIRECTORY -> AddressOfFunctions, g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	LPDWORD pExportNames = (LPDWORD)(ChangeRvaToFoa32(pIMAGE_EXPORT_DIRECTORY -> AddressOfNames, g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	LPWORD pExportNameOrdinals = (LPWORD)(ChangeRvaToFoa32(pIMAGE_EXPORT_DIRECTORY -> AddressOfNameOrdinals, g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);

	// ���¸�dwTempNumber��ֵΪ0
	dwTempNumber = 0;

	// ���ڼ���
	DWORD dwNumberOfOrdinals = 0;

	// �е�������û�е�������
	if (!pIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions)
	{
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��PE�ļ�û���κε�������!");
		return RETURN_FAILURE;
	}

	// ������
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"[�����������]\r\t[������ַRVA]\r\t[��������]\r\n");

	// ��ӡ���������ṹ
	do
	{
		if (*(pExportFunctions + dwTempNumber))
		{
			// ���������ַ���е�ַ���ȳ�ʼ������������־λ
			EXPORT_FUNC_INIT(g_pStTLS -> m_dwGlobalFlag);
			
			// ��ʼ�����ʹ�ӡ
			do
			{
				// �ú�����ַ����±굽������ű���Ա�,����û������±�
				if (dwTempNumber == *(pExportNameOrdinals + dwNumberOfOrdinals))
				{
					// ����ҵ��˶�Ӧ��������ȸ���ȫ�ֱ�־λΪ�����ֵ���
					EXPORT_BY_NAME(g_pStTLS -> m_dwGlobalFlag);

					// �ȴ�ӡ��� ������ŵ�����ű����+base
					sprintf(szDATA, "%04X", *(pExportNameOrdinals + dwNumberOfOrdinals) + pIMAGE_EXPORT_DIRECTORY -> Base);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\t");

					// �ٴ�ӡ������RVA
					sprintf(szDATA, "%08X", *(pExportFunctions + dwTempNumber));
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");

					// ʹ������ű�����±굽���ֱ���ȥ�Ҷ�Ӧ�����Ƶĵ�ַ,�ٽ�����������ʾ��Edit��
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)(ChangeRvaToFoa32(*(pExportNames + dwNumberOfOrdinals), g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer));
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

					// ��dwNumberOfOrdinals��ֵ�����Ա��´�ʹ��
					dwNumberOfOrdinals = 0;

					// ����ҵ�����ֱ�������ڲ�ѭ��
					break;
				}
			}
			while(++dwNumberOfOrdinals < pIMAGE_EXPORT_DIRECTORY -> NumberOfNames);

			// ���ڲ�do-whileѭ��������,�����ж��Ƿ�����ű��ҵ��˶�Ӧ��ֵ(�Ƿ��������ֵ�����)
			if (!EXPORT_OF_NAME_COMPARE(g_pStTLS -> m_dwGlobalFlag))
			{
				// ���Ƚ�dwNumberOfOrdinals����
				dwNumberOfOrdinals = 0;

				// ����ŵ����򵼳���ŵ����±�+base
				sprintf(szDATA, "%04X", dwTempNumber + pIMAGE_EXPORT_DIRECTORY -> Base);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\t");

				// RVA
				sprintf(szDATA, "%08X", *(pExportFunctions + dwTempNumber));
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");

				// ����д��"-"
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"-");
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
			}
		} // End if
	}	
	while(++dwTempNumber < pIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsExportOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	/*
		����64λ��PE�ļ��ĵ���������������ʾ��IDC_EDIT_DS_ALL��
	*/
	
	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS64 pIMAGE_NT_HEADERS64 = (IMAGE_NT_HEADERS64*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS64 + sizeof(pIMAGE_NT_HEADERS64 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER64 pIMAGE_OPTIONAL_HEADER64 = (IMAGE_OPTIONAL_HEADER64*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER64 -> DataDirectory);

	// �����ж�PE�ļ��Ƿ��е�����
	if (!pIMAGE_DATA_DIRECTORY -> VirtualAddress)
	{
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��PE�ļ�û�е�����");
		return RETURN_FAILURE;
	}

	// ���嵼����ṹ��ָ��
	PIMAGE_EXPORT_DIRECTORY pIMAGE_EXPORT_DIRECTORY = (IMAGE_EXPORT_DIRECTORY*)(ChangeRvaToFoa64(pIMAGE_DATA_DIRECTORY -> VirtualAddress, g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	
	// ����д��
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��������Ϣ:\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);

	// �ָ���
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"------------------------------------------------\r\n");

	// ���ڴ洢����
	PTCHAR ElementalArrays[0x8] =
	{
		"\r\nTimeDateStamp\r\t\t[ʱ���]\r\t\t\t",
		"\r\nName\r\t\t\t[ģ������]\r\t\t\t",
		"\r\nBase\r\t\t\t[����������ʼ���]\r\t\t",
		"\r\nNumberOfFunctions\r\t[������������]\r\t\t",
		"\r\nNumberOfNames\r\t\t[�����ֵ����ĺ�������]\r\t",
		"\r\nAddressOfFunctions\r\t[����������ַ��RVA]\r\t",
		"\r\nAddressOfNames\r\t\t[�����������Ʊ�RVA]\r\t",
		"\r\nAddressOfNameOrdinals\r\t[����������ű�RVA]\r\t",
	};

	// ���ڴ洢����
	DWORD dwDATA[0x8] =
	{
		pIMAGE_EXPORT_DIRECTORY -> TimeDateStamp,
		pIMAGE_EXPORT_DIRECTORY -> Name,
		pIMAGE_EXPORT_DIRECTORY -> Base,
		pIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions,
		pIMAGE_EXPORT_DIRECTORY -> NumberOfNames,
		pIMAGE_EXPORT_DIRECTORY -> AddressOfFunctions,
		pIMAGE_EXPORT_DIRECTORY -> AddressOfNames,
		pIMAGE_EXPORT_DIRECTORY -> AddressOfNameOrdinals,
	};

	// ��ʱ����
	DWORD dwTempNumber = 0;
	
	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	// ��д��ģ������
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"ģ������:\r\t");
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)(ChangeRvaToFoa64(pIMAGE_EXPORT_DIRECTORY -> Name, g_pStTLS -> m_fpFileBuffer)) + (DWORD)g_pStTLS -> m_fpFileBuffer);

	do
	{
		// ת��Ϊ�ַ������Ͳ�ѭ��д��
		sprintf(szDATA, "%08X", dwDATA[dwTempNumber]);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)ElementalArrays[dwTempNumber]);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	}
	while(dwTempNumber++ < 0x7);

	// �ָ���
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n------------------------------------------------\r\n");

	// �õ�����������ַ��/���Ʊ�/��ű��ʵ�����ڵ�ַ
	LPDWORD pExportFunctions = (LPDWORD)(ChangeRvaToFoa64(pIMAGE_EXPORT_DIRECTORY -> AddressOfFunctions, g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	LPDWORD pExportNames = (LPDWORD)(ChangeRvaToFoa64(pIMAGE_EXPORT_DIRECTORY -> AddressOfNames, g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	LPWORD pExportNameOrdinals = (LPWORD)(ChangeRvaToFoa64(pIMAGE_EXPORT_DIRECTORY -> AddressOfNameOrdinals, g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);

	// ���¸�dwTempNumber��ֵΪ0
	dwTempNumber = 0;

	// ���ڼ���
	DWORD dwNumberOfOrdinals = 0;

	// �е�������û�е�������
	if (!pIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions)
	{
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��PE�ļ�û���κε�������!");
		return RETURN_FAILURE;
	}

	// ������
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"[�����������]\r\t[������ַRVA]\r\t[��������]\r\n");

	// ��ӡ���������ṹ
	do
	{
		if (*(pExportFunctions + dwTempNumber))
		{
			// ���������ַ���е�ַ���ȳ�ʼ������������־λ
			EXPORT_FUNC_INIT(g_pStTLS -> m_dwGlobalFlag);
			
			// ��ʼ�����ʹ�ӡ
			do
			{
				// �ú�����ַ����±굽������ű���Ա�,����û������±�
				if (dwTempNumber == *(pExportNameOrdinals + dwNumberOfOrdinals))
				{
					// ����ҵ��˶�Ӧ��������ȸ���ȫ�ֱ�־λΪ�����ֵ���
					EXPORT_BY_NAME(g_pStTLS -> m_dwGlobalFlag);

					// �ȴ�ӡ��� ������ŵ�����ű����+base
					sprintf(szDATA, "%04X", *(pExportNameOrdinals + dwNumberOfOrdinals) + pIMAGE_EXPORT_DIRECTORY -> Base);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\t");

					// �ٴ�ӡ������RVA
					sprintf(szDATA, "%08X", *(pExportFunctions + dwTempNumber));
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");

					// ʹ������ű�����±굽���ֱ���ȥ�Ҷ�Ӧ�����Ƶĵ�ַ,�ٽ�����������ʾ��Edit��
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)(ChangeRvaToFoa64(*(pExportNames + dwNumberOfOrdinals), g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer));
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

					// ��dwNumberOfOrdinals��ֵ�����Ա��´�ʹ��
					dwNumberOfOrdinals = 0;

					// ����ҵ�����ֱ�������ڲ�ѭ��
					break;
				}
			}
			while(++dwNumberOfOrdinals < pIMAGE_EXPORT_DIRECTORY -> NumberOfNames);

			// ���ڲ�do-whileѭ��������,�����ж��Ƿ�����ű��ҵ��˶�Ӧ��ֵ(�Ƿ��������ֵ�����)
			if (!EXPORT_OF_NAME_COMPARE(g_pStTLS -> m_dwGlobalFlag))
			{
				// ���Ƚ�dwNumberOfOrdinals����
				dwNumberOfOrdinals = 0;

				// ����ŵ����򵼳���ŵ����±�+base
				sprintf(szDATA, "%04X", dwTempNumber + pIMAGE_EXPORT_DIRECTORY -> Base);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\t");

				// RVA
				sprintf(szDATA, "%08X", *(pExportFunctions + dwTempNumber));
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");

				// ����д��"-"
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"-");
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
			}
		} // End if
	}	
	while(++dwTempNumber < pIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions);

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsImportOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	/*
		����32λ��PE�ļ��ĵ��������������ʾ��IDC_EDIT_DS_ALL��
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER32 -> DataDirectory);

	// �����ж��Ƿ��е����
	if (!(pIMAGE_DATA_DIRECTORY + 1) -> VirtualAddress)
	{
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��PE�ļ�û�е����");
		return RETURN_FAILURE;
	}
	
	// ���嵼���ṹ��ָ��
	PIMAGE_IMPORT_DESCRIPTOR pIMAGE_IMPORT_DESCRIPTOR = (IMAGE_IMPORT_DESCRIPTOR*)(ChangeRvaToFoa32((pIMAGE_DATA_DIRECTORY + 1) -> VirtualAddress, \
		g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	
	// ��������ṹ��ָ����ֵ��ʼ��ӡ
	if (!pIMAGE_IMPORT_DESCRIPTOR -> Name)
	{
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��PE�ļ�û���κε��뺯��!");
		return RETURN_FAILURE;
	}

	// ����д��
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"�������Ϣ(��ǰ�汾���ݹ��ཫ��ʾ��ȫ):\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	do
	{
		// �ж��Ƿ�������ṹ���� ����������
		if (!(pIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk | pIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp |\
			pIMAGE_IMPORT_DESCRIPTOR -> ForwarderChain | pIMAGE_IMPORT_DESCRIPTOR -> Name | \
			pIMAGE_IMPORT_DESCRIPTOR -> FirstThunk))
			break;

		// ������Ҫ�����ȫ���� DLL ѭ����ӡ _IMAGE_IMPORT_DESCRIPTOR �������Ϣ
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"------------------------------------------------ \r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"OriginalFirstThunk:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");
		sprintf(szDATA, "%08X", pIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"TimeDateStamp:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");
		sprintf(szDATA, "%08X", pIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"ForwarderChain:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");
		sprintf(szDATA, "%08X", pIMAGE_IMPORT_DESCRIPTOR -> ForwarderChain);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"Name:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\r\t");
		sprintf(szDATA, "%08X", pIMAGE_IMPORT_DESCRIPTOR -> Name);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"FirstThunk:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");
		sprintf(szDATA, "%08X", pIMAGE_IMPORT_DESCRIPTOR -> FirstThunk);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

		// ��ӡģ������
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"ģ������:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\r\t");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)(LPTSTR)(ChangeRvaToFoa32(pIMAGE_IMPORT_DESCRIPTOR -> Name, \
			g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer));
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
		// ��ӡ���ṹ

		// ��ӡ INT ��
		// �ҵ� PIMAGE_THUNK_DATA32 �� FOA (4�ֽ�)
		DWORD pINT_PIMAGE_THUNK_DATA32 = (DWORD)(ChangeRvaToFoa32(pIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk, \
			g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
		while(*(LPDWORD)pINT_PIMAGE_THUNK_DATA32 != 0)
		{
			// ֵΪ0��ѭ������
			
			// �ж����λ�Ƿ�Ϊ1
			if (*(LPDWORD)pINT_PIMAGE_THUNK_DATA32 & IMAGE_ORDINAL_FLAG32)
			{
				// ���Ϊ1 ��ô��ȥ���λ��ֵ ���Ǻ����ĵ������
				DWORD Original = *(LPDWORD)pINT_PIMAGE_THUNK_DATA32 & ~IMAGE_ORDINAL_FLAG32;
				sprintf(szDATA, "%08X", Original);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"INT[���]");
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
			}
			// ������ǣ���ô���ֵ��һ��RVA ָ�� IMAGE_IMPORT_BY_NAME 
			else
			{	// ��ӡ INT ��
				PIMAGE_IMPORT_BY_NAME pINT_PIMAGE_IMPORT_BY_NAME  = (IMAGE_IMPORT_BY_NAME*)(ChangeRvaToFoa32(*(LPDWORD)pINT_PIMAGE_THUNK_DATA32, \
					g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"INT[����]");
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)pINT_PIMAGE_IMPORT_BY_NAME -> Name);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
			}

			// �ҵ���һ����ַ
			pINT_PIMAGE_THUNK_DATA32 += 4;
		}

		// ��ӡ IAT ��
		// �ҵ� PIMAGE_THUNK_DATA32 �� FOA (4�ֽ�)
		DWORD pIMAGE_THUNK_DATA32 = (DWORD)(ChangeRvaToFoa32(pIMAGE_IMPORT_DESCRIPTOR -> FirstThunk, \
			g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
		
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n\n");

		// ���� IAT ��ṹ��ָ�� FirstThunk ָ�� IAT ��
		while(*(LPDWORD)pIMAGE_THUNK_DATA32 != 0)
		{
			// ֵΪ0��ѭ������

			// �жϴ�DLL�Ƿ񱻰� �������ֱ�Ӵ�ӡ������ַ
			if (pIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp)
			{
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��ַ[Bound]: ");
				sprintf(szDATA, "%08X", *(LPDWORD)pIMAGE_THUNK_DATA32);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
				
				// �ҵ���һ����ַ
				pIMAGE_THUNK_DATA32 += 4;
				continue;
			}

			// �ж����λ�Ƿ�Ϊ1
			if (*(LPDWORD)pIMAGE_THUNK_DATA32 & IMAGE_ORDINAL_FLAG32)
			{
				// ���Ϊ1 ��ô��ȥ���λ��ֵ ���Ǻ����ĵ������
				DWORD Original = *(LPDWORD)pIMAGE_THUNK_DATA32 & ~IMAGE_ORDINAL_FLAG32;

				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"IAT[���]: ");
				sprintf(szDATA, "%08X", Original);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
			}

			// ������ǣ���ô���ֵ��һ��RVA ָ�� IMAGE_IMPORT_BY_NAME 
			else
			{
				PIMAGE_IMPORT_BY_NAME pIMAGE_IMPORT_BY_NAME  = (IMAGE_IMPORT_BY_NAME*)(ChangeRvaToFoa32(*(LPDWORD)pIMAGE_THUNK_DATA32, \
					g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"IAT[����]: ");
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)pIMAGE_IMPORT_BY_NAME -> Name);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
			}

			// �ҵ���һ����ַ
			pIMAGE_THUNK_DATA32 += 4;
		}

		// �ҵ���һ��ģ��
		pIMAGE_IMPORT_DESCRIPTOR++;
	}
	while(TRUE);

	return RETURN_SUCCESS; 
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsImportOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	/*
		����64λ��PE�ļ��ĵ��������������ʾ��IDC_EDIT_DS_ALL��
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS64 pIMAGE_NT_HEADERS64 = (IMAGE_NT_HEADERS64*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS64 + sizeof(pIMAGE_NT_HEADERS64 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER64 pIMAGE_OPTIONAL_HEADER64 = (IMAGE_OPTIONAL_HEADER64*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER64 -> DataDirectory);

	// �����ж��Ƿ��е����
	if (!(pIMAGE_DATA_DIRECTORY + 1) -> VirtualAddress)
	{
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��PE�ļ�û�е����");
		return RETURN_FAILURE;
	}
	
	// ���嵼���ṹ��ָ��
	PIMAGE_IMPORT_DESCRIPTOR pIMAGE_IMPORT_DESCRIPTOR = (IMAGE_IMPORT_DESCRIPTOR*)(ChangeRvaToFoa64((pIMAGE_DATA_DIRECTORY + 1) -> VirtualAddress, \
		g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	
	// ��������ṹ��ָ����ֵ��ʼ��ӡ
	if (!pIMAGE_IMPORT_DESCRIPTOR -> Name)
	{
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��PE�ļ�û���κε��뺯��!");
		return RETURN_FAILURE;
	}

	// ����д��
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"�������Ϣ(��ǰ�汾���ݹ��ཫ��ʾ��ȫ):\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	do
	{
		// �ж��Ƿ�������ṹ���� ����������
		if (!(pIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk | pIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp |\
			pIMAGE_IMPORT_DESCRIPTOR -> ForwarderChain | pIMAGE_IMPORT_DESCRIPTOR -> Name | \
			pIMAGE_IMPORT_DESCRIPTOR -> FirstThunk))
			break;

		// ������Ҫ�����ȫ���� DLL ѭ����ӡ _IMAGE_IMPORT_DESCRIPTOR �������Ϣ
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"------------------------------------------------ \r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"OriginalFirstThunk:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");
		sprintf(szDATA, "%08X", pIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"TimeDateStamp:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");
		sprintf(szDATA, "%08X", pIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"ForwarderChain:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");
		sprintf(szDATA, "%08X", pIMAGE_IMPORT_DESCRIPTOR -> ForwarderChain);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"Name:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\r\t");
		sprintf(szDATA, "%08X", pIMAGE_IMPORT_DESCRIPTOR -> Name);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"FirstThunk:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");
		sprintf(szDATA, "%08X", pIMAGE_IMPORT_DESCRIPTOR -> FirstThunk);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

		// ��ӡģ������
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"ģ������:");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\r\t");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)(LPTSTR)(ChangeRvaToFoa64(pIMAGE_IMPORT_DESCRIPTOR -> Name, \
			g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer));
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n"); // continue...
		// ��ӡ���ṹ

		// ��ӡ INT ��
		// �ҵ� PIMAGE_THUNK_DATA64 �� FOA (8�ֽ�)
		ULONGLONG pINT_PIMAGE_THUNK_DATA64 = (ULONGLONG)(ChangeRvaToFoa64(pIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk, \
			g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
		while(*(PULONGLONG)pINT_PIMAGE_THUNK_DATA64 != 0)
		{
			// ֵΪ0��ѭ������
			
			// �ж����λ�Ƿ�Ϊ1
			if (*(PULONGLONG)pINT_PIMAGE_THUNK_DATA64 & IMAGE_ORDINAL_FLAG64)
			{
				// ���Ϊ1 ��ô��ȥ���λ��ֵ ���Ǻ����ĵ������
				ULONGLONG Original = *(PULONGLONG)pINT_PIMAGE_THUNK_DATA64 & ~IMAGE_ORDINAL_FLAG64;
				sprintf(szDATA, "%08X", Original);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"INT[���]");
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
			}
			// ������ǣ���ô���ֵ��һ��RVA ָ�� IMAGE_IMPORT_BY_NAME 
			else
			{	// ��ӡ INT ��
				PIMAGE_IMPORT_BY_NAME pINT_PIMAGE_IMPORT_BY_NAME  = (IMAGE_IMPORT_BY_NAME*)(ChangeRvaToFoa64(*(LPDWORD)pINT_PIMAGE_THUNK_DATA64, \
					g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"INT[����]");
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)pINT_PIMAGE_IMPORT_BY_NAME -> Name);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
			}

			// �ҵ���һ����ַ
			pINT_PIMAGE_THUNK_DATA64 += 8;
		}

		// ��ӡ IAT ��
		// �ҵ� PIMAGE_THUNK_DATA64 �� FOA (4�ֽ�)
		ULONGLONG pIMAGE_THUNK_DATA64 = (ULONGLONG)(ChangeRvaToFoa64(pIMAGE_IMPORT_DESCRIPTOR -> FirstThunk, \
			g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
		
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n\n");

		// ���� IAT ��ṹ��ָ�� FirstThunk ָ�� IAT ��
		while(*(PULONGLONG)pIMAGE_THUNK_DATA64 != 0)
		{
			// ֵΪ0��ѭ������

			// �жϴ�DLL�Ƿ񱻰� �������ֱ�Ӵ�ӡ������ַ
			if (pIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp)
			{
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��ַ[Bound]: ");
				sprintf(szDATA, "%08X", *(LPDWORD)pIMAGE_THUNK_DATA64);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
				
				// �ҵ���һ����ַ
				pIMAGE_THUNK_DATA64 += 8;
				continue;
			}

			// �ж����λ�Ƿ�Ϊ1
			if (*(PULONGLONG)pIMAGE_THUNK_DATA64 & IMAGE_ORDINAL_FLAG64)
			{
				// ���Ϊ1 ��ô��ȥ���λ��ֵ ���Ǻ����ĵ������
				ULONGLONG Original = *(PULONGLONG)pIMAGE_THUNK_DATA64 & ~IMAGE_ORDINAL_FLAG64;

				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"IAT[���]: ");
				sprintf(szDATA, "%08X", Original);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
			}

			// ������ǣ���ô���ֵ��һ��RVA ָ�� IMAGE_IMPORT_BY_NAME 
			else
			{
				PIMAGE_IMPORT_BY_NAME pIMAGE_IMPORT_BY_NAME  = (IMAGE_IMPORT_BY_NAME*)(ChangeRvaToFoa64(*(LPDWORD)pIMAGE_THUNK_DATA64, \
					g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"IAT[����]: ");
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)pIMAGE_IMPORT_BY_NAME -> Name);
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
			}

			// �ҵ���һ����ַ
			pIMAGE_THUNK_DATA64 += 8;
		}

		// �ҵ���һ��ģ��
		pIMAGE_IMPORT_DESCRIPTOR++;
	}
	while(TRUE);

	return RETURN_SUCCESS; 
}


//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsResourceOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	/*
		����32λ��PE�ļ�����Դ������������ʾ��IDC_EDIT_DS_ALL��
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER32 -> DataDirectory);

	// �����ж��Ƿ�����Դ��
	if (!(pIMAGE_DATA_DIRECTORY + 2) -> VirtualAddress)
	{
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��PE�ļ�û����Դ��");
		return RETURN_FAILURE;
	}

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	// ������Դ��ṹ��ͷ��ָ��
	PIMAGE_RESOURCE_DIRECTORY pIMAGE_RESOURCE_DIRECTORY = (IMAGE_RESOURCE_DIRECTORY*)(ChangeRvaToFoa32((pIMAGE_DATA_DIRECTORY + 2) -> VirtualAddress, \
		g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);

	// ����д��
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��Դ����Ϣ(��ǰ�汾���ݹ��ཫ��ʾ��ȫ):\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);

	// �ҵ��ж��ٸ���ͬ����Դ����
	DWORD dwNumberOfTypes = pIMAGE_RESOURCE_DIRECTORY -> NumberOfIdEntries + pIMAGE_RESOURCE_DIRECTORY -> NumberOfNamedEntries;

	// ������Դ����ָ��
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pIMAGE_RESOURCE_DIRECTORY_ENTRY = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pIMAGE_RESOURCE_DIRECTORY + 1);
	do
	{ 
		// �����ж����ֲ�ͬ����Դ����
		if (!pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameIsString)
		{
			// �����λΪ0 ���4���ֽڵĺ�31λ���� ��Դ���͵�ID
			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"------------------------------------------------ \r\n��Դ����(ID):");
			sprintf(szDATA, "%08X", pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameOffset);
			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");
			switch(pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameOffset)
			{

			case RT_CURSOR:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(���)\r\n");
					break;
				}
			case RT_BITMAP:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(λͼ)\r\n");
					break;
				}
			case RT_ICON:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(ͼ��)\r\n");
					break;
				}
			case RT_MENU:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�˵�)\r\n");
					break;
				}
			case RT_DIALOG:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�Ի���)\r\n");
					break;
				}
			case RT_STRING:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�ַ�����)\r\n");
					break;
				}
			case RT_FONTDIR:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(����Ŀ¼)\r\n");
					break;
				}
			case RT_FONT:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(����)\r\n");
					break;
				}
			case RT_ACCELERATOR:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��������)\r\n");
					break;
				}
			case RT_RCDATA:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�Զ�����Դ)\r\n");
					break;
				}
			case RT_MESSAGETABLE:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��Ϣ��)\r\n");
					break;
				}
			case RT_GROUP_CURSOR:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(ͼ����)\r\n");
					break;
				}
			case RT_GROUP_ICON:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�����)\r\n");
					break;
				}
			case RT_DLGINCLUDE:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��ȡ��Դ)\r\n");
					break;
				}
			case RT_VERSION:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�汾��Ϣ)\r\n");
					break;
				}
			case RT_PLUGPLAY:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(���弴����Դ)\r\n");
					break;
				}
			case RT_VXD:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(VXD)\r\n");
					break;
				}
			case RT_ANICURSOR:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��̬���)\r\n");
					break;
				}
			case RT_ANIICON:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��̬ͼ��)\r\n");
					break;
				}
			case RT_HTML:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(HTML�ĵ�)\r\n");
					break;
				}
			default:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(δ֪��Դ����)\r\n");
				}
			};
		}
		else
		{
			// �����λΪ1 ��ָ�� _IMAGE_RESOURCE_DIR_STRING_U �ṹ ��Դ���;����Զ���� ��һ���ַ���
			PIMAGE_RESOURCE_DIR_STRING_U pIMAGE_RESOURCE_DIR_STRING_U = (IMAGE_RESOURCE_DIR_STRING_U*)(pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameOffset + (DWORD)pIMAGE_RESOURCE_DIRECTORY);

			// ��Դ���͵��ַ�������
			DWORD IMAGE_RESOURCE_DIR_STRING_U_Length = pIMAGE_RESOURCE_DIR_STRING_U -> Length;

			// ��Դ���͵���ʼλ��
			PTCHAR StringOfResource = (PTCHAR)(&pIMAGE_RESOURCE_DIR_STRING_U -> NameString);

			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��Դ����(����): ");
			do
			{
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)StringOfResource);
				StringOfResource += 2;
			}
			while(--IMAGE_RESOURCE_DIR_STRING_U_Length);
			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");
		}
		
		// ��ʼ������һ��(���)
		if (!pIMAGE_RESOURCE_DIRECTORY_ENTRY -> DataIsDirectory)
		{
			// �����λ��0
			// ����һ������0
		}
		else
		{
			// �����λ��1 �ҵ���һ��Ŀ¼�ڵ����ʼλ�� (��ŵ���ʼ��ַ)
			PIMAGE_RESOURCE_DIRECTORY pIMAGE_RESOURCE_DIRECTORY_Digit = (IMAGE_RESOURCE_DIRECTORY*)((DWORD)pIMAGE_RESOURCE_DIRECTORY + pIMAGE_RESOURCE_DIRECTORY_ENTRY -> OffsetToDirectory);
			
			// �������
			DWORD dwNumberOfDigit = pIMAGE_RESOURCE_DIRECTORY_Digit -> NumberOfIdEntries + pIMAGE_RESOURCE_DIRECTORY_Digit -> NumberOfNamedEntries;

			// �ҵ��ڶ������Դ�������
			PIMAGE_RESOURCE_DIRECTORY_ENTRY pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pIMAGE_RESOURCE_DIRECTORY_Digit + 1);
			do
			{
				if (!pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> NameIsString)
				{
					// �����λΪ0 ���4���ֽڵĺ�31λ���� ��Դ���
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��Դ���:");
					sprintf(szDATA, "%08X", pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> NameOffset);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");
				}	
				else
				{
					// �����λΪ1 ��ָ�� _IMAGE_RESOURCE_DIR_STRING_U �ṹ ��Դ��ž����Զ���� ��һ���ַ���
					PIMAGE_RESOURCE_DIR_STRING_U pIMAGE_RESOURCE_DIR_STRING_U = (IMAGE_RESOURCE_DIR_STRING_U*)(pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> NameOffset + (DWORD)pIMAGE_RESOURCE_DIRECTORY);

					// ��Դ���͵��ַ�������
					DWORD IMAGE_RESOURCE_DIR_STRING_U_Length = pIMAGE_RESOURCE_DIR_STRING_U -> Length;

					// ��Դ���͵���ʼλ��
					PTCHAR StringOfResource = (PTCHAR)(&pIMAGE_RESOURCE_DIR_STRING_U -> NameString);

					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��Դ���(����): ");
					do
					{
						SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)StringOfResource);
						StringOfResource += 2;
					}
					while(--IMAGE_RESOURCE_DIR_STRING_U_Length);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");
				}

				// �ҵ�����ҳ
				PIMAGE_RESOURCE_DIRECTORY pIMAGE_RESOURCE_DIRECTORY_CodePage = (IMAGE_RESOURCE_DIRECTORY*)((DWORD)pIMAGE_RESOURCE_DIRECTORY + pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> OffsetToDirectory);

				// ����ҳ����
				DWORD dwNumberOfCodePage = pIMAGE_RESOURCE_DIRECTORY_CodePage -> NumberOfIdEntries + pIMAGE_RESOURCE_DIRECTORY_CodePage -> NumberOfNamedEntries;
				// �ҵ�������Ĵ���ҳ����
				PIMAGE_RESOURCE_DIRECTORY_ENTRY pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pIMAGE_RESOURCE_DIRECTORY_CodePage + 1);
				do
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"����ҳ:");
					sprintf(szDATA, "%08X", pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage -> NameOffset);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					switch (pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage -> NameOffset)
					{
					case 1033:
						{
							SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(Ӣ��)\r\n");
							break;
						}
					case 2052:
						{
							SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(����)\r\n");
							break;
						}
					default:
						{
							SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��������)\r\n");
						}
					};
					// �ҵ��ڵ�
					PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)((DWORD)pIMAGE_RESOURCE_DIRECTORY + pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage -> OffsetToDirectory);
					
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"Rva: ");
					sprintf(szDATA, "%08X", pIMAGE_DATA_DIRECTORY -> VirtualAddress);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"OffSet: ");
					sprintf(szDATA, "%08X", ChangeRvaToFoa32(pIMAGE_DATA_DIRECTORY -> VirtualAddress, g_pStTLS -> m_fpFileBuffer));
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"Size: ");
					sprintf(szDATA, "%08X", pIMAGE_DATA_DIRECTORY -> Size);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n\r\n");
					
					pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage++;
				}
				while(--dwNumberOfCodePage);

				// �ҵ���һ����Դ��ŵ���ʼλ��
				pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element++;
			}
			while(--dwNumberOfDigit);
		}
		// �ҵ���һ����Դ���͵���ʼλ��
		pIMAGE_RESOURCE_DIRECTORY_ENTRY++;
	}
	while(--dwNumberOfTypes);

	return RETURN_SUCCESS; 
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsResourceOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	/*
		����64λ��PE�ļ�����Դ������������ʾ��IDC_EDIT_DS_ALL��
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS64 pIMAGE_NT_HEADERS64 = (IMAGE_NT_HEADERS64*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS64 + sizeof(pIMAGE_NT_HEADERS64 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER64 pIMAGE_OPTIONAL_HEADER64 = (IMAGE_OPTIONAL_HEADER64*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER64 -> DataDirectory);

	// �����ж��Ƿ�����Դ��
	if (!(pIMAGE_DATA_DIRECTORY + 2) -> VirtualAddress)
	{
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��PE�ļ�û����Դ��");
		return RETURN_FAILURE;
	}

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	// ������Դ��ṹ��ͷ��ָ��
	PIMAGE_RESOURCE_DIRECTORY pIMAGE_RESOURCE_DIRECTORY = (IMAGE_RESOURCE_DIRECTORY*)(ChangeRvaToFoa32((pIMAGE_DATA_DIRECTORY + 2) -> VirtualAddress, \
		g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);

	// ����д��
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��Դ����Ϣ(��ǰ�汾���ݹ��ཫ��ʾ��ȫ):\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);

	// �ҵ��ж��ٸ���ͬ����Դ����
	DWORD dwNumberOfTypes = pIMAGE_RESOURCE_DIRECTORY -> NumberOfIdEntries + pIMAGE_RESOURCE_DIRECTORY -> NumberOfNamedEntries;

	// ������Դ����ָ��
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pIMAGE_RESOURCE_DIRECTORY_ENTRY = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pIMAGE_RESOURCE_DIRECTORY + 1);
	do
	{ 
		// �����ж����ֲ�ͬ����Դ����
		if (!pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameIsString)
		{
			// �����λΪ0 ���4���ֽڵĺ�31λ���� ��Դ���͵�ID
			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"------------------------------------------------ \r\n��Դ����(ID):");
			sprintf(szDATA, "%08X", pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameOffset);
			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t");
			switch(pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameOffset)
			{

			case RT_CURSOR:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(���)\r\n");
					break;
				}
			case RT_BITMAP:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(λͼ)\r\n");
					break;
				}
			case RT_ICON:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(ͼ��)\r\n");
					break;
				}
			case RT_MENU:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�˵�)\r\n");
					break;
				}
			case RT_DIALOG:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�Ի���)\r\n");
					break;
				}
			case RT_STRING:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�ַ�����)\r\n");
					break;
				}
			case RT_FONTDIR:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(����Ŀ¼)\r\n");
					break;
				}
			case RT_FONT:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(����)\r\n");
					break;
				}
			case RT_ACCELERATOR:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��������)\r\n");
					break;
				}
			case RT_RCDATA:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�Զ�����Դ)\r\n");
					break;
				}
			case RT_MESSAGETABLE:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��Ϣ��)\r\n");
					break;
				}
			case RT_GROUP_CURSOR:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(ͼ����)\r\n");
					break;
				}
			case RT_GROUP_ICON:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�����)\r\n");
					break;
				}
			case RT_DLGINCLUDE:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��ȡ��Դ)\r\n");
					break;
				}
			case RT_VERSION:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(�汾��Ϣ)\r\n");
					break;
				}
			case RT_PLUGPLAY:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(���弴����Դ)\r\n");
					break;
				}
			case RT_VXD:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(VXD)\r\n");
					break;
				}
			case RT_ANICURSOR:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��̬���)\r\n");
					break;
				}
			case RT_ANIICON:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��̬ͼ��)\r\n");
					break;
				}
			case RT_HTML:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(HTML�ĵ�)\r\n");
					break;
				}
			default:
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(δ֪��Դ����)\r\n");
				}
			};
		}
		else
		{
			// �����λΪ1 ��ָ�� _IMAGE_RESOURCE_DIR_STRING_U �ṹ ��Դ���;����Զ���� ��һ���ַ���
			PIMAGE_RESOURCE_DIR_STRING_U pIMAGE_RESOURCE_DIR_STRING_U = (IMAGE_RESOURCE_DIR_STRING_U*)(pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameOffset + (DWORD)pIMAGE_RESOURCE_DIRECTORY);

			// ��Դ���͵��ַ�������
			DWORD IMAGE_RESOURCE_DIR_STRING_U_Length = pIMAGE_RESOURCE_DIR_STRING_U -> Length;

			// ��Դ���͵���ʼλ��
			PTCHAR StringOfResource = (PTCHAR)(&pIMAGE_RESOURCE_DIR_STRING_U -> NameString);

			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��Դ����(����): ");
			do
			{
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)StringOfResource);
				StringOfResource += 2;
			}
			while(--IMAGE_RESOURCE_DIR_STRING_U_Length);
			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");
		}
		
		// ��ʼ������һ��(���)
		if (!pIMAGE_RESOURCE_DIRECTORY_ENTRY -> DataIsDirectory)
		{
			// �����λ��0
			// ����һ������0
		}
		else
		{
			// �����λ��1 �ҵ���һ��Ŀ¼�ڵ����ʼλ�� (��ŵ���ʼ��ַ)
			PIMAGE_RESOURCE_DIRECTORY pIMAGE_RESOURCE_DIRECTORY_Digit = (IMAGE_RESOURCE_DIRECTORY*)((DWORD)pIMAGE_RESOURCE_DIRECTORY + pIMAGE_RESOURCE_DIRECTORY_ENTRY -> OffsetToDirectory);
			
			// �������
			DWORD dwNumberOfDigit = pIMAGE_RESOURCE_DIRECTORY_Digit -> NumberOfIdEntries + pIMAGE_RESOURCE_DIRECTORY_Digit -> NumberOfNamedEntries;

			// �ҵ��ڶ������Դ�������
			PIMAGE_RESOURCE_DIRECTORY_ENTRY pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pIMAGE_RESOURCE_DIRECTORY_Digit + 1);
			do
			{
				if (!pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> NameIsString)
				{
					// �����λΪ0 ���4���ֽڵĺ�31λ���� ��Դ���
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��Դ���:");
					sprintf(szDATA, "%08X", pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> NameOffset);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");
				}	
				else
				{
					// �����λΪ1 ��ָ�� _IMAGE_RESOURCE_DIR_STRING_U �ṹ ��Դ��ž����Զ���� ��һ���ַ���
					PIMAGE_RESOURCE_DIR_STRING_U pIMAGE_RESOURCE_DIR_STRING_U = (IMAGE_RESOURCE_DIR_STRING_U*)(pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> NameOffset + (DWORD)pIMAGE_RESOURCE_DIRECTORY);

					// ��Դ���͵��ַ�������
					DWORD IMAGE_RESOURCE_DIR_STRING_U_Length = pIMAGE_RESOURCE_DIR_STRING_U -> Length;

					// ��Դ���͵���ʼλ��
					PTCHAR StringOfResource = (PTCHAR)(&pIMAGE_RESOURCE_DIR_STRING_U -> NameString);

					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��Դ���(����): ");
					do
					{
						SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)StringOfResource);
						StringOfResource += 2;
					}
					while(--IMAGE_RESOURCE_DIR_STRING_U_Length);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");
				}

				// �ҵ�����ҳ
				PIMAGE_RESOURCE_DIRECTORY pIMAGE_RESOURCE_DIRECTORY_CodePage = (IMAGE_RESOURCE_DIRECTORY*)((DWORD)pIMAGE_RESOURCE_DIRECTORY + pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> OffsetToDirectory);

				// ����ҳ����
				DWORD dwNumberOfCodePage = pIMAGE_RESOURCE_DIRECTORY_CodePage -> NumberOfIdEntries + pIMAGE_RESOURCE_DIRECTORY_CodePage -> NumberOfNamedEntries;
				// �ҵ�������Ĵ���ҳ����
				PIMAGE_RESOURCE_DIRECTORY_ENTRY pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pIMAGE_RESOURCE_DIRECTORY_CodePage + 1);
				do
				{
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"����ҳ:");
					sprintf(szDATA, "%08X", pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage -> NameOffset);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					switch (pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage -> NameOffset)
					{
					case 1033:
						{
							SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(Ӣ��)\r\n");
							break;
						}
					case 2052:
						{
							SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(����)\r\n");
							break;
						}
					default:
						{
							SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"(��������)\r\n");
						}
					};
					// �ҵ��ڵ�
					PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)((DWORD)pIMAGE_RESOURCE_DIRECTORY + pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage -> OffsetToDirectory);
					
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"Rva: ");
					sprintf(szDATA, "%08X", pIMAGE_DATA_DIRECTORY -> VirtualAddress);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"OffSet: ");
					sprintf(szDATA, "%08X", ChangeRvaToFoa32(pIMAGE_DATA_DIRECTORY -> VirtualAddress, g_pStTLS -> m_fpFileBuffer));
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"Size: ");
					sprintf(szDATA, "%08X", pIMAGE_DATA_DIRECTORY -> Size);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
					SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n\r\n");
					
					pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage++;
				}
				while(--dwNumberOfCodePage);

				// �ҵ���һ����Դ��ŵ���ʼλ��
				pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element++;
			}
			while(--dwNumberOfDigit);
		}
		// �ҵ���һ����Դ���͵���ʼλ��
		pIMAGE_RESOURCE_DIRECTORY_ENTRY++;
	}
	while(--dwNumberOfTypes);

	return RETURN_SUCCESS; 
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsBaseRelocOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	/*
		����32λ��PE�ļ����ض�λ������������ʾ��IDC_EDIT_DS_ALL��
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER32 -> DataDirectory);

	// �����ж��Ƿ����ض�λ��
	if (!(pIMAGE_DATA_DIRECTORY + 5) -> VirtualAddress)
	{
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��PE�ļ�û���ض�λ��");
		return RETURN_FAILURE;
	}

	// �����ض�λ��ṹ��ָ��
	PIMAGE_BASE_RELOCATION pIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)(ChangeRvaToFoa32((pIMAGE_DATA_DIRECTORY + 5) -> VirtualAddress, g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);

	// ����д��
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"�ض�λ����Ϣ(��ǰ�汾���ݹ��ཫ��ʾ��ȫ):\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);

	// �ָ���
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" ------------------------------------------------\r\n");

	// �ж��ض�λ����û������
	if (!pIMAGE_BASE_RELOCATION -> VirtualAddress || !pIMAGE_BASE_RELOCATION -> SizeOfBlock)
	{
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��PE�ļ��ض�λ����û��ֵ!");
		return RETURN_FAILURE;
	}

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	// �����ж���Ŀ��ѭ������
	DWORD dwTempNumber = 0;
	DWORD dwCount = 0;

	// ��ʼ��ӡ�ض�λ��
	do
	{
		// ����
		dwTempNumber = (pIMAGE_BASE_RELOCATION -> SizeOfBlock - IMAGE_SIZEOF_BASE_RELOCATION) / sizeof(WORD);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"VirtualAddress[ҳRVA]: \r\t");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"SizeOfBlock[���С]: \r\t");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"Items[��Ŀ��]: \r\t\r\n");

		// VirtualAddress
		sprintf(szDATA, "%08X", pIMAGE_BASE_RELOCATION -> VirtualAddress);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\t");
		
		// SizeOfBlock
		sprintf(szDATA, "%08X", pIMAGE_BASE_RELOCATION -> SizeOfBlock);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\t");
		
		// Items
		sprintf(szDATA, "%08X", (pIMAGE_BASE_RELOCATION -> SizeOfBlock - IMAGE_SIZEOF_BASE_RELOCATION) / sizeof(WORD));
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\r\n");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��������[RVA]: \r\n");
		do
		{
			// ��������RVA
			sprintf(szDATA, "%08X", GET_OVER_LOBYTE(*(LPWORD)((DWORD)(pIMAGE_BASE_RELOCATION) + \
				IMAGE_SIZEOF_BASE_RELOCATION + dwCount++ * sizeof(WORD))) + pIMAGE_BASE_RELOCATION -> VirtualAddress);
			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

			// �ж��Ƿ񵽴��ض�λ��ĩβ
			if (!*(LPWORD)((DWORD)(pIMAGE_BASE_RELOCATION) + IMAGE_SIZEOF_BASE_RELOCATION + dwCount * sizeof(WORD)))
			{
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"00000000[������]\r\n");
				break;
			}
		}
		while(--dwTempNumber);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" ------------------------------------------------\r\n");

		// ��ʼ��dwCount��ֵ
		dwCount = 0;

		// ������ǰ���ȫ����ַ
		pIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)((DWORD)pIMAGE_BASE_RELOCATION + pIMAGE_BASE_RELOCATION -> SizeOfBlock);
	}
	// ����һ�����VirtualAddress��SizeOfBlock����Ϊ��ż���ִ��
	while(pIMAGE_BASE_RELOCATION -> VirtualAddress || pIMAGE_BASE_RELOCATION -> SizeOfBlock);
	
	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsBaseRelocOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	/*
		����64λ��PE�ļ����ض�λ������������ʾ��IDC_EDIT_DS_ALL��
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS64 pIMAGE_NT_HEADERS64 = (IMAGE_NT_HEADERS64*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS64 + sizeof(pIMAGE_NT_HEADERS64 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER64 pIMAGE_OPTIONAL_HEADER64 = (IMAGE_OPTIONAL_HEADER64*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER64 -> DataDirectory);

	// �����ж��Ƿ����ض�λ��
	if (!(pIMAGE_DATA_DIRECTORY + 5) -> VirtualAddress)
	{
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��PE�ļ�û���ض�λ��");
		return RETURN_FAILURE;
	}

	// �����ض�λ��ṹ��ָ��
	PIMAGE_BASE_RELOCATION pIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)(ChangeRvaToFoa64((pIMAGE_DATA_DIRECTORY + 5) -> VirtualAddress, g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);

	// ����д��
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"�ض�λ����Ϣ(��ǰ�汾���ݹ��ཫ��ʾ��ȫ):\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);

	// �ָ���
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" ------------------------------------------------\r\n");

	// �ж��ض�λ����û������
	if (!pIMAGE_BASE_RELOCATION -> VirtualAddress || !pIMAGE_BASE_RELOCATION -> SizeOfBlock)
	{
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��PE�ļ��ض�λ����û��ֵ!");
		return RETURN_FAILURE;
	}

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	// �����ж���Ŀ��ѭ������
	DWORD dwTempNumber = 0;
	DWORD dwCount = 0;

	// ��ʼ��ӡ�ض�λ��
	do
	{
		// ����
		dwTempNumber = (pIMAGE_BASE_RELOCATION -> SizeOfBlock - IMAGE_SIZEOF_BASE_RELOCATION) / sizeof(WORD);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"VirtualAddress[ҳRVA]: \r\t");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"SizeOfBlock[���С]: \r\t");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"Items[��Ŀ��]: \r\n");

		// VirtualAddress
		sprintf(szDATA, "%08X", pIMAGE_BASE_RELOCATION -> VirtualAddress);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\r\t");
		
		// SizeOfBlock
		sprintf(szDATA, "%08X", pIMAGE_BASE_RELOCATION -> SizeOfBlock);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\t\r\t");
		
		// Items
		sprintf(szDATA, "%08X", (pIMAGE_BASE_RELOCATION -> SizeOfBlock - IMAGE_SIZEOF_BASE_RELOCATION) / sizeof(WORD));
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"��������[RVA]: \r\n");

		do
		{
			// ��������RVA
			sprintf(szDATA, "%08X", GET_OVER_LOBYTE(*(LPWORD)((DWORD)(pIMAGE_BASE_RELOCATION) + \
				IMAGE_SIZEOF_BASE_RELOCATION + dwCount++ * sizeof(WORD))) + pIMAGE_BASE_RELOCATION -> VirtualAddress);
			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
			SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" \r\n");

			// �ж��Ƿ񵽴��ض�λ��ĩβ
			if (!*(LPWORD)((DWORD)(pIMAGE_BASE_RELOCATION) + IMAGE_SIZEOF_BASE_RELOCATION + dwCount * sizeof(WORD)))
			{
				SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"00000000[������]\r\n");
				break;
			}
		}
		while(--dwTempNumber);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"------------------------------------------------ \r\n");

		// ��ʼ��dwCount��ֵ
		dwCount = 0;

		// ������ǰ���ȫ����ַ
		pIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)((DWORD)pIMAGE_BASE_RELOCATION + pIMAGE_BASE_RELOCATION -> SizeOfBlock);
	}
	// ����һ�����VirtualAddress��SizeOfBlock����Ϊ��ż���ִ��
	while(pIMAGE_BASE_RELOCATION -> VirtualAddress || pIMAGE_BASE_RELOCATION -> SizeOfBlock);
	
	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsBoundImportOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	/*
		����32λ��PE�ļ��İ󶨵��������������ʾ��IDC_EDIT_DS_ALL��
	*/
	
	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER32 -> DataDirectory);

	// �����ж��Ƿ��а󶨵����
	if (!(pIMAGE_DATA_DIRECTORY + 11) -> VirtualAddress)
	{
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��PE�ļ�û�а󶨵����");
		return RETURN_FAILURE;
	}

	// ���嵼���ṹ��ָ��
	PIMAGE_IMPORT_DESCRIPTOR pIMAGE_IMPORT_DESCRIPTOR = (IMAGE_IMPORT_DESCRIPTOR*)(ChangeRvaToFoa32((pIMAGE_DATA_DIRECTORY + 1) -> VirtualAddress, \
		g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	
	// ����󶨵����ṹ��ָ��
	PIMAGE_BOUND_IMPORT_DESCRIPTOR pIMAGE_BOUND_IMPORT_DESCRIPTOR = (IMAGE_BOUND_IMPORT_DESCRIPTOR*)(ChangeRvaToFoa32((pIMAGE_DATA_DIRECTORY + 11) -> VirtualAddress, \
		g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	
	// �󶨵�����еĵ�һ���ṹ�� DESCRIPTOR ���� OffsetModuleName ���Եõ�ģ����
	DWORD dwNameBase = (DWORD)pIMAGE_BOUND_IMPORT_DESCRIPTOR;

	// ����д��
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"�󶨵������Ϣ(��ǰ�汾���ݹ��ཫ��ʾ��ȫ):\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);

	// �ָ���
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" ------------------------------------------------\r\n");

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	// ��ӡ��һ���󶨵�����е�����ֵ
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"FirstTimeDateStamp: ");
	sprintf(szDATA, "%08X", pIMAGE_BOUND_IMPORT_DESCRIPTOR -> TimeDateStamp);
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"FirstModuleName: ");
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)pIMAGE_BOUND_IMPORT_DESCRIPTOR -> OffsetModuleName + dwNameBase);
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	// ��ӡ��һ���󶨵������ NumberOfModuleForwarderRefs ���¼��ʣ������� ���ֵ���ܲ�׼(����Ϊ0)
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"FirstNumberOfModuleForwarderRefs: ");
	sprintf(szDATA, "%08X", pIMAGE_BOUND_IMPORT_DESCRIPTOR -> NumberOfModuleForwarderRefs);
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	// ����󶨵����� _IMAGE_BOUND_FORWARDER_REF �ṹ
	PIMAGE_BOUND_FORWARDER_REF pIMAGE_BOUND_FORWARDER_REF = (IMAGE_BOUND_FORWARDER_REF*)++pIMAGE_BOUND_IMPORT_DESCRIPTOR;

	do
	{
		// �����һ�������Ľṹ���ֵȫΪ0������
		if (!(pIMAGE_BOUND_FORWARDER_REF ->TimeDateStamp  | \
			pIMAGE_BOUND_FORWARDER_REF -> OffsetModuleName | \
			pIMAGE_BOUND_FORWARDER_REF -> Reserved))
			break;

		// �ж��Ƿ��ģ���а󶨵����
		if (!pIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp)
		{
			// �����ģ��û�а󶨵����������
			pIMAGE_IMPORT_DESCRIPTOR++;

			// ת����һ���󶨵����
			pIMAGE_BOUND_FORWARDER_REF++;

			// û�а󶨵�������ת����һ��
			continue;
		}

		// ��ӡ�󶨵����
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"TimeDateStamp: ");
		sprintf(szDATA, "%08X", pIMAGE_BOUND_FORWARDER_REF -> TimeDateStamp);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)pIMAGE_BOUND_FORWARDER_REF -> OffsetModuleName + dwNameBase);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"Reserved: ");
		sprintf(szDATA, "%08X", pIMAGE_BOUND_FORWARDER_REF -> Reserved);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n\r\n");

		// ת����һ���󶨵����
		pIMAGE_BOUND_FORWARDER_REF++;

		// ת����һ�������
		pIMAGE_IMPORT_DESCRIPTOR++;
	}
	while(TRUE);

	return RETURN_SUCCESS; 
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsBoundImportOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	/*
		����64λ��PE�ļ��İ󶨵��������������ʾ��IDC_EDIT_DS_ALL��
	*/
	
	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)g_pStTLS -> m_fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS64 pIMAGE_NT_HEADERS64 = (IMAGE_NT_HEADERS64*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS64 + sizeof(pIMAGE_NT_HEADERS64 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER64 pIMAGE_OPTIONAL_HEADER64 = (IMAGE_OPTIONAL_HEADER64*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER64 -> DataDirectory);

	// �����ж��Ƿ��а󶨵����
	if (!(pIMAGE_DATA_DIRECTORY + 11) -> VirtualAddress)
	{
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"��PE�ļ�û�а󶨵����");
		return RETURN_FAILURE;
	}

	// ���嵼���ṹ��ָ��
	PIMAGE_IMPORT_DESCRIPTOR pIMAGE_IMPORT_DESCRIPTOR = (IMAGE_IMPORT_DESCRIPTOR*)(ChangeRvaToFoa64((pIMAGE_DATA_DIRECTORY + 1) -> VirtualAddress, \
		g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	
	// ����󶨵����ṹ��ָ��
	PIMAGE_BOUND_IMPORT_DESCRIPTOR pIMAGE_BOUND_IMPORT_DESCRIPTOR = (IMAGE_BOUND_IMPORT_DESCRIPTOR*)(ChangeRvaToFoa64((pIMAGE_DATA_DIRECTORY + 11) -> VirtualAddress, \
		g_pStTLS -> m_fpFileBuffer) + (DWORD)g_pStTLS -> m_fpFileBuffer);
	
	// �󶨵�����еĵ�һ���ṹ�� DESCRIPTOR ���� OffsetModuleName ���Եõ�ģ����
	DWORD dwNameBase = (DWORD)pIMAGE_BOUND_IMPORT_DESCRIPTOR;

	// ����д��
	SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)"�󶨵������Ϣ(��ǰ�汾���ݹ��ཫ��ʾ��ȫ):\r\n");

	// ����Ϊĩβ׷�ӵ�ģʽ
	SendMessage(hwndEdit, EM_SETSEL, -2, -1);

	// �ָ���
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)" ------------------------------------------------\r\n");

	// ���ڴ洢ת����õ����ַ���
	TCHAR szDATA[0x10] = {0};

	// ��ӡ��һ���󶨵�����е�����ֵ
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"FirstTimeDateStamp: ");
	sprintf(szDATA, "%08X", pIMAGE_BOUND_IMPORT_DESCRIPTOR -> TimeDateStamp);
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"FirstModuleName: ");
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)pIMAGE_BOUND_IMPORT_DESCRIPTOR -> OffsetModuleName + dwNameBase);
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	// ��ӡ��һ���󶨵������ NumberOfModuleForwarderRefs ���¼��ʣ������� ���ֵ���ܲ�׼(����Ϊ0)
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"FirstNumberOfModuleForwarderRefs: ");
	sprintf(szDATA, "%08X", pIMAGE_BOUND_IMPORT_DESCRIPTOR -> NumberOfModuleForwarderRefs);
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

	// ����󶨵����� _IMAGE_BOUND_FORWARDER_REF �ṹ
	PIMAGE_BOUND_FORWARDER_REF pIMAGE_BOUND_FORWARDER_REF = (IMAGE_BOUND_FORWARDER_REF*)++pIMAGE_BOUND_IMPORT_DESCRIPTOR;

	do
	{
		// �����һ�������Ľṹ���ֵȫΪ0������
		if (!(pIMAGE_BOUND_FORWARDER_REF ->TimeDateStamp  | \
			pIMAGE_BOUND_FORWARDER_REF -> OffsetModuleName | \
			pIMAGE_BOUND_FORWARDER_REF -> Reserved))
			break;

		// �ж��Ƿ��ģ���а󶨵����
		if (!pIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp)
		{
			// �����ģ��û�а󶨵����������
			pIMAGE_IMPORT_DESCRIPTOR++;

			// ת����һ���󶨵����
			pIMAGE_BOUND_FORWARDER_REF++;

			// û�а󶨵�������ת����һ��
			continue;
		}

		// ��ӡ�󶨵����
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"TimeDateStamp: ");
		sprintf(szDATA, "%08X", pIMAGE_BOUND_FORWARDER_REF -> TimeDateStamp);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)pIMAGE_BOUND_FORWARDER_REF -> OffsetModuleName + dwNameBase);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n");

		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"Reserved: ");
		sprintf(szDATA, "%08X", pIMAGE_BOUND_FORWARDER_REF -> Reserved);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)szDATA);
		SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"\r\n\r\n");

		// ת����һ���󶨵����
		pIMAGE_BOUND_FORWARDER_REF++;

		// ת����һ�������
		pIMAGE_IMPORT_DESCRIPTOR++;
	}
	while(TRUE);

	return RETURN_SUCCESS; 
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsIATOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"���ڵ�����в鿴!");
	return RETURN_SUCCESS; 
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsIATOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS)
{
	SendMessage(hwndEdit, EM_REPLACESEL, 1, (LPARAM)"���ڵ�����в鿴!");
	return RETURN_SUCCESS;  
}