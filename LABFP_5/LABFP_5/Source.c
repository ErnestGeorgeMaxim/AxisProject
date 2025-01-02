#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "Functii.h"

//double Sum(double a, double b);
//void Swap(int *a, int *b);

int main()
{
	/*double a, b;
	int x, y;
	scanf("%lf%lf", &a, &b);
	scanf("%d%d", &x, &y);
	printf("&a = %p\n&b = %p\n");
	printf("%lf + %lf = %lf\n", a, b, Sum(a, b));
	printf("%d,%d =swap=> ", x, y);
	Swap(&x, &y);
	printf(" %d,%d", x, y);
	*/

	int n, * v;
	printf("Nr de elemente ale vectorului: ");
	scanf("%d", &n);
	alocareVector(n, &v);
	if(!v)
	{
		printf("Nu s-a realizat alocarea\n");
		return 1;
	}
	citireVector(n, v);
	printf("Suma = %d\n", sumaElementeVector(n, v));
	printf("Elementul maxim din vector = %d\n", maxVector(n, v));
	free(v);
	printf("Dati numarul de elemente pentru vectorul de sortat: ");
	scanf("%d", &n);
	v = alocareVector2(n);
	citireVector(n, v);
	sortareVector(n, v);
	afisareVector(n, v);
	free(v);
	v = alocareVector2(n);
	citireVector(n, v);
	afisarenumerePrime(n, v);
	free(v);
	return 0;
}

/*void Swap(int* a, int* b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

double Sum(double a, double b)
{	
	printf("&a = %p\n&b = %p\n", &a, &b);
	double s = a + b;
	return s;
}
*/