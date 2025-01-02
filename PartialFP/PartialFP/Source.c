#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Produs
{
	char nume_produs[30];
	int cantitate;
	int pret;
};

typedef struct Produs Produs;

Produs readProduct(FILE* fis)
{
	Produs product;
	if (!fgets(&product.nume_produs, 30, fis))
	{
		perror("Nu s-a citit sirul!\n");
		return;
	}
	product.nume_produs[strlen(product.nume_produs) - 1] = '\0';
	if(fscanf(fis, "%d%d", &product.cantitate, &product.pret) != 2 )
	{
		perror("Nu s-au citit numerele!\n");
		return;
	}
	char s[30];
	fgets(s, 30, fis);
	return product;
}

void writeAProduct(Produs* prod)
{
	printf("%s:", prod->nume_produs);
	printf("%d x %d\n", prod->cantitate, prod->pret);
}

void writeProducts(Produs* prod, int n)
{
	for (int i = 0; i < n; i++)
		writeAProduct(&prod[i]);
}

void allocateVector(Produs **prod, int n)
{
	(*prod) = (Produs*)malloc(n * sizeof(Produs));
	if (!(*prod))
	{
		perror("Nu s-a alocat memorie!\n");
		exit(1);
	}
}

int readVector(FILE* fis, Produs **prod,int* n)
{
	int r = fscanf(fis, "%d", &(*n));
	if (r != 1)
		return 0;
	fgetc(fis);
	allocateVector(prod, *n);
	for (int i = 0; i < *n; i++)
	{
		(*prod)[i] = readProduct(fis);
	}
	return 1;
}

int compareProducts(const void* a, const void* b)
{
	Produs *proda = b;
	Produs *prodb = a;
	int preta = proda->pret * proda->cantitate;
	int pretb = prodb->pret * prodb->cantitate;
	if (preta < pretb)
		return 1;
	else if (preta == pretb)
		if (strcmp(proda->nume_produs, prodb->nume_produs) == -1)
			return 1;
	return 0;
}

int mostExpansiveProduct(Produs* prod, int n)
{
	int maxi = -1, pos;
	for (int i = 0; i < n; i++)
		if (prod[i].pret > maxi)
			maxi = prod[i].pret, pos = i;
	return pos;
}

int main()
{
	FILE* fis = fopen("produse.txt", "r");
	Produs* prod;
	int n;
	if (!fis)
	{
		perror("Fisierul nu s-a deschis!\n");
		fclose(fis);
		return 1;
	}
	readVector(fis, &prod, &n);
	writeProducts(prod, n);
	int x = mostExpansiveProduct(prod, n);
	printf("\n");
	writeAProduct(&prod[x]);
	printf("\n");
	qsort(prod, n, sizeof(Produs), compareProducts);
	writeProducts(prod, n);
	FILE* fisb = fopen("produsebinare.txt", "wb");
	if (!fisb)
	{
		perror("Nu s-a deschis fisierul!\n");
		fclose(fisb);
		return 1;
	}
	fwrite(&n, sizeof(int), 1, fisb);
	fwrite(prod, sizeof(Produs),n, fisb);
	fclose(fisb);
	fclose(fis);
	free(prod);
	return 0;
}
