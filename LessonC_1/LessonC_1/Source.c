#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define max(a,b) ((a > b) ? (a) : (b))
#define sum(a,b) (a+b)*5 + a + b * 5
#define PI 3,14
#define min(a,b) ((a < b) ? (a) : (b))
#define max3(a,b,c) ((c > max(a,b)) ? (c) : (max(a,b)))
#define max4(a,b,c,d) ((d > max3(a,b,c)) ? (d) : (max3(a,b,c)))
#define merge(a,b) a##b // ## pt alipire a 2 tokeni
int main()
{
	int x;
	int v[100];
	char s[100];
	printf("%d %.1f %d %d %d %d\n", max(4, 3), sum(1, 2.3), min(3, 10), max3(34, 2, 5), max4(3, 5, 2, 6), merge(1, 2));
	printf("%d == %d\n", sizeof v, sizeof(int));
	printf("%d != %d\n", sizeof s, sizeof(char*));

	int nr_oct = sizeof(int) + sizeof(char) + sizeof(unsigned char) + sizeof(short int) + sizeof(short unsigned int) + sizeof(int) + sizeof(unsigned int) + sizeof(long long int) + sizeof(unsigned long long);
	printf("%d / 9 = %d\n", nr_oct, nr_oct / 9);

	int nr_oct_real = sizeof(float) + sizeof(double) + sizeof(long double);
	printf("%d / 3 = %d\n", nr_oct_real, nr_oct_real / 3);
	printf("\x4A == J\n");// transforma in baza 10 un nr in baza 16
	
	scanf("%s", s);
	printf("%s", s);
	return 0;
}