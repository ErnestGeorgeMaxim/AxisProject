#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

// Macrocomenzi
/*
	#define PI 3.14159
	#define max(a,b) a > b ? a : b
					conditie ? val1 : val2
*/

/*	INSTRUCTIUNI
	-> if/else		
			if(conditie)
			{
				set de instructiuni 1
			}
			else 
			{
				set de instructiuni 2
			{

	-> switch
			switch (val)
			{
				case val1:
					set de instructiuni 1
					break;

				case val2:
					set de instructiuni 2
					break;
				...

				case valn:
					set de instructiuni n
					break;

				default:
					set de instructiuni
			}

	-> while
			while(conditie)
			{
				set de instructiuni
			}

	-> do...while
			do
			{
				set de intructiuni
			}while(conditie);
	
	-> for
			for(int i = 0; i < n; i++)
			{
				set de instructiuni;
			}
*/

#define PI 3.14159
#define max(a,b) (a > b) ? (a) : (b)
#define max3(a,b,c) (a > (max(b,c))) ? (a) : (max(b,c))
#define AREA(r) PI*(r)*(r)
#define PRODUS(a,b) (a)*(b)	

int main()
{
	int x, y;
	double a, b;// %lf pt double(long float)
	scanf("%lf%lf", &a, &b);
	printf("max(%lf,%lf) = %lf\n", a, b, max(a, b));

	scanf("%d%d", &x, &y);
	printf("max(%d,%d) = %d\n", x, y, max(x, y));

	int c, d, e;
	scanf("%d%d%d", &c, &d, &e);
	printf("max3(%d,%d,%d) = %d\n", c, d, e, max3(c, d, e));

	double r; // pi * r * r = 3.14 * 9 = 28,..
	// pi * r + 2 * r + 2
	r = 3;
	printf("Aria1 = %lf\n", AREA(r));//28,.. PI * r * r
	r = 1;
	printf("Aria2 = %lf\n", AREA(r + 2));// 7,.. PI * r + 2 * r + 2 = 3.14 * 1 + 2 * 1 + 2 = 7,14
	
	int t, s;
	t = 3;
	s = 7;
	printf("%d*%d = %d\n", t, s, PRODUS(t, s)); // 3 * 7 = 21 
	t = 2, s = 5;
	printf("%d*%d = %d\n", t+1, s+2, PRODUS(t+1, s+2)); //2 + 1 * 5 + 2 = 2 + 5 + 2 = 9
	// da 9 daca si numai daca macrofunctia nu are paranteze pt fiecare termen al inmultirii

	printf("\n\n\n");

	/*
		citim un n de la tastatura, daca :

		n = 1 -> citeste 2 val reale si afiseaza suma lor
		n = 2 -> afiseaza "Hello!"
		n = 3 -> citeste 2 valori intregi si afiseaza maximul dintre ele
		n != {1,2,3} -> "Optiunea nu este definita"
	*/

	int n;
	int ok = 1;

	while (ok)
	{
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			{
				double o, p;
				scanf("%lf%lf", &o, &p);
				printf("%lf + %lf = %lf", o, p, o + p);
				break;
			}
		case 2:
			{
				printf("Hello!");
				break;
			}
		case 3:
			{
				int o, p;
				scanf("%d%d", &o, &p);
				printf("max(%d,%d) = %d", o, p, max(o, p));
				break;
			}
		default:
			{
				ok = 0;
				printf("Optiunea nu este definita!");
			}
		}
	}


	int z, ogl = 0, aux;
	scanf("%d", &z);
	aux = z;
	while (aux)
	{
		ogl = ogl * 10 + aux % 10;
		aux /= 10;
	}
	if (ogl == z)
		printf("E palindrom");
	else
		printf("Nu e palindrom");
	return 0;
}