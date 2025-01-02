#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

struct Persoana
{
	char nume[100];
	int varsta;
	float salariu;
};

int main()
{
	struct Persoana pers[4];
	for (int i = 0; i < 4; i++)
		scanf("%s%d%f", &pers[i].nume, &pers[i].varsta, &pers[i].salariu);

	float medieV, medieS;
	float sumV = 0, sumS = 0;
	for (int i = 0; i < 4; i++)
	{
		sumV += pers[i].varsta;
		sumS += pers[i].salariu;
	}
	medieV = sumV / 4;
	medieS = sumS / 4;
	printf("______________________________________________\n");
	printf("|Nr. | NUMELE SI PRENUMELE  | VARSTA| SALARIU|\n");
	printf("|crt.|			    |	    |	     |\n");
	printf("|----+----------------------+-------+--------|\n");
	printf("|   1|%s        |     %d|  %.2f|\n",pers[0].nume, pers[0].varsta, pers[0].salariu);
	printf("|   2|%s |     %d|  %.2f|\n", pers[1].nume, pers[1].varsta, pers[1].salariu);
	printf("|   3|%s         |     %d|  %.2f|\n", pers[2].nume, pers[2].varsta, pers[2].salariu);
	printf("|   4|%s         |     %d| %.2f|\n", pers[3].nume, pers[3].varsta, pers[3].salariu);
	printf("|----+----------------------+-------+--------|\n");
	printf("| Medie                     |  %.2f|  %.2f|\n", medieV, medieS);
	printf("----------------------------------------------\n");

	return 0;
}