#include "ExpressionTree.h"


template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode* leftPtr, 
		ExprTreeNode* rightPtr)
{
	dataItem = elem;
	left = leftPtr;
	right = rightPtr;
}

template <typename DataType>
ExprTree<DataType>::ExprTree()
{
	root = NULL;
}

template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
	root = inOrderCopy(source.root);
}

template <typename DataType>
typename ExprTree<DataType>::ExprTreeNode* ExprTree<DataType>::inOrderCopy(ExprTreeNode* source)
{
	if(source == NULL)
	{
		return NULL;
	}
	ExprTreeNode* nodeTmp = new ExprTreeNode(source->dataItem, NULL, NULL);
	nodeTmp->left = inOrderCopy(source->left);
	nodeTmp->right = inOrderCopy(source->right);
	return nodeTmp;
}

template <typename DataType>
ExprTree<DataType>::~ExprTree()
{
	clear();
}

template <typename DataType>
void ExprTree<DataType>::build()
{
	char input;
	cin >> input;
	root = new ExprTreeNode(input, NULL, NULL);
	cin >> input;
	buildBranch(input, root);
	cin >> input;
	buildBranch(input, root);
}

template <typename DataType>
void ExprTree<DataType>::buildBranch(char input, ExprTreeNode* parent)
{
	if(parent->left == NULL)
	{
		parent->left = new ExprTreeNode(input, NULL, NULL);
		char nextIn;
		cin >> nextIn;
		if(input == '+' || input == '-' || input == '*' || input == '/')
		{
			buildBranch(nextIn, parent->left);
		}
		else
		{
			parent->right = new ExprTreeNode(nextIn, NULL, NULL);
		}
	}
	else
	{
		parent->right = new ExprTreeNode(input, NULL, NULL);
		if(input == '+' || input == '-' || input == '*' || input == '/')
		{
			char nextIn;
			cin >> nextIn;
			buildBranch(nextIn, parent->right);
		}
	}
}

template <typename DataType>
void ExprTree<DataType>::expression() const
{
	if(root == NULL)
	{
		return;
	}
	inOrderPrint(root->left);
	cout << root->dataItem;
	inOrderPrint(root->right);
}

template <typename DataType>
void ExprTree<DataType>::inOrderPrint(ExprTreeNode* metaRoot) const
{
	static bool open = false;
	if(metaRoot == NULL)
	{
		return;
	}
	if((metaRoot->dataItem == '+' ||
		metaRoot->dataItem == '-' ||
		metaRoot->dataItem == '*' ||
		metaRoot->dataItem == '/') &&
		!open)
	{
		cout << '(';
		open = true;
	}
	inOrderPrint(metaRoot->left);
	cout << metaRoot->dataItem;
	inOrderPrint(metaRoot->right);
	if((metaRoot->dataItem == '+' ||
		metaRoot->dataItem == '-' ||
		metaRoot->dataItem == '*' ||
		metaRoot->dataItem == '/') &&
		open)
	{
		cout << ')';
		open = false;
	}
}

template <typename DataType>
void ExprTree<DataType>::clear()
{
	if(root == NULL)
	{
		return;
	}
	postOrderDelete(root->left);
	postOrderDelete(root->right);
	delete root;
	root = NULL;
}

template <typename DataType>
void ExprTree<DataType>::postOrderDelete(ExprTreeNode* metaRoot)
{
	if(metaRoot == NULL)
	{
		return;
	}
	postOrderDelete(metaRoot->left);
	postOrderDelete(metaRoot->right);
	delete metaRoot;
	metaRoot = NULL;
}

template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
	return preOrderEvaluate(root);
}

template <typename DataType>
DataType ExprTree<DataType>::preOrderEvaluate(ExprTreeNode* metaRoot) const
{
	if(metaRoot == NULL)
	{
		return 0;
	}
	DataType result = 0;
	switch(metaRoot->dataItem)
	{
		case '+':
			result = DataType(preOrderEvaluate(metaRoot->left) + preOrderEvaluate(metaRoot->right));
			break;
		case '-':
			result = DataType(preOrderEvaluate(metaRoot->left) - preOrderEvaluate(metaRoot->right));
			break;
		case '*':
			result = DataType(preOrderEvaluate(metaRoot->left) * preOrderEvaluate(metaRoot->right));
			break;
		case '/':
			if(preOrderEvaluate(metaRoot->right) == 0)
			{
				throw logic_error("ERROR: Divide by zero");
			}
			else
			{
				result = DataType(preOrderEvaluate(metaRoot->left) / 
							preOrderEvaluate(metaRoot->right));
			}
			break;
		default:
			result = DataType(metaRoot->dataItem - 48);
	}
	return result;
}


template <typename DataType>
void ExprTree<DataType>:: showStructure () const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

{
    if ( root == NULL )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
void ExprTree<DataType>:: showHelper ( ExprTreeNode *p, int level ) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ( ( p->left != 0 ) &&          // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);         // Output left subtree
     }
}

template <typename DataType>
void ExprTree<DataType>::commute()
{
	commuteHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode* metaRoot)
{
	if(metaRoot->dataItem == '+' || metaRoot->dataItem == '-')
	{
		ExprTreeNode* temp = metaRoot->left;
		metaRoot->left = metaRoot->right;
		metaRoot->right = temp;
		commuteHelper(metaRoot->left);
		commuteHelper(metaRoot->right);
	}
}


