#include "stdafx.h"
#include "MainFram.h"


CMainFram::CMainFram()
{

}


CMainFram::~CMainFram()
{

}

LRESULT CMainFram::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	::MessageBox(GetHwnd(), _T("ÄãºÃ"), _T("ÄãºÃ"), 0);

	return 0;
}

void CMainFram::CommandMap()
{
	MakeCommandMap(WM_LBUTTONUP, RSig::rSig_lbtn, (R_PMSG)(static_cast<LRESULT(xWindow::*)(WPARAM, LPARAM)>(&CMainFram::OnLButtonUp)));
}
