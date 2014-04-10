/**
 * @file Heap.cpp
 * @author Daniel Goodnow
 * 
 * @mainpage Heap ADT
 * @detail This is a heap data structure. It contains all necessary functionality
 * to implement an array-based heap. It contains a user defined maximum size, 
 * as well as the ability for the user to define the comparison type for 
 * organizing the heap. Also, the class is templated which allows any data type
 * to be used, provided that it has a comparison operator available for it. 
 * Also, the data type must have a getPriority method in order to perform the 
 * comparison. 
*/
#include "Heap.h"

/**
 * @name Constructor
 * @brief Initializes the private variables for the heap and allocates the memory
 * for the array where the data is stored. 
 *
 * @param maxNumber The size of the array to store the heap in. Defaults to the
 * default max size declared in the specification file (Heap.h).
 *
 * @pre Heap is not instantiated.
 * @post Heap is allocated in memory.
*/
template < typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DataType[maxSize];
}

/**
 * @name Copy Constructor
 * @brief Initializes the private variables for the heap and allocates the memory
 * for the array where the data is stored. Copies the data from 'other' into this.
 *
 * @param other The heap to be copied from.
 *
 * @pre Heap is not instantiated.
 * @post Heap is allocated in memory and is a copy of the 'other' heap. 
*/
template < typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap( const Heap& other)
{
	maxSize = other.maxSize;
	size = other.size;
	dataItems = new DataType[maxSize];
	if(other.isEmpty())
	{
		return;
	}
	for(int i = 0; i < size; i++)
	{
		dataItems[i] = other.dataItems[i];
	}
}
/**
 * @name Destructor
 * @brief Deallocates all memory the heap.
 *
 * @pre The heap is allocated in memory.
 * @post The heap no longer exists and is not accessible by the program.
*/
template < typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::~Heap()
{
	size = 0;
	maxSize = DEFAULT_MAX_HEAP_SIZE;
	delete[] dataItems;
}

/**
 * @name Overloaded Assignment Operator
 * @brief Copies one heap into another heap.
 *
 * @param other The heap to be copied from.
 * @retval The heap that was copied from.
 *
 * @pre Both this heap and 'other' heap exist.
 * @post Heap is a copy of other.
*/
template < typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>& 
	Heap<DataType, KeyType, Comparator>::operator=( const Heap& other)
{
	clear();
	maxSize = other.maxSize;
	size = other.size;
	dataItems = new DataType[maxSize];
	if(other.isEmpty())
	{
		return *this;
	}
	for(int i = 0; i < size; i++)
	{
		dataItems[i] = other.dataItems[i];
	}
	return *this;
}

/**
 * @name Insert
 * @brief Inserts a new data item into the heap.
 * @detail Checks if the heap has room to insert an item, if not it throws an
 * error. Then it appends the enw data item to the end of the heap, and moves 
 * it up the heap if necessary inorder to maintain a legal heap structure.
 *
 * @param newDataItem The item to be inserted.
 *
 * @pre The heap exists and is not full.
 * @post The heap contains the new item and remains in proper form. 
 */
template < typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::insert(const DataType &newDataItem) 
														throw (logic_error)
{
	if(isFull())
	{
		throw("Heap is full"); //not sure if correct wording
		return;
	}
	size++;
	dataItems[size-1] = newDataItem;
	int newDataIndex = size-1;
	int parentIndex;
	bool inPlace = false;
	while( newDataIndex > 0 && !inPlace)
	{
		parentIndex = (newDataIndex - 1)/2;
		if(comparator(dataItems[parentIndex].getPriority(), dataItems[newDataIndex].getPriority()))
		{
			inPlace = true;
		}
		else
		{
			DataType temp = dataItems[parentIndex];
			dataItems[parentIndex] = dataItems[newDataIndex];
			dataItems[newDataIndex] = temp;
			newDataIndex = parentIndex;
		}
	}
}

/**
 * @name Remove
 * @brief Removes the top data item from the heap.
 * @detail Checks if the heap is empty and if not it removes the root item of
 * the heap and restructures the heap by calling the recursive function heapify.
 * Then, the root item is returned. If it is empty, throws an error. 
 *
 * @retval The root item of the heap.
 *
 * @pre The heap exists and is not empty.
 * @post The heap contains 1 less item and is restructured to reflect the new
 * root. 
 */
template < typename DataType, typename KeyType, typename Comparator>
DataType Heap<DataType, KeyType, Comparator>::remove() throw (logic_error)
{
	if(!isEmpty())
	{
		DataType toReturn = dataItems[0];
		dataItems[0] = dataItems[size-1];
		size--;
		heapify(0, dataItems);
		return toReturn;
	}
	else
	{
		throw("Heap is empty");
	}
}

/**
 * @name Heapify
 * @brief Restructures a heap to support legal heap order. 
 * @detail Beginning with the root of a heap, it compares a parent to its larger
 * child and swaps them if they are out of place. It calls itself recursively on
 * the next level down until the root parameter has no children.
 *
 * @param root The root/parent item to be checked against its children.
 * @param array The array storing the heap.
 *
 * @pre The heap exists and is not empty.
 * @post The heap is in proper order. 
 */
template < typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::heapify(int root, DataType* array)
{
	if(size > (2*root -1))   //not sure if correct value
	{
		int bigChild = 2 * root + 1;
		int rightChild;
		if(size >( 2 * root + 2))
		{
			rightChild = bigChild+1;
			if(comparator(array[rightChild].getPriority(), array[bigChild].getPriority()))
			{
				bigChild = rightChild;
			}
		}
		if(comparator(array[bigChild].getPriority(), array[root].getPriority()))
		{
			DataType temp = array[root];
			array[root] = array[bigChild];
			array[bigChild] = temp;
		}
		heapify(bigChild, array);
	}
}

/**
 * @name Clear
 * @brief Clears the array storing the heap.
 * @detail Sets the size to zero because it makes the heap appear empty. The 
 * items can remain in the heap because they are viewed as garbage. 
 *
 * @pre The heap exists and is not empty.
 * @post The heap appears empty.
 */
template < typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::clear()
{
	size = 0;
}

/**
 * @name IsEmpty
 * @brief Checks whether a heap is empty or not.
 *
 * @retval True if empty, false if not.
 *
 * @pre The heap exists.
 */
template < typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
	if(size==0)
	{
		return true;
	}
	return false;
}

/**
 * @name IsFull
 * @brief Checks whether a heap is full or not.
 *
 * @retval True if full, false if not.
 *
 * @pre The heap exists.
 */
template < typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isFull() const
{
	if(size>=maxSize)
	{
		return true;
	}
	return false;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showStructure () const

// Outputs the priorities of the data items in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const

// Helper function for the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}

