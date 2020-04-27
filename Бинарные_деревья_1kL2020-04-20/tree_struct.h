#pragma once
struct node
{
	int value;
	int count = 1;
	node* left = nullptr;
	node* right = nullptr;
};

struct tree
{
	node* root = nullptr;
	size_t elem_count = 0;
};

struct elem
{
	node* node;
	elem* next = nullptr;
};

struct queue
{
	elem* head = nullptr;
	elem* tail = nullptr;
	size_t size = 0;
};