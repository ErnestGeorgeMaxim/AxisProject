#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct Complex
{
    int re, im;
};

typedef struct Complex Complex;

void allocationVectorOfComplexNumbers(Complex** comp, int n)
{
    *comp = (Complex*)malloc(n * sizeof(Complex));
    if (!*comp) // Check if allocation was successful
    {
        perror("Error allocating memory!\n");
        exit(1);
    }
}

int readComplexNumbersFromFile(FILE* fis, Complex** comp, int* n)
{
    if (fscanf(fis, "%d", n) != 1) // Use fscanf to correctly read an integer
        return 0;

    allocationVectorOfComplexNumbers(comp, *n);

    for (int i = 0; i < *n; i++)
        fscanf(fis, "%d%d", &(*comp)[i].re, &(*comp)[i].im);

    return 1;
}

void writeComplexNumbers(Complex* comp, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (comp[i].im == 0)
            printf("%d\n", comp[i].re);
        else if (comp[i].re == 0)
            printf("i * %d\n", comp[i].im);
        else
            printf("%d + i * %d\n", comp[i].re, comp[i].im);
    }
}


int compareComplexNumbers(const void* a, const void* b)
{
    double moda, modb;
    Complex* compa = (Complex*)a;
    Complex* compb = (Complex*)b;
    moda = sqrt((compa->im * compa->im) + (compa->re * compa->re));
    modb = sqrt((compb->im * compb->im) + (compb->re * compb->re));

    if (moda < modb)
        return 1;
    else
        return 0;
}

double generateModule(Complex* a)
{
    return sqrt((a->re * a->re) + (a->im * a->im));
}

double sumOfModules(Complex* comp, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += generateModule(&comp[i]);
    return sum;
}

void writeBinaryComplex(FILE* fis, Complex* comp, int n)
{
    if (!fis)
    {
        perror("Eroare!\n");
        return ;
    }
    fwrite(comp, sizeof(Complex), n, fis);
}

int main()
{
    FILE* fis = fopen("complex.txt", "r");
    Complex* comp;
    int n;
    if (!fis)
    {
        perror("Eroare in deschiderea fisierului!\n");
        return 1;
    }
    if (!readComplexNumbersFromFile(fis, &comp, &n))
    {
        perror("File not read successfully!\n");
        fclose(fis);
        return 1;
    }
    fclose(fis);
    writeComplexNumbers(comp, n);
    printf("%.0lf\n", sumOfModules(comp, n));
    qsort(comp, n, sizeof(Complex), compareComplexNumbers);
    writeComplexNumbers(comp, n);
    FILE* fisb = fopen("complexbinar.txt", "wb");
    writeBinaryComplex(fisb, comp, n);
    free(comp);
    return 0;
}
