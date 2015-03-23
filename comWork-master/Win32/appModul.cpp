#include "stdafx.h"
#include "winApp.h"

extern int WINAPI MWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, int nCmdShow);
extern HINSTANCE RGetInstanceHandle();

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, int nCmdShow)
{
	return MWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

HINSTANCE g_Instance = NULL;

int WINAPI MWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, int nCmdShow)
{
	int nReturnCode = -1;

	g_Instance = hInstance;

	winApp* pWinApp = GetApp();
	if (pWinApp && pWinApp->InitInstance())
	{
		nReturnCode = pWinApp->Run();
	}

	return nReturnCode;
}

HINSTANCE RGetInstanceHandle()
{
	return g_Instance;
}

