#pragma once
#include <iostream>
using namespace std;

//保证一个类仅有一个实例，并提供一个访问它的全局访问点
class Single
{
public:
	static Single* GetInstance();
	//添加其它业务接口
private:
	static Single* obj;
	~Single()
	{
		std::cout<<"Release Single"<<std::endl;
	}
	 Single(const Single&);
	 Single(){}
	 Single& operator=(const Single&);
	 class internalSingle
	 {	
	 public:
		 internalSingle()
		 {
			 std::cout<<"Create Single"<<std::endl;
		 }
		~internalSingle()
		{			
			delete obj;
		}
	 };
	 static internalSingle deleteobj;
};
Single::internalSingle Single::deleteobj;
Single* Single::obj=new Single();
Single* Single::GetInstance()
{
	return obj;
}
void TestSingle()
{
	//
}