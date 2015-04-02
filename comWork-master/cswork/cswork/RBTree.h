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

		void swap(const Node* pther) //--异常安全 怎么办
		{
			T _value = value;
			value = pther->value;
			pther->value = _value;
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

	void  LeftRotation(Node* p) //-- left  《=====
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

	Node* GetBrother(Node* p)
	{
		assert(p);
		assert(p->parent);

		if (p == p->left)
			return p->right;
		else
			return p->left;
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
				if (pf == pg->left) 
				{
					if (p == pf->right)
					{
						p->colorType = eBlack;
						LeftRotation(pf);
					}
					else
					{
						pf->colorType = eBlack;
					}
						
					RightRotation(pg);
				}
				else if (pf == pg->right)
				{
					if (p == pf->left)
					{
						p->colorType = eBlack;
						RightRotation(pf);
					}
					else
					{
						pf->colorType = eBlack;
					}
						
					LeftRotation(pg);
				}

				pg->colorType = eRed;
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

	Node* GetSubTreeMini(Node* p)//--p
	{
		assert(p);
		if (p->right == NULL)
			return p;//--return itself
		else
		{
			Node* pc = p->right;
			while (pc->left)
			{
				pc = pc->left;
			}
			return pc;
		}
	}

	void DeleteNode(Node* p) //--左子树一定是没有的
	{
		if (p == NULL)
			return;

		if (p->parent == NULL)
		{
			root = NULL;
			delete p;   
		}
		else if (p->colorType == eRed || (p->colorType == eBlack && p->right && p->right->colorType == eRed)) //-- direct delete  --
		{
			if (p->colorType == eBlack)
			{
				p->right->colorType = eBlack;
			}

			Node* pf = p->parent;
			if (pf->left == p)
			{
				pf->left == p->right;
				if (p->right)
					p->right->parent = pf;
			}
			else
			{
				pf->right = p->right;
				if (p->right)
					p->right->parent = pf;
			}
		}
		else 
		{
			
		}
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