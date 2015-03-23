//针对一组算法，将每一个算法封装到具有共同接口的独立的类中，从而使得它们可以相互替换。
#include "stddef.h"
#include <iostream>
#include <memory>

using namespace std;

class  Strategy
{
public:
	virtual void Work()=0;
	virtual ~Strategy(){}
};
class SkyStategy:public Strategy
{
public:
	virtual void Work()
	{
		std::cout<<"Strategy Sky"<<endl;
	}
	virtual ~SkyStategy()
	{
		std::cout<<"realse Strategy Sky"<<endl;
	}
};
class SeaStategy:public Strategy
{
public:
	virtual void Work()
	{
		std::cout<<"Strategy Sea"<<endl;
	}
	virtual ~SeaStategy()
	{
		std::cout<<"realse Strategy Sea"<<endl;
	}
};

class ConcreteStrategy
{
public:
	ConcreteStrategy(Strategy* mptr):stratepy(mptr)
	{

	}
	void Work()
	{
		this->stratepy->Work();
	}   
private:
	tr1::shared_ptr<Strategy> stratepy;
};

void TestStrategy()
{
	ConcreteStrategy strategy(new SeaStategy());
	strategy.Work();
}

