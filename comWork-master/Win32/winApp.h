#pragma once

class winApp;

extern winApp* GetApp();

class winApp
{
public:
	winApp();
	virtual ~winApp();

public:
	virtual bool InitInstance();
	virtual int  ExitInstance();
	virtual bool OnIdle(LONG lCount);
	virtual int Run();
	virtual bool PreTranslateMessage(MSG *pMsg); //renturn true pass
private:

};

