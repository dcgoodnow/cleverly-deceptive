/**
 * @file HashTable.cpp
 * @author Daniel Goodnow
 *
 * @mainpage Hash Table Data Structure Class
 * @detail This is the implementation for a simple hash table data structure.
 * It contains the necessary basic functionality of a hash table.
*/
#include "HashTable.h"


/**
 * @name Constructor
 * @brief Constructs an empty hashtable.
 * 
 * @param initTableSize The size of the hash table to be created.
 *
 * @pre Hash table does not exist.
 * @post Hash Table is instantiated and has memory allocated in memory.
*/
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
{
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType>[initTableSize];
}

/**
 * @name Copy Constructor
 * @brief Creates a new hash table that is a copy of another. 
 *
 * @param other The hash table to copy from.
 *
 * @pre Hash table does not exist.
 * @post Hash table is allocated in memory and filled with data from other.
*/
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

/**
 * @name Assignment Operator
 * @brief Makes the already created hash table a copy of other.
 *
 * @param other The hash table to copy from.
 * @retval The other hash table being copied from (allows chaining).
 *
 * @pre Hash table exists.
 * @post This hash table is a copy of other.
*/
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

/**
 * @name Destructor
 * @brief Deallocates all memory allocated for the hash table.
 *
 * @pre Hash table exists.
 * @post Hash table is deallocated from memory.
*/
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
   clear();
   delete[] dataTable;
   dataTable = NULL;
}

/**
 * @name insert
 * @brief inserts a new data item into the hash table.
 * @algorithm Computes the hash of the key of the data item, then inserts it
 * into the table at the slot which is the modulo of the hash.
 *
 * @param newDataItem THe data item to be isnerted.
 *
 * @pre The hash table exists
 * @post The new item is inerted into the table.
*/
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{
	int h = newDataItem.hash(newDataItem.getKey());
	dataTable[(h%tableSize)].insert(newDataItem);
}

/**
 * @name remove
 * @brief Removes a data item from the table.
 * @algorithm Computes the hash of the data item to delete, and if found,
 * deletes the item from the table.
 *
 * @param deleteKey The key of the item to be deleted.
 * @retval True if the item was deleted, false if otherwise.
 *
 * @pre Hash table exists.
 * @post Item is deleted from table.
*/
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

/**
 * @name retrieve
 * @brief Fetches the value associated with the key in question.
 * @algorithm Computes the hash of the key being searched for, and returns the 
 * data item at that hash if found.
 *
 * @param searchKey The key of the item being searched for.
 * @param returnItem Item being returned (by reference).
 * @retval True if found, false if otherwise.
 *
 * @pre Hash table exists.
 * @post Data at returnItem is replaced with the found item.
*/
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

/**
 * @name clear
 * @brief removes all items from the hash table.
 * @algorithm Loops through all elements of the array and deletes the binary
 * search tree at that location.
 *
 * @pre Hash table exists.
 * @post The table is empty.
*/
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
{
	for(int i = 0; i < tableSize; i++)
	{
		dataTable[i].clear();
	}
}

/**
 * @name isEmpty
 * @brief Determines whether the table is empty or not.
 * @algorithm Loops through the elements of the array and if any of the trees
 * contain one or more items, returns false.
 *
 * @retval False if not empty, True if empty.
 *
 * @pre Hash table exists.
*/
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
