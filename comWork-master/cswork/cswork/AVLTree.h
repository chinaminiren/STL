#pragma once

template<typename Type> //--copy constructor
struct Node
{
	Node(Node* pLeft, Node* pRight, Type Value):
		_pLeft(pLeft),
		_pRight(pRight),
		_Value(Value),
		_heigh(0)
	{

	}

	Node* _pLeft;
	Node* _pRight;
	Type  _Value;
	int _heigh;
};

template<typename Type>  //--其实 目前没有卫星数据 key == value
class AVLTree
{
public:
	AVLTree():root(NULL)
	{

	}
	~AVLTree()
	{

	}

	void Insert(const Type& keyValue)
	{

	}

	Type& Search(const Type& key)
	{

	}

	void DeleteNode(const Type& key)
	{

	}

private:


private:
	Node<Type>* root;
};