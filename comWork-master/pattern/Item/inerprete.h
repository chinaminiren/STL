#pragma once
//解释器模式
//定义一个语言，定义它的文法的一种表示，并定义一个解释器，
//这个解释器使用该种表示来解释语言中的句子

#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <Windows.h>
#include <string>

using namespace std;

class Context; //包含解释器之外的全局信息

class Expression
{
public:
	 virtual void Interprete(Context*)=0;
};

class TerminalExpression:public Expression
{
public:
	virtual void Interprete(Context* ptr)
	{

	}
};

class NonATerminalExpression:public Expression
{
public:
	virtual void Interprete(Context* ptr)
	{
		//
	}
};

class NonBTerminalExpression:public Expression
{
public:
	virtual void Interprete(Context* ptr)
	{
       //
	}
};

void TestInterprete()
{

}
