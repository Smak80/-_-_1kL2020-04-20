#include <iostream>
#include <Windows.h>


#include "queue.h"
#include "Tree.h"
using namespace std;
void show_tree_query(queue t)
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
void main()
{
	setlocale(LC_ALL, "Rus");
	int arr[] = {
		5, 2, 8, 1, 4, 0, 6, 9, 10, 7, 1, 1, 7, 7, 0, 4, 5, 5, 10
	};
	auto sz = sizeof(arr)/sizeof(arr[0]);
	tree tree;
	for (int i = 0; i<sz; i++)
	{
		addToTree(tree, arr[i]);
	}
	auto q = infix_traverse(tree);
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