#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define power(a,b) (a)*(b)

int isPrime(int n)
{
	if (n < 2)
		return 0;
	if (n % 2 == 0 && n != 2)
		return 0;
	for (int d = 3; d * d <= n; d += 2)
		if (n % d == 0)
			return 0;
	return 1;
}

int oglinditNumar(int n)
{
	int ogl = 0;
	while (n)
	{
		ogl = ogl * 10 + n % 10;
		n /= 10;
	}
	return ogl;
}

int main()
{
	int n,x;
	scanf("%d%d", &n, &x);

	int m, k;
	scanf("%d%d", &m, &k);
	if (isPrime(n) == 1)
		printf("E prim!\n");
	else
		printf("Nu e prim!\n");
	for (int i = 2; i < n; i++)
		if (isPrime(i) == 1)
			printf("%d ", i);
	printf("\n");
	if (x == oglinditNumar(x))
		printf("Palindromic!\n");
	else
		printf("Nu e palindromic!\n");
	int j, s = 0;
	for (int i = 1; i <= m; i++)
	{
		j = 1;
		int nr = i;
		while (j < k)
		{
			nr = power(nr, i);
			j++;
		}
		printf("%d ", nr);
		s += nr;
	}
	printf("%d", s);

	for (int i = 0; i <= 255; i++)
	{
		printf("%c\n", );
	}
	return 0;
}