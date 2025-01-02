/*
* include-uri
* define -> macrocomenzi
* antete functii
* main
* implementarea functiei
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	int varsta;
	float x;
	printf("Cati ani ai? \n");
	scanf("%d%f", &varsta, &x); 
	printf("Tu ai %010d de ani %.0f\n", varsta, x);
	// la afisare de float-uri putem scapa de zecimale astfel
	// %f afiseaza 4 zecimale
	// %.2f afiseaza 2 zecimale
	// %.1f afiseaza 1 zecimala
	// %.0f afiseaza 0 zecimala
	// %-10d afiseaza 10 spatii dupa variabila
	// %10d afiseaza 10 spatii inainte variabila
	return 0;
}