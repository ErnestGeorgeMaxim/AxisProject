#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "Functii.h"

void afisareVector(int n, int* v)
{
	int i;
	for (int i = 0; i < n; i++)
		printf("%d ", v[i]);
	printf("\n");
}

void citireVector(int n, int* v)
{
	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);
}

int sumaElementeVector(int n, int* v)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += v[i];
	return sum;
}

int maxVector(int n, int* v)
{
	int maxi = v[0];
	for (int i = 1; i < n; i++)
		if (maxi > v[i])
			maxi = v[i];
	return maxi;
}

void swap(int* x1, int* x2)
{
	int aux = *x1;
	*x1 = *x2;
	*x2 = aux;
}

void sortareVector(int n, int* v)
{
	int ok = 1;
	while (ok)
	{
		ok = 0;
		for(int i = 1; i < n; i++)
			if (v[i - 1] > v[i])
			{
				swap(&v[i - 1], &v[i]);
				ok = 1;
			}
	}
}

void alocareVector(int n, int** v)
{
	*v = (int*)malloc(n * sizeof(int));
}

int* alocareVector2(int n)
{
	int* v = (int*)malloc(n * sizeof(int));
	return v;
}

int IsPrime(int n)
{
	if( n < 2)
		return 0;
	if (n % 2 == 0 && n != 2)
		return 0;
	for (int d = 3; d * d <= n; d += 2)
		if (n % d == 0)
			return 0;
	return 1;
}

void afisarenumerePrime(int n, int* v)
{
	for (int i = 0; i < n; i++)
		if (IsPrime(v[i]))
			printf("%d ", v[i]);
	printf("\n");
}
