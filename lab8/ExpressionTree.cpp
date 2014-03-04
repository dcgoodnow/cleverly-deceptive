#include "ExpressionTree.h"

template <typename DataType>
ExprTree<DataType>::ExprTree()
{
	root = NULL;
}

template <typename DataType>
void ExprTree<DataType>::build()
{
	char input;
	cin >> input;
	root = new ExprTreeNode(input, NULL, NULL);
	cin >> input;
	buildBranch(input, root);
}

template <typename DataType>
void ExprTree<DataType>::buildBranch(char input, ExprTreeNode* parent)
{
	parent->left = new ExprTreeNode(input, NULL, NULL);
	char nextIn;
	cin >> nextIn;
	if(input == '+' || input == '-' || input == '*' || input == '/')
	{
		buildBranch(nextIn, parent->left);
	}
	cin >> nextIn;
	parent->right = new ExprTreeNode(nextIn, NULL, NULL);
	if(input == '+' || input == '-' || input == '*' || input == '/')
	{
		buildBranch(nextIn, parent->right);
	}
}

template <typename DataType>
void ExprTree<DataType>::expression() const
{
	
}

template <typename DataType>
void ExprTree<DataType>::clear()
{

}
