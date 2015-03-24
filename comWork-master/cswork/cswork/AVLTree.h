#pragma once
#include <iostream>

template<typename Type>  //--其实 目前没有卫星数据 key == value
class AVLTree
{
private:
	struct Node
	{
		Node(Node* pLeft, Node* pRight, const Type& Value) : //-- copy constructor
			_pLeft(pLeft),									 //-- operaotr <  or less
			_pRight(pRight),
			_Value(Value),
			_heigh(0)
		{

		}

		~Node()
		{
			if (_pLeft)
				delete _pLeft;
			_pLeft = NULL;

			if (_pRight)
				delete _pRight;
			_pRight = NULL;
		}

		Node* _pLeft;
		Node* _pRight;
		Type  _Value; //-- stream 可以流输出
		int _heigh;
	};
public:
	AVLTree():root(NULL)
	{

	}
	~AVLTree()
	{
		delete root;
	}

	void PrintAVLTree(Node* pNode) //-- 中序遍历
	{
		if (pNode)
		{
			PrintAVLTree(pNode->_pLeft);
			std::cout << pNode->_Value << " ";
			PrintAVLTree(pNode->_pRight);
		}
	}

	//--
	void Insert(const Type& keyValue)
	{
		Node* nodeItem = new Node(NULL, NULL, keyValue);

		if (root == NULL)
		{ 
			root = nodeItem;
		}
		else
		{
			
			Node* pCurNode = root;
			while (pCurNode)
			{
				if (pCurNode->_Value > keyValue) //-- left
				{
					if (pCurNode->_pLeft == NULL)
					{
						pCurNode->_pLeft = nodeItem;
						break;//end
					}
					else
					{
						pCurNode = pCurNode->_pLeft;
					}
				}
				else
				{
				   //--right
					if (pCurNode->_pRight == NULL)
					{
						pCurNode->_pRight = nodeItem;
						break;//end
					}
					else
					{
						pCurNode = pCurNode->_pRight;
					}
				}
			}
			//reAVL

		}
	}

	Type* Search(const Type& key)
	{
		Type* pItem = NULL;

		Node* pCurNode = root;
		while (pCurNode)
		{
			if (pCurNode->_Value == key) //-- key == value
			{
				pItem = &(pCurNode->_Value);
			}
			else if (pCurNode->_Value < key)
			{
				pCurNode = pCurNode->_pRight;
			}
			else
			{
				pCurNode = pCurNode->_pLeft;
			}
		}

		return pItem;
	}

	void DeleteNode(const Type& key)
	{
		Node* pCurNode = root;
		while (pCurNode)
		{
			if (pCurNode->_Value == key) //-- key == value
			{
				//delete node
				break;
			}
			else if (pCurNode->_Value < key)
			{
				pCurNode = pCurNode->_pRight;
			}
			else
			{
				pCurNode = pCurNode->_pLeft;
			}
		}
	}
	//--
private:
	int GetHeigh(Node* pNode)
	{
		int heigh = 0;
		

		return heigh;
	}

public:
	Node* root;
};