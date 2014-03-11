#include "BSTree.h"

template < typename DataType, class KeyType >   
BSTree<DataType, KeyType>::BSTree()
{
   root = NULL;
}

template < typename DataType, class KeyType >   
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode( const DataType &nodeDataItem,
                                       BSTreeNode *leftPtr,
                                       BSTreeNode *rightPtr )
{
   dataItem = nodeDataItem;
   left = leftPtr;
   right = rightPtr;
}

template < typename DataType, class KeyType >   
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem )
{
   insertHelper(root, newDataItem);
}

template < typename DataType, class KeyType >   
void BSTree<DataType, KeyType>::insertHelper( BSTreeNode* &ptr, 
                                              const DataType& newDataItem)
{
   if(ptr == NULL)
   {
      ptr = new BSTreeNode(newDataItem, NULL, NULL);
      return;
   }
   if(ptr->dataItem > newDataItem)
   {
      insertHelper(ptr->left, newDataItem);
      return;
   }
   if(ptr->dataItem < newDataItem)
   {
      insertHelper(ptr->right, newDataItem);
      return;
   }
   return;
}

template < typename DataType, class KeyType >   
bool BSTree<DataType, KeyType>::retrieve ( const KeyType& searchKey,
                                           DataType& searchDataItem ) const
{
   //stub
}

template < typename DataType, class KeyType >   
bool BSTree<DataType, KeyType>::isEmpty () const
{
   if(root == NULL)
   {
      return true;
   }
   else return false;
}

template < typename DataType, class KeyType >   
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey )
{
   //stub
}

template < typename DataType, class KeyType >   
int BSTree<DataType, KeyType>::getHeight () const
{
   return heightHelper(root);
}

template < typename DataType, class KeyType >   
int BSTree<DataType, KeyType>::heightHelper(BSTreeNode *parent) const
{
   if(parent == NULL)
   {
      return 0;
   }
   if(heightHelper(parent->left) > heightHelper(parent->right))
   {
      return 1 + heightHelper(parent->left);
   }
   else
   {
      return 1 + heightHelper(parent->right);
   }
}


template < typename DataType, class KeyType >   
void BSTree<DataType, KeyType>::clear()
{
   clearHelper(root);
}

template < typename DataType, class KeyType >   
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode* &parent)
{
   if(parent == NULL)
   {
      return;
   }
   if(parent->right != NULL)
   {
      clearHelper(parent->right);
   }
   if(parent->left != NULL)
   {
      clearHelper(parent->left);
   }
   delete parent;
   parent = NULL;
}
