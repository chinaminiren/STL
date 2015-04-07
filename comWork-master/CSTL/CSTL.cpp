// CSTL.cpp : Defines the entry point for the console application.
//
//C++11 C++ �������� ���ѧϰ

#include "stdafx.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

//C++ �ڴ�������

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
	void* operator new(std::size_t,void* ptr)
	{
		std::cout << "operator new" << std::endl;
		return ptr;
	}

    //*************************************************************************************************
	//��׼ operator delete 
	// �ڶ������� std::size_t size  //û��ȫ�ֵ�˫�ΰ汾
	void operator delete(void* ptr, std::size_t size) // delete p ��������� 
	{
		std::cout << "operator delete (void* ptr, std::size_t size)" << std::endl; //Ϊʲô���������
	}

	void operator delete(void* p)
	{
		std::cout << "operator delete (void* p)" << std::endl; // Ϊʲô���������
	}
	//*************************************************************************************************

	void operator delete(void*, void*) //�������Զ���� operator new ��ͬ
	{
		//ֻ�е� ��Ӧ�� operator new ʧ�ܲű�����
	}

private:
	int m_ia;
};

//��׼�棺
//void * operator new (std::size_t size) throw (std::bad_alloc);
//void operator delete (void * pMemory��td::size_t size) throw();
typedef char* newType;

newType MyFunction()
{
	char* p = "asd";

	return p;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//Ԥ��
	size_t sz = sizeof(std::string);
	std::string str("���");
	sz = sizeof(str);
	std::allocator<std::string> strAlloc;
	std::string* ptr = strAlloc.allocate(2);
	new (ptr)std::string("123");
	strAlloc.construct(ptr + 1, "456");

	//trAlloc.allocate.address();

	//
	int memoryPtr[30];
	MemoryTest* pTest = new(memoryPtr)MemoryTest(10);
	
	delete pTest;//������ȫ����ʽ�� operator delete  ���Ե��� operator delete 

	//���� ���
	int* pArray = new int [10];
	unsigned long a = 10;
	unsigned long b = 10;
	std::swap(a, b);
	//--typedef ���

	return 0;
}


