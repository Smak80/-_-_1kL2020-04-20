#pragma once
#include "tree_struct.h"

void addToTree(tree& tree, int value);
bool removeFromTree(tree& tree, int value);
int findInTree(tree tree, int value);
void dropTree(tree& tree);

queue prefix_traverse(tree tree);
queue infix_traverse(tree tree);
queue postfix_traverse(tree tree);

queue wide_traverse(tree tree, bool include_empty = true);