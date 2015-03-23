//定义对象间的一种一对多的依赖关系，以便当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并自动更新。
#pragma once
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class ISub
{
public:
	void DoWork2()
	{
		std::cout<<"s2"<<std::endl;
	}
	virtual void DoWork()
	{
		std::cout<<"s1"<<std::endl;
	}
	virtual ~ISub(){};
};

class Subscibea:public ISub
{
public:
	virtual void DoWork()
	{
		std::cout<<"a"<<std::endl;
	}
};
class Subscibeb:public ISub
{
public:
	virtual void DoWork()
	{
		std::cout<<"b"<<std::endl;
	}
};

class  Subject
{
public:
	virtual void RegistSub(ISub* sub)=0;
	virtual void Action()=0;
protected:
	vector<ISub*> sublist;
};

class BookSubject:public Subject
{
public:
	void RegistSub(ISub* sub)
	{
		sublist.push_back(sub);
	}
	void Action()
	{
		for(vector<ISub*>::const_iterator iter=this->sublist.begin();iter!=this->sublist.end();++iter)
		{
			(**iter).DoWork();
		}
	}
};

void TestObserver()
{
	Subject* subject=new BookSubject();
	Subscibea a;
	Subscibeb b;
	
	typedef void (ISub::*work)();
	work w=&ISub::DoWork;
	ISub* sub=&a;
	/*(sub->*w)();*/
	((*sub).*w)(); 

	//subject->RegistSub(&a);
	//subject->RegistSub(&b);
	//subject->Action();
}
