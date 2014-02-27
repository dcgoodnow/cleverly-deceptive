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
	buildBranch(input, root->left);
}

template <typename DataType>
void ExprTree<DataType>::buildBranch(char input, ExprTreeNode* parent)
{
	parent = new ExprTreeNode(input, NULL, NULL);
	if(input == '+' || input == '-' || input == '*' || input == '/')
	{
		char nextIn;
		cin >> nextIn;
		buildBranch(nextIn, parent->left);
	}
}
