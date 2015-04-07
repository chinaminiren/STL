#pragma once

#include "winApp.h"

class MApp :winApp
{
public:
	MApp();
	virtual ~MApp();

public:
	virtual bool InitInstance();
	virtual int ExitInstance();
	virtual bool OnIdle(long lCount);

};