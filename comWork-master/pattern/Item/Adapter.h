#pragma once

#include <iostream>
#include <string>

using namespace std;

//对已有的接口进行 封装 调整 达到 客户的要求
// 比如 用户需要实现一个 栈...而目前接口只有 数组
//需要用 数组模拟一个 堆栈
//对象适配器
//类适配器

class Array
{
public:
	void Add(string str)
	{
		//
	}
	void Get(int key)
	{
		//
	}
};

class StackAdapter  //也可以用继承实现
{
public:
	void Pop(){}
	void Push(){}
private:
	Array array;
};

void TestAdapter()
{
	//
	StackAdapter sa;
}