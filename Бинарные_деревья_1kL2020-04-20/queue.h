#pragma once
#include "tree_struct.h"
//���������� �������� � �������
void enqueue(queue& q, node* nd);
//���������� �������� �� �������
bool dequeue(queue& queue, node*& node);
//������� �������
void clear(queue& queue);