#include "stdafx.h"
#include "DayTest.h"
#include <iostream>

void ChangeB()
{
	CDayTest < int>::a = 200;
	std::cout << CDayTest<int>::a << std::endl;
}

