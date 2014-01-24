#include "ListLinked.h"


template <typename DataType>
List<DataType>::List(int ignored )
{
   head = NULL;
   cursor = NULL;
}

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

template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
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
         }
         delete nodeTmp;
         nodeTmp = NULL;
      }
      else
      {
         gotoPrior();
         cursor->next = nodeTmp->next;
         delete nodeTmp;
         nodeTmp = NULL;
      }
   }
   return;
}

template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
{
   if( !isEmpty() )
   {
      cursor->dataItem= newDataItem;
   }
   return;
}

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

template <typename DataType>
bool List<DataType>::isEmpty() const
{
   if( head == NULL )
   {
      return true;
   }
   return false;
}

template <typename DataType>
bool List<DataType>::isFull() const
{
   return false;
}

template <typename DataType>
void List<DataType>::gotoBeginning() throw(logic_error)
{
   if( !isEmpty() )
   {
      cursor = head;
   }
   return;
}

template <typename DataType>
void List<DataType>::gotoEnd() throw (logic error)
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

template <typename DataType>
bool List<DataType>::gotoNext() throw(logic error)
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

template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic error)
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

template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic error)
{
   if( !isEmpty() )
   {
      return cursor->dataItem;
   }
}
template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
   dataItem = nodeData;
   next = nextPtr;
}
