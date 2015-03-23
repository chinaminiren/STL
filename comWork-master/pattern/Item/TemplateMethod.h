//模板方法 是由抽象类定义一个算法的骨架，而后由子类来具体实现算法中的逻辑。
//策略模式的话，是封装了可以相互替换的多个行为（也就是算法），然后便可以在客户端动态决定采用那一种行为。

#include <iostream>

using namespace std;

class BaseTemplate
{
public:
	void DoWork()
	{
		this->WorkA();
		this->WorkB();
	}
protected:
	virtual void WorkA()=0;
	virtual void WorkB()=0;
};
class Cream:public BaseTemplate
{
protected:
	virtual void WorkA();
	virtual void WorkB();
};
void Cream::WorkA()
{
	std::cout<<"workA Cream"<<endl;
}
void Cream::WorkB()
{
	std::cout<<"workB Cream"<<endl;
}

void TestTemplateMethod()
{
	BaseTemplate* ptr=new Cream();
	ptr->DoWork();
}
