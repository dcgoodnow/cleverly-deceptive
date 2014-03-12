/**
 * @file BSTree.cpp
 * @author Daniel Goodnow
 * @mainpage Binary Search Tree
 * @detail This provides a class for a binary search tree. The class is 
 * templated to accept any type key and datatype. The class also provides
 * functionality to output the available keys, depth of the tree, and the
 * number of nodes in the tree. Another method is available to provide a 
 * visible representation of the tree. 
*/
#include "BSTree.h"

/**
 * @name Constructor
 * @brief Constructor for the Binary search tree.
 * 
 * @pre The tree is non existent
 *
 * @post The tree is instantiated
*/
template < typename DataType, class KeyType >   
BSTree<DataType, KeyType>::BSTree()
{
   root = NULL;
}

/**
 * @name Destructor
 * @brief Deletes all memory allocated for the BST.
 *
 * @pre The tree exists.
 * @post The tree is deallocated from memory.
*/
template < typename DataType, class KeyType >   
BSTree<DataType, KeyType>::~BSTree()
{
   clear();
}

/**
 * @name Node Constructor
 * @brief Constructor for BST node.
 *
 * @param nodeDataItem The data item to be contained in the node.
 * @param leftPtr The pointer to the left node of the branch.
 * @param rightPtr The pointer to the right node of the branch.
 *
 * @pre The node does not exist.
 * @post The node is created and initialized.
*/
template < typename DataType, class KeyType >   
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode( const DataType &nodeDataItem,
                                       BSTreeNode *leftPtr,
                                       BSTreeNode *rightPtr )
{
   dataItem = nodeDataItem;
   left = leftPtr;
   right = rightPtr;
}

/**
 * @name Insert
 * @brief Inserts a new node into the tree.
 *
 * @param newDataItem Data item to be inserted.
 *
 * @pre Tree exists.
 * @post New node is added to tree.
*/
template < typename DataType, class KeyType >   
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem )
{
   insertHelper(root, newDataItem);
}

/**
 * @name Insert Helper
 * @brief Recursive function to insert a node at the correct spot.
 * @detail Tests to determine where the new item should be inserted in the 
 * BST and inserts the node at this point.
 *
 * @param ptr The root node of the current tree (or subtree).
 * @param newDataItem The data item to be inserted.
 *
 * @pre The tree exists.
 * @post A new node is inserted.
*/
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

/**
 * @name Retrieve
 * @brief Gets the data item at the specified key.
 *
 * @param searchKey The key corresponding to the desired data item.
 * @param searchDataItem The data item which will be returned by reference.
 *
 * @retval True if the key is found, false if otherwise.
 *
 * @pre The tree exists.
 * @post The searchDataItem is replaced with the found data item.
*/
template < typename DataType, class KeyType >   
bool BSTree<DataType, KeyType>::retrieve ( const KeyType& searchKey,
                                           DataType& searchDataItem ) const
{
   retrieveHelper(searchKey, searchDataItem, root);
}

/**
 * @name Retrieve Helper
 * @brief Recursive function to retrieve a data item.
 * @detail Recursively traverses the BST in a in-order method to find the 
 * specified key.
 * 
 * @param searchKey The key corresponding to the desired data item.
 * @param searchDataItem The data item which will be returned by reference.
 * @param parent The root of the current tree (or subtree).
 * 
 * @retval  True if the key is found, false if otherwise.
 *
 * @pre The tree exists.
 * @post The searchDataItem is replaced with the found data item.
*/
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

/**
 * @name Is Empty
 * @brief Determines whether or not the tree is empty.
 *
 * @retval True if the tree is empty, false if otherwise.
 *
 * @pre The tree exists.
 * @post No change, const function.
*/
template < typename DataType, class KeyType >   
bool BSTree<DataType, KeyType>::isEmpty () const
{
   if(root == NULL)
   {
      return true;
   }
   else return false;
}

/**
 * @name Remove
 * @brief Removes a node from the tree.
 *
 * @param deleteKey Key of the node to be deleted.
 *
 * @retval True if delete key value found, false if otherwise.
 *
 * @pre The tree and key node exist.
 * @post The node is removed from the tree.
*/
template < typename DataType, class KeyType >   
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey )
{
   return removeHelper(root, deleteKey);
}

/**
 * @name removeHelper
 * @brief Recursive function to remove node from the tree.
 *
 * @param parent Root of the current tree (or subtree).
 * @param deleteKey Key value of the node to be deleted.
 *
 * @retval True if delete key value found, false if otherwise.
 *
 * @pre The tree and key node exist.
 * @post The node is removed from the tree.
*/
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

/**
 * @name Write Keys
 * @brief Writes all keys in ascending order to standard output.
 * 
 * @pre Tree exists.
 * @post Keys are output to standard output.
*/
template < typename DataType, class KeyType >   
void BSTree<DataType, KeyType>::writeKeys() const
{
   keyHelper(root);
   cout << endl;
}

/**
 * @name Key Helper
 * @brief Recursive function to output key values.
 * @detail Uses a pre-order traversal to output the keys in ascending order.
 *
 * @param parent The root of the current tree (or subtree).
 *
 * @pre The tree exists.
 * @post Keys are output to standard output.
*/
template < typename DataType, class KeyType >   
void BSTree<DataType, KeyType>::keyHelper(BSTreeNode* parent) const
{
   if(parent == NULL)
   {
      return;
   }
   keyHelper(parent->left);
   cout << parent->dataItem.getKey() << ' ';
   keyHelper(parent->right);
}

/**
 * @name Get Height
 * @brief Determines the height of the tree.
 *
 * @retval The height of the tree.
 *
 * @pre The tree exists.
 * @post N/A
*/
template < typename DataType, class KeyType >   
int BSTree<DataType, KeyType>::getHeight () const
{
   return heightHelper(root);
}

/**
 * @name Height Helper
 * @brief Recursive function to determine the height.
 * @detail Recursively calls itself, adding one each time it is called until
 * it reaches a leaf. Each branch is compared and the largest value is returned
 * to the get height function.
 *
 * @param parent The root of the current tree (or subtree).
 *
 * @retval The height of the branch so far.
 * @pre The tree exists.
 * @post N/A
*/
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

/**
 * @name Get Count
 * @brief Gets the total count of nodes in the tree.
 *
 * @retval The number of nodes in the tree.
 *
 * @pre The tree exists.
 * @post The number of nodes is returned.
*/
template < typename DataType, class KeyType >   
int BSTree<DataType, KeyType>::getCount() const
{
   return countHelper(root);
}

/**
 * @name Count Helper
 * @brief Recursive function to determine the number of nodes in a tree.
 * @detail Recursively calls itself for each branch, adding one every time it 
 * is called.
 * 
 * @param parent The root of the current tree (or subtree).
 *
 * @retval The height of the current branch.
 *
 * @pre The tree exists.
 * @post The height so far is returned.
*/
template < typename DataType, class KeyType >   
int BSTree<DataType, KeyType>::countHelper(BSTreeNode *parent) const
{
   if(parent == NULL)
   {
      return 0;
   }
   return countHelper(parent->left) + countHelper(parent->right) + 1;
}

/**
 * @name Clear
 * @brief Deletes all nodes in a tree.
 *
 * @pre The tree exists.
 * @post The tree is empty.
*/
template < typename DataType, class KeyType >   
void BSTree<DataType, KeyType>::clear()
{
   clearHelper(root);
}

/**
 * @name Clear Helper
 * @brief Recursive function which deletes all nodes in a tree.
 * @detail Uses a post-order traversal to delete all nodes.
 *
 * @param parent The root of the tree (or subtree).
 *
 * @pre The tree exists.
 * @post The tree is empty.
*/
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
