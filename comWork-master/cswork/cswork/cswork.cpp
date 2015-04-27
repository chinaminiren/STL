// cswork.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include "RHash.h"
#include "AVLTree.h"
#include "RBTree.h"
#include "OSTree.h"

//--LeetCode
#include "TwoSum.h"

//--end LeetCode
#include <vector>

using namespace std;

//需要做的 工作:http://www.csdn.net/article/2011-05-06/297285


int myAtoi(string str) {
	if (str.size() == 0)
		return 0;
	int res = 0;
	int flag = 1;
	bool begin = false;
	for (int i = 0; i<str.size(); ++i)
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == ' ')
		{
			if (begin)
				break;
			if (str[i] == ' ')
				continue;

			if (str[i] == '+' || str[i] == '-')
			{
				begin = true;
				flag = str[i] == '+' ? 1 : -1;
				continue;
			}

		}

		if (str[i] >= 48 && str[i] <= 57)
		{
			begin = true;
			if (res > INT_MAX / 10)
			{
				return INT_MAX;
			}
			int t = str[i] - 48;
			res = res * 10 + t;
		}
		else
		{
			break;
		}



	}

	return res * flag;

}

int _tmain(int argc, _TCHAR* argv[])
{


	system("pause");

	return 0;
}

