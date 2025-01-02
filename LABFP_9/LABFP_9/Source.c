#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

const int INVALID_VALUE = -1000000;
struct Nod
{
	int info;
	struct Nod* next;
};

typedef struct Nod Nod;

void pushStack(Nod** head, int x)
{	
	Nod* nod_nou = (Nod*)malloc(sizeof(Nod));
	nod_nou->info = x;
	nod_nou->next = *head;
	*head = nod_nou;
}

void popStack(Nod** head)
{
	if (*head != NULL)
	{
		Nod* n = *head;
		*head = n->next;
		free(n);
	}
}

int getInfoStack(Nod* head)
{
	if (head != NULL)
		return head->info;
	return INVALID_VALUE;
}

void empty(Nod** head)
{
	while (*head != NULL)
	{
		printf("%d ", getInfoStack(*head));
		popStack(&(*head));
	}
}

struct Coada
{
	Nod* head, * last;
};

typedef struct Coada Coada;

void pushQueue(Coada* q, int x)
{
	Nod* nod_nou = (Nod*)malloc(sizeof(Nod));
	nod_nou->info = x;
	nod_nou->next = NULL;
	if (q->head == NULL)
	{
		q->head = nod_nou;
		q->last = nod_nou;
	}
	else
	{
		q->last->next = nod_nou;
		q->last = nod_nou;
	}
}

void popQueue(Coada*q)
{
	if (q->head != NULL)
	{
		Nod* n = q->head;
		q->head = n->next;
		free(n);
	}
}

int getInfoQueue(Coada q)
{
	if (q.head != NULL)
		return q.head->info;
	return INVALID_VALUE;
}

void emptyQueue(Coada* q)
{
	while (q->head != NULL)
	{
		printf("%d ", getInfoQueue(*q));
		popQueue(q);
	}
	
}

int main()
{
	Nod* head = NULL;
	pushStack(&head, 9);
	pushStack(&head, 5);
	pushStack(&head, 3);
	pushStack(&head, 1);
	popStack(&head);
	empty(&head);
	puts("");


	Coada q;
	q.head = NULL;
	q.last = NULL;
	pushQueue(&q.head, 9);
	pushQueue(&q.head, 5);
	pushQueue(&q.head, 3);
	pushQueue(&q.head, 1);
	popQueue(&q.head);
	emptyQueue(&q);
	return 0;
}