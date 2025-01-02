#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

int main()
{
	int* sir, n, *sir_impare, n_impare;
	FILE* fis_in = fopen("sirNumere.txt", "r");
	FILE* fis_out = fopen("fis_out", "wb");
	if (!fis_in)
	{
		printf("Fisierul sirNumere.txt nu s-a deschis!");
		return 1;
	}
	if (!fis_out)
	{
		printf("Fisierul fis_out.txt nu s-a deschis!");
		return 1;
	}
	fscanf(fis_in, "%d", &n);
	sir = (int*)malloc(n * sizeof(int));
	if (!sir)
	{
		printf("Sirul nu s-a alocat!");
		return 1;
	}
	for (int i = 0; i < n; i++)
		fscanf(fis_in, "%d", &sir[i]);
	n_impare = 0;
	for (int i = 0; i < n; i++)
		if (sir[i] % 2)
			n_impare++;
	sir_impare = (int*)malloc(n_impare * sizeof(int));
	if (!sir_impare)
	{
		printf("Sirul nu s-a alocat!");
		return 1;
	}
	int cnt = 0;
	for (int i = 0; i < n; i++)
		if (sir[i] % 2)
			sir_impare[cnt++] = sir[i];
	fwrite(&n_impare, 1, sizeof(int), fis_out);
	fwrite(&sir_impare, sizeof(int), n_impare, fis_out);

	fclose(fis_in);
	fclose(fis_out);
	free(sir);
	free(sir_impare);
	return 0;
}