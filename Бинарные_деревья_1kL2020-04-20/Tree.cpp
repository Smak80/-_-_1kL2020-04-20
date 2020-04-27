#include "Tree.h"

#include "queue.h"

void traverse(queue& q, node* root, traverse_type type);
bool addToTree(node*& tree, int value);
bool removeFromTree(node*& tree, int value);
int findInTree(const node* tree, int value);
void dropTree(node*& tree);



bool addToTree(node*& root, int value)
{
	if (root)
	{
		if (value == root->value){
			root->count++;
			return false;
		}
		auto& subtree = (value < root->value)? root->left : root->right;
		bool r = addToTree(subtree, value);
		return r;
		
	}
	node* newnode = new node;
	newnode->value = value;
	root = newnode;
	return true;
}

void mergeTree(node*& tree, node* subtree);

bool removeFromTree(node*& root, int value)
{
	if (root)
	{
		if (value == root->value)
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
		auto& subtree = (value<root->value)?root->left:root->right;
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

void addToTree(tree& t, int value)
{
	if (addToTree(t.root, value))
		t.elem_count++;
}

bool removeFromTree(tree& t, int value)
{
	auto res = removeFromTree(t.root, value);
	if (res) t.elem_count--;
	return res;
}

int findInTree(tree t, int value)
{
	return findInTree(t.root, value);
}

void dropTree(tree& t)
{
	dropTree(t.root);
	t.elem_count = 0;
}

queue prefix_traverse(tree t)
{
	queue q;
	traverse(q, t.root, prefix);
	return q;
}

queue infix_traverse(tree t)
{
	queue q;
	traverse(q, t.root, infix);
	return q;
}

queue postfix_traverse(tree t)
{
	queue q;
	traverse(q, t.root, postfix);
	return q;
}


void traverse(queue& q, node* root, traverse_type type)
{
	if (root)                      //               5
	{                              //           2       8
		switch (type)              //         1   3   -   9
		{
		case infix: //LNR // 1 2 3 5 8 9
			if (root->left) traverse(q, root->left, type);
			enqueue(q, root);
			if (root->right) traverse(q, root->right, type);
			break;
		case prefix: //NLR
			enqueue(q, root);
			if (root->left) traverse(q, root->left, type);
			if (root->right) traverse(q, root->right, type);
			break;
		case postfix: //LRN
			if (root->left) traverse(q, root->left, type);
			if (root->right) traverse(q, root->right, type);
			enqueue(q, root);
		}
	}
}

void mergeTree(node*& root, node* subtree)
{
	if (root)
		if (subtree->value < root->value)
			mergeTree(root->left, subtree);
		else
			mergeTree(root->right, subtree);
	else root = subtree;
}
