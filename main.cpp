#include<Windows.h>
#include<stdio.h>
#include"resource.h"
#pragma warning(disable:4996)

DWORD Money;
HWND hEditIn;
HWND hEdit1;
HWND hEdit2;
HWND hEdit3;

CRITICAL_SECTION csMoney;

//Thread1

DWORD WINAPI ThreadProc1(
	LPVOID lpParameter   // thread data		
)
{
	TCHAR buffer[10];
	memset(buffer, 0, 10);
	DWORD Temp1 = 0;

	if (Money<=50)
	{
		ExitThread(1);
	}

	while (Money > 50)
	{
		Sleep(1000);

		EnterCriticalSection(&csMoney);
		Money = Money - 50;
		Temp1 = Temp1 + 50;
		LeaveCriticalSection(&csMoney);

		sprintf(buffer, "%d", Temp1);
		SetWindowText(hEdit1, buffer);
	}

	return 0;
}

//Thread2

DWORD WINAPI ThreadProc2(
	LPVOID lpParameter   // thread data		
)
{
	TCHAR buffer[10];
	memset(buffer, 0, 10);
	DWORD Temp1 = 0;

	if (Money <= 50)
	{
		ExitThread(2);
	}

	while (Money > 50)
	{
		Sleep(1000);

		EnterCriticalSection(&csMoney);	
		Temp1 = Temp1 + 50;
		LeaveCriticalSection(&csMoney);

		sprintf(buffer, "%d", Temp1);
		SetWindowText(hEdit1, buffer);
	}

	return 0;
}

//Thread3

DWORD WINAPI ThreadProc3(
	LPVOID lpParameter   // thread data		
)
{
	TCHAR buffer[10];
	memset(buffer, 0, 10);
	DWORD Temp1 = 0;

	if (Money <= 50)
	{
		ExitThread(3);
	}

	while (Money > 50)
	{
		Sleep(1000);

		EnterCriticalSection(&csMoney);
		Money = Money - 50;
		Temp1 = Temp1 + 50;
		LeaveCriticalSection(&csMoney);

		sprintf(buffer, "%d", Temp1);
		SetWindowText(hEdit1, buffer);
	}

	return 0;
}

BOOL CALLBACK DialogProc(

	HWND hwndDlg,
	// handle to dialog box

	UINT uMsg,
	// message

	WPARAM wParam,
	// first message parameter

	LPARAM lParam
	// second message parameter

)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			//DeleteCriticalSection(&csMoney);
			ExitProcess(0);
			break;
		}

		case WM_INITDIALOG:
		{
			InitializeCriticalSection(&csMoney);
			hEditIn = GetDlgItem(hwndDlg, IDC_EDIT_Orign);
			hEdit1 = GetDlgItem(hwndDlg, IDC_EDIT1);
			hEdit2 = GetDlgItem(hwndDlg, IDC_EDIT2);
			hEdit3 = GetDlgItem(hwndDlg, IDC_EDIT3);
			break;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDC_BUTTON:
				{
					TCHAR buffer[10];
					memset(buffer, 0, 10);
					GetWindowText(hEditIn, buffer, 10);
					sscanf(buffer, "%d", &Money);
					/*if (Money == 0)
					{
						MessageBox(0, "请输入一个大于0的金额", "警告", 0);
						return TRUE;
					}*/
					HANDLE hThread1 = CreateThread(0, 0, ThreadProc1, 0, 0, 0);
					HANDLE hThread2 = CreateThread(0, 0, ThreadProc2, 0, 0, 0);
					HANDLE hThread3 = CreateThread(0, 0, ThreadProc3, 0, 0, 0);
				}
		
			}
			break;
		}

	}



	return 0;
}



int WINAPI WinMain(

	HINSTANCE hInstance,
	// handle to current instance

	HINSTANCE hPrevInstance,
	// handle to previous instance

	LPSTR lpCmdLine,
	// pointer to command line

	int nCmdShow
	// show state of window

)
{
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProc);

	
	
	return 0;
}

