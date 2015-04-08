#include "stdafx.h"
#include "DayTest.h"
#include <iostream>

void ChangeA()
{
	CDayTest < int>::a = 100;
	std::cout << CDayTest<int>::a << std::endl;
}

void TestA()
{
	std::cout << CDayTest<int>::a << std::endl;
}