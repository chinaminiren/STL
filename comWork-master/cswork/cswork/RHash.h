#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

#include <string>
#include <cassert>

//--���ӷ�
#define MAXHASHSIZE 100

template<typename KeyType>
size_t Hash(const KeyType& key)
{
	return key.Hash(); //--�Զ������� ����ʵ��Hash����
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
class HashMap // -- ���ܶ��key һ��
{

//--�ڲ�����
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

				while (ptr != NULL) //�����ӱ� --��ǰ������� todo Ӧ�ø�Ϊ�Ӻ���ǰɾ��
				{
					valueAlloc.destroy(ptr->pValue);//��������
					valueAlloc.deallocate(ptr->pValue, 1);

					keyAlloc.destroy(ptr->pKey);
					keyAlloc.deallocate(ptr->pKey, 1);

					ptr = ptr->pNextValueItem;
					valueItemAlloc.destroy(ptr);
					valueItemAlloc.deallocate(ptr, 1);
				}

				//�ͷ�hashTable�ϵĽڵ�
				valueAlloc.destroy(m_pValueArray[i].pValue);//��������
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

			valueItemAlloc.construct(pItem); //Ĭ�Ϲ��캯��
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
				else //ͷָ��
				{
					pItem->pKey = NULL;
					delete(pItem->pValue);//release �ڴ�
				}
			}
			preItem = pItem;
			pItem = pItem->pNextValueItem;
		}
	}

private:
	ValueItem* m_pValueArray; //HashTable ָ��
	std::allocator<KeyType> keyAlloc;
	std::allocator<ValueType> valueAlloc;
	std::allocator<ValueItem> valueItemAlloc;
};

//--ֱ��Ѱַ��

//���100 �� ʵ��������� > =0 ������ݶ�����0
int T[1000];
int M[100];
int cindex = 0; //��ǰ
bool ArrayInsert(int key,int Value)  //key == value
{
	//�Ѵ���
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
	if (T[key] >= 0 && T[key]<100 && M[T[key]] != -1)  //-1 ���Ϊ��ʼ������
	{
		int j = T[key];
		M[j] = M[cindex];//�����һ�����λ��
		T[M[cindex]] = j; //�޸�
		cindex--;
	}
}

int Search(int key)  // no return -1;
{ 
	if (T[key] >= 0 && T[key] < 100 && M[T[key]] != -1)  //-1 ���Ϊ��ʼ������
	{
		return M[T[key]];
	}
	else
	{
		return -1;
	}
}


