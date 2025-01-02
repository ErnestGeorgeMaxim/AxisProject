#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

void alocareMatrice1(int n, int m, float*** mat);
float** alocareMatrice2(int n, int m);
void afisareMatrice(int n, int m, float** mat);
void citireMatrice(int n, int m, float** mat);
void getVectorMedii(int n, int m, float** mat, float** medii);
void swap(float* x, float* y);
void swap_ptr(float** x, float** y);
int partitionare(int first, int last, float* medii, float** mat);
void qSort(int first, int last, float* medii, float** mat);
/*
*A254 5 6 7 8		1 2 3 4
*3B98 9 10 11 12 => 5 6 7 8
*574F 1 2 3 4		9 10 11 12
* 
*/

int main()
{
	float** mat, * medii;
	int n, m, i;
	printf("Dimensiunile matricei:\n");
	scanf("%d%d", &n, &m);
	alocareMatrice1(n, m, &mat);
	citireMatrice(n, m, mat);
	getVectorMedii(n, m, mat, &medii);
	qSort(0, n - 1, medii, mat);
	afisareMatrice(n, m, mat);
	free(medii);
	for (i = 0; i < n; i++)
		free(mat[i]);
	free(mat);

	return 0;
}

void alocareMatrice1(int n, int m, float*** mat)
{
	int i;
	*mat = (float**)malloc(n * sizeof(float*));
	for (i = 0; i < n; i++)
		(*mat)[i] = (float*)malloc(m * sizeof(float));
}
float** alocareMatrice2(int n, int m)
{
	int i;
	float** mat;
	mat = (float**)malloc(n * sizeof(float*));
	float *p = (float*)malloc(n * m * sizeof(float));
	for (i = 0; i < n; i++)
		mat[i] = p + i*m;
	return mat;
}
void afisareMatrice(int n, int m, float** mat)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			printf("%6.2f ", mat[i][j]);
		printf("\n");
	}
}
void citireMatrice(int n, int m, float** mat)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			scanf("%f", &mat[i][j]);
	}
}
void getVectorMedii(int n, int m, float** mat, float** medii)
{
	int i, j;
	*medii = (float*)calloc(n, sizeof(float));
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			(*medii)[i] += mat[i][j];
		(*medii)[i] /= m;
	}
}
void swap(float* x, float* y)
{
	float aux = *x;
	*x = *y;
	*y = aux;
}
void swap_ptr(float** x, float** y)
{
	float* aux = *x;
	*x = *y;
	*y = aux;
}
int partitionare(int first, int last, float* medii, float** mat)
{
	float p = medii[last];
	int i = first, j;
	for (j = first; j <= last; j++)
	{
		if (medii[j] < p)
		{
			swap(&medii[i], &medii[j]);
			swap_ptr(&mat[i], &mat[j]);
			i++;
		}
	}
	swap(&medii[i], &medii[last]);
	swap_ptr(&mat[i], &mat[last]);
	return i;
}
void qSort(int first, int last, float* medii, float** mat)
{
	int i;
	if (first < last)
	{
		i = partitionare(first, last, medii, mat);
		qSort(first, i-1, medii, mat);
		qSort(i+1, last, medii, mat);
	}
}