#include "Tree.h"

void addToTree(node*& root, int value)
{
	if (root)
	{
		if (value == root->value)
			root->count++;
		else
		{
			if (value < root->value)
				addToTree(root->left, value);			
			else
				addToTree(root->right, value);
		}
	} else
	{
		node* newnode = new node;
		newnode->value = value;
		root = newnode;
	}
}

void mergeTree(node*& tree, node* subtree);

bool removeFromTree(node*& root, int value)
{
	if (root)
	{
		if (value==root->value)
		{
			node* rem = root;
			if (root->left)
			{
				mergeTree(root->left, root->right);
				root = root->left;
			} else root = root->right;
			delete rem;
			return true;
		}
		auto subtree = (value<root->value)?root->left:root->right;
		return removeFromTree(subtree, value);
	}
	return false;
}

int findInTree(const node* root, int value)
{
	if (!root) return 0;
	if (root->value==value) return root->count;
	if (value < root->value)
		return findInTree(root->left, value);
	return findInTree(root->right, value);
}

void dropTree(node*& root)
{
	if (root)
	{
		dropTree(root->left);
		dropTree(root->right);
		delete root;
		root = nullptr;
	}
}

void mergeTree(node*& root, node* subtree)
{
	if (root)
		mergeTree(root->right, subtree);
	else root = subtree;
}
