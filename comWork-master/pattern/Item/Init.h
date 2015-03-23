#pragma once 

#include <iostream>
//C++ 初始化规则
//TODO:搞不明白..........
using namespace std;

class data
{
public:
	data()
	{
		cout<<"data"<<endl;
	}
	void PP()
	{
		cout<<"pp"<<endl;
	}
};

class BaseT
{
public:
	BaseT(data* ptr):da(ptr)
	{
		cout<<"BaseT"<<endl;
		ptr[0].PP();
	}
	virtual ~BaseT(){}
private:
	data* da;
};

class Drive:public BaseT
{
public:
	Drive():BaseT(da)
	{
		cout<<"Drive"<<endl;
	}
    ~Drive(){}
private:
	data da[1];
};

void TestInit()
{
	Drive* ptr=new Drive();
	int a=100;
}