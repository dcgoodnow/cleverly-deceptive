#include "QueueArray.h"

template <typename DataType>
QueueArray<DataType>::QueueArray(int maxNumber)
{
	maxSize = maxNumber;
	front = -1;
	back = -1;
	dataItems = new DataType[maxSize];
}

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

template <typename DataType>
QueueArray<DataType>::~QueueArray()
{
	front = -1;
	back = -1;
	delete[] dataItems;
}

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
}


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
}


template <typename DataType>
void QueueArray<DataType>::clear()
{
	if( !isEmpty() )
	{
		front = -1;
		back = -1;
	}
}


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
}

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
}


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

template <typename DataType>
void QueueArray<DataType>::showStructure() const 
// Array implementation. Outputs the data items in a queue. If the
// queue is empty, outputs "Empty queue". This operation is intended
// for testing and debugging purposes only.

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
