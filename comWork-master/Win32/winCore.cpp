#include "stdafx.h"
#include <assert.h>
#include "winCore.h"

extern HINSTANCE RGetInstanceHandle();
extern void WINAPI RHookWindowCreate(xWindow* pWnd);
extern BOOL RUnhookWindowCreate();
extern LRESULT CALLBACK RCbtFilterHook(int code, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::map<UINT, MSGMAP_ITEM> xWindow::m_CommandMap;

static std::map<HWND, xWindow*> sHandlerMap; //��������Ӧ����ȥ�� ��ض�Ӧ

xWindow::xWindow()
{
	//
}

xWindow::~xWindow()
{
	//
}

void xWindow::MakeCommandMap(UINT message, UINT_PTR nSig, R_PMSG pfn)
{
	MSGMAP_ITEM item;
	item.nMessage = message;
	item.nSig = nSig;
	item.pfn = pfn;
	xWindow::m_CommandMap.insert(std::make_pair(message, item));
}

void xWindow::CommandMap() 
{
	MakeCommandMap(WM_LBUTTONUP, RSig::rSig_lbtn, (R_PMSG)(static_cast<LRESULT(xWindow::*)(WPARAM, LPARAM)>(&xWindow::OnLButtonUp)));
}

LRESULT xWindow::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	::MessageBox(this->m_hWnd, _T(""), _T(""), 0);

	return 0;
}

BOOL xWindow::CreateWnd(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
	DWORD dwStyle, int x, int y, int nWith, int nHeigh, HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam)
{
	//valid param
	CREATESTRUCT cs;
	cs.dwExStyle   = dwExStyle;
	cs.lpszClass   = lpszClassName;
	cs.lpszName    = lpszWindowName;
	cs.style       = dwStyle;
	cs.x = x;
	cs.y = y;
	cs.cx = nWith;
	cs.cy = nHeigh;
	cs.hwndParent = hWndParent;
	cs.hMenu = nIDorHMenu;
	cs.hInstance = RGetInstanceHandle();
	cs.lpCreateParams = lpParam;

	RHookWindowCreate(this);

	//PreCreateWindow

	HWND hWnd = CreateWindowEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy, cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);

	if (!RUnhookWindowCreate())
	{
		//cleanup if CreateWindowEx fails too soon  ???
		return FALSE; //ʧ��
	}

	if (hWnd == NULL)
		return FALSE;

	//
	CommandMap();
	return TRUE;
}

BOOL xWindow::Attach(HWND hWndNew) // handle--obj map
{
	if (NULL == hWndNew)
		return FALSE;
	
	sHandlerMap.insert(std::make_pair(hWndNew, this));

	m_hWnd = hWndNew;

	return TRUE;
}

LRESULT xWindow::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	if (!OnWndMsg(message, wParam, lParam,lResult))
		lResult = xWindow::DefWindowProc(message, wParam, lParam); //�Լ�ʵ�ֵ� DefWindowProc

	return lResult;
}

LRESULT xWindow::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	if (m_lpfn != NULL)
	{
		return ::CallWindowProc(m_lpfn, m_hWnd, nMsg, wParam, lParam);
	}
	else
	{
		return ::DefWindowProc(m_hWnd, nMsg, wParam, lParam);
	}
}

BOOL xWindow::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT &lResult)
{
	lResult = 0;

	//����˳�ϵͳ
	if (message == WM_NCDESTROY)
	{
		//����Ƿ�������
		::PostQuitMessage(0);
	}

	if (message == WM_COMMAND)
	{
		//OnCommand() //����������Ϣ
		//return TRUE;
	}

	if (message == WM_NOTIFY)
	{
		//OnNotify() //����֪ͨ��Ϣ
		//return TRUE;
	}

	if (message == WM_ACTIVATE)
	{
		//���⴦��
	}

	//WM_SETCURSOR  //���⴦��

	//xWindow::m_CommandMap::i
	auto iter = xWindow::m_CommandMap.find(message);
	if (iter == xWindow::m_CommandMap.end())
	{
		return FALSE;
	}

	MessageMapFunctions mfn;
	mfn.pfn = iter->second.pfn;

	switch (iter->second.nSig)
	{
	case rSig_lbtn:
	{
	   lResult = (this->*mfn.pfn_comm)(wParam, lParam);
	   return TRUE;
	}
	break;
	default:
		break;
	}

	return FALSE;
}

WNDPROC xWindow::GetSurperWndProcAddr()
{
	return m_lpfn;
}

void xWindow::SetSurperWndProcAddr(WNDPROC lpfn)
{
	m_lpfn = lpfn;
}

HWND xWindow::GetHwnd()
{
	return m_hWnd;
}

//--Hook Window Create

HHOOK hookOldCbtFilter = NULL;
xWindow* pHookWind = NULL;
void WINAPI RHookWindowCreate(xWindow* pWnd)
{
	pHookWind = pWnd;
	hookOldCbtFilter = ::SetWindowsHookEx(WH_CBT, RCbtFilterHook, NULL, ::GetCurrentThreadId());
}

BOOL RUnhookWindowCreate()
{
	if (pHookWind != NULL)  //����ΪNULL ��Ϊ�� ���Ӻ�������д����ˡ�
	{
		pHookWind = NULL;
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK RCbtFilterHook(int code, WPARAM wParam, LPARAM lParam)
{
	if (code != HCBT_CREATEWND)
	{
		return ::CallNextHookEx(hookOldCbtFilter, code, wParam, lParam);
	}
	//IME window no understand
	LPCREATESTRUCT lpcs = ((LPCBT_CREATEWND)lParam)->lpcs;
	assert(lpcs);

	HWND hWnd = (HWND)wParam;
	WNDPROC oldWndProc;
	if (pHookWind)
	{
		pHookWind->Attach(hWnd);

		//PreSubClassWindow

		WNDPROC rWndProc = pHookWind->GetSurperWndProcAddr();
		oldWndProc = (WNDPROC)::SetWindowLong(hWnd, GWLP_WNDPROC, (DWORD_PTR)WndProc); //ȫ�ֹ��̺���
		if (rWndProc != oldWndProc)
		{
			pHookWind->SetSurperWndProcAddr(oldWndProc);
		}

		pHookWind = NULL;
	}

	return 0;
}



//�ο�http://www.vckbase.com/index.php/wv/1309
//http://blog.csdn.net/bagboy_taobao_com/article/details/6171616
MSG gMsg;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	xWindow *pWnd = NULL; //get from map by hwnd;
	auto iter = sHandlerMap.find(hwnd);
	if (iter != sHandlerMap.end())
	{
		pWnd = iter->second;
	}

	if (NULL == pWnd)
	{
		return ::DefWindowProc(hwnd, msg, wParam, lParam);
	}
	else
	{
		if (pWnd->GetHwnd() != hwnd)
		{
			return ::DefWindowProc(hwnd, msg, wParam, lParam);
		}
		else
		{
			MSG oldmsg = gMsg;
			gMsg.hwnd = hwnd;
			gMsg.message = msg;
			gMsg.wParam = wParam;
			gMsg.lParam = lParam;

			//�㲻�� ���Ǹ�ʲô���� ���ֺ�ħ��

			lResult = pWnd->WindowProc(msg, wParam, lParam);
		}
	}

	return lResult;
}
//--end Hook
