#pragma once
#include "winCore.h"

class CMainFram:public xWindow
{
public:
	CMainFram();
	~CMainFram();

protected:
	void CommandMap();

private:
	LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);

};

