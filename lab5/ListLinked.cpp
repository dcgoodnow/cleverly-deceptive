/**
 * @file "ListLinked.cpp"
 * @mainpage Singly Linked List
 * @detail This is the implementation for a singly linked list as specified in
 * ListLinked.h. It contains all necessary functions to perform basic operations
 * on the list. It also utilizes a private ListNode class to create nodes which
 * are only accessible to instantiated list objects.
*/


#include "ListLinked.h"
#include <iostream>
/**
 * @brief Default constructor for the List
 * @param ignored only used for array based implementations
 * @pre the list is non existent
 * @post the list is instantiated
 *	
*/

template <typename DataType>
List<DataType>::List(int ignored )
{
	head = NULL;
	cursor = NULL;
}

/**
 * @brief Copy Constructor for list
 * @param other list to be copied from
*/
template <typename DataType>
List<DataType>::List(const List& other)
{
	if( other.isEmpty() )
	{
		head = NULL;
		cursor = NULL;
	}
	else
	{
		ListNode* srcNode = other.head;
		ListNode* destNode = new ListNode( srcNode->dataItem, NULL);
		head = destNode;
		if( other.cursor == srcNode )
		{
			cursor = destNode;
		}
		while( srcNode->next != NULL )
		{
			srcNode = srcNode->next;
			destNode->next = new ListNode( srcNode->dataItem, NULL);
			destNode = destNode->next;
			if( other.cursor == srcNode )
			{
				cursor = destNode;
			}
		}
	}
}

/**
 * @brief Assignment operator
 * @param other list from which to assign
*/
template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
{
	if(this != &other)
	{
		if( !isEmpty() )
		{
			clear();
		}
		if( other.isEmpty() )
		{
			head = NULL;
			cursor = NULL;
		}
		else
		{
			ListNode* srcNode = other.head;
			ListNode* destNode = new ListNode( srcNode->dataItem, NULL);
			head = destNode;
			if( other.cursor == srcNode )
			{
				cursor = destNode;
			}
			while( srcNode->next != NULL )
			{
				srcNode = srcNode->next;
				destNode->next = new ListNode( srcNode->dataItem, NULL);
				destNode = destNode->next;
				if( other.cursor == srcNode )
				{
					cursor = destNode;
				}
			}
		}
	}
}
/**
 * @brief Destructor
*/
template <typename DataType>
List<DataType>::~List()
{
	if( !isEmpty() )
	{
		cursor = head;
		ListNode* nodeTmp = cursor;
		cursor = cursor->next;
		delete nodeTmp;
		while(cursor != NULL)
		{
			nodeTmp = cursor;
			cursor = cursor->next;
			delete nodeTmp;
		}
		head = NULL;
		cursor = NULL;
	}
}

/**
 * @brief Inserts new node after cursor
 * @param newDataItem Data item to be inserted.
 * @post Cursor points to new node after insertion
*/
template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
{
	if( isEmpty() )
	{
		head = new ListNode(newDataItem, NULL);
		cursor = head;
	}

	else if( !isFull() )
	{
		if( cursor->next == NULL)
		{
			cursor->next = new ListNode(newDataItem, NULL);
			cursor = cursor->next;
		}
		else
		{
			ListNode* nodeTmp = new ListNode(newDataItem, cursor->next);
			cursor->next = nodeTmp;
			cursor = nodeTmp;
		}
	}

	return;
}

/**
 * @brief Removes node at cursor
 * @post Cursor moves to following node except when at the tail, in which case it moves
 * to the beginning
*/
template <typename DataType>
void List<DataType>::remove() throw (logic_error)
{
	if(!isEmpty())
	{
		ListNode* nodeTmp = cursor;

		if(cursor->next == NULL)
		{
			if(cursor == head)
			{
				cursor = NULL;
				head = NULL;
			}
			else
			{
				gotoPrior();
				cursor->next = NULL;
				cursor = head;
			}
			delete nodeTmp;
			nodeTmp = NULL;
		}
		else
		{
			if( cursor == head )
			{
				cursor = cursor->next;
				head = cursor;
			}
			else
			{
				gotoPrior();
				cursor->next = nodeTmp->next;
				cursor->next;
			}
			delete nodeTmp;
			nodeTmp = NULL;
		}
	}
	return;
}

