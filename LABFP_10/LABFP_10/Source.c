#define _CRT_SECURE_NO_WARNINGS	
#include<stdio.h>
#include<stdarg.h>

/*
tip nume_fct (tip1 param, ...)
{
	va_list argum;
	va_start(argum, param);
	..........
	p = va_arg(argum, tip_p);
	..........
	va_end(argum);
}
*/

int min(int n, ...)
{
	va_list arg;
	int min = 9999999, p;
	va_start(arg, n);
	for (int i = 0; i < n; i++)
	{
		p = va_arg(arg, int);
		if (p < min)
			min = p;
	}
	va_end(arg);
	return min;
}

double Sum(int n, ...)
{
	va_list arg;
	double sum = 0, p;
	va_start(arg, n);
	for (int i = 0; i < n; i++)
	{
		p = va_arg(arg, double);
		sum += p;
	}
	va_end(arg);
	return sum;
}

void prodAndMax(char* format, ...)
{
	va_list arg;
	double max = -9999999, p;
	int prod = 1, i = 0;
	va_start(arg, format);
	while (format[i] != '\0')
	{
		if (format[i] == 'd')
			prod *= va_arg(arg, int);
		else if (format[i] == 'f')
		{
			p = va_arg(arg, double);
			if (max < p)
				max = p;
		}
		i++;
	}
	printf("Produsul = %d \nMax = %.2lf\n", prod, max);
	va_end(arg);
}

void fct()
{
	static int cnt = 0;
	printf("%d\n", ++cnt);
}

int main()
{
	prodAndMax("ddffdf", 3, 2, 5.6, 9.8, 9, 7, 8);
	printf("min3 = %d\n", min(3, 56, 25, 78));
	printf("min5 = %d\n", min(5, 10, 8, 56, 25, 78));
	printf("sum5 = %lf\n", Sum(5, 12.0, 12.3, 3., 4., 5.98));//la double sa pui punct dupa ca sa ti iasa corect
	fct();
	fct();
	fct();
	return 0;
}