// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// ʹ DbgPrintf ���� debug ģʽ������
#ifdef _DEBUG
#define DbgPrintf   OutputDebugStringF
#else
#define DbgPrintf
#endif

// ͨ�ñ�־λ
#define CALLBACK_UNCOMPLETED				0x00000000			// �ص�����δ����
#define CALLBACK_COMPLETED					0x00000001			// �ص������������
#define ERROR_MEMORY_REQUEST_FAILURE		0x00000002			// �ڴ�����ʧ��
#define ERROR_DOS_MZ						0x00000004			// �����DOS_MZͷ��־
#define ERROR_PE_SIGNATURE					0x00000008			// �����PEͷ��־
#define ERROR_OPEN_FILE						0x00000010			// �ļ���ʧ��
#define ERROR_READ_FILE						0x00000020			// �ļ���ȡʧ��
#define ERROR_CLOSE_FILE					0x00000040			// �ļ��ر�ʧ��
#define ERROR_PE_FILE_TOO_BIG				0x00000080			// PE�ļ���������ռ�ʧ��
#define FILE_OF_PE_UNKNOWN					0x00000100			// δ֪��ִ�г���
#define ERROR_CLICK							0x00000200			// ����ĵ����Ϣ
#define RETURN_FAILURE						0x00000400			// ����ִ��ʧ��
#define RETURN_SUCCESS						0x00000800			// ����ִ�гɹ�
#define FILE_MAX_SIZE						0x40000000			// �ܽ��ܵ�ʵ��PE�ļ����ֵ

// ȫ�ֱ�־λ
#define FILE_OF_PE32						0x00000001			// 32λPE�ļ�
#define FILE_OF_PE64						0x00000002			// 64λPE�ļ�
#define CLICK_DS_EXPORT						0x00000004			// ���������ť
#define CLICK_DS_IMPORT						0x00000008			// ��������ť
#define CLICK_DS_RESOURCE					0x00000010			// �����Դ��ť
#define CLICK_DS_BASERELOC					0x00000020			// ����ض�λ��ť
#define CLICK_DS_BOUNDIMPORT				0x00000040			// ����󶨵����ť
#define CLICK_DS_IAT						0x00000080			// ���IAT��ť
#define EXPORT_NAME							0x00000100			// �����ֵ���

// �궨��
#define FILE_OF_PE_INIT(i)					(i &= (~(FILE_OF_PE32 | FILE_OF_PE64 )))			// ��ʼ��PE��־λ
#define FILE_OF_PE32_COMPARE(i)				((i & FILE_OF_PE32) == FILE_OF_PE32)				// �Ƿ���32λPE�ļ�
#define FILE_OF_PE64_COMPARE(i)				((i & FILE_OF_PE64) == FILE_OF_PE64)				// �Ƿ���64λPE�ļ�
#define	FILE_OF_PE_BY_32(i)					(i |= FILE_OF_PE32)									// 32λPE��־,��1
#define	FILE_OF_PE_BY_64(i)					(i |= FILE_OF_PE64)									// 64λPE��־,��1

#define CLICK_DS_ALL_FLAG					(CLICK_DS_EXPORT				|\
											 CLICK_DS_IMPORT				|\
											 CLICK_DS_RESOURCE				|\
											 CLICK_DS_BASERELOC				|\
											 CLICK_DS_BOUNDIMPORT			|\
											 CLICK_DS_IAT)										// DS��־λ

#define CLICK_DS_INIT(i)					(i &= (~CLICK_DS_ALL_FLAG))							// ��ʼ��DS��־λ
#define CLICK_DS_COMPARE(i)					(i & CLICK_DS_ALL_FLAG)								// ��ȡDS��־λ��ֵ
#define CLICK_DS_SELECT_EXPORT(i)			(i |= CLICK_DS_EXPORT)								// EXPORT��־λ,��1
#define CLICK_DS_SELECT_IMPORT(i)			(i |= CLICK_DS_IMPORT)								// IMPORT��־λ,��1
#define CLICK_DS_SELECT_RESOURCE(i)			(i |= CLICK_DS_RESOURCE)							// RESOURCE��־λ,��1
#define CLICK_DS_SELECT_BASERELOC(i)		(i |= CLICK_DS_BASERELOC)							// BASERELOC��־λ,��1
#define CLICK_DS_SELECT_BOUNDIMPORT(i)		(i |= CLICK_DS_BOUNDIMPORT)							// BOUNDIMPORT��־λ,��1
#define CLICK_DS_SELECT_IAT(i)				(i |= CLICK_DS_IAT)									// IAT��־λ,��1

