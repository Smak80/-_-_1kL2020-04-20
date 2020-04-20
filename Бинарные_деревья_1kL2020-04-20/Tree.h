#pragma once
struct node
{
	int value;
	int count = 1;
	node* left = nullptr;
	node* right = nullptr;
};

void addToTree(node*& tree, int value);

bool removeFromTree(node*& tree, int value);

int findInTree(const node* tree, int value);

void dropTree(node*& tree);