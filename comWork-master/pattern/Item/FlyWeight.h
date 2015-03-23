
#pragma once
//享元模式
// 缓存 共享可以 共享的对象 属性 避免创建大量的 重复的对象


//避免 大量拥有相同内容的小类的开销 大家共享一个类
// 找出这些对象群 的共同点 设计一个元类 封装可以共享的类 
//另外 还有一些特性是取决于应用 context 是不可以共享 
//flyWeight 2个重要概念 内部状态  外部状态
#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

class Flyweight //引用计数 和 垃圾回收
{
public:
	Flyweight(string str)
	{

	}
	virtual void Operator(string str)=0; //str 外部状态
private:
	string mstr;
};
class CFlyweight:public Flyweight
{
public:
	CFlyweight(string str):Flyweight(str)
	{
	}
	virtual void Operator(string str)
	{
		//
		//根据传入的外部状态 进行相关操作
		//比如 显示 打印输出 等等
		cout<<str<<endl;
	}
};
class UFlyweight:public Flyweight
{
public:
	UFlyweight(string str):Flyweight(str)
	{

	}
	virtual void Operator(string)
	{

	}
private:
	//保存全部状态 //没法共享 //Clent 可以直接引用
};
class FlyweightFactory
{
public:
	static Flyweight* CreateFlyweight(string str)
	{
		Flyweight* ptr=NULL;
		map<string,Flyweight*>::iterator iter =cmap.find(str);
		if(iter==cmap.end())
			cmap[str]=new CFlyweight(str);
		ptr=cmap[str];
		return ptr;
	}

	~FlyweightFactory()
	{
		for(map<string,Flyweight*>::const_iterator iter=cmap.begin();iter!=cmap.end();++iter)
		{
			delete iter->second;
		}
	}
private:
	static map<string,Flyweight*> cmap;
};
map<string,Flyweight*> FlyweightFactory::cmap;

void TestFlyWeight()
{
	Flyweight* ptra=FlyweightFactory::CreateFlyweight("a");
	ptra->Operator("外部状态");
	Flyweight* ptrb=FlyweightFactory::CreateFlyweight("a");
}
