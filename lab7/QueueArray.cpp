/**@file QueueArray.cpp
 *
 * @author Daniel Goodnow
 * 
 * @version 0.1
 *
 * @date Tuesday, January 28, 2014
 *
 * @mainpage Linked and Array-based Queue Implementation
 *
 * @detail This is a queue data structure. (Technically it is a deque because
 * of its extra functionality, but it will be referred to as a queue for the
 * sake of simplicity). Both array and singly-linked versions are provided. It
 * contains all the functions necessary to perform standard queue operations
 * which are described in the class documentation. The array-based
 * implementation  uses a wrap style of queue, which means that both the front
 * and rear of the queue can move inside the array. This maximizes the
 * processing and memory efficiency of the data structure by reducing the
 * processor cycles that would be used to shuffle data items up and down the
 * array and by ensuring that the entire array can always be used. Also,
 * functions to put an item in the front and retrieve an item from the rear
 * were implemented which allows the queue to function like a deque. The ADT is
 * templated and therefore can be used with any data type. 
*/
#include "QueueArray.h"

/**
 * @brief Constructor
 * 
 * @param maxNumber Sets the maximum size for the array. Defaults to the max
 * size specified in Queue.h. 
 *
 * @pre Queue non-existent
 * @post Queue initialized
*/
template <typename DataType>
QueueArray<DataType>::QueueArray(int maxNumber)
{
	maxSize = maxNumber;
	front = -1;
	back = -1;
	dataItems = new DataType[maxSize];
}

/**
 * @brief Copy constructor
 * 
 * @param other Queue to be copied from
 *
 * @pre Queue non-existent
 * @post Queue initialized
*/
template <typename DataType>
QueueArray<DataType>::QueueArray(const QueueArray<DataType>& other)
{
	maxSize = other.maxSize;
	front = other.front;
	back = other.back;
	dataItems = new DataType[maxSize];

	if( !other.isEmpty() )
	{
		if(back >= front)
		{
			for(int i = front; i <= back; i++)
			{
				dataItems[i] = other.dataItems[i];
			}
		}
		else
		{
			for(int i = back; i < maxSize; i++)
			{
				dataItems[i] = other.dataItems[i];
			}
			for(int i = 0; i <=front; i++)
			{
				dataItems[i] = other.dataItems[i];
			}
		}
	}
}

/**
 * @brief Assignment operator
 * 
 * @param other Queue to be copied from
 *
 * @post Queue is the same as other
*/
template <typename DataType>
QueueArray<DataType>& QueueArray<DataType>::operator=(const QueueArray<DataType>& other)
{
	if( this == &other )
	{
		return this;
	}
	else
	{
		delete[] dataItems;
		front = other.front;
		back = other.back;
		maxSize = other.maxSize;
		dataItems = new DataType[maxSize];
		if( !other.isEmpty() )
		{
			if(back >= front)
			{
				for(int i = front; i <= back; i++)
				{
					dataItems[i] = other.dataItems[i];
				}
			}
			else
			{
				for(int i = back; i < maxSize; i++)
				{
					dataItems[i] = other.dataItems[i];
				}
				for(int i = 0; i <=front; i++)
				{
					dataItems[i] = other.dataItems[i];
				}
			}
		}
		return this;
	}
}

/**
 *	@brief Destructor
 *
 *	@post All memory allocated by the queue is deallocated and front/rear are set
 *	to -1
*/
template <typename DataType>
QueueArray<DataType>::~QueueArray()
{
	front = -1;
	back = -1;
	delete[] dataItems;
}

/**
 * @brief Appends a new data item to the end of the queue. 
 *
 * @param newDataItem Data item to be enqueued.
 *
 * @post The new item is appended to the end and \a back points to this item.
*/
template <typename DataType>
void QueueArray<DataType>::enqueue( const DataType& newDataItem) throw (logic_error)
{
	if( !isFull() )
	{
		if( isEmpty() )
		{
			front++;
			back++;
			dataItems[back] = newDataItem;
		}
		else
		{
			if(back != maxSize -1)
			{
				back++;
			}
			else
			{
				back = 0;
			}
			dataItems[back] = newDataItem;
		}
	}
	else 
	{
		throw logic_error("Queue is full.");
	}
}

