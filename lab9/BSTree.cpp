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
   if(ptr->dataItem.getKey() > newDataItem.getKey())
   {
      insertHelper(ptr->left, newDataItem);
      return;
   }
   if(ptr->dataItem.getKey() < newDataItem.getKey())
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
   retrieveHelper(searchKey, searchDataItem, root);
}

template < typename DataType, class KeyType >   
bool BSTree<DataType, KeyType>::retrieveHelper(const KeyType& searchKey,
                                               DataType& searchDataItem,
                                               BSTreeNode* parent) const
{
   if(parent == NULL)
   {
      return false;
   }
   if(searchKey == parent->dataItem.getKey())
   {
      searchDataItem = parent->dataItem;
      return true;
   }
   if(retrieveHelper(searchKey, searchDataItem, parent->left))
   {
      return retrieveHelper(searchKey, searchDataItem, parent->left);
   }
   if(retrieveHelper(searchKey, searchDataItem, parent->right))
   {
      return retrieveHelper(searchKey, searchDataItem, parent->right);
   }
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
   removeHelper(root, deleteKey);
}

template < typename DataType, class KeyType >   
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode* parent,  const KeyType& deleteKey)
{

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

