#pragma once
//组合模式
//将对象组合成 树的形式以表示 “部分 整体”的层次结构。
//该模式使得用户对单个对象和组合对象的使用具有一致性。
//

#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Component
{
public:
	virtual void Operator() = 0;

	virtual void Add(int key,Component*){}
	virtual void Remove(int key){}
	virtual Component* GetChild(int index){return NULL;}
	~Component(){};
};
class Leaf:public Component
{
public:
	virtual void Operator()
	{
		cout<<"Leaf Operator"<<endl;
	}
};
class Compsite:public Component
{
public:
	void  Add(int key,Component* item)
	{
		map<int,Component*>::iterator iter= this->m_ComMap.find(key);
		if(iter!=this->m_ComMap.end())
		{	
			make_pair(key,item); //
			this->m_ComMap.insert(std::make_pair<int&,Component* &>(key,item));
		}
	}
	void Remove(int index)
	{
	    map<int,Component*>::iterator iter= this->m_ComMap.find(index);
		if(iter!=this->m_ComMap.end())
		{
			this->m_ComMap.erase(iter);
		}
	}
	Component* GetChild(int index)
	{
		map<int,Component*>::iterator iter= this->m_ComMap.find(index);
		if(iter!=this->m_ComMap.end())
			return iter->second;
		else
			return NULL;
	}
private:
	map<int,Component*> m_ComMap;
};


void TestComposite()
{
	//
}