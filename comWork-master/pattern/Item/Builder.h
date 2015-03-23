
//建造者模式：将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。
//建造者模式关注的是的零件类型和装配工艺（顺序）
//生成器模式
//模板方法模式
#pragma once
//OS SDK .h , C标准库、C++标准库、其它库的头文件、你自己工程的头文件。
#include <iostream>

class Product
{
public:
	void MakeA(){}
	void MakeB(){}
	void MakeC(){}
	void MakeD(){}
};

class IBuilder
{
public:
	virtual void Init(){
		this->product=new Product();
	}
	virtual void MakeA()=0;
	virtual void MakeB()=0;
	virtual void MakeC()=0;
	virtual void MakeD()=0;
	virtual Product* GetProduct()=0;
protected:
	Product* product;
};
class Builder:public IBuilder
{
public:
	virtual void MakeA()
	{
		this->product->MakeA();
	}
	virtual void MakeB()
	{
		this->product->MakeB();
	}
	virtual void MakeC()
	{
		this->product->MakeC();
	}
	virtual void MakeD()
	{
		this->product->MakeD();
	}
	virtual Product* GetProduct()
	{
		return this->product;
	}
};

class  Director
{
public:
	Product* Construct(IBuilder* builer)
	{
		builer->Init();
		builer->MakeA();
		builer->MakeB();
		builer->MakeC();
		builer->MakeD();
		return builer->GetProduct();
	}
};

void TestBuilder()
{
	Director director;
	Builder builder;
	Product* ptr=director.Construct(&builder);
	Product* ptr2=director.Construct(&builder);
}
