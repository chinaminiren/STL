#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{
public:
	Node(int m,Node* l,Node* r)
	{
		a=m;
		left=l;
		right=r;
	}
	Node* left;
	Node* right;
	int a;
};
bool FindNode(Node* root,int a,int b)
{
	if(root==NULL)
		return false;
	if(root->a==a||root->a==b)
		return true;
	else
	{
		bool c= FindNode(root->left,a,b);
		if(c==true)
			return c;
		bool d=FindNode(root->right,a,b);
		if(d==true)
			return d;
	}
	return false;
}
Node* FindParentNode(Node* root,int a,int b)
{
	if(root==NULL)
		return NULL;
	bool c=FindNode(root->left,a,b);
	bool d=	FindNode(root->right,a,b);
	if(c&&d)
		return root;
	else if(c)
		return FindParentNode(root->left,a,b);
	else if(d)
		return FindParentNode(root->right,a,b);
	else
		return NULL;
}
Node* FindPNode(Node* root,int a,int b)
{
	if(root==NULL)
		return NULL;
	if(root->a==a||root->a==b)
		return root;
	Node* left=FindPNode(root->left,a,b);
	Node* right=FindPNode(root->right,a,b);
	if(left&&right)
		return root;
	else
		return left==NULL?right:left;
}
const Node GetNode()
{
	Node node(2,NULL,NULL);
	return node;
}
void PrintTree(Node* root)
{
	if(root==NULL)
		return;
	PrintTree(root->left);
	std::cout<<root->a<<" ";
	PrintTree(root->right);
}
void AddBSTNode(Node* root,Node* node)
{
	Node* mnode=root;
	while(true)
	{
		if(node->a>mnode->a)
		{
			if(mnode->right)
			{
				mnode=mnode->right;
			}
			else
			{
				mnode->right=node;
				break;
			}
		}
		else
		{
			if(mnode->left)
			{
				mnode=mnode->left;
			}
			else
			{
				mnode->left=node;
				break;
			}
		}
	}
}
Node* MakeBST()
{
	Node* root=new Node(5,NULL,NULL);
	int m=10;	
	while(m--)
	{
		Node* node=new Node(m,NULL,NULL);	
	    AddBSTNode(root,node);
	}
	return root;
}