#pragma once
//抽象工厂 抽象工厂：提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
//当你发现，有一个接口可以有多种实现的时候，可以考虑使用工厂方法来创建实例。
//当你返现，有一组接口可以有多种实现方案的时候，可以考虑使用抽象工厂创建实例组。
#pragma once
#include <memory>
#include <iostream>

using namespace std;

class  Food
{
public:
	virtual void DoWork()=0;
};
class FuitFood:public Food
{
public:
	virtual void DoWork()
	{

	}
};
class GreensFood:public Food
{
public:
	virtual void DoWork()
	{

	}
};

class Car
{
public:
	virtual void Run()=0;
};
class Ford:public Car
{
public:
	virtual void Run()
	{
		
	}

};
class GMC:public Car
{
public:
	virtual void Run()
	{

	}
};

class IFactory
{
public:
	virtual Food* CreateFood()=0; 
	virtual Car* CreateCar()=0;
};
class FactoryA:public IFactory
{
public:
	virtual Food* CreateFood()
	{
	  Food* ptr=new FuitFood();
	  return ptr;
    }
	virtual Car* CreateCar()
	{
		return new Ford();
	}
};
class  FactoryB:public IFactory
{
public:
	virtual Food* CreateFood()
	{
	  Food* ptr=new FuitFood();
	  return ptr;
    }
		virtual Car* CreateCar()
	{
		return new Ford();
	}
};

void TestAbstactFactory()
{
	//抽象工厂：
	//
}