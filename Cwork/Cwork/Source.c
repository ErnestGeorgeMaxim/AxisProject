#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>

int main()
{
	int x, n, *a;
	scanf("%d%d", &n, &x);
	a = (int*)malloc((n+1) * sizeof(int*));
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	a[n] = &x;
	for (int i = 0; i <= n; i++)
		printf("%d, ", a[i]);
	return 0;
}