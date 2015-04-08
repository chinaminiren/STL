// CSTL.cpp : Defines the entry point for the console application.
//
//C++11 C++ 基本技能 相关学习

#include "stdafx.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

extern void TestB();
extern void TestA();
extern void ChangeA();
extern void ChangeB();

__declspec(dllimport) void DllTest();

#pragma comment(lib,"stddll.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	 ChangeA();
	 ChangeB();

	 DllTest();
	
	int a;
	std::cin >> a;
	return 0;
}


