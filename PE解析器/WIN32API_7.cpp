// WIN32API_7.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PeFiles.h"

//////////////////////////////////////////////////////////////////////
// ���ļ��ǳ�������ļ�
// DWORD Erro = ::GetLastError();
// DbgPrintf("%d\n", Erro);
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// ȫ��ָ��
TLSDirectory g_stTLS;

BOOL CALLBACK DialogProcDS_ALL(
						 HWND hwndDlg,
						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam
						 )
{
	/*
		���ڴ���"IDD_DIALOG_DS_Export"�Ի���Ļص�����
	*/

	switch(uMsg)
	{
	case  WM_INITDIALOG:
		{
			// ����Сͼ�꼰��ͼ��Ϊͬһ��ͼ��
			SetIcon(g_stTLS.m_hAppInstance, hwndDlg, IDI_ICON_ALL, IDI_ICON_ALL);
			if (FILE_OF_PE32_COMPARE(g_stTLS.m_dwGlobalFlag))
			{
				// ���ݱ�־λִ�в�ͬ����
				switch (CLICK_DS_COMPARE(g_stTLS.m_dwGlobalFlag))
				{
				case CLICK_DS_EXPORT:
					{
						// 32λ������
						AnalysisDsExportOfPEData32(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				case CLICK_DS_IMPORT:
					{
						// 32λ�����
						AnalysisDsImportOfPEData32(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				case CLICK_DS_RESOURCE:
					{
						// 32λ��Դ��
						AnalysisDsResourceOfPEData32(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				case CLICK_DS_BASERELOC:
					{
						// 32λ�ض�λ��
						AnalysisDsBaseRelocOfPEData32(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				case CLICK_DS_BOUNDIMPORT:
					{
						// 32λ�󶨵����
						AnalysisDsBoundImportOfPEData32(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				case CLICK_DS_IAT:
					{
						// 32λIAT��
						AnalysisDsIATOfPEData32(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				} // End switch
			
			}
			else
			{
				// 64λ
				switch (CLICK_DS_COMPARE(g_stTLS.m_dwGlobalFlag))
				{
				case CLICK_DS_EXPORT:
					{
						// 64λ������
						AnalysisDsExportOfPEData64(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				case CLICK_DS_IMPORT:
					{
						// 64λ�����
						AnalysisDsImportOfPEData64(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				case CLICK_DS_RESOURCE:
					{
						// 64λ��Դ��
						AnalysisDsResourceOfPEData64(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				case CLICK_DS_BASERELOC:
					{
						// 64λ�ض�λ��
						AnalysisDsBaseRelocOfPEData64(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				case CLICK_DS_BOUNDIMPORT:
					{
						// 64λ�󶨵����
						AnalysisDsBoundImportOfPEData64(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				case CLICK_DS_IAT:
					{
						// 64λIAT��
						AnalysisDsIATOfPEData64(GetDlgItem(hwndDlg, IDC_EDIT_DS_ALL), &g_stTLS);
						break;
					}
				} // End switch
			}

			return CALLBACK_COMPLETED;
		}
	case WM_CLOSE:
		{
			// ����(x)��ť
			EndDialog(hwndDlg, TRUE);
			return CALLBACK_COMPLETED;
		}
	} // End switch

	return CALLBACK_UNCOMPLETED;
	
}

//////////////////////////////////////////////////////////////////////

BOOL CALLBACK DialogProcDirectory(
						 HWND hwndDlg,
						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam
						 )
{
	/*
		���ڴ���"IDD_DIALOG_Directory"�Ի���Ļص�����
	*/
	switch(uMsg)
	{
	case  WM_INITDIALOG:
		{
			// ����Сͼ�꼰��ͼ��Ϊͬһ��ͼ��
			SetIcon(g_stTLS.m_hAppInstance, hwndDlg, IDI_ICON_ALL, IDI_ICON_ALL);

			// ��32λ��64λ���н�һ����PE�ļ���������ʾ��IDD_DIALOG_Directory��
			if (FILE_OF_PE32_COMPARE(g_stTLS.m_dwGlobalFlag))
			{
				// 32λ����
				AnalysisDirectoryOfPEData32(hwndDlg, &g_stTLS);
			}
			else
			{
				// 64λ����
				AnalysisDirectoryOfPEData64(hwndDlg, &g_stTLS);
			}

			return CALLBACK_COMPLETED;
		}
	case WM_COMMAND:
		{
			// ���¸��ְ�ť��ʱ���ͽ�������Ϣ
			switch (LOWORD(wParam))
			{
			// ���ݵ���Ĳ�ͬ��ť���Ĳ���ͬ��־λ
			case IDC_BUTTON_D_Export:
					DsEditHandle(&g_stTLS, hwndDlg, (DWORD)&DialogProcDS_ALL, 0);
					break;
			case IDC_BUTTON_D_Import:
					DsEditHandle(&g_stTLS, hwndDlg, (DWORD)&DialogProcDS_ALL, 1);
					break;
			case IDC_BUTTON_D_Resource:
					DsEditHandle(&g_stTLS, hwndDlg, (DWORD)&DialogProcDS_ALL, 2);
					break;
			case IDC_BUTTON_D_BaseReloc:
					DsEditHandle(&g_stTLS, hwndDlg, (DWORD)&DialogProcDS_ALL, 3);
					break;
			case IDC_BUTTON_D_BoundImport:
					DsEditHandle(&g_stTLS, hwndDlg, (DWORD)&DialogProcDS_ALL, 4);
					break;
			case IDC_BUTTON_D_IAT:
					DsEditHandle(&g_stTLS, hwndDlg, (DWORD)&DialogProcDS_ALL, 5);
					break;
			}

			return CALLBACK_COMPLETED;
		}
	case WM_CLOSE:
		{
			// ����(x)��ť
			EndDialog(hwndDlg, TRUE);

			return CALLBACK_COMPLETED;
		}
	} // End switch

	return CALLBACK_UNCOMPLETED;
}

//////////////////////////////////////////////////////////////////////

BOOL CALLBACK DialogProcSection(
						 HWND hwndDlg,
						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam
						 )
{
	/*
		���ڴ���"IDD_DIALOG_Section"�Ի���Ļص�����
	*/
	switch(uMsg)
	{
	case  WM_INITDIALOG:
		{
			// ����Сͼ�꼰��ͼ��Ϊͬһ��ͼ��
			SetIcon(g_stTLS.m_hAppInstance, hwndDlg, IDI_ICON_ALL, IDI_ICON_ALL);
			
			// ��32λ��64λ���н�һ����PE�ļ���������ʾ��dialog��
			if (FILE_OF_PE32_COMPARE(g_stTLS.m_dwGlobalFlag))
			{
				// 32λPE�ļ�
				InitSectionListView(hwndDlg);
				AnalysisSectionOfPEData32(hwndDlg, &g_stTLS);
			}
			else
			{
				// 64λPE�ļ�
				InitSectionListView(hwndDlg);
				AnalysisSectionOfPEData64(hwndDlg, &g_stTLS);
			}

			return CALLBACK_COMPLETED;
		}
	case WM_CLOSE:
		{
			// ����(x)��ť
			EndDialog(hwndDlg, TRUE);

			return CALLBACK_COMPLETED;
		}
	}// End switch

	return CALLBACK_UNCOMPLETED; 
}

//////////////////////////////////////////////////////////////////////

BOOL CALLBACK DialogProcPE(
						 HWND hwndDlg,
						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam
						 )
{
	/*
		���ڴ���"IDD_DIALOG_PE"�Ի���Ļص�����
	*/
	switch(uMsg)
	{
	case WM_COMMAND:
		{
			// ���¸��ְ�ť��ʱ���ͽ�������Ϣ
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON_Directory:
				{
					// ����Ŀ¼��ť
					DialogBox(g_stTLS.m_hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_Directory), hwndDlg, DialogProcDirectory);
					break;
				}
			case IDC_BUTTON_Section:
				{
					// �������ΰ�ť
					DialogBox(g_stTLS.m_hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_Section), hwndDlg, DialogProcSection);
					break;
				}
			}
			return CALLBACK_COMPLETED;
		}
	case WM_CLOSE:
		{
			// ����(x)��ť
			// �ͷ�����Ŀռ䲢����ָ��
			free(g_stTLS.m_fpFileBuffer);
			g_stTLS.m_fpFileBuffer = NULL;

			// �رմ˽���
			EndDialog(hwndDlg, TRUE);
			return CALLBACK_COMPLETED;
		}
	case  WM_INITDIALOG:
		{
			// ����Сͼ�꼰��ͼ��Ϊͬһ��ͼ��
			SetIcon(g_stTLS.m_hAppInstance, hwndDlg, IDI_ICON_ALL, IDI_ICON_ALL);

			// ���ݲ�ͬλ������PE�ļ�,�������õ����ݷֱ�д�뵽�˶Ի����ж�Ӧ�ı༭����
			if (FILE_OF_PE32_COMPARE(g_stTLS.m_dwGlobalFlag))
			{
				// 32λ����
				AnalysisOfPEData32(hwndDlg, &g_stTLS);
			}
			else
			{
				// 64λ����
				AnalysisOfPEData64(hwndDlg, &g_stTLS);
			}

			return CALLBACK_COMPLETED;
		}
	} // End switch

	return CALLBACK_UNCOMPLETED;
}

//////////////////////////////////////////////////////////////////////

BOOL CALLBACK DialogProcAbout(
						 HWND hwndDlg,
						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam
						 )
{
	/*
		���ڴ���"IDD_DIALOG_ABOUT"�Ի���Ļص�����
	*/
	switch(uMsg)								
	{
	case  WM_INITDIALOG:								
		{		
			// ����Сͼ�꼰��ͼ�� Ϊͬһ��ͼ��
			SetIcon(g_stTLS.m_hAppInstance, hwndDlg, IDI_ICON_ALL, IDI_ICON_ALL);

			return CALLBACK_COMPLETED;							
		}	
	case WM_CLOSE:
		{
			// �����˳���ť
			EndDialog(hwndDlg, TRUE);
			return CALLBACK_COMPLETED;
		}
	} // End switch

	return CALLBACK_UNCOMPLETED;
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
			DWORD dwResult = MessageBox(hwndDlg, "ȷ��Ҫ�˳���?", "Really?", MB_ICONQUESTION | MB_OKCANCEL);
			if (dwResult == IDOK)
			{
				// ������Ϊ1��֤���û�������ȷ�� ���˳�����
				EndDialog(hwndDlg, TRUE);
			}

			return CALLBACK_COMPLETED;
		}
	case WM_NOTIFY:
		{
			// �������ͨ�ÿؼ���Ϣ
			if (wParam == IDC_LIST_PROCESS_UPPER && ((LPNMHDR)lParam) -> code == NM_CLICK)
			{
				// �������������� IDC_LIST_PROCESS_UPPER

				// ��ȡ GetPidByListViewText �Ľ��
				TCHAR szResult[0x20] = {0};

				// ��ȡ�û���Ҫ�鿴�Ľ��̵� PID
				BOOL IsTrue = GetPidByListViewText(GetDlgItem(hwndDlg, IDC_LIST_PROCESS_UPPER), szResult);
				if (!IsTrue)
				{
					return CALLBACK_COMPLETED;
				}

				// ���ڴ洢��ȡ���� PID ��ֵ
				DWORD dwPID = NULL;

				// ʹ�� atoi ����ȡ�����ַ���ת��Ϊ����
				dwPID = atoi(szResult);
				
				// �����ò���ϵͳ��ʾֵ�Ľṹ
				LV_ITEM vitem = {0};

				// ����ɾ��ȫ���� IDC_LIST_PROCESS_LOWER �е���Ϣ
				SendMessage(GetDlgItem(hwndDlg, IDC_LIST_PROCESS_LOWER), LVM_DELETEALLITEMS, 0, (DWORD)&vitem);

				// ����ģ�鲢��ʾ�� IDC_LIST_PROCESS_LOWER ��
				EnumMoudelByProcID(GetDlgItem(hwndDlg, IDC_LIST_PROCESS_LOWER), dwPID);
			}

			return CALLBACK_COMPLETED;
		}
	case  WM_INITDIALOG:								
		{
			// ����Сͼ�꼰��ͼ�� Ϊͬһ��ͼ��
			SetIcon(g_stTLS.m_hAppInstance, hwndDlg, IDI_ICON_ALL, IDI_ICON_ALL);

			// ��ʼ����һ�� ListView
			InitProcessListViewUpper(hwndDlg);

			// ��ʼ���ڶ��� ListView
			InitProcessListViewLower(hwndDlg);		

			// ö�ٽ��̲���ʾ�� ListViewUpper ��
			EnumProcByWinApi(GetDlgItem(hwndDlg, IDC_LIST_PROCESS_UPPER));

			return CALLBACK_COMPLETED;							
		}
	case  WM_COMMAND:
		{
			// ���¸��ְ�ť��ʱ���ͽ�������Ϣ
			switch (LOWORD(wParam))							
			{
			case IDC_BUTTON_OPEN:
				{
					// ����"�鿴"��ť
					
					// д���µ�·���ַ���
					DWORD dwUserChoose = PushViewButton(hwndDlg, g_stTLS.m_szFileName, "��ѡ��һ�� PE �ļ�");

					// ����������ļ�ѡ��
					if (dwUserChoose)
					{
						// ÿ��ѡ�����µ��ļ�Ӧ���ȳ�ʼ���й�32λ��64λPE�ļ��ı�־
						FILE_OF_PE_INIT(g_stTLS.m_dwGlobalFlag);

						// ѡ��ɹ�����Ҫ�ж��Ƿ��� PE �ļ�
						DWORD isPeFile = IsPeFile(g_stTLS.m_szFileName, &g_stTLS);

						switch (isPeFile)
						{
						case ERROR_MEMORY_REQUEST_FAILURE:
							MessageBox(hwndDlg, "�ڴ�����ʧ��", "������ѡ���ļ�", MB_ICONINFORMATION | MB_ICONASTERISK);
							return CALLBACK_COMPLETED;
						case ERROR_DOS_MZ:
							MessageBox(hwndDlg, "����� DOS_MZ ͷ", "��Ч�� PE �ļ�", MB_ICONWARNING);
							return CALLBACK_COMPLETED;
						case ERROR_PE_SIGNATURE:
							MessageBox(hwndDlg, "����� PE ��ʶ", "��Ч�� PE �ļ�", MB_ICONWARNING);
							return CALLBACK_COMPLETED;
						case ERROR_OPEN_FILE:
							MessageBox(hwndDlg, "�ļ���ʧ��", "���ٴ�ѡ���ļ�", MB_ICONINFORMATION | MB_ICONASTERISK);
							return CALLBACK_COMPLETED;
						case ERROR_READ_FILE:
							MessageBox(hwndDlg, "�ļ���ȡʧ��", "���ٴ�ѡ���ļ�", MB_ICONINFORMATION | MB_ICONASTERISK);
							return CALLBACK_COMPLETED;
						case ERROR_CLOSE_FILE:
							MessageBox(hwndDlg, "�ļ��ر�ʧ��", "���ٴ�ѡ���ļ�", MB_ICONINFORMATION | MB_ICONASTERISK);
							return CALLBACK_COMPLETED;
						case ERROR_PE_FILE_TOO_BIG:
							MessageBox(hwndDlg, "PE�ļ�����", "������ѡ���ļ�", MB_ICONINFORMATION | MB_ICONASTERISK);
							return CALLBACK_COMPLETED;
						case FILE_OF_PE_UNKNOWN:
							MessageBox(hwndDlg, "��֧�ֽ���32λ��64λ��PE�ļ�", "������ѡ���ļ�", MB_ICONINFORMATION | MB_ICONASTERISK);
							return CALLBACK_COMPLETED;
						}

						// �������Ч�� PE �ļ��򵯳� PE �ļ�����Ի���
						DialogBox(g_stTLS.m_hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_PE), hwndDlg, DialogProcPE);
					}

					return CALLBACK_COMPLETED;
				}
			case IDC_BUTTON_Shell:
				{
					// ����"�ӿ�"��ť
					MessageBox(hwndDlg, "������", "Sorry", MB_ICONINFORMATION | MB_ICONASTERISK);
					return CALLBACK_COMPLETED;
				}
			case IDC_BUTTON_TEXT:
				{
					// ����"�����޸�"��ť
					MessageBox(hwndDlg, "������", "Sorry", MB_ICONINFORMATION | MB_ICONASTERISK);
					return CALLBACK_COMPLETED;
				}
			case IDC_BUTTON_FixIcon:
				{
					// ����"ͼ���޸�"��ť
					MessageBox(hwndDlg, "������", "Sorry", MB_ICONINFORMATION | MB_ICONASTERISK);
					return CALLBACK_COMPLETED;
				}
			case IDC_BUTTON_DynamicInject:
				{
					// ����"��̬ע��"��ť
					MessageBox(hwndDlg, "������", "Sorry", MB_ICONINFORMATION | MB_ICONASTERISK);
					return CALLBACK_COMPLETED;
				}
			case IDC_BUTTON_StaticInject:
				{
					// ����"��̬ע��"��ť
					MessageBox(hwndDlg, "������", "Sorry", MB_ICONINFORMATION | MB_ICONASTERISK);
					return CALLBACK_COMPLETED;
				}
			case IDC_BUTTON_MEMORY:
				{
					// ����"�ڴ��д"��ť
					MessageBox(hwndDlg, "������", "Sorry", MB_ICONINFORMATION | MB_ICONASTERISK);
					return CALLBACK_COMPLETED;
				}
			case IDC_BUTTON_Reverse:
				{
					// ����"�����"��ť
					MessageBox(hwndDlg, "������", "Sorry", MB_ICONINFORMATION | MB_ICONASTERISK);
					return CALLBACK_COMPLETED;
				}
			case IDC_BUTTON_ABOUT:
				{
					// ����"����"��ť
					// �ٵ���һ������ д����˵��
					DialogBox(g_stTLS.m_hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_ABOUT), hwndDlg, DialogProcAbout);
					return CALLBACK_COMPLETED;
				}
			case IDC_BUTTON_HELP:
				{
					// ����"����"��ť
					MessageBox(hwndDlg, "������", "Sorry", MB_ICONINFORMATION | MB_ICONASTERISK);
					return CALLBACK_COMPLETED;
				}
			} // End switch

		} // case WM_COMMAND
		
    } // End switch

	return CALLBACK_UNCOMPLETED;							
}

//////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(
					HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR     lpCmdLine,
					int       nCmdShow
					)
{
 	// TODO: Place code here.

	/*
		������ϰ��		
			1������PETools�ĵ�һ������.		
			2���������̡�����ģ��
	*/

	/*
		����˵����
			1���������ڣ�5��
			2������Ҫ��淶
			3�������޷���������⣬���Ը���֧��
			���ˣ�
			��ϰ�޷�����ߣ�����һ��
	*/

	// ����Ƿ�ֻ��һ��ͬ������
	CheckIsExsist();

	// ��exe�ľ����ֵ��ȫ�ֱ���
	g_stTLS.m_hAppInstance = hInstance;

	// ������Ҫʹ�õ�ͨ�ÿؼ�
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icex);   

	// �������Ի���
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProcMain);

	return 0;
}
