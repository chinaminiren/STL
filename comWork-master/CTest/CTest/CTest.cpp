// CTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>

#include <functional>
#include <memory>

//设计模式
//#include "Pattern\Prototype.h"
//#include "Pattern\Single.h"
//#include "Pattern\Factory.h"
//#include "Pattern\abstractFactory.h"
//#include "Builder.h"
//#include "TemplateMethod.h"
//#include "Strategy.h"
//#include "Command.h"	
//#include "Observer.h"
//#include "Iterator.h"
//#include "Mediator.h"
//#include "visitor.h"
//#include "State.h"
//#include "memento.h"
//#include "FlyWeight.h"
//#include "Composite.h"

//面向对象
//#include "Init.h"

#include <string>
using namespace std;

string ChangeChar(char* src)
{
	string str(src);
	if(str.length()>=12)
	{
		return	str.replace(8,4,"****");
	}
	return str;
}
char* Change(char* src)
{
	rsize_t length=strlen(src)+1;
	char* newstr=new char[length];
	strcpy_s(newstr,length,src);
	if(length>=12)
	{
		for(int i=0;i<length-1;++i)
		{
			if(i>=8&&i<=11)
				newstr[i]='*';
		}
	}
	return newstr;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char* cstr="111111111111111";
	char* dest= Change(cstr);
	delete dest;
	return 0;
}

