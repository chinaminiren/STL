#pragma once
#include <memory>

using namespace std;
//定义一个用于创建对象的接口，让子类决定实例化哪一个类，工厂方法使一个类的实例化延迟到其子类
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
class IFactory
{
public:
	virtual Food* CreateFood()=0;    
};
class  FuitFactory:public IFactory
{
public:
	virtual Food* CreateFood(){
	  Food* ptr=new FuitFood();
	  return ptr;
   }
};
class  GreensFactory:public IFactory
{
public:
	virtual Food* CreateFood()
	{
		Food* ptr=new GreensFood();
		return ptr;
	}
};


void TestFactory()
{
	IFactory* fac=new FuitFactory();
	Food* ptr=fac->CreateFood();

	std::auto_ptr<IFactory>(fac);
	std::auto_ptr<Food>(ptr);
}