// cswork.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include "RHash.h"
#include "AVLTree.h"
#include "RBTree.h"

using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	//--Hash
	{

		HashMap<std::string, std::string> map;
		bool bFlag = map.HashInsert("123", "CBC");
		bFlag = map.HashInsert("234", "CBC");
		bFlag = map.HashInsert("456", "CBC");
		map.HashDelete("234");
		std::string* ptrStr = map.HashSearch("234");

	}

	//-- AVLTree
	{
		/*
		AVLTree<int> avlTree;
		avlTree.InsertNode(1);
		avlTree.InsertNode(232);
		avlTree.InsertNode(53);
		avlTree.InsertNode(54);
		avlTree.InsertNode(55);
		avlTree.InsertNode(6);
		avlTree.InsertNode(57);
		avlTree.InsertNode(86);
		avlTree.InsertNode(9);
		avlTree.InsertNode(10);

		avlTree.Print();

		std::cout << std::endl;

		avlTree.DeleteNode(233);
		avlTree.DeleteNode(38);
		avlTree.DeleteNode(233);
		avlTree.DeleteNode(75);
		avlTree.Print();
		std::cout << std::endl;

		avlTree.InsertNode(46);
		avlTree.InsertNode(52);
		avlTree.Print();
		std::cout << std::endl;
		*/
	}

	//--RBTree
	{
		RBTree<int> rbTree;
		rbTree.Insert(1);
		rbTree.Insert(232);
		rbTree.Insert(53);
		rbTree.Insert(54);
		rbTree.Insert(55);
		rbTree.Insert(6);
		rbTree.Insert(57);
		rbTree.Insert(86);
		rbTree.Insert(9);
		rbTree.Insert(10);
		rbTree.Insert(255);
	    rbTree.Insert(62);
	    rbTree.Insert(-17);

		rbTree.PrintTree();

		std::cout << std::endl;
	}

	system("pause");

	return 0;
}

