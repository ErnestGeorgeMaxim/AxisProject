#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>


/*
				ALOCARE DINAMICA

	float* sir;
	// facem operatii cu el

	sir = (float *)realloc(sir , nr_nou_de_octeti)
	n = 5
	7 5 8 2 4 10
	   |
	   x =[0,n]

	sir[i] = *(sir+i)
	&sir[i] = &*(sir+i) = sir+i (cei doi operatori &* se anuleaza)
*/

int main()
{
	/*
	int n;
	float* sir, x;
	printf("Dimensiunea sirului:");
	scanf("%d", &n);
	sir = (float*)malloc(n * sizeof(float));
	if (!sir)
	{
		perror("Alocarea nu s a realizat cu succes!\n");
		return 1;
	}
	for (int i = 0; i < n; i++)
		scanf("%f", sir + i);
	//scanf("%f", sir[i]);

	printf("Elemtentul nou: ");
	scanf("%f", &x);

	if (!sir)
	{
		perror("Alocarea nu s a realizat cu succes!\n");
		return 1;
	}

	printf("%p\n", sir);
	sir = (float*)realloc(sir, (n + 1) * sizeof(float));
	printf("%p\n", sir);
	//sir[n] = x;
	*(sir + n) = x;
	for (int i = 0; i <= n; i++)
		printf("%.2f ", *(sir + i));
	//printf("%.2f ", sir[i]);

	int k;
	printf("Pozitia pe case se insereaza: ");
	scanf("%d", &k);
	if (k < 0 || k > n)
	{
		perror("Pozitia de inserat nu este valida!");
		return 1;
	}
	sir = (float*)realloc(sir, (n + 2) * sizeof(float));
	for (int i = n+1; i > k; i--)
		sir[i] = sir[i - 1];
	sir[k] = x;
	for (int i = 0; i <= n+1; i++)
		printf("%.2f ", *(sir + i));
	free(sir);
	*/
	//sa se implementeze un program c in care sa se aloce spatiu pt o mat cu n linii si m coloane
	//se calculeaza media elementelor de pe fiecare linie in parte
	// sa se afiseze sirul de medii


	int n, m, i, j;
	scanf("%d%d", &n, &m); // adresa lui n si m
	float* sir;
	int** a;
	a = (int**)malloc(n * sizeof(int*));
	a[0] = (int*)malloc(n * m * sizeof(int));
	for (i = 1; i < n; i++)
		a[i] = a[i - 1] + m;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
		{
			printf("a[%d][%d] = ", i, j);
			scanf("%d", *(a + i) + j);
			//echivalent cu scanf("%d", a[i][j]);
		}
	sir = (float*)calloc(n, sizeof(float));
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			sir[i] += a[i][j];
		sir[i] /= m;
	}
	for (i = 0; i < n; i++)
		printf("%.2f ", sir[i]);

	free(sir);
	free(a[0]);
	free(a);
	return 0;
}