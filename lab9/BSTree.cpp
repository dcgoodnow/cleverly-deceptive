#include "BSTree.h"

template < typename DataType, class KeyType >   
BSTree<DataType, KeyType>::BSTree()
{
   root = NULL;
}


template < typename DataType, class KeyType >   
BSTree<DataType, KeyType>::~BSTree()
{
   clear();
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
   return removeHelper(root, deleteKey);
}

template < typename DataType, class KeyType >   
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode* &parent,  const KeyType& deleteKey)
{
   if(parent == NULL)
   {
      return false;
   }
   if(deleteKey < parent->dataItem.getKey())
   {
      return removeHelper(parent->left, deleteKey);
   }
   else if(deleteKey > parent->dataItem.getKey())
   {
      return removeHelper(parent->right, deleteKey);
   }
   else if(deleteKey == parent->dataItem.getKey())
   {
      if(parent->left == NULL && parent->right == NULL)
      {
         BSTreeNode* tmp = parent;
         parent = NULL;
         delete tmp;
         return true;
      }
      if(parent->left == NULL)
      {
         BSTreeNode* tmp = parent->right;
         parent->dataItem = tmp->dataItem;
         parent->left = tmp->left;
         parent->right = tmp->right;
         delete tmp;
         return true;
      }
      if(parent->right == NULL)
      {
         BSTreeNode* tmp = parent->left;
         parent->dataItem = tmp->dataItem;
         parent->right = tmp->right;
         parent->left = tmp->left;
         delete tmp;
         return true;
      }
      else
      {
         BSTreeNode* tmp = parent->left; while(tmp->right != NULL)
         {
            tmp = tmp->right;
         }
         parent->dataItem = tmp->dataItem;
         removeHelper(parent->left, tmp->dataItem.getKey());
         return true;
      }
   }
   return false;
}

template < typename DataType, class KeyType >   
void BSTree<DataType, KeyType>::writeKeys() const
{
   keyHelper(root);
}

template < typename DataType, class KeyType >   
void BSTree<DataType, KeyType>::keyHelper(BSTreeNode* parent) const
{
   if(parent == NULL)
   {
      return;
   }
   keyHelper(parent->left);
   cout << parent->dataItem.getKey();
   keyHelper(parent->right);
   cout << parent->dataItem.getKey();
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

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showStructure () const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p,
                               int level             ) const

// Recursive helper for showStructure. 
// Outputs the subtree whose root node is pointed to by p. 
// Parameter level is the level of this node within the tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}