/**
 * @brief Replaces data member at cursor.
 * @param newDataItem The data item to replace the existing item with
*/
template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
{
	if( !isEmpty() )
	{
		cursor->dataItem= newDataItem;
	}
	return;
}

/**
 * @brief Deletes all nodes in the list
 * @post Head and cursor set to NULL
*/
template <typename DataType>
void List<DataType>::clear()
{
	if( !isEmpty() )
	{
		cursor = head;
		ListNode* nodeTmp = cursor;
		cursor = cursor->next;
		delete nodeTmp;
		while(cursor != NULL)
		{
			nodeTmp = cursor;
			cursor = cursor->next;
			delete nodeTmp;
		}
		head = NULL;
		cursor = NULL;
	}
	return;
}

/**
 * @brief Checks for an empty list
 * @return True if empty, false if not.
*/
template <typename DataType>
bool List<DataType>::isEmpty() const
{
	if( head == NULL )
	{
		return true;
	}
	return false;
}

/**
 * @brief Checks for full list
 * @return Always returns false
*/
template <typename DataType>
bool List<DataType>::isFull() const
{
	return false;
}

/**
 * @brief Moves cursor to beginning
*/
template <typename DataType>
void List<DataType>::gotoBeginning() throw(logic_error)
{
	if( !isEmpty() )
	{
		cursor = head;
	}
	return;
}

/**
 * @brief Moves cursor to end
*/
template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
	if( !isEmpty() )
	{
		while( cursor->next != NULL )
		{
			cursor = cursor->next;
		}
	}
	return;
}

/**
 * @brief Moves cursor to next node
 * @return True if successful move, false if cursor is already at the tail
*/
template <typename DataType>
bool List<DataType>::gotoNext() throw(logic_error)
{
	if( isEmpty() )
	{
		return false;
	}
	else if( cursor->next == NULL )
	{
		return false;
	}
	else
	{
		cursor = cursor->next;
		return true;
	}
}

/**
 * @brief Moves cursor to previous node
 * @return True if successful move, false if cursor is already at the head
*/
template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
	if( isEmpty() )
	{
		return false;
	}
	else if( cursor == head )
	{
		return false;
	}
	else
	{
		ListNode* nodeTmp = cursor;
		cursor = head;
		while(cursor->next != nodeTmp )
		{
			cursor = cursor->next;
		}
		return true;
	}
}

/**
 * @brief Returns data item at cursor
 * @return Data item at cursor
*/
template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
	if( !isEmpty() )
	{
		return cursor->dataItem;
	}
}

/**
 * @brief Moves current node to beginning of list
*/
template <typename DataType>
void List<DataType>::moveToBeginning () throw (logic_error)
{
	if( !isEmpty() )
	{
		if(cursor != head)
		{
			ListNode* nodeTmp = cursor;
			gotoPrior();
			cursor->next = nodeTmp->next;
			cursor = new ListNode(nodeTmp->dataItem, head);
			head = cursor;
			delete nodeTmp;
			nodeTmp = NULL;
		}
	}
}

/**
 * @brief Inserts a new node before the cursor
 * @param newDataItem Data item to insert
 * @post Cursor at the new node
*/
template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error)
{
	if( isEmpty() )
	{
		head = new ListNode(newDataItem, NULL);
		cursor = head;
	}
	else
	{
		ListNode* newNode = new ListNode(cursor->dataItem, cursor->next);
		cursor->dataItem = newDataItem;
		cursor->next = newNode;
	}
}

/**
 * @brief Prints the list using iostream
 * @detail If the list is empty, the string "Empty list" is output. Otherwise the list is output
 * starting at the head, with the cursor surrounded by '[]'.
*/
template <typename DataType>
void List<DataType>::showStructure() const
{
	if( isEmpty() )
	{
		cout << "Empty list" << endl;        
	}
	else
	{
		ListNode* nodeTmp = head;
		while(nodeTmp != NULL)
		{
			if(nodeTmp == cursor)
			{
				cout << '[' << nodeTmp->dataItem << "] ";
			}
			else
			{
				cout << nodeTmp->dataItem << ' ';
			}
			nodeTmp = nodeTmp->next;
		}
		cout << endl;
	}
	return;
}

/**
 * @brief Constructor for nodes
 * @param nodeData Data item contained by the node.
 * @param nextPtr The next node in the list to be pointed to. 
*/
template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}
