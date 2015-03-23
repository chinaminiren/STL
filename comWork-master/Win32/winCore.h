#pragma once
#include <windows.h>
#include <map>

class xWindow;

typedef void(xWindow::*R_PMSG)(void); //ָ��xWindow �ĳ�Ա����ָ��

struct MSGMAP_ITEM
{
	MSGMAP_ITEM()
	{
		memset(this, 0, sizeof(*this));
	}

	UINT nMessage;
	UINT_PTR nSig;
	R_PMSG pfn;
};

enum RSig
{
	rSig_end = 0,
	rSig_lbtn,
};

union MessageMapFunctions  //�����ο���http://www.suninf.net/2011/06/member-function-transform-in-inherit.html
{
	R_PMSG pfn;

	LRESULT(xWindow::*pfn_comm)(WPARAM, LPARAM);
	LRESULT(xWindow::*pfn_nparam)();

};

class xWindow
{

public:
	xWindow();
	virtual ~xWindow();

public:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL CreateWnd(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
		DWORD dwStyle,int x,int y,int nWith,int nHeigh,HWND hWndParent,HMENU nIDorHMenu,LPVOID lpParam);
	BOOL Attach(HWND hWndNew); //����������Ҫ�Զ� ���� map�е����� �Լ�

	WNDPROC GetSurperWndProcAddr();
	void SetSurperWndProcAddr(WNDPROC lpfn);

	HWND GetHwnd();

protected:
	virtual void CommandMap(); //ģ����Ϣӳ��
	void MakeCommandMap(UINT message, UINT_PTR nSig, R_PMSG pfn);

private:
	LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);

protected:
	virtual LRESULT DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);

	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT &lResult);


private:
	HWND m_hWnd;
	WNDPROC m_lpfn; //��¼�ɵ�

private:
	static std::map<UINT, MSGMAP_ITEM> m_CommandMap; //
};
				

