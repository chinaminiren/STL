#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
/*
 Iterator（迭代器）模式又称Cursor（游标）模式，用于提供一种方法顺序访问一个聚合对象中各个元素, 
 而又不需暴露该对象的内部表示。或者这样说可能更容易理解：Iterator模式是运用于聚合对象的一种模式，
 通过运用该模式，使得我们可以在不知道对象内部表示的情况下，按照一定顺序（由iterator提供的方法）访问聚合对象中的各个元素。

 提供一种方法顺序访问一个聚合对象中各个元素，而又不暴露该对象的内部表示。当你需要访问一个聚集对象，
 而且不管这些对象是什么都需要遍历的时候，就应该考虑用迭代器模式。同时需要对聚集有多种方式遍历时，
 可以考虑用迭代器模式。为遍历不同的聚集结构提供如开始、下一个、是否结束、当前哪一项等统一接口。
 迭代器模式就是分离了集合对象的遍历行为，抽象出一个迭代器类来负责，这样既可以做到不暴露集合的内部结构，
 又可让外部代码透明地访问集合内部的数据。
 */
using namespace std;

class IIterator
{
public:
	virtual ~IIterator(){}
	virtual void First()=0;
	virtual void Next()=0;
	virtual bool IsEOF()=0;
	virtual int CurrentItem()=0;
};
class BookAggregate;

class Iterator:public IIterator
{
public:
	Iterator(BookAggregate* mag)
	{
		this->ag=mag;
	}
	virtual void First()
	{
		this->i=0;
	}
	virtual void Next()
	{
		++i;
	}
	virtual bool IsEOF()
	{
		return false;
	}
	virtual int CurrentItem()
	{
		return 1;
	}
private:
	BookAggregate* ag;
	int i;
};

class Aggregate
{
public:
	virtual IIterator* CreateIterator()=0;
};
class BookAggregate:public Aggregate
{
public:
	virtual IIterator* CreateIterator()
	{
		return new Iterator(this);
	}
private:
	vector<int> vec;
};

class IteratorPtr
{
public:
	IteratorPtr(IIterator* iter)
	{
		this->miter=iter;
	}
	~IteratorPtr()
	{
		delete miter;
	}

	IIterator* operator->()
	{
		return miter;
	}
	IIterator& operator*()
	{
		return *miter;
	}
private:
	IIterator* miter;
	//TODO:STL 中的迭代器 支持 复制相关
	//
	IteratorPtr(const IteratorPtr&); 
	IteratorPtr& operator=(const IteratorPtr&);
};



void TestIterator()
{
	Aggregate* ba=new BookAggregate();
	IIterator* iter=ba->CreateIterator();
	IteratorPtr ptr(iter);
}