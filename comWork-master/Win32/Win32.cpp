// Win32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32.h"
#include "resource.h"

#include "MainFram.h"

extern HINSTANCE RGetInstanceHandle();
#define RXSWHNCLASSNAME _T("rxsClassName")

MApp theApp;

MApp::MApp()
{
	//
}

MApp::~MApp()
{
   //
}

bool MApp::InitInstance()
{
	winApp::InitInstance();

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ::DefWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = RGetInstanceHandle();
	wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_WIN32));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;  //MAKEINTRESOURCE(IDC_WIN32);
	wcex.lpszClassName = RXSWHNCLASSNAME;//szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);

	//
	CMainFram *pMainFrame = new CMainFram;
	DWORD dwStyle = WS_SYSMENU;
	pMainFrame->CreateWnd(0, RXSWHNCLASSNAME, _T("你好"), dwStyle, 400, 400, 500, 500, NULL, NULL, NULL);

	ShowWindow(pMainFrame->GetHwnd(), SW_SHOW);
	UpdateWindow(pMainFrame->GetHwnd());

	return true;
}

int MApp::ExitInstance()
{

	return winApp::ExitInstance();
}

bool MApp::OnIdle(LONG lCount)
{
	
	return winApp::OnIdle(lCount);
}





/*
#include "Win32.h"
#include "windowsx.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = _T("");  //MAKEINTRESOURCE(IDC_WIN32);
	wcex.lpszClassName = _T("OldWn");//szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK BigWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	//窗口超类化
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	GetClassInfoEx(hInstance, _T("OldWn"), &wc);

	wc.lpszClassName = _T("Miren");
	//wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.lpfnWndProc = BigWndProc;
	RegisterClassEx(&wc);

   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
   DWORD dwStyle = WS_SYSMENU;// | WS_VSCROLL | WS_HSCROLL;
   //dwStyle &= ~WS_BORDER;
   hWnd = CreateWindow(_T("Miren"), szTitle, dwStyle,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   
   //SetWindowLong(hWnd, GWL_WNDPROC, (LONG)NewWndProc);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_LBUTTONDOWN:
			MessageBox(hWnd, L"我是改变了,但比较小", L"小提示", MB_OK | MB_ICONINFORMATION);
			break;
		default:
			return CallWindowProc(WndProc, hWnd, message, wParam, lParam);
			break;
	}
	return 0;
}

LRESULT CALLBACK BigWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		MessageBox(hWnd, L"我是改变了,变的更大了非常大", L"小提示", MB_OK | MB_ICONINFORMATION);
		break;
	default:
		return CallWindowProc(WndProc, hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	HDC hdcMem;
	HBITMAP hTemp;
	BITMAP  bitmap;

	HWND hButton;
	HMENU hRoot;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case 333:
			SendMessage((HWND)lParam, WM_SETTEXT, (WPARAM)NULL, (LPARAM)L"我被点击了");
			MessageBox(hWnd, L"你点击了我", L"小提示", MB_OK | MB_ICONINFORMATION);
			break;
		case ID_123_32772:

			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_VSCROLL: //响应垂直滚动条操作的消息

		break;
	case WM_CREATE:
		//
		hButton = CreateWindow(L"Button", L"来点击我！", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 35, 45, 160, 65, hWnd, (HMENU)333, hInst, NULL);
		CreateWindow(L"Button", L"男", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE | WS_GROUP,
			100, 200, 50, 25, hWnd, (HMENU)444, hInst, NULL);
		CreateWindow(L"Button", L"女", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
			200, 200, 50, 25, hWnd, (HMENU)445, hInst, NULL);

		CreateWindow(L"Button", L"红色", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE | WS_GROUP,
			100, 230, 50, 25, hWnd, (HMENU)446, hInst, NULL);
		CreateWindow(L"Button", L"黑色", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
			200, 230, 50, 25, hWnd, (HMENU)447, hInst, NULL);
		break;
	case WM_SHOWWINDOW:
		//Invalidate();
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_CONTEXTMENU:
		hRoot = LoadMenu((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDR_MENUTest));
		if (hRoot)
		{
			HMENU hPop = GetSubMenu(hRoot, 0);
			//
			int px = GET_X_LPARAM(lParam);
			int py = GET_Y_LPARAM(lParam);
			POINT pt;
			pt.x = px;
			pt.y = py;

			RECT rect;
			GetClientRect((HWND)wParam, &rect);
			ScreenToClient((HWND)wParam, &pt);
			if (PtInRect(&rect, pt))
			{
				ClientToScreen((HWND)wParam, &pt);
				TrackPopupMenu(hPop, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,
					px, py, 0, (HWND)wParam, NULL);
			}
			else
			{
				DefWindowProc(hWnd, message, wParam, lParam);
			}

			DestroyMenu(hRoot);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
*/

/*
//SetWindowPos(hWnd, NULL, 100, 100, 500, 500, SWP_NOMOVE);
//hdc = GetDC(hWnd);
//hdcMem = CreateCompatibleDC(hdc);
//hTemp = (HBITMAP)LoadImage(NULL, _T("C:\\Users\\Public\\Pictures\\Sample Pictures\\Hydrangeas.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//SelectObject(hdcMem, hTemp);
//GetObject(hTemp, sizeof(BITMAP), &bitmap);
////BitBlt
//BitBlt(hdc, 0, 0, 1024, 768, hdcMem, 0, 0, SRCCOPY);
//DeleteDC(hdcMem);
//DeleteObject(hTemp);
//ReleaseDC(hWnd, hdc);
*/