#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <new>

using namespace std;
//访问者 模式
//就是表示一个作用于某对象结构中的各元素的操作，它使你可以在不改变各元素的类的前提下定义作用于这些元素的新操作。
class Visitor;

class Item //作为接口 让 具体类 实现该接口
{
public:
	virtual void Accept(Visitor&)=0;
};

class Visitor
{
public:
	virtual void vis(ItemA&)=0;
	virtual void vis(ItemB&)=0;
};

class ItemA:public Item
{
private:
	virtual void Accept(Visitor& vs)
	{
		vs.vis(*this);
	}
};
class ItemB:Item
{
public:
	virtual void Accept(Visitor& vs)
	{
		vs.vis(*this);
	}
};

class ConVisitor
{
public:
    virtual void vis(ItemA&)
	{
		string str("自定义 访问A 元素的操作");
		cout<<str<<endl;
	}
	virtual void vis(ItemB&)
	{
		string str("自定义 访问B 元素的操作");
		cout<<str<<endl;
	}
};

void TestVisitor()
{
   
}