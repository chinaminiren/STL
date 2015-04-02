#pragma once
#include <iostream>
#include <cassert>

template<typename T>
class RBTree
{
public:
	enum ColorType
	{
		eRed,
		eBlack,
	};

	struct Node
	{
		Node(Node* _left, Node* _right, Node* _parent, const T& _value, ColorType _colorType)
			:left(_left),
			right(_right),
			value(_value),
			parent(_parent),
			colorType(_colorType) //default is red
		{

		}

		~Node()
		{
			if (left)
				delete left;
			if (right)
				delete right;
		}

		Node* left;
		Node* right;
		Node* parent;
		T value;
		ColorType colorType;
	};

public:
	RBTree():root(NULL)
	{

	}

	//--Rotation

	void  LeftRotation(Node* p) //-- left  ¡¶=====
	{
		assert(p);
		assert(p->right);
		//-- make sure p and p.right is not null

		Node* pf = p->parent;

		Node* q = p->right;

		p->right = q->left;
		if (q->left != NULL)
		{
			q->left->parent = p;
		}

		q->left = p;
		p->parent = q;


		q->parent = pf;
		if (pf == NULL)
		{
			root = q;
		}
		else if (pf->left == p)
		{
			pf->left = q;
		}
		else
		{
			pf->right = q;
		}

		q->parent = pf;
	}

	void  RightRotation(Node* p) //-- ====>
	{
		assert(p);
		assert(p->left);

		Node* pf = p->parent;

		Node* q = p->left;	
		p->left = q->right; // 
		if (q->right != NULL)
		{
			q->right->parent = p;
		}

		q->right = p;
		p->parent = q;


		if (pf == NULL)
		{
			root = q;
		}
		else if (pf->left == p)
		{
			pf->left = q;
		}
		else
		{
			pf->right = q;
		}
		q->parent = pf;

	}
	//--find grandfather
	Node* GetGrandFather(Node* p)
	{
		if (NULL == p)
			return NULL;

		if (p->parent == NULL)
			return NULL;

		return p->parent->parent;
	}

	//-- find uncle
	Node* GetUncle(Node* p)
	{
		Node* grandFather = GetGrandFather(p);
		if (grandFather)
		{
			assert(p->parent);
			return p->parent == grandFather->left ? grandFather->right : grandFather->left;
		}

		return NULL;
	}

	//
	void Insert(const T& key)
	{
		//new node default is red 
		Node* p = new Node(NULL, NULL, NULL, key, eRed);
		if (root == NULL)
		{
			InsertNode(p);
		}
		else
		{
			Node* pt = root;
			while (pt)
			{
				if (pt->value > key)
				{
					if (pt->left == NULL)
					{
						pt->left = p;
						p->parent = pt;
						InsertNode(p);
						break;
					}
					else
					{
						pt = pt->left;
					}
				}
				else
				{
					if (pt->right == NULL)
					{
						pt->right = p;
						p->parent = pt;
						InsertNode(p);
						break;
					}
					else
					{
						pt = pt->right;
					}

				}
			}
		}
		
	}


	void InsertNode(Node* p)
	{
		if (p->parent == NULL) //case 1 root 
		{
			p->colorType = eBlack;
			root = p;
		}
		else if (p->parent->colorType == eRed)
		{
			Node* pu = GetUncle(p);
			Node* pf = p->parent;
			Node* pg = GetGrandFather(p);//sure exist
			if (pu != NULL && pu->colorType == eRed)
			{
				pg->colorType = eRed;
				p->parent->colorType = eBlack;
				pu->colorType = eBlack;
				InsertNode(pg);
			}
			else //--pu == null or pu.colorType ==eBlack is same case because  nil 
			{
				pg->colorType = eRed;
				p->colorType = eBlack;

				if (pf == pg->left) 
				{
					if (p == pf->right)
						LeftRotation(pf);
					RightRotation(pg);
				}
				else if (pf == pg->right)
				{
					if (p == pf->left)
						RightRotation(pf);
					LeftRotation(pg);
				}
			}
		}
		else
		{
			//end;
		}

	}


	void Delete(const T& key)
	{

	}

	Node* Search(const T& key)
	{
		return SearchNode(key);
	}

	void PrintTree()
	{
		PrintNode(root);
	}

	void PrintNode(Node* p)
	{
		if (p)
		{
			PrintNode(p->left);
			std::cout << p->value << " ";
			PrintNode(p->right);
		}
	}

private:
	Node* SearchNode(Node* p, const T& key)
	{
		if (p == NULL)
			return NULL;

		if (p->value == key)
		{
			return p;
		}
		else if (p->value < key)
		{
			return SearchNode(p->left, key);
		}
		else
		{
			return SearchNode(p->right, key);
		}
	}

private:
	Node* root;
};