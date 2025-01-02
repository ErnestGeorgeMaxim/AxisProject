#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct
{
	char nume[50];
	char prenume[50];
	int varsta;
	float salariu;
}Persoana;

void CitirePersoana(Persoana* p)
{
	scanf("%s", &p->nume);
	scanf("%s", &p->prenume);
	scanf("%d%f", &p->varsta,&p->salariu);
}

int Compare(Persoana* p1, Persoana* p2)
{	
	if (strcmp(p1->nume, p2->nume) == 1)
			return 1;
	if (strcmp(p1->nume, p2->nume) == 0)
		if (strcmp(p1->prenume, p2->prenume) == 1)
			return 1;
	return 0;
}

void SwapPers(Persoana* p1, Persoana* p2)
{
	Persoana aux = *p1;
	*p1 = *p2;
	*p2 = aux;
}

void AfisPers(Persoana* p)
{
	printf("Nume %s -", p->nume);
	printf("Prenume %s -",p->prenume);
	printf("Varsta %d -",p->varsta);
	printf("Salariu %f\n",p->salariu);
}
int main()
{
	Persoana* p;
	int n;
	scanf("%d", &n);
	p = (Persoana*)malloc(n * sizeof(Persoana));
	for (int i = 0; i < n; i++)
		CitirePersoana(&p[i]);
	for (int i = 0; i < n - 1; i++)
		if (Compare(&p[i], &p[i + 1]) == 1)
			SwapPers(&p[i], &p[i + 1]);
	for (int i = 0; i < n; i++)
		AfisPers(&p[i]);
	free(p);
	return 0;
}