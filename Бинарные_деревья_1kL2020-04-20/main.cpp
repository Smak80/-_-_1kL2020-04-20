#include <iostream>
#include <Windows.h>

#include "Tree.h"
using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");
	int arr[] = {
		5, 2, 8, 1, 4, 0, 6, 9, 10, 7, 1, 1, 7, 7, 0, 4, 5, 5, 10
	};
	auto sz = sizeof(arr)/sizeof(arr[0]);
	node* tree = nullptr;
	for (int i = 0; i<sz; i++)
	{
		addToTree(tree, arr[i]);
	}
	removeFromTree(tree, 5);
	removeFromTree(tree, 9);
	removeFromTree(tree, 0);
	removeFromTree(tree, 2);
	removeFromTree(tree, -1);
	findInTree(tree, 1);
	findInTree(tree, 5);
	dropTree(tree);
	system("pause");
}