#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <malloc.h>

/*
	FILE* fis = fopen("Nume_fisire","r");
									"w"
									"a"
									"rb"
									"wb"
									"ab"
									"r+"

	fprintf(fis , formatare , variabile);
	fprintf(fis, "Hello World! in fis %d", n);
	fscanf(fis, formatam,variabile);
	fgets(fis, s) - extrage o linie din cod din fis
	fputs(fis, s) - adauga o linie in cod din fis

	fread(pointer, nr date, dim_date, fis)
	int *pointer
	int n;
	dim_date = sizeof(int);
*/

int main()
{
	char s[101];
	FILE* fis_in = fopen("fis_in.txt","r");
	FILE* fis_out = fopen("fis_out.txt", "w");
	int n, cnt = 0;
	if (!fis_in)
	{
		printf("Fisierul fis_in.txt nu s-a deschis pentru citire!\n");
		return 1;
	}
	if (!fis_out)
	{
		printf("Fisierul fis_out.txt nu s-a deschis pentru citire!\n");
		return 1;
	}
	scanf("%d", &n);
	printf("Linia ce trebuie stearsa este: %d\n", n);
	while (!feof(fis_in))
	{
		fgets(s, 101, fis_in);
		if (cnt != n)
			fputs(s, fis_out);
		cnt++;
	}
	fclose(fis_in);
	fclose(fis_out);
	return 0;
}