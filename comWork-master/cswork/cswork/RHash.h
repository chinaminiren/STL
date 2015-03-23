#include <unordered_map>
#include <map>
#include <cassert>
//
void TestHashMap()
{
	std::unordered_map<int, int> map;
	std::map<int,int> mp;

}

#define MAXHASHSIZE 100

struct HashItem
{
	char* pszValue;
	char* pszItem;
};



unsigned long Hash_Value(char* pszValue)
{
	assert(pszValue);

	register size_t hash = 2166136261;
	while (size_t ch = (size_t)*pszValue++)
	{
		hash *= 16777619;
		hash ^= ch;
	}

	return hash;
}

bool InsertHash(char* pszValue, char* pszItem)
{
	//
}

