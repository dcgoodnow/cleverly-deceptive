#include "Heap.h"

template < typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DataType[maxSize];
}

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

template < typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::~Heap()
{
	size = 0;
	maxSize = DEFAULT_MAX_HEAP_SIZE;
	delete[] dataItems;
}

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
		return;
	}
	for(int i = 0; i < size; i++)
	{
		dataItems[i] = other.dataItems[i];
	}
}

//not correct
template < typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::insert(const DataType &newDataItem) 
														throw (logic_error)
{
	if(isFull())
	{
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
}

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

template < typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::clear()
{
	size = 0;
}

template < typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
	if(size==0)
	{
		return true;
	}
	return false;
}

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

