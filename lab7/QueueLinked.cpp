#include "QueueLinked.h"
#include <iostream>
using namespace std;



template <typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber)
{
	front = NULL;
	back = NULL;
}


template <typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked<DataType>& other)
{
	if(other.isEmpty() )
	{
		front = NULL;
		back = NULL;
	}
	else
	{
		QueueNode* srcNode = other.front;
		front = new QueueNode(srcNode->dataItem, NULL);
		back = front;
		srcNode = srcNode->next;
		while(srcNode != NULL)
		{
			back->next = new QueueNode(srcNode->dataItem, NULL);
			back = back->next;
			srcNode = srcNode->next;
		}
		srcNode = NULL;
	}
}

template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked<DataType>& other)
{
	if( this != &other )
	{
		if( !isEmpty() )
		{
			clear();
		}
		if( !other.isEmpty() )
		{
			QueueNode* srcNode = other.front;
			front = new QueueNode(srcNode->dataItem, NULL);
			back = front;
			srcNode = srcNode->next;
			while(srcNode != NULL)
			{
				back->next = new QueueNode(srcNode->dataItem, NULL);
				back = back->next;
				srcNode = srcNode->next;
			}
			srcNode = NULL;
		}
	}
	return this;
}

template <typename DataType>
QueueLinked<DataType>::~QueueLinked()
{
	if( !isEmpty() )
	{
		QueueNode* nodeTmp = front;
		while(front != NULL)
		{
			front = front->next;
			delete nodeTmp;
			nodeTmp = front;
		}
		nodeTmp = front = back = NULL;
	}
}

template <typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
	if( !isFull() )
	{
		if( isEmpty() )
		{
			front = new QueueNode(newDataItem, NULL);
			back = front; 
		}
		else
		{
			back->next = new QueueNode(newDataItem, NULL);
			back = back->next;
		}
	}
}

template <typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{
	if( !isEmpty() )
	{
		QueueNode* nodeTmp = front;
		DataType toDeq = nodeTmp->dataItem;
		if(back == front)
		{
			delete nodeTmp;
			nodeTmp = front = back = NULL;
		}
		else
		{
			front = front->next;
			delete nodeTmp;
			nodeTmp = NULL;
		}
		return toDeq;
	}
}

template <typename DataType>
void QueueLinked<DataType>::clear()
{
	if( !isEmpty() )
	{
		QueueNode* nodeTmp = front;
		while(front != NULL)
		{
			front = front->next;
			delete nodeTmp;
			nodeTmp = front;
		}
		nodeTmp = front = back = NULL;
	}
}

template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
	if( front == NULL )
	{
		return true;
	}
	else return false;
}

template <typename DataType>
bool QueueLinked<DataType>::isFull() const
{
	//always returns false
	return false;
}

template <typename DataType>
void QueueLinked<DataType>::putFront( const DataType& newDataItem) throw (logic_error)
{
	if( !isFull() )
	{
		QueueNode* toPut = new QueueNode(newDataItem, front);
		front = toPut;
	}
}

template <typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
	if( !isEmpty() )
	{
		QueueNode* nodeTmp = back;
		DataType toGet = nodeTmp->dataItem;
		if(back == front)
		{
			delete nodeTmp;
			back = front = nodeTmp = NULL;
		}
		else
		{
			//move back to previous node
			back = front;
			while(back->next != nodeTmp)
			{
				back = back->next;
			}
			delete nodeTmp;
			nodeTmp = NULL;
			back->next = NULL;
		}
		return toGet;
	}
}
template <typename DataType>
int QueueLinked<DataType>::getLength() const
{
	if( isEmpty() )
	{
		return 0;
	}
	else
	{
		QueueNode* nodeCtr = front;
		int count = 1;
		while( nodeCtr->next != NULL )
		{
			nodeCtr = nodeCtr->next;
			count++;
		}
		return count;
	}
}

template <typename DataType>
void QueueLinked<DataType>:: showStructure () const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
    QueueNode *p;   // Iterates through the queue

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != 0 ; p = p->next )
	{
	    if( p == front ) 
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}


template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(
		const DataType& nodeData, QueueNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}
