#define _CRT_SECURE_NO_WARNINGS	
#include<stdio.h>
#include<malloc.h>

int main()
{
	int n	;
	double** mat, * vmax;
	scanf("%d", &n);
	double* p = (double**)malloc(n * (n + 1) * sizeof(double) + n * sizeof(double*));
	mat = (double**)p;
	if (p == NULL)
	{
		perror("Nu s-a alocat memeorie!");
		return 1;
	}
	for (int i = 0; i < n; i++)
		mat[i] = (double**)p + n * i;
	vmax = p + n * n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%lf", &mat[i][j]);
	for (int i = 0; i < n; i++)
	{
		vmax[i] = -1E10;
		for (int j = 0; j < n; j++)
			if (vmax[i] < mat[i][j])
				vmax[i] = mat[i][j];
	}
	for (int i = 0; i < n; i++)
		printf("%.0lf ", vmax[i]);
	free(p);
	free(mat);

	/*
	int n;
	double** mat, * vmax;
	scanf("%d", &n);
	mat = (double**)malloc(n * sizeof(double*));
	if (mat == NULL)
	{
		perror("Nu s-a alocat memorie!");
		return 1;
	}
	double* p = (double*)malloc(n * (n + 1) * sizeof(double));
	if (p == NULL)
	{
		perror("Nu s-a alocat memeorie!");
		return 1;
	}
	for (int i = 0; i < n; i++)
		mat[i] = p + n * i;
	vmax = p + n * n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%lf", &mat[i][j]);
	for (int i = 0; i < n; i++)
	{
		vmax[i] = -1E10;
		for (int j = 0; j < n; j++)
			if (vmax[i] < mat[i][j])
				vmax[i] = mat[i][j];
	}
	for (int i = 0; i < n; i++)
		printf("%.0lf ", vmax[i]);
	free(p);
	free(mat);
	*/
	return 0;
}