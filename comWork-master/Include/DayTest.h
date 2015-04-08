#pragma once

template<typename T>
class CDayTest
{
public:
	CDayTest();
	~CDayTest();

public:
	static T a;
};

template<typename T>
T CDayTest<T>::a;

template<typename T>
CDayTest<T>::CDayTest()
{
}


template<typename T>
CDayTest<T>::~CDayTest()
{
}

class StaticTest
{
public:
	static int a;
};
