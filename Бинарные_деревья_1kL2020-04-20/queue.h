#pragma once
#include "tree_struct.h"
//Добавление элемента в очередь
void enqueue(queue& q, node* nd);
//Извлечение элемента из очереди
bool dequeue(queue& queue, node*& node);
//Очистка очереди
void clear(queue& queue);