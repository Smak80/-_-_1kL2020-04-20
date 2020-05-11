#include <iostream>
#include <Windows.h>
#include "queue.h"
#include "Tree.h"
using namespace std;
void show_tree_query(queue& t)
{
	while (t.size>0)
	{
		node* n;
		auto got = dequeue(t, n);
		if (got)
		{
			if (n) cout << n->value; else cout << "-";
			cout << (t.size>0 ? " " : "\n");
		}
	}
}

inline void show_spaces(int num){
	for (int i = 0; i< num; i++){
		cout << "=";
	}
}

void show_tree_as_tree(queue& t)
{
	int h = 0;
	if (t.head->node) h = t.head->node->height;
	if (!h) return;
	auto level = 0;
	int full_row = (1 << h) - 1;
	while (t.size > 0)
	{
		node* n;
		level++;
		auto pos = 0;
		int spaces = (1 << (h - level)) - 1;
		do {
			show_spaces(spaces);
			pos += spaces;
			auto got = dequeue(t, n);
			if (got)
			{
				if (n) cout << n->value;
				else cout << " ";
				pos++;
			}
			show_spaces(spaces);
			pos+=spaces;
			if (pos < full_row) {
				cout << "=";
				pos++;
			}
		} while (pos < full_row);
		cout << endl;
	}	
}


void main()
{
	setlocale(LC_ALL, "Rus");
	int arr[] = {
		5, 2, 8, 1, 0, 4, 0, 6, 8, 9, 7, 1, 1, 7, 7, 0, 4, 5, 5, 9
	};
	
	auto sz = sizeof(arr)/sizeof(arr[0]);
	tree tree;
	queue q;
	for (int i = 0; i<sz; i++)
	{
		addToTree(tree, arr[i]);
		q = wide_traverse(tree, true);
		show_tree_query(q);
	}
	cout << "-----TREE------" << endl;
	q = wide_traverse(tree, true);
	show_tree_as_tree(q);
	cout << "---------------" << endl;
	q = infix_traverse(tree);
	show_tree_query(q);
	q = prefix_traverse(tree);
	show_tree_query(q);
	q = postfix_traverse(tree);
	show_tree_query(q);

	q = wide_traverse(tree, true);
	show_tree_query(q);
	q = wide_traverse(tree, false);
	show_tree_query(q);
	
	removeFromTree(tree, 5);
	q = wide_traverse(tree, true);
	show_tree_query(q);
	
	removeFromTree(tree, 9);
	removeFromTree(tree, 0);
	removeFromTree(tree, 2);
	removeFromTree(tree, -1);
	q = wide_traverse(tree, true);
	show_tree_query(q);
	findInTree(tree, 1);
	findInTree(tree, 5);
	dropTree(tree);
	system("pause");
}