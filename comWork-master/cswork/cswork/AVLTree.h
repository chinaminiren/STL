#pragma once
#include <iostream>

//参考:http://kukuruku.co/hub/cpp/avl-trees
//求树的最大高度
//树的一些其它属性值相关

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
			_heigh(1)
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

	void Print()
	{
		this->PrintAVLTree(this->root);
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

	//--rotate
	unsigned int height(Node* p)
	{
		return p ? p->_heigh : 0;
	}

	int bfactor(Node* p)
	{
		return height(p->_pLeft) - height(p->_pRight);
	}

	void fixHeight(Node* p)
	{
		unsigned int hl = height(p->_pLeft);
		unsigned int hr = height(p->_pRight);
		p->_heigh = (hl > hr ? hl : hr) + 1;
		
	}
	Node* RigthRotate(Node* p)
	{
		Node* q = p->_pLeft;
		p->_pLeft = q->_pRight;
		q->_pRight = p;

		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node* LeftRotate(Node* q)
	{
		Node* p = q->_pRight;
		q->_pRight = p->_pLeft;
		p->_pLeft = q;

		fixHeight(q);
		fixHeight(p);
		return p;
	}

	Node* banlance(Node* p)
	{
		fixHeight(p);
		if (bfactor(p) == 2)  //left > right
		{
			if (bfactor(p->_pLeft) < 0)
				p->_pLeft = LeftRotate(p->_pLeft);
			return RigthRotate(p);
		}

		if (bfactor(p) == -2) //right > left
		{
			if (bfactor(p->_pRight) > 0)
				p->_pRight = RigthRotate(p->_pRight);
			return LeftRotate(p);
		}
        
		return p;
	}

	//--
	void InsertNode(const Type& keyValue)
	{
		this->root = Insert(this->root, keyValue);
	}

	Node* Insert(Node* nodeItem, const Type& keyValue)
	{
		if (nodeItem == NULL)
		{
			return new Node(NULL, NULL, keyValue);
		}

		if (nodeItem->_Value > keyValue)
		{
			nodeItem->_pLeft = Insert(nodeItem->_pLeft, keyValue);
		}
		else
		{
			nodeItem->_pRight = Insert(nodeItem->_pRight, keyValue);
		}

		return banlance(nodeItem);
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
		this->root = Delete(this->root, key);
	}

	Node* Delete(Node* p, const Type& key)
	{
		if (p == NULL)
			return NULL;

		if (p->_Value > key)
			p->_pLeft = Delete(p->_pLeft, key);
		else if (p->_Value < key)
			p->_pRight = Delete(p->_pRight, key);
		//--value == key
		else
		{
			Node* q = p->_pLeft;
			Node* r = p->_pRight;
			delete p; //free memory
			if (r == NULL)  //
			{
				return q; //--递归返回的时候 banlance  ---- 1 
			}
			//
			Node* pmin = FindMiniNode(r); //--find right sub tree min node
			assert(pmin);

			pmin->_pLeft = q;
			pmin->_pRight = RemoveMinNode(r);

			return banlance(pmin);
		}
		return banlance(p);
	}
	
	Node* GetMiniValueNode(Node* p)
	{
		if (p == NULL)
			return p;
		return GetMiniValueNode(p->_pLeft);
	}

	Node* RemoveMinNode(Node* p) //
	{
		assert(p);

		if (p->_pLeft == NULL)
			return p->_pRight; // possible |be likely to  return NULL --3

		p->_pLeft = RemoveMinNode(p->_pLeft); // --  2

		return banlance(p);
	}

	Node* FindMiniNode(Node* p)
	{
		assert(p);

		if (p->_pLeft == NULL)
			return p;
		else
			return FindMiniNode(p->_pLeft);
	}

private:
	Node* root;
};

/*
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
*/

