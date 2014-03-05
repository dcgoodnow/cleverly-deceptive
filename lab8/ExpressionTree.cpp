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
	if(metaRoot == NULL)
	{
		return;
	}
	inOrderPrint(metaRoot->left);
	cout << metaRoot->dataItem;
	inOrderPrint(metaRoot->right);
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
	if(root == NULL)
	{
		return 0;
	}
	DataType result = 0;
	switch(root->dataItem)
	{
		case '+':
			result = preOrderEvaluate(root->left) + preOrderEvaluate(root->right);
			break;
		case '-':
			result = preOrderEvaluate(root->left) - preOrderEvaluate(root->right);
			break;
		case '*':
			result = preOrderEvaluate(root->left) * preOrderEvaluate(root->right);
			break;
		case '/':
			if(preOrderEvaluate(root->right == 0))
			{
				throw logic_error("ERROR: Divide by zero");
			}
			else
			{
				result = preOrderEvaluate(root->left) / preOrderEvaluate(root->right);
			}
			break;
		default:
			result = root->dataItem - 48;
	}
	return result;
}

template <typename DataType>
DataType ExprTree<DataType>::preOrderEvaluate(ExprTreeNode* metaRoot)
{
	
	if(metaRoot == NULL)
	{
		return 0;
	}
	DataType result = 0;
	switch(metaRoot->dataItem)
	{
		case '+':
			result = preOrderEvaluate(metaRoot->left) + preOrderEvaluate(metaRoot->right);
			break;
		case '-':
			result = preOrderEvaluate(metaRoot->left) - preOrderEvaluate(metaRoot->right);
			break;
		case '*':
			result = preOrderEvaluate(metaRoot->left) * preOrderEvaluate(metaRoot->right);
			break;
		case '/':
			if(preOrderEvaluate(metaRoot->right == 0))
			{
				throw logic_error("ERROR: Divide by zero");
			}
			else
			{
				result = preOrderEvaluate(metaRoot->left) / preOrderEvaluate(metaRoot->right);
			}
			break;
		default:
			result = metaRoot->dataItem - 48;
	}
	return result;
}
