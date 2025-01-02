#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<varargs.h>
#include <algorithm>


int suma(int n, ...)
{
	va_list list;
	int s = 0, arg;
	va_start(list, n);
	for (int i = 0; i < n; i++)
	{
		arg = va_arg(list, int);
		s += arg;
	}
	va_end(list);
	return s;
}

int comparator(int a, int b)
{
	return a > b;
}

int main()
{
	int* arr;
	int n;
	scanf("%d", &n);
	arr = (int*)malloc(n * sizeof(int));
	if (arr == NULL)
	{
		perror("Memorie insuficienta!");
		exit(1);
	}
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	qsort(arr, n, sizeof(int*), comparator);
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("%d", suma(4, 2, 4, 10, 3));
	return 0;
}