#pragma once
#include <iostream>
#include <cassert>

template<typename T>
class OSTree
{
public:
	enum ColorType
	{
		eRed,
		eBlack,
	};

	struct Node
	{
		Node(Node* _left, Node* _right, Node* _parent, const T& _value, ColorType _colorType,size_t _size)
			:left(_left),
			right(_right),
			value(_value),
			parent(_parent),
			colorType(_colorType), //default is red
			size(_size)
		{

		}

		~Node()
		{
			if (left && left != OSTree::nil)
			{
				delete left;
				left = NULL;
			}

			if (right && right != OSTree::nil)
			{
				delete right;
				right = NULL;
			}
		}

		Node* left;
		Node* right;
		Node* parent;
		T value;
		ColorType colorType;

		size_t size;
	};

public:
	OSTree()
	{
		root = nil;
	}

	~OSTree()
	{
		delete root;
		root = NULL;
	}

	//--Rotation

	void  LeftRotation(Node* p) //-- left  《=====
	{
		assert(p);
		assert(p->right);
		//-- make sure p and p.right is not null

		//-- 修改Size 相关

		p->size = GetSize(p->left) + GetSize(p->right->left) + 1;
		p->right->size = GetSize(p) + GetSize(p->right->right) + 1;

		//--end edit

		Node* pf = p->parent;

		Node* q = p->right;

		p->right = q->left;
		if (q->left != nil)
		{
			q->left->parent = p;
		}

		q->left = p;
		p->parent = q;


		q->parent = pf;
		if (pf == nil)
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

		//-- 修改Size 相关

		p->size = GetSize(p->right) + GetSize(p->left->right) + 1;
		p->left->size = GetSize(p) + GetSize(p->left->left) + 1;

		//--end edit

		Node* pf = p->parent;

		Node* q = p->left;
		p->left = q->right; // 
		if (q->right != nil)
		{
			q->right->parent = p;
		}

		q->right = p;
		p->parent = q;


		if (pf == nil)
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
		if (nil == p)
			return nil;

		if (p->parent == nil)
			return nil;

		return p->parent->parent;
	}

	//-- find uncle
	Node* GetUncle(Node* p)
	{
		Node* grandFather = GetGrandFather(p);
		if (grandFather != nil)
		{
			assert(p->parent);
			return p->parent == grandFather->left ? grandFather->right : grandFather->left;
		}

		return nil;
	}

