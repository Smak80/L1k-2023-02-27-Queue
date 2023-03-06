#pragma once

struct man
{
	char name[50];
	int   year;
};

struct queue_elem
{
	man employee;
	queue_elem* next = nullptr;
	queue_elem* prev = nullptr;
};

struct queue
{
	queue_elem* first = nullptr;
	queue_elem* last  = nullptr;
};

void enqueue(queue& q, man employee);
bool dequeue(queue& q, man& employee);
void clear(queue& q);
