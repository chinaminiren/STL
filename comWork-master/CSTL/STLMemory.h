#include "stdafx.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

//C++ 内存管理相关

class MemoryTest
{
public:
	MemoryTest(int a) :m_ia(a)
	{
		std::cout << "MemoryTest()" << std::endl;
	}
	~MemoryTest()
	{
		std::cout << "~MemoryTest()" << std::endl;
	}

public:
	void* operator new(std::size_t, void* ptr)
	{
		std::cout << "operator new" << std::endl;
		return ptr;
	}

		//*************************************************************************************************
		//标准 operator delete 
		// 第二个参数 std::size_t size  //没有全局的双参版本
		void operator delete(void* ptr, std::size_t size) // delete p 将调用这个 
	{
		std::cout << "operator delete (void* ptr, std::size_t size)" << std::endl; //为什么调用这个？
	}

	void operator delete(void* p)
	{
		std::cout << "operator delete (void* p)" << std::endl; // 为什么调用这个？
	}
	//*************************************************************************************************

	void operator delete(void*, void*) //参数与自定义的 operator new 相同
	{
		//只有当 对应的 operator new 失败才被调用
	}

private:
	int m_ia;
};

//标准版：
//void * operator new (std::size_t size) throw (std::bad_alloc);
//void operator delete (void * pMemory，td::size_t size) throw();
typedef char* newType;

newType MyFunction()
{
	char* p = "asd";

	return p;
}

int TestMemory()
{
	//预热
	size_t sz = sizeof(std::string);
	std::string str("你好");
	sz = sizeof(str);
	std::allocator<std::string> strAlloc;
	std::string* ptr = strAlloc.allocate(2);
	new (ptr)std::string("123");
	strAlloc.construct(ptr + 1, "456");

	//trAlloc.allocate.address();

	//
	int memoryPtr[30];
	MemoryTest* pTest = new(memoryPtr)MemoryTest(10);

	delete pTest;//将调用全局形式的 operator delete  测试调用 operator delete 

	//数组 相关
	int* pArray = new int[10];
	unsigned long a = 10;
	unsigned long b = 10;
	std::swap(a, b);
	//--typedef 相关

	return 0;
}