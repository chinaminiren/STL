#pragma once
#include <string>
#include <iostream>
#include <memory>

//装饰模式
//在不改变给已有接口的情况下动态的扩展 一个对象的功能
//装饰对象 包含一个真实对象的引用
//装饰对象接受所有来自客户端的请求。把这些请求转发给真实的对象
//装饰对象可以转发这些请求 以前或者以后增加一些附近功能。这样就确保在运行时，
//不用修改给定对象的结构就可以在外部增加附加的功能。
// AOP
//装饰 继承 比较
//
//我们可以通过继承的方式来给原对象增加新功能，但是装饰者模式采用组合的方式比生成子类更加灵活。
using namespace std;

class Tank
{
public:
	void Run()
	{
		cout<<"run"<<endl;
	}
};

class Decorator
{
public:
	void Run()
	{
		//add other 
		tank.Run();
		//add other
	}
private:
	void Add()
	{
		cout<<"add other"<<endl;
	}
private:
	Tank tank;
};
void TestDecorator()
{
	Decorator tank;
	tank.Run();
}