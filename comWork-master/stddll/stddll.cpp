// stddll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DayTest.h"
#include <iostream>

__declspec(dllexport) void DllTest()
{
	std::cout << CDayTest<int>::a << std::endl;
}


