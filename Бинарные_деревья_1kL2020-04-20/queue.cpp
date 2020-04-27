#include "queue.h"
#include <cstring>

//���������� ���������� �������� � �������
void enqueue(queue& q, node* nd)
{
	//������� ����� ������� ��� ���������� � �������
	elem* newel = new elem;
	newel->node = nd;
	if (!q.tail)
	{
		//���� ������� ��� �� ����, ����� ������� ���������� ����������� � ���
		q.head = q.tail = newel;
	} else
	{
		//���� ������� ��� ����, ����� ������� ���������� � �����:
		q.tail->next = newel;
		q.tail = newel;
	}
	q.size++;
}

//���������� ��������� �������� �� �������
bool dequeue(queue& q, node*& nd)
{
	if (!q.head) //������� ���
		return false; //������� �������� ����������
	//��������� ������������ ��������
	nd = q.head->node;
	//��������� ��������� �� ������ �������
	elem* rem = q.head;
	//�������� ����� ��������� ��������
	q.head = q.head->next;
	//������� ������� � ������ �������
	delete rem;
	//���� ��������� � ������� �� ��������, �������� � ��������� �� �� �����.
	if (!q.head) q.tail = nullptr;
	q.size--;
	return true;
}

void clear(queue& queue)
{
	//�������� �� ���� ��������� �������, ���� ��� �� ��������
	while (queue.head)
	{
		elem* rem = queue.head; //��������� ������ �� ��������� �������
		queue.head = queue.head->next; //��������� ��������� "������" ������
		delete rem; // ������� ������� �� ������������ ���������
	}
	queue.size = 0; //�������� ������ �������
	queue.tail = nullptr; //��������� ��������� �� ��������� �������
}