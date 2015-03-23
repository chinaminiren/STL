#pragma once
#include <string>
#include <iostream>
#include <memory>

//代理模式
//
//对一个对象进行访问控制
//比如延迟加载一个对象
using namespace std;

class Work
{
public:
	void Do()
	{
		//
	}
};

void TestProxy()
{
	weak_ptr<Work> ptr(make_shared<Work>(new Work()));
}