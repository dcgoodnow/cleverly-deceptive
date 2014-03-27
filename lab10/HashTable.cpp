#include "HashTable.h"


template <typename DataType, typename KeyType>
HashTable::HashTable(int initTableSize)
{
	tableSize = initTableSize;
	dataTable = NULL;
}


template <typename DataType, typename KeyType>
void HashTable::insert(const DataType& newDataItem)
{
	int h = newDataItem.hash();
	
}
