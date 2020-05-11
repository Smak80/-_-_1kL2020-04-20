#include "Tree.h"

#include <cmath>


#include "queue.h"

enum traverse_type{infix, prefix, postfix};
void traverse(queue& q, node* root, traverse_type type);

bool addToTree(node*& tree, int value);
bool removeFromTree(node*& tree, int value);
void mergeTree(node*& tree, node* subtree);
int findInTree(const node* tree, int value);
void dropTree(node*& tree);

void wide_traverse(queue& q, node*& root, bool include_empty);
inline int get_height(const node* n);
inline void calc_height(node*& n);

//Функция балансировки дерева
void balance(node*& n);
//Малый левый поворот
void small_left_rotate(node*& n);
//Большой левый поворот
void big_left_rotate(node*& n);
//Малый правый поворот
void small_right_rotate(node*& n);
//Большой правый поворот
void big_right_rotate(node*& n);

void wide_traverse(queue& queue, node*& root, bool include_empty)
{
	if (!root) return;
	enqueue(queue, root);
	auto q = queue.head;
	const auto cnt = 1 << (root->height - 1);
	for (int i = 1; i < cnt && q; i++)
	{
		auto ln = q->node ? q->node->left : nullptr;
		auto rn = q->node ? q->node->right : nullptr;
		if (ln || include_empty) enqueue(queue, ln);
		if (rn || include_empty) enqueue(queue, rn);
		q = q->next;
	}
}

inline int get_height(const node* n)
{
	if (!n) return 0;
	auto lh = n->left ? n->left->height : 0;
	auto rh = n->right ? n->right->height : 0;
	return 1 + (lh > rh ? lh : rh);
}

inline void calc_height(node*& n)
{
	if (n)
		n->height = get_height(n);
}

queue wide_traverse(tree tree, bool include_empty)
{
	queue q;
	wide_traverse(q, tree.root, include_empty);
	return q;
}

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
		if (r) calc_height(root);
		balance(root);
		return r;
		
	}
	node* newnode = new node;
	newnode->value = value;
	root = newnode;
	return true;
}

bool removeFromTree(node*& root, int value)
{
	if (root)
	{
		if (value == root->value)
		{
			node* rem = root;
			mergeTree(root->left, root->right);
			root = root->left;
			delete rem;
			return true;
		}
		auto& subtree = (value<root->value)?root->left:root->right;
		bool r = removeFromTree(subtree, value);
		return r;
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

void mergeTree(node*& leftRoot, node* rightRoot)
{
	if (!leftRoot)
		leftRoot = rightRoot;
	else {
		mergeTree(leftRoot->right, rightRoot);
		calc_height(leftRoot);
		balance(leftRoot);
	}
}

void balance(node*& root)
{
	if (!root) return;
	//Определяем высоту левого и правого поддеревьев
	auto lh = get_height(root->left);
	auto rh = get_height(root->right);
	//Если высоты различаются на 2 или более уровней
	if (abs(lh-rh)>=2)
	{
		//Если правая ветвь больше, будем делать левый поворот
		if (rh>lh)
		{
			//Определем высоты поддеревьев в правом поддереве
			auto rlh = get_height(root->right->left);
			auto rrh = get_height(root->right->right);
			//Если правое под-поддерево больше, делаем малый поворот 
			if (rrh>rlh) small_left_rotate(root);
			//иначе - большой
			else big_left_rotate(root);
		}
		//Будем делать правый поворот, если левая ветвь больше
		else
		{
			//Определем высоты поддеревьев в левом поддереве
			auto llh = get_height(root->left->left);
			auto lrh = get_height(root->left->right);
			//Если левое под-поддерево больше, делаем малый поворот
			if (llh>lrh) small_right_rotate(root);
			//иначе - большой
			else big_right_rotate(root);
		}
	}
}

void small_left_rotate(node*& root)
{
	//Выполнение малого левого поворота возможно,
	//если есть узел и правое поддерево
	if (root && root->right)
	{
		node* t = root;
		root = root->right;
		t->right = root->left;
		root->left = t;
		calc_height(root->left);
		calc_height(root);
	}
}

void big_left_rotate(node*& root)
{
	//Выполнение большого левого поворота возможно,
	//если есть узел и правое поддерево
	if (root && root->right)
	{
		small_right_rotate(root->right);
		small_left_rotate(root);
	}
}

void small_right_rotate(node*& root)
{
	//Выполнение малого правого поворота возможно,
	//если есть узел и левое поддерево
	if (root && root->left)
	{
		node* t = root;
		root = root->left;
		t->left = root->right;
		root->right = t;
		calc_height(root->right);
		calc_height(root);
	}
}

void big_right_rotate(node*& root)
{
	//Выполнение большого правого поворота возможно,
	//если есть узел и левое поддерево
	if (root && root->left)
	{
		small_left_rotate(root->left);
		small_right_rotate(root);
	}
}