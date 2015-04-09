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

	void  LeftRotation(Node* p) //-- left  ��=====
	{
		assert(p);
		assert(p->right);
		//-- make sure p and p.right is not null

		//-- �޸�Size ���

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

		//-- �޸�Size ���

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

	void Delete(const T& key) //--�Ȱ��� �����������ʽ ɾ�� �ٽ����޸�����
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

		if (pmin == nil) //--û�������� --��������һ����
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
			//--����ɾ���޸�����
			if (pc->colorType == eBlack)
			{
				ReBalanceNode(pc->left); // �� + �� pc->left �п���Ϊ nil 
			}

			delete pc;
			//ɾ�����Ǻ�ɫ�ڵ� ����Ҫ�޸�
		}
		else
		{
			pc->value = pmin->value; //== 
			//ʵ��ɾ�� pmin --pmin ������һ����û�� ��������һ����
			//ɾ������
			if (pmin == pmin->parent->left)
			{
				pmin->parent->left = pmin->right;
			}
			else
			{
				pmin->parent->right = pmin->right;
			}

			pmin->right->parent = pmin->parent; //-- pmin->right may be nill

			//-- ��ʼ�޸�����
			if (pmin->colorType == eBlack)
			{
				ReBalanceNode(pmin->right); // ���� + �� -- pmin->right may be nill
			}

			delete pmin;
		}
	}

	void ReBalanceNode(Node* p) // �޸�--����� �޸�ǰ  ���� + �� p
	{
		assert(p);
		if (p->parent == nil) //�޸����� root
			return;
		if (p->colorType == eRed)
		{
			p->colorType = eBlack; //ֱ���޸�
			return;
		}

		//-- pb is sure is not null 
		//--��ǰ�ڵ��Ǻ�ɫ �ֲ���root �ڵ�
		//pb Ҳ������nil �ڵ� ��Ϊɾ��ǰ ɾ���ڵ��� ��ɫ ����һ���� �ֵܽڵ㣨���Ǹ��ڵ㣩
		Node* pb = GetBrother(p);
		assert(pb);
		assert(pb != nil);

		if (pb->colorType == eRed)
		{
			DeleteNodeCase1(p); // �� + �� + ���� ��ɫ
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
				//�����Һ���Ϊ��ɫ  Ȼ�����ֱ��ת��Ϊ case4
				DeleteNodeCase3(p);
			}
			else
			{
				DeleteNodeCase4(p);
			}
		}

	}

	void DeleteNodeCase1(Node* p) //�޸�ǰ �� + ��   ����ڵ�Ϊ��ɫ  pb == eRed
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

		//�޸��� �� + ��  ����Ϊ��  ��Ϊ��ɫ
		ReBalanceNode(p);

	}

	void DeleteNodeCase2(Node* p) //�޸�ǰ �� + ��
	{
		assert(p);
		Node* pb = GetBrother(p);
		assert(pb);
		assert(pb->colorType == eBlack);
		assert(pb->left == NULL || pb->left->colorType == eBlack);
		assert(pb->right == NULL || pb->right->colorType == eBlack);

		pb->colorType = eRed;

		ReBalanceNode(p->parent);//--�ݹ����� �޸����ڵ� �൱�� ���ڵ� + ��
	}

	void DeleteNodeCase3(Node* p) 	//-- �޸�ǰ �� + �� �ֵ� ����Ϊ��ɫ �Һ���Ϊ�� case 3
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

	void DeleteNodeCase4(Node* p) //p-- �� + ��  ���һ���޸�  �Һ���Ϊ��ɫ
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

	Node* OS_Select(Node* p, int i)  //-- ���� �� i С�� ��Ԫ��
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

	size_t OS_Rank(const T& key) //--Ԫ���� ˳�������� �� �� x λ
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
			std::cout << "����2����ɫ�ڵ�:" << p->value << std::endl;
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
			std::cout << "2�������ڸ߲�һ��:" << p->value << std::endl;
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

