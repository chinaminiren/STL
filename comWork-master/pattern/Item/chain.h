#pragma once
//职责链模式
//使多个对象都有机会处理请求，从而避免请求的发送者 和接收者之间的耦合关系
//将这些对象连成链，并沿着这个链传递该请求，直到该请求被处理为止

// 将有效 剔除代码中的 if elseif  语句

// 表驱动对比

#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <Windows.h>
#include <string>
//#include <winsock.h>

using namespace std;

class Handler
{
public:
	virtual void Request()=0;
private:
	Handler* nextHander;
};

class AHandler:public Handler
{
public:
	virtual void Request()
	{
		//
	}
};

class BHandler:public Handler
{
public:
	virtual void Request()
	{
		//
	}
};
void TestChain()
{
	//
}


