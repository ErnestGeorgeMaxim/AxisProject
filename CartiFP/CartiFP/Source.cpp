#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
3
Frank Herbert
Dune
2012
Issac Asimov
Fundatia
1961
Bram Stoker
Dracula
1897

*/

struct Book
{
	char author[50];
	char title[50];
	int yearOfPublication;
};

typedef struct Book Book;

void allocateVector(Book** book, int n)
{
	*book = (Book*)malloc(n * sizeof(Book));
	if (!(*book))
	{
		perror("Nu s-a alocat memorie!\n");
		return;
	}
}

int readBooks(FILE* fis, Book** book, int* n)
{
	if (!fis)
	{
		perror("Nu s-a deschis fisierul!\n");
		return 0;
	}
	if (fscanf(fis, "%d", n) != 1)
		return 0;
	fgetc(fis);
	allocateVector(book, *n);
	for (int i = 0; i < (*n); i++)
	{
		if (fgets((*book)[i].author, 50, fis) == NULL)
		{	
			perror("Nu s-a citit corect sirul!\n");
			return 0;
		}
		if (fgets((*book)[i].title, 50, fis) == NULL)
		{
			perror("Nu s-a citit corect sirul!\n");
			return 0;
		}
		if(fscanf(fis,"%d", &(*book)[i].yearOfPublication) != 1)
		{
			perror("Nu s-a citit corect valoarea!\n");
			return 0;
		}
		fgetc(fis);
	}
	return 1;
}

void swapCarti(Book* a, Book* b)
{
	 Book aux = *a;
	 *a = *b;
	 *b = aux;
}

int comparatorBooks(Book* a, Book* b)
{
	if (strcmp(a->author, b->author) == 1)
		return 1;
	else if (strcmp(a->author, b->author) == 0)
		if (strcmp(a->title, b->title) == 1)
			return 1;
	return 0;
}

void writeBooks(Book* book, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%s", book[i].author);
		printf("%s", book[i].title);
		printf("%d", book[i].yearOfPublication);
		printf("\n");
	}
}

int oldestBook(Book* book, int n)
{
	int min = 1000000, poz;
	for (int i = 0; i < n; i++)
		if (min > book[i].yearOfPublication)
			min = book[i].yearOfPublication, poz = i;
	return poz;
}




int main()
{
	Book* book;
	FILE* fis = fopen("carti.txt", "r");
	int n;
	readBooks(fis, &book, &n);
	writeBooks(book, n);
	printf("\n");
	for (int i = 1; i < n; i++)
		if (comparatorBooks(&book[i - 1], &book[i]))
			swapCarti(&book[i - 1], &book[i]);
	writeBooks(book, n);
	int x = oldestBook(book, n);
	printf("\n%s", book[x].author);
	printf("%s", book[x].title);
	printf("%d", book[x].yearOfPublication);

	FILE* fisb = fopen("cartibinare.txt", "wb");
	if (!fisb)
	{
		perror("Error opening binary file!\n");
		free(book);
		return 1;
	}
	fwrite(&n, sizeof(int), 1, fisb);
	fwrite(book, sizeof(Book), n, fisb);
	fclose(fisb);
	fclose(fis);
	free(book);
	return 0;
}