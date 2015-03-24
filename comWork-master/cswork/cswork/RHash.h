#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

#include <string>
#include <cassert>

//--链接法
#define MAXHASHSIZE 100

template<typename KeyType>
size_t Hash(const KeyType& key)
{
	return key.Hash(); //--自定义类型 必须实现Hash函数
}

template<>
size_t Hash(const std::string& key)
{
	long hash = 1315423911;

	for (size_t i = 0; i < key.length(); i++)
	{
		hash ^= ((hash << 5) + key[i] + (hash >> 2));
	}

	return hash;
}

template<typename KeyType,typename ValueType>  
class HashMap // -- 不能多个key 一样
{

//--内部对象
private:
	struct ValueItem
	{
		ValueItem()
		{
			pKey           = NULL;
			pValue         = NULL;
			pNextValueItem = NULL;
		}
		KeyType  * pKey;
		ValueType* pValue;
		ValueItem* pNextValueItem;
	};

public:
	~HashMap()
	{
		assert(m_pValueArray);

		for (int i = MAXHASHSIZE - 1; i >= 0; --i)
		{
			if (m_pValueArray[i].pKey != NULL)
			{
				ValueItem* ptr = m_pValueArray[i].pNextValueItem;
				m_pValueArray[i].pNextValueItem = NULL;

				while (ptr != NULL) //有连接表 --从前向后消除 todo 应该改为从后向前删除
				{
					valueAlloc.destroy(ptr->pValue);//析构函数
					valueAlloc.deallocate(ptr->pValue, 1);

					keyAlloc.destroy(ptr->pKey);
					keyAlloc.deallocate(ptr->pKey, 1);

					ptr = ptr->pNextValueItem;
					valueItemAlloc.destroy(ptr);
					valueItemAlloc.deallocate(ptr, 1);
				}

				//释放hashTable上的节点
				valueAlloc.destroy(m_pValueArray[i].pValue);//析构函数
				valueAlloc.deallocate(m_pValueArray[i].pValue, 1);

				keyAlloc.destroy(m_pValueArray[i].pKey);
				keyAlloc.deallocate(m_pValueArray[i].pKey, 1);
			}
		}
		//
		valueItemAlloc.deallocate(m_pValueArray, MAXHASHSIZE);
	}

	HashMap()
	{
		m_pValueArray = valueItemAlloc.allocate(MAXHASHSIZE);
		memset(m_pValueArray, 0, MAXHASHSIZE*sizeof(ValueItem));
	}


public:
	int HashKey(const KeyType& key) //
	{
		size_t k = Hash(key);
		int index = k % MAXHASHSIZE;

		index = 1;
		return index;
	}

	bool HashInsert(const KeyType& key, const ValueType& value) //-- bool false failure | true success
	{
		/*std::unordered_map<int, int> map;
		map.insert(std::make_pair(1,1));*/

		//-- bigger will rehash. be careful shake!!! todo will realizes
		int index = HashKey(key);

		ValueItem* pItem = m_pValueArray + index;

		if (pItem->pKey == NULL)
		{
			//--key
			KeyType* keyPtr = keyAlloc.allocate(1);
			keyAlloc.construct(keyPtr, key);
			//--value
			ValueType* ptr = valueAlloc.allocate(1);
			valueAlloc.construct(ptr, value);

			valueItemAlloc.construct(pItem); //默认构造函数
			pItem->pValue = ptr;
			pItem->pKey = keyPtr;
		}
		else 
		{
			ValueItem* curItem = pItem;
			const KeyType& comKey = *(curItem->pKey);
			if (key == comKey)
			{
				return false; //exist
			}
			else
			{
				bool bExist = false;
				while (curItem->pNextValueItem)
				{
					if (*(curItem->pNextValueItem->pKey) == key)
					{
						bExist = true;
						break;
					}
					else
					{
						curItem = curItem->pNextValueItem;
					}
				}

				if (!bExist)
				{
					//--key
					KeyType* keyPtr = keyAlloc.allocate(1);
					keyAlloc.construct(keyPtr, key);
					//--value
					ValueType* ptr = valueAlloc.allocate(1);
					valueAlloc.construct(ptr, value);

					ValueItem* pNewItem = valueItemAlloc.allocate(1);
					valueItemAlloc.construct(pNewItem);
					pNewItem->pValue = ptr;
					pNewItem->pKey = keyPtr;

					curItem->pNextValueItem = pNewItem;

					return true;
				}
				else
				{
					return false;
				}
			}
		}

		return false;
        
	}

	ValueType* HashSearch(const KeyType& key) //-- no result create default value
	{
		int index = HashKey(key);

		ValueItem* pItem = m_pValueArray + index;
		if (pItem->pKey == NULL)
			return NULL;

		while (pItem && pItem->pValue)
		{
			if (*(pItem->pKey) == key)
			{
				return pItem->pValue;
			}

			pItem = pItem->pNextValueItem;
		}

		return NULL;
	}

	void HashDelete(const KeyType& key) // true success,false failure
	{
		int index = HashKey(key);

		ValueItem* pItem = m_pValueArray + index;

		ValueItem* preItem = NULL;
		while (pItem && pItem->pKey)
		{
			if (*(pItem->pKey) == key)
			{
				if (preItem)
				{
					preItem->pNextValueItem = pItem->pNextValueItem;
				}
				else //头指针
				{
					pItem->pKey = NULL;
					delete(pItem->pValue);//release 内存
				}
			}
			preItem = pItem;
			pItem = pItem->pNextValueItem;
		}
	}

private:
	ValueItem* m_pValueArray; //HashTable 指针
	std::allocator<KeyType> keyAlloc;
	std::allocator<ValueType> valueAlloc;
	std::allocator<ValueItem> valueItemAlloc;
};

//--直接寻址表

//最大100 项 实际相关数据 > =0 标记数据都大于0
int T[1000];
int M[100];
int cindex = 0; //当前
bool ArrayInsert(int key,int Value)  //key == value
{
	//已存在
	if (T[key] >= 0 && T[key]<100 && M[T[key]] == Value)
	{
		return false;
	}
	else
	{
		if (cindex > 100)
		{
			return false;
		}

		cindex++;
		M[cindex] = Value;
		T[key] = cindex;

		return true;
	}
}

void Delete(int key)
{
	if (T[key] >= 0 && T[key]<100 && M[T[key]] != -1)  //-1 标记为初始化数据
	{
		int j = T[key];
		M[j] = M[cindex];//把最后一项更换位置
		T[M[cindex]] = j; //修改
		cindex--;
	}
}

int Search(int key)  // no return -1;
{ 
	if (T[key] >= 0 && T[key] < 100 && M[T[key]] != -1)  //-1 标记为初始化数据
	{
		return M[T[key]];
	}
	else
	{
		return -1;
	}
}