#define EXPORT_FUNC_INIT(i)					(i &= (~EXPORT_NAME))								// ��ʼ������������־λ					
#define EXPORT_OF_NAME_COMPARE(i)			((i & EXPORT_NAME) == EXPORT_NAME)					// �Ƿ������ֵ���
#define EXPORT_BY_NAME(i)					(i |= EXPORT_NAME)									// ���ֵ�����־λ,��1

#define GET_OVER_LOBYTE(i)					(i &= 0x0FFF)										// WORDĨȥ��4λ

// TODO: reference additional headers your program requires here
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <Tlhelp32.h>					// ���ڱ������̺�ģ��
#include <commctrl.h>					// ��ģ������ͨ�ÿؼ�
#include <Commdlg.h>					// �ļ�·�����
#pragma comment(lib,"comctl32.lib")
#include "resource.h"					// ��Դ�ļ�

//////////////////////////////////////////////////////////////////////
// GLOABAL
typedef class _TLSDirectory {
public:
	DWORD			m_dwGlobalFlag;				// ȫ�ֱ�־
	LPVOID			m_fpFileBuffer;				// �ļ�������ָ��
	HINSTANCE		m_hAppInstance;				// ����ģ����
	LPTSTR			m_szFileName;				// ·���ַ���������
public:
	WINAPI _TLSDirectory();						// ��ʼ����Ա����
	WINAPI _TLSDirectory(IN DWORD dwNumber);	// ·���ַ���С���Զ���
	WINAPI ~_TLSDirectory();					// �ͷŶѿռ䲢����ָ�뼰����
} TLSDirectory, *PTLSDirectory;

//////////////////////////////////////////////////////////////////////
//
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//
//////////////////////////////////////////////////////////////////////

VOID WINAPIV OutputDebugStringF(const char *format, ...);
//////////////////////////////////////////////////////////////////////

VOID WINAPI CheckIsExsist(void);
//////////////////////////////////////////////////////////////////////

VOID WINAPI SetListViewText(IN HWND hListProcess, 
							IN DWORD Count, 
							IN PTCHAR szNumber, 
							IN PTCHAR szString, 
							IN PTCHAR szProcessID, 
							IN PTCHAR szImageBase, 
							IN PTCHAR szSizeOfImage
							);
//////////////////////////////////////////////////////////////////////

VOID WINAPI SetListViewTextLow(IN HWND hListProcess, 
							   IN DWORD Count, 
							   IN PTCHAR szNumber, 
							   IN PTCHAR szName, 
							   IN PTCHAR szModBaseAddr, 
							   IN PTCHAR szModBaseSize, 
							   IN PTCHAR szLocal
							   );
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
									 );
//////////////////////////////////////////////////////////////////////

BOOL WINAPI GetPidByListViewText(IN HWND hwndDlg, OUT PTCHAR szResult);
//////////////////////////////////////////////////////////////////////

VOID WINAPI EnumMoudelByProcID(IN HWND hListViewLower, IN DWORD ProcessID);
//////////////////////////////////////////////////////////////////////

VOID WINAPI EnumProcByWinApi(IN HWND hListViewUpper);
//////////////////////////////////////////////////////////////////////

VOID WINAPI InitProcessListViewUpper(IN HWND hwndDlg);
//////////////////////////////////////////////////////////////////////

VOID WINAPI InitProcessListViewLower(HWND hwndDlg);
//////////////////////////////////////////////////////////////////////

VOID WINAPI InitSectionListView(HWND hwndDlg);

//////////////////////////////////////////////////////////////////////

DWORD WINAPI SetIcon(IN HINSTANCE hAppInstance, IN HWND hwndDlg, IN DWORD IconSmall, IN DWORD IconBig);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI PushViewButton(IN HWND hwndDlg, IN LPTSTR TEXT(szFileName), IN PTCHAR TEXT(szTitle));
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisOfPEData32(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisOfPEData64(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDirectoryOfPEData32(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDirectoryOfPEData64(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisSectionOfPEData32(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisSectionOfPEData64(IN HWND hwndDlg, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI DsEditHandle(IN PTLSDirectory g_pStTLS, IN HWND hwndDlg, IN DWORD dwCallBackFunction, IN DWORD dwFlag);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsExportOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsExportOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsImportOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsImportOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsResourceOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsResourceOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsBaseRelocOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsBaseRelocOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsBoundImportOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsBoundImportOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsIATOfPEData32(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

DWORD WINAPI AnalysisDsIATOfPEData64(IN HWND hwndEdit, IN PTLSDirectory g_pStTLS);
//////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_STDAFX_H__A89DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)