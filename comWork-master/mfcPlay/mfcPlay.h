
// mfcPlay.h : main header file for the mfcPlay application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CmfcPlayApp:
// See mfcPlay.cpp for the implementation of this class
//

class CmfcPlayApp : public CWinApp
{
public:
	CmfcPlayApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CmfcPlayApp theApp;
