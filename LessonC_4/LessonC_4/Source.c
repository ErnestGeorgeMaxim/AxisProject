#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

int main()
{
	int* v;
	int var;
	v = &var + 1;// aduna 4 octeti la adresa retinuta de v din var
	v += 10;
	// -1 scade 4 octeti la adresa
	// +1 aduna 4 octeti la adresa
	printf("%d\n", sizeof(*v)); // == 4
	printf("%p\n", &var);

	int* a;
	a = (int*)malloc(4 * sizeof(int));
	for (int i = 0; i < 4; i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < 4; i++)
	{
		printf("%d\n", *(a + i));// *(a+i) afiseaza valoarea de la adresa elementului a[i]
		printf("%p\n", (a + i));// (a+i) afiseaza adresa la care se afla elemntul a[i]
	}
	free(a);

	int i,k,* s;
	printf("Dati lungimea vectorului: ");
	scanf("%d", &k);
	s = (int*)malloc(k * sizeof(int));
	if (a == NULL)
	{
		perror("Memorie insuficienta!");
		exit(0);
	}
	for (i = 0; i < k; i++)
	{
		printf("a[%d] =", i);
		scanf("%d", &a[i]);
	}
	for (i = 0; i < k; i++)
		printf("%d ", a[i]);
	printf("\n\n");
	free(a);

	/*
	a = (int*)malloc(n * sizeof(int)) - aloca memorie
	a = (int*)calloc(n, sizeof(int)) - aloca memorie si initializeaza intreg vectorul cu 0
	a = (int*)realloc(a,m * sizeof(int)) - realoca memorie pentru a schimba marimea vectorului
	*/

	int n, m;
	float** mat;
	scanf("%d%d", &n, &m);
	mat = (float**)malloc(n * sizeof(float*));
	if( mat == NULL )
	{
		perror("Nu s-a alocat destula memorie!");
		exit(1);
	}
	mat[0] = (float*)malloc(n * m * sizeof(float));
	if (mat[0] == NULL)
	{
		perror("Nu s-a alocat destula memorie!");
		exit(1);
	}
	for (int i = 1; i < n; i++)
		mat[i] = mat[i - 1] + m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%f", &mat[i][j]);


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%.0f", mat[i][j]);
		printf("\n");
	}
	free(mat[0]);
	free(mat);

	return 0;
}