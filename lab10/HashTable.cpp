#include "HashTable.h"


template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
{
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType>[initTableSize];
}


template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{
	int h = newDataItem.hash();
	dataTable[h%tableSize].insert(newDataItem);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	if(isEmpty())
	{
		return false;
	}
	if(dataTable[deleteKey.hash()%tableSize].remove(deleteKey))
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
	if(dataTable[searchKey.hash()%tableSize].retrieve(searchKey, returnItem))
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
