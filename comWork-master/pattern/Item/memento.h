#pragma once
//在不破坏封装的前提下 捕获一个对象的内部状态，并在该对象之外保存这个状态。
//这样以后就可将该对象恢复到原先保存的状态
//在可做到的编程语言中，备忘录模式提供了一种在维持对象状态的同时维持封装性的方法。
//应该只有发起者类对其他有访问权限的数据就有效的保持了其私有性。
//该模式还通过把信息的保存和还原委托给某个备忘录类而维持了发起者的简单性。
//但是备忘录模式有时候也可能因为要保存的信息量非常大，会占用相当多的存储空间，影响系统的运行效率。
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <Windows.h>
#include <string>
#include <winsock.h>

using namespace std;

class Data;

class Memento
{
public:

private:
	Memento(){};
	friend class Object;
	void SetData(Data* mda){da=mda;}
	Data* GetData(){return da;}
private:
	Data* da;
};

class Object
{
public:
	Memento* Create()
	{
		return new Memento(); //保存状态
	}
	void SetMemento(Memento* men)
	{
		da=men->GetData();
	}
private:
	Data* da;
};

class Catetaker
{
public:
	void SaveMemento(Memento* pt)
	{
		//保存 
	}

	Memento* Get()
	{
		return pt;
	}
private:
Memento* pt;//如何保存 与索引？？？ Hash
};

void TestMemento()
{
	Catetaker ct;
	Object obj; //
	//----操作
	//
	ct.SaveMemento(obj.Create());
	//其它操作
	//
	//恢复...
	obj.SetMemento(ct.Get());
	//
}
