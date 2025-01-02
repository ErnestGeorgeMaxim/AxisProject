#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    FILE* fisier;
    char linie[100];  // presupunem că linia nu va depăși 100 de caractere

    fisier = fopen("VaiDeRares.txt", "r");  // înlocuiți "nume_fisier.txt" cu numele real al fișierului

    if (fisier == NULL) {
        printf("Nu am putut deschide fisierul.\n");
        return 1;
    }

    int numar_linie = 1;

    while (fgets(linie, sizeof(linie), fisier) != NULL) {
        if (numar_linie % 2 == 1) {
            printf("%s", linie);
        }
        numar_linie++;
    }

    fclose(fisier);

    return 0;
}
