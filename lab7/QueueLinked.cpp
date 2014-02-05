#include "QueueLinked.h"
#include <iostream>
using namespace std;

//test

/**
 * @name Constructor
 * @brief Constructor
 * 
 * @param maxNumber Ignored for linked queue implementation.
 *
 * @pre Queue non-existent
 * @post Queue initialized
*/
template <typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber)
{
	front = NULL;
	back = NULL;
}


/**
 * @name Copy Constructor
 * @brief Copy constructor
 * 
 * @param other Queue to be copied from
 *
 * @algorithm Loop through the existing list, creating new copies of each node
 * and linking them in the new Queue
 *
 * @pre Queue non-existent
 * @post Queue initialized
*/
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

/**
 * @name Assignment Operator
 * @brief Assignment operator
 * 
 * @param other Queue to be copied from
 *
 * @algorithm Loop through the existing list, creating new copies of each node
 * and linking them in the new Queue
 *
 * @pre nothing will happen if the other list is the same
 * @post Queue is the same as other
*/
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

/**
 * @name	~QueueLinked
 *	@brief Destructor
 *
 * @algorithm Starting at the beginning of the queue, each node is deleted
 *
 * @pre The queue exists
 *	@post All memory allocated by the queue is deallocated and front/rear are set
 *	to NULL
*/
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

/**
 * @name enqueue
 * @brief Appends a new data item to the end of the queue. 
 *
 * @param newDataItem Data item to be enqueued.
 *
 * @algorithm If the queue is empty the first node is created, otherwise a node
 * is added to the end of the queue
 *
 * @post The new item is appended to the end and \a back points to this item.
*/
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

/**
 * @name dequeue
 * @brief Removes a data item from the front of the queue.
 *
 * @return The item which was removed
 *
 * @algorithm The last node is removed from the queue and the data returned. If
 * it is the last item in the queue, set the queue to empty
 *	
 *	@pre the list is not empty
 * @post Front is moved to the next node and the first node is deleted. If it 
 * was the last item, the queue is set to empty.
*/
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

/**
 * @name clear
 *	@brief Deletes all nodes in the queue
 *
 *	@algorithm The queue is looped through from the beginning to delete all the
 *	nodes.
 *
 * @pre the list is not empty
 *	@post All memory allocated by the queue is deallocated and front/rear are set
 *	to NULL
*/
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

/**
 * @name isEmpty
 * @brief Determines whether the queue is empty.
 *
 * @algorithm The queue is empty if the front is null.
 *
 * @return Returns true if empty, false if not empty.
*/
template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
	if( front == NULL )
	{
		return true;
	}
	else return false;
}

/**
 * @name isFull
 * @brief Determines whether the queue is full.
 *
 * @algorithm The linked queue cannot be full.
 *
 * @return Returns true if full, false if not full.
*/
template <typename DataType>
bool QueueLinked<DataType>::isFull() const
{
	//always returns false
	return false;
}

/**
 * @name putFront
 * @brief Appends a data item at the front of the queue. 
 *
 * @param newDataItem Data item to be added.
 *
 * @algorithm inserts a node at the front of the queue.
 *
 * @post Front is moved to the new data item.
*/
template <typename DataType>
void QueueLinked<DataType>::putFront( const DataType& newDataItem) throw (logic_error)
{
	if( !isFull() )
	{
		QueueNode* toPut = new QueueNode(newDataItem, front);
		front = toPut;
	}
}

/**
 * @brief Removes a data item from the rear of the queue.
 *
 * @return Data item removed.
 *
 * @post Back is moved to the previous node and the node removed is deleted.
*/
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

/**
 * @brief Computes the actual length of the queue.
 *
 * @return The length of the queue.
 */
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

/**
 *	@brief Prints the structure to the standard output.
 *	@post queue is printed to screen
 */
template <typename DataType>
void QueueLinked<DataType>::showStructure () const


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

/**
 * @brief Constructor
 *
 * @param nodeData Data item to be stored in the node.
 *
 * @param nextPtr Pointer which points to the next node in the queue.
 * @pre Node is non-existent
 * @post Node is initialized with given values.
 */
template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(
		const DataType& nodeData, QueueNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}
