#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>

struct Persoana
{
	char nume[101];
	int varsta;
	float salariu;
};

typedef struct Persoana Persoana;

int main()
{
	printf("________________________________________________________\n");
	printf("|Denumire tip        |Numar octeti |Domeniu de valori  |\n");
	printf("|____________________|_____________|___________________|\n");
	printf("|(signed) char       |	   1	   |    -128 la 128    |\n");
	printf("|____________________|_____________|___________________|\n");
	printf("|unsigned char       |	   1	   |      0 la 255     |\n");
	printf("|____________________|_____________|___________________|\n");
	printf("|enum      	     |	   2	   | -32.768 la 32.767 |\n");
	printf("|____________________|_____________|___________________|\n");
	printf("|short(signed) (int) |	   2	   |    0 la 65.535    |\n");
	printf("|____________________|_____________|___________________|\n");
	printf("|short unsigned (int)|	   2	   | -32.768 la 32.767 |\n");
	printf("|____________________|_____________|___________________|\n");
	printf("|(signed) int	     |	   4	   | -2.147.483.648 la |\n");
	printf("|		     |	   	   |   2.147.483.647   |\n");
	printf("|____________________|_____________|___________________|\n");
	printf("|unsigned int	     |	   4 	   |0 la 4.294.967.295 |\n");
	printf("|____________________|_____________|___________________|\n");
	printf("|(signed) long	     |	   4	   | -2.147.483.648 la |\n");
	printf("|		     |	           |   2.147.483.647   |\n");
	printf("|____________________|_____________|___________________|\n");
	printf("|unsigned long	     |     4 	   |0 la 4.294.967.295 |\n");
	printf("|____________________|_____________|___________________|\n");

	printf("\n\n\n\n\n");

	int n;
	float sv, ss;
	sv = ss = 0;
	scanf("%d", &n);
	Persoana pers[10];
	for (int i = 0; i < n; i++)
	{
		scanf("%d%f%s", &pers[i].varsta, &pers[i].salariu, &pers[i].nume);
		sv += pers[i].varsta;
		ss += pers[i].salariu;
	}
	float mv, ms;
	mv = sv / 4.0;
	ms = ss / 4.0;

	printf("______________________________________________________________________\n");
	printf("|Nr.  |NUMELE SI PRENUMELE                           |VARSTA|SALARIU |\n");
	printf("|crt. |                                              |      |        |\n");
	printf("|-----+----------------------------------------------+------+--------|\n");
	printf("|%5d|%-46s|%6d|%8.1f|\n",1,pers[0].nume,pers[0].varsta,pers[0].salariu);
	printf("|-----+----------------------------------------------+------+--------|\n");
	printf("|%5d|%-46s|%6d|%8.1f|\n",2,pers[1].nume,pers[1].varsta,pers[1].salariu);
	printf("|-----+----------------------------------------------+------+--------|\n");
	printf("|%5d|%-46s|%6d|%8.1f|\n", 3, pers[2].nume, pers[2].varsta, pers[2].salariu);
	printf("|-----+----------------------------------------------+------+--------|\n");
	printf("|%5d|%-46s|%6d|%8.1f|\n", 4, pers[3].nume, pers[3].varsta, pers[3].salariu);
	printf("|----------------------------------------------------+------+--------|\n");
	printf("| MEDIE                                              |%6.2f|%8.2f|\n", mv, ms);
	printf("----------------------------------------------------------------------\n");
	return 0;
}