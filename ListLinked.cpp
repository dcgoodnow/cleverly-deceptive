#include "ListLinked.h"

template <typename DataType> 
ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
   dataItem = nodeData;
   next = nextPtr;
}

template <typename DataType>
List::List(int ignored = 0);
{
   head = NULL;
   cursor = NULL;
}

template <typename DataType>
void List::insert(const DataType& newDataItem) throw (logic_error)
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
void List::remove() throw (logic_error)
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
