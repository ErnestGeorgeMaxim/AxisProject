#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

struct Nod
{
	int info;
	struct Nod* next;
};

typedef struct Nod Nod;
struct CircQ
{
	Nod* first, * last;
};
typedef struct CircQ CircQ;

void push(CircQ* q, int x)
{
	Nod* nn = (Nod*)malloc(sizeof(Nod));
	nn->info = x;
	if (q->first == NULL)
	{
		q->first = nn;
	}
	else
		q->last->next = nn;
	nn->next = q->first;
	q->last = nn;
}

void empty(CircQ* q)
{
	Nod* n;
	while (q->first != q->last)
	{
		n = q->first;
		q->last->next = n->next;
		q->first = n->next;
		free(n);
	}
	free(q->first);
	q->first = NULL;
	q->last = NULL;
}

Nod* getNod(CircQ q, int n)
{
	if (n <= 0)
		return NULL;
	Nod* nod = q.first;
	for (int i = 1; i < n; i++)
		nod = nod->next;
	return nod;
}

void game(CircQ* q, int m, int p)
{
	Nod* n, *noddeSters;
	while (q->first != q->last)
	{
		n = getNod(*q, p);
		for (int i = 1; i < m; i++)
			n = n->next;
		noddeSters = n->next;
		n->next = noddeSters->next;
		if (noddeSters == q->first)
		{
			q->first = q->last->next;
		}
		else if (noddeSters == q->last)
			q->last = n;
		printf("%d ", noddeSters->info); 
		free(noddeSters);
	}
	printf("And the winner is...... %d\n", q->first->info);
}

int main()
{
	CircQ q;
	q.first = NULL;
	q.last = NULL;
	int n, m, p;
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 1; i <= n; i++)
	{
		push(&q, i);
	}
	game(&q, m, p);
	empty(&q);

	return 0;
}
