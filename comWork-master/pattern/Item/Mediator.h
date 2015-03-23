#pragma once
/*
中介者模式
*/
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#include <map>
#include <algorithm>

using namespace std;

class Mediator;
class Colleague;

class Colleague
{
public:
	Colleague(string key,Mediator* ptr)
	{
		this->key=key;
		this->me=ptr;		
	}
	virtual void Exec(string arg)=0;
	virtual ~Colleague()
	{

	}
protected:
	Mediator* me;
	string key;
};

class Mediator
{
public:
    void DoWork(string workType,string arg)
	{
        map<string,Colleague*>::const_iterator iter= this->mmap.find(workType);
		if(iter!=mmap.end())
		{
			iter->second->Exec(arg);
		}
	}
	void AddColleague(string key,Colleague* ptr)
	{
		map<string,Colleague*>::const_iterator iter= this->mmap.find(key);
		if(iter==mmap.end())
		{
			mmap.insert(map<string,Colleague*>::value_type(key,ptr));
		}
	}
	void RemoveColleague(string key)
	{	
		map<string,Colleague*>::const_iterator iter= this->mmap.find(key);
		if(iter!=mmap.end())
		   iter= this->mmap.erase(iter);//
	}
private:
	map<string,Colleague*> mmap;
};

class ColleagueA:public Colleague
{
public:
	ColleagueA(string key,Mediator* ptr):Colleague(key,ptr)
	{
		this->me->AddColleague(key,this);
	}
	virtual void Exec(string arg)
	{
		cout<<arg<<endl;
	}
	void DoSomething(string c,string arg)
	{
		//
		this->me->DoWork(c,arg);
	}
	virtual ~ColleagueA()
	{
		this->me->RemoveColleague(key);
	}
};
class ColleagueB:public Colleague
{ 
public:
	ColleagueB(string key,Mediator* ptr):Colleague(key,ptr)
	{
		this->me->AddColleague(key,this);
	}
	virtual void Exec(string arg)
	{
		cout<<"接收的消息："<<arg<<endl;
	}
	void DoSomething()
	{
		//
	}
	virtual ~ColleagueB()
	{
		this->me->RemoveColleague(key);
	}
};
class ColleagueC:public Colleague
{ 
public:
	ColleagueC(string key,Mediator* ptr):Colleague(key,ptr)
	{
		this->me->AddColleague(key,this);
	}
	virtual void Exec(string arg)
	{
		cout<<arg<<endl;
	}
	void DoSomething()
	{
		//
	}
	virtual ~ColleagueC()
	{
		this->me->RemoveColleague(key);
	}
};

void TestMediator()
{
	// a b c 相当于契约
	Mediator* me=new Mediator();
	ColleagueA* a=new ColleagueA("a",me);
	ColleagueB* b=new ColleagueB("b",me);
	delete b;
	a->DoSomething("b","我想和B交流");
}