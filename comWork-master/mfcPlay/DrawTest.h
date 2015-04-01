#pragma once


// DrawTest dialog

class DrawTest : public CDialogEx
{
	DECLARE_DYNAMIC(DrawTest)

public:
	DrawTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~DrawTest();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
