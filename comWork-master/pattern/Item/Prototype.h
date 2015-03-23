#pragma once
//OS SDK .h , C标准库、C++标准库、其它库的头文件、你自己工程的头文件。
#include <iostream>

using namespace std;

class AutoPrototype
{
public:
	virtual AutoPrototype* Clone() const =0;  // =0 仅对虚函数有用 const 函数重载 标记函数签名
};

class BPrototype:public AutoPrototype
{
public:
	AutoPrototype* Clone() const;
};

AutoPrototype* BPrototype::Clone() const
{
	//左操作数具有有操作数所指向类型的全部限定符（右操作数没有限定符），同时自己有限定符（const）
	// 1. 两个操作数都是指向有限定符或无限定符的相容类型的指针。
    // 2. 左边指针所指向的类型必须具有右边指针所指向类型的全部限定符。
	//C++标准规定，const关键字放在类型或变量名之前等价的。
    const int n=5; //same as below
    int const m=10;
	//const char* p=NULL; // p 为指向 常量的 非常量指针

	char str[]="abc";
	//******************************
	const char* p=str;//p为指向 char 类型的 非常量指针
	const char**pp=&p; //pp 指向 const char* 的非常量指针  是错误的 因为指向的数据类型已经不一样了 const 标记
	//******************************

	char* ptr=str;
	char** const pp2=&ptr;
	//******************************
	char* const ptr2=str;
	const char* const* pp3=&ptr2;
	char* const* pp4=&ptr2;
	//******************************
	const char* ptr3=str;
	const char** const pp5=&ptr3;
	//******************************
	const char* const ptr4=str;
	const char* const* const pp6=&ptr4;
	//******************************
	char* const ptr5=str;
	char* const* const pp7=&ptr5;
	//*****************************
    const char* ptr6=str;
	const char** pp8=&ptr6;

	BPrototype* pt= new BPrototype(*this); //运用复制构造函数
	return pt;
}
//原型模式：
