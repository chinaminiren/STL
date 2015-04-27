
void allTest()
{

	//--Hash
	{

		/*	HashMap<std::string, std::string> map;
		bool bFlag = map.HashInsert("123", "CBC");
		bFlag = map.HashInsert("234", "CBC");
		bFlag = map.HashInsert("456", "CBC");
		map.HashDelete("234");
		std::string* ptrStr = map.HashSearch("234");*/

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
		/*
		RBTree<int> rbTree;
		rbTree.Insert(9);
		rbTree.Insert(0);
		rbTree.Insert(5);
		rbTree.Insert(62);
		rbTree.Insert(4);
		rbTree.Insert(53);
		rbTree.Insert(91);
		rbTree.Insert(10);
		rbTree.Insert(25);
		rbTree.Insert(612);
		rbTree.Insert(-317);
		rbTree.Insert(38);
		rbTree.Insert(557);
		rbTree.Insert(816);
		rbTree.Insert(19);
		rbTree.Insert(210);

		rbTree.PrintTree();
		std::cout << std::endl;

		rbTree.Delete(816);
		rbTree.Delete(232);
		rbTree.Delete(55);
		rbTree.Insert(170);
		rbTree.Delete(86);
		rbTree.Insert(170);

		rbTree.PrintTree();
		std::cout << std::endl;

		rbTree.Insert(557);
		rbTree.Insert(816);
		rbTree.Insert(19);
		rbTree.Insert(210);

		rbTree.PrintTree();
		std::cout << std::endl;
		*/
	}

	//-- OSTree
	{
		/*
		OSTree<int> osTree;
		osTree.Insert(1);
		osTree.Insert(232);
		osTree.Insert(53);
		osTree.Insert(54);
		osTree.Insert(55);
		osTree.Insert(6);
		osTree.Insert(7);
		osTree.Insert(6);
		osTree.Insert(9);
		osTree.Insert(0);
		osTree.Insert(5);
		osTree.Insert(62);
		osTree.Insert(4);
		osTree.Insert(53);
		osTree.Insert(91);
		osTree.Insert(10);
		osTree.Insert(25);
		osTree.Insert(612);
		osTree.Insert(-317);
		osTree.Insert(38);
		osTree.Insert(557);
		osTree.Insert(816);
		osTree.Insert(19);
		osTree.Insert(210);

		osTree.PrintTree();
		std::cout << std::endl;

		OSTree<int>::Node* p = osTree.OS_Select(11);
		std::cout << p->size << " " << p->value << std::endl;

		osTree.Delete(19);
		osTree.Delete(210);
		osTree.Delete(62);
		osTree.Delete(54);
		osTree.Delete(4);
		osTree.Delete(1);

		osTree.PrintTree();
		std::cout << std::endl;

		OSTree<int>::Node* ph = osTree.OS_Select(11);
		std::cout << ph->size << " " << ph->value << std::endl;
		*/
	}

	//-- RankTree

	//--end RankTree

	//--LeetCode

	//--end LeetCode
}