#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Complex
{
	int re, im;
};

typedef struct Complex Complex;

int readComplexNumber(FILE* fis, Complex* comp)
{
	if (feof(fis))
		return 0;
	int r = fscanf("%d%d", &comp->re, &comp->im);
	if (r != 2)
	{
		perror("Eroare citire fisier!\n");
		return 0;
	}
	return 1;
}

int main() 
{
	FILE* fis = fopen("complex.txt", "r");
	Complex* comp;
	int n;
	if (!fis)
	{
		perror("Eroare deschidere fisier!\n");
		return 1;
	}
	fscanf(fis, "%d", &n);
	comp = (Complex*)malloc(n * sizeof(Complex));
	if (!comp )
	{
		perror("Eroare de alocare a memoriei!\n");
		fclose(fis);
		return 1;
	}
	for (int i = 0; i < n; i++)
	{
		if (!readComplexNumber(fis, &comp[i]))
		{
			fclose(fis);
			free(comp);
			return 1;
		}
	}
	fclose(fis);
	for (int i = 0; i < n; i++)
	{
		if (comp[i].im != 0)
			printf("%d + i * %d\n", comp[i].re, comp[i].im);
		else
			printf("%d\n", comp[i].re);
	}
	free(comp);
}

