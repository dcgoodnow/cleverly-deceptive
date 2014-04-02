#include "HashTable.h"


template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
{
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType>[initTableSize];
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
{
	tableSize = other.tableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
	if(!other.isEmpty())
	{
		for(int i = 0; i < tableSize; i++)
		{
			dataTable[i] = other.dataTable[i];
		}
	}
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other)
{
	if(this == &other)
	{
		return *this;
	}
	clear();
	if(other.isEmpty())
	{
		return *this;
	}
	tableSize = other.tableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
	if(!other.isEmpty())
	{
		for(int i = 0; i < tableSize; i++)
		{
			dataTable[i] = other.dataTable[i];
		}
	}
	return *this;
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
   clear();
   delete[] dataTable;
   dataTable = NULL;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{
	int h = newDataItem.hash(newDataItem.getKey());
	dataTable[(h%tableSize)].insert(newDataItem);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	if(isEmpty())
	{
		return false;
	}
	DataType temp;
	if(dataTable[temp.hash(deleteKey)%tableSize].remove(deleteKey))
	{
		return true;
	}
	return false;
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, 
														  DataType& returnItem) const
{
	if(isEmpty())
	{
		return false;
	}
	DataType temp;
	if(dataTable[temp.hash(searchKey)%tableSize].retrieve(searchKey, returnItem))
	{
		return true;
	}
	return false;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
{
	for(int i = 0; i < tableSize; i++)
	{
		dataTable[i].clear();
	}
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const
{
	for(int i = 0; i < tableSize; i++)
	{
		if(!dataTable[i].isEmpty())
		{
			return false;
		}
	}
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {
    for (int i = 0; i < tableSize; ++i) {
	cout << i << ": ";
	dataTable[i].writeKeys();
    }
}
