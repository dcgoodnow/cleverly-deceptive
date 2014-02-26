#include "ExpressionTree.h"

template <typename DataType>
ExprTree::ExprTree()
{
	root = NULL;
}

template <typename DataType>
ExprTree::build()
{
	char input;
	cin >> input;
	root = new ExprTreeNode(input, NULL, NULL);
	cin >> input;
	buildBranch(input, root->leftPtr);
}
