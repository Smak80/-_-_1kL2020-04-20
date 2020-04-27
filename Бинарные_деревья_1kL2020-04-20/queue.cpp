#include "queue.h"
#include <cstring>

//Реализация добавления элемента в очередь
void enqueue(queue& q, node* nd)
{
	//Создаем новый элемент для размещения в очереди
	elem* newel = new elem;
	newel->node = nd;
	if (!q.tail)
	{
		//Если очереди еще не было, новый элемент становится едиственным в ней
		q.head = q.tail = newel;
	} else
	{
		//Если очередь уже была, новый элемент помещается в конец:
		q.tail->next = newel;
		q.tail = newel;
	}
	q.size++;
}

//Реализация получения элемента из очереди
bool dequeue(queue& q, node*& nd)
{
	if (!q.head) //Очереди нет
		return false; //Вернуть значение невозможно
	//Сохраняем возвращаемое значение
	nd = q.head->node;
	//Сохраняем указатель на начало очереди
	elem* rem = q.head;
	//Изменяем адрес головного элемента
	q.head = q.head->next;
	//Удаляем элемент с головы очереди
	delete rem;
	//Если элементов в очереди не осталось, обнуляем и указатель на ее конец.
	if (!q.head) q.tail = nullptr;
	q.size--;
	return true;
}

void clear(queue& queue)
{
	//Проходим по всем элементам очереди, пока она не опустеет
	while (queue.head)
	{
		elem* rem = queue.head; //Сохраняем ссылку на удаляемый элемент
		queue.head = queue.head->next; //Переносим указатель "головы" вперед
		delete rem; // Удаляем элемент по сохраненному указателю
	}
	queue.size = 0; //Убнуляем размер очереди
	queue.tail = nullptr; //Обновляем указатель на последний элемент
}