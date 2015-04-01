// DrawTest.cpp : implementation file
//

#include "stdafx.h"
#include "mfcPlay.h"
#include "DrawTest.h"
#include "afxdialogex.h"


// DrawTest dialog

IMPLEMENT_DYNAMIC(DrawTest, CDialogEx)

DrawTest::DrawTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(DrawTest::IDD, pParent)
{

}

DrawTest::~DrawTest()
{
}

void DrawTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DrawTest, CDialogEx)
END_MESSAGE_MAP()


// DrawTest message handlers
