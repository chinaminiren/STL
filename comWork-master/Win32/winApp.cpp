#include "stdafx.h"
#include "winApp.h"


static winApp* curWinApp = NULL;

winApp* GetApp()
{
	return curWinApp;
}

winApp::winApp()
{
	curWinApp = this;
}


winApp::~winApp()
{
	//
}

bool winApp::InitInstance()
{
	return true;
}

int  winApp::ExitInstance()
{
	return 0;
}

bool winApp::OnIdle(LONG lCount)
{
	return false;
}

bool winApp::PreTranslateMessage(MSG *pMsg)
{
	return false;
}

BOOL PumpMessage()
{
	MSG msg;
	if (!::GetMessage(&msg, NULL, NULL, NULL))
	{
		return FALSE;
	}

	::TranslateMessage(&msg);
	::DispatchMessage(&msg);

	return TRUE;
}

int winApp::Run()
{
	MSG msg;

	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;

	/*for (;;)
	{*/
		//while (bIdle && !::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
		//{
		//	if (!OnIdle(lIdleCount++))
		//	{
		//		bIdle = FALSE;
		//	}
		//}

		
	/*	do
		{*/
			while (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}


			//if (msg.message == WM_MOUSEMOVE || msg.message == WM_NCMOUSEMOVE)
			//{
			//	//�������ظ��������Ϣ
			//	bIdle = TRUE;
			//	lIdleCount = 0;
			//}
			//else if (msg.message != WM_PAINT && msg.message != 0x0118)
			//{
			//	bIdle = TRUE;
			//	lIdleCount = 0;
			//}
		//} while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE));
	/*}*/

	return 0;
}