/**
 * @brief Removes a data item from the front of the queue.
 *
 * @return The item which was removed
 *
 * @post Front is moved to the next item. If it was the last item, the list is
 * set to empty.
*/
template <typename DataType>
DataType QueueArray<DataType>::dequeue() throw (logic_error)
{
	if( !isEmpty() )
	{
		DataType toDeq = dataItems[front];
		if(front == back)
		{
			//set list empty
			front = -1;
			back = -1;
		}
		else
		{
			if(front != maxSize-1)
			{
				front++;
			}

			//front at end of array
			else
			{
				front = 0;
			}
		}
		return toDeq;
	}
	else
	{
		throw logic_error("Queue is empty.");
	}
}


/**
 *	@brief Sets the list to empty
 *
 *	@post Front and rear are set to -1.
*/
template <typename DataType>
void QueueArray<DataType>::clear()
{
	if( !isEmpty() )
	{
		front = -1;
		back = -1;
	}
}

/**
 * @brief Determines whether the queue is empty.
 *
 * @return Returns true if empty, false if not empty.
*/
template <typename DataType>
bool QueueArray<DataType>::isEmpty() const
{
	if(front == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * @brief Determines whether the queue is full.
 *
 * @return Returns true if full, false if not full.
*/
template <typename DataType>
bool QueueArray<DataType>::isFull() const
{
	if( isEmpty() )
	{
		return false;
	}
	else
	{
		if(back > front)
		{
			if((back == maxSize-1) && (front == 0))
			{
				return true;
			}
		}
		else
		{
			if(front == back+1)
			{
				return true;
			}
		}
		return false;
	}
}

/**
 * @brief Appends a data item at the front of the queue. 
 *
 * @param newDataItem Data item to be added.
 *
 * @post Front is moved to the new data item.
*/
template <typename DataType>
void QueueArray<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
	if( !isFull() )
	{
		if( isEmpty() )
		{
			front++;
			back++;
			dataItems[front] = newDataItem;
		}
		else
		{
			//front is at beginning of array
			if(front == 0)
			{
				//add new item at end of array
				front = maxSize -1;
				dataItems[front] = newDataItem;
			}
			else
			{
				front--;
				dataItems[front] = newDataItem;
			}
		}
	}
	else
	{
		throw logic_error("Queue is full.");
	}
}
/**
 * @brief Removes a data item from the rear of the queue.
 *
 * @return Data item removed.
 *
 * @post Back is moved to the previous data item. 
*/
template <typename DataType>
DataType QueueArray<DataType>::getRear() throw (logic_error)
{
	if( !isEmpty() )
	{
		DataType toGet = dataItems[back];
		if(back == front)
		{
			front = -1;
			back = -1;
		}
		else
		{
			if( back == maxSize-1)
			{
				back = 0;
			}
			else
			{
				back--;
			}
		}
		return toGet;
	}
	else
	{
		throw logic_error("Queue is empty.");
	}
}

/**
 * @brief Computes the actual length of the queue.
 *
 * @return The length of the queue.
 */
template <typename DataType>
int QueueArray<DataType>::getLength() const
{
	if( isEmpty() )
	{
		return 0;
	}
	else
	{
		if(back >= front)
		{
			return back - front + 1;
		}
		else
		{
			return maxSize - (front - back) + 1;
		}
	}
}

/**
 *	@brief Prints the structure to the standard output. 
 */
template <typename DataType>
void QueueArray<DataType>::showStructure() const 
{
    int j;   // Loop counter

    if ( front == -1 )
       cout << "Empty queue" << endl;
    else
    {
       cout << "Front = " << front << "  Back = " << back << endl;
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       if ( back >= front )
          for ( j = 0 ; j < maxSize ; j++ )
              if ( ( j >= front ) && ( j <= back ) )
                 cout << dataItems[j] << "\t";
              else
                 cout << " \t";
       else
          for ( j = 0 ; j < maxSize ; j++ )
              if ( ( j >= front ) || ( j <= back ) )
                 cout << dataItems[j] << "\t";
              else
                 cout << " \t";
       cout << endl;
    }
}