	Node* GetBrother(Node* p)
	{
		assert(p);
		assert(p->parent);

		if (p == p->parent->left)
			return p->parent->right;
		else
			return p->parent->left;
	}
	//
	void Insert(const T& key)
	{
		//new node default is red 
		Node* p = new Node(nil, nil, nil, key, eRed,1);
		if (root == nil)
		{
			InsertNode(p);
		}
		else
		{
			Node* pt = root;
			while (pt)
			{
				assert(pt != nil);

				pt->size = pt->size + 1;

				if (pt->value > key)
				{
					if (pt->left == nil)
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

					if (pt->right == nil)
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
		if (p->parent == nil) //case 1 root 
		{
			p->colorType = eBlack;
			root = p;
		}
		else if (p->parent->colorType == eRed)
		{
			Node* pu = GetUncle(p);
			Node* pf = p->parent;
			Node* pg = GetGrandFather(p);//sure exist
			if (pu != nil && pu->colorType == eRed)
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

	Node* GetSubTreeMini(Node* p)//--p
	{
		assert(p);
		assert(p != nil);

		Node* pc = p->right;
		while (pc != nil && pc->left != nil)
		{
			pc->size = pc->size - 1;
			pc = pc->left;
		}
		return pc;
	}

	void Delete(const T& key) //--先按照 二叉查找树方式 删除 再进行修复操作
	{
		assert(root);
		if (nil == root)
			return;

		Node* pc = root;
		while (pc != nil)
		{
			pc->size = pc->size - 1;

			if (pc->value == key)
			{
				break;
			}
			else if (pc->value > key)
			{
				pc = pc->left;
			}
			else
			{
				pc = pc->right;
			}
		}
		if (pc == nil)
			return; //no result

		Node* pf = pc->parent;

		Node* pmin = GetSubTreeMini(pc);

		if (pmin == nil) //--没有右子树 --左子树不一定有
		{
			if (pf->left == pc)
			{
				pf->left = pc->left;
			}
			else
			{
				pf->right = pc->left;
			}

			pc->left->parent = pc->parent; //--nil->parent = pc->parent
			//--进入删除修复操作
			if (pc->colorType == eBlack)
			{
				ReBalanceNode(pc->left); // 黑 + 黑 pc->left 有可能为 nil 
			}

			delete pc;
			//删除的是红色节点 不需要修复
		}
		else
		{
			pc->value = pmin->value; //== 
			//实际删除 pmin --pmin 左子树一定是没有 右子树不一定有
			//删除操作
			if (pmin == pmin->parent->left)
			{
				pmin->parent->left = pmin->right;
			}
			else
			{
				pmin->parent->right = pmin->right;
			}

			pmin->right->parent = pmin->parent; //-- pmin->right may be nill

			//-- 开始修复工作
			if (pmin->colorType == eBlack)
			{
				ReBalanceNode(pmin->right); // 额外 + 黑 -- pmin->right may be nill
			}

			delete pmin;
		}
	}

	void ReBalanceNode(Node* p) // 修改--红黑树 修复前  额外 + 黑 p
	{
		assert(p);
		if (p->parent == nil) //修复的是 root
			return;
		if (p->colorType == eRed)
		{
			p->colorType = eBlack; //直接修复
			return;
		}

		//-- pb is sure is not null 
		//--当前节点是黑色 又不是root 节点
		//pb 也不会是nil 节点 因为删除前 删除节点是 黑色 所有一定有 兄弟节点（不是根节点）
		Node* pb = GetBrother(p);
		assert(pb);
		assert(pb != nil);

		if (pb->colorType == eRed)
		{
			DeleteNodeCase1(p); // 黑 + 黑 + 叔叔 红色
		}
		else
		{
			if ((pb->left == nil || pb->left->colorType == eBlack)
				&& (pb->right == nil || pb->right->colorType == eBlack))
			{
				DeleteNodeCase2(p);
			}
			else if ((pb->left && pb->left->colorType == eRed)
				&& (pb->right == nil || pb->right->colorType == eBlack))
			{
				//调整右孩子为红色  然后可以直接转化为 case4
				DeleteNodeCase3(p);
			}
			else
			{
				DeleteNodeCase4(p);
			}
		}

	}

	void DeleteNodeCase1(Node* p) //修复前 黑 + 黑   叔叔节点为红色  pb == eRed
	{
		assert(p);
		Node* pb = GetBrother(p);
		assert(pb);
		assert(pb->colorType == eRed);

		pb->colorType = eBlack;
		pb->parent->colorType = eRed;

		if (p == p->parent->left)
		{
			LeftRotation(p->parent);
		}
		else
		{
			RightRotation(p->parent);
		}

		//修复后 黑 + 黑  叔叔为黑  父为红色
		ReBalanceNode(p);

	}

	void DeleteNodeCase2(Node* p) //修复前 黑 + 黑
	{
		assert(p);
		Node* pb = GetBrother(p);
		assert(pb);
		assert(pb->colorType == eBlack);
		assert(pb->left == NULL || pb->left->colorType == eBlack);
		assert(pb->right == NULL || pb->right->colorType == eBlack);

		pb->colorType = eRed;

		ReBalanceNode(p->parent);//--递归向上 修复父节点 相当于 父节点 + 黑
	}

	void DeleteNodeCase3(Node* p) 	//-- 修复前 黑 + 黑 兄弟 左孩子为红色 右孩子为黑 case 3
	{
		assert(p);
		Node* pb = GetBrother(p);
		assert(pb);
		assert(pb->colorType == eBlack);
		assert(pb->left);
		assert(pb->left->colorType == eRed);
		assert(pb->right == NULL || pb->right->colorType == eBlack);

		pb->colorType = eRed;
		pb->left->colorType = eBlack;


		RightRotation(pb);

		//turn to case 4
		DeleteNodeCase4(p);
	}

	void DeleteNodeCase4(Node* p) //p-- 黑 + 黑  最后一次修复  右孩子为红色
	{
		//--if (pb->right != NULL && pb->right->colorType == eRed ) //--case 4
		assert(p);

		Node* pb = GetBrother(p);
		assert(pb);
		assert(pb->colorType == eBlack);
		assert(pb->right->colorType == eRed);

		//
		pb->colorType = p->parent->colorType;
		pb->right->colorType = eBlack;
		p->parent->colorType = eBlack;
		if (p == p->parent->left)
			LeftRotation(p->parent);
		else
			RightRotation(p->parent);
	}

	Node* Search(const T& key)
	{
		return SearchNode(key);
	}

	void PrintTree()
	{
		PrintNode(root);
		Validate();
	}

	void PrintNode(Node* p)
	{
		if (p != nil)
		{
			PrintNode(p->left);
			std::cout << p->value << " ";
			PrintNode(p->right);
		}
	}

	Node* SearchNode(Node* p, const T& key)
	{
		if (p == nil)
			return nil;

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

	//---OS operator
	size_t GetSize(Node* p) 
	{
		return p != NULL ? p->size : 0;
	}
	Node* OS_Select(int i)
	{
		return OS_Select(this->root, i);
	}

	Node* OS_Select(Node* p, int i)  //-- 返回 第 i 小的 的元素
	{
		if (p == nil)
			return NULL;

		size_t r = GetSize(p->left) + 1;
		if (r == i)
		{
			return p;
		}
		else if (r > i)
		{
			return OS_Select(p->left, i);
		}
		else
		{
			return OS_Select(p->right, i - r);
		}
	}

	size_t OS_Rank(const T& key) //--元素在 顺序的情况下 的 第 x 位
	{
		Node* p = SearchNode(key);
		if (p == NULL)
			return 0;

		return GetSize(p->left) + 1;
	}

	//--end OS operator

	bool Validate()
	{
		std::cout << std::endl;

		if (root && root->colorType == eRed)
			return false;

		int count = 0;
		return Validate(root, &count);
	}

	bool Validate(Node* p, int* pcount)
	{
		assert(p);
		if (p == nil)
		{
			*pcount = 0;
			return true;
		}

		if ((p->colorType == eRed)
			&& ((p->left && p->left->colorType == eRed) || (p->right && p->right->colorType == eRed))
			)
		{
			std::cout << "连续2个红色节点:" << p->value << std::endl;
			return false;
		}

		int lc, rc;
		bool lf = Validate(p->left, &lc);
		bool rf = Validate(p->right, &rc);
		if (lf && rf && lc == rc)
		{
			*pcount = lc;
			if (p->colorType == eBlack)
				*pcount = *pcount + 1;

			return true;
		}
		else
		{
			std::cout << "2个子树黑高不一样:" << p->value << std::endl;
			return false;
		}
	}


private:
	Node* root;

private:
	static Node node;
	static Node* nil;
};

template<typename T>
typename OSTree<T>::Node OSTree<T>::node(NULL, NULL, NULL, 0, OSTree<T>::eBlack,0);

template<typename T>
typename OSTree<T>::Node* OSTree<T>::nil = &OSTree<T>::node;

