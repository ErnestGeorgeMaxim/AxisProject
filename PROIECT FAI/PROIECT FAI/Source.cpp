#include <iostream>

void Citire(int &a, int &b, int &n)
{
	std::cout << "Introduceti numerele dorite: \n\n";
	std::cout << "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;
	std::cout << "n = ";
	std::cin >> n;
	std::cout << "\n\n";
}

int CMMDC(int a, int b)
{
	while (b)
	{
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

std::pair<int, int> K_L(int a, int n, int c)
{
	std::pair<int, int> KL;
	a = a / c;
	n = n / c;
	// KL.first = k
	// KL.second = l
	// a * k + n * l		 = 1
	// a * k = 1 - n * l
	KL.second = 1;//l
	if (a != 0 && a != 1)
	{
		while (n * KL.second % a != 1) // cautam l
		{
			KL.second++;
		}
		KL.first = n * (-KL.second) / a; // k = ( -n * l) / a
	}
	else
	{
		KL.second = 1; // l = 1
		KL.first = -(n-1); // k = 0
	}
	return KL;
}

void ElmInv(int n)
{
	int i = 0;
	if (n > 0)
	{
		std::cout << "{ ";
		while (i < n)
		{
			if (CMMDC(i, n) == 1)
				std::cout << i << ", ";
			i++;
		}
		std::cout << "\b\b";
		std::cout << " }\n\n";
	}
	else
		std::cout << "multimea vida\n\n";
}

void Inmultire(int a, int b, int n)
{
	int x = 0, ok = 0;
	std::cout << "{ ";
	while (x < n)
	{
		if ((a * x) % n == b % n )
		{
			std::cout << x << ", ";
			ok = 1;
		}
		x++;
	}
	std::cout << "\b\b }";
	if( ok == 0 )
		std::cout << "\b\b\b\b multimea vida";
	std::cout << "\n\n";
}

void Rezolvare()
{
	int a, b, n;
	Citire(a, b, n);
	std::cout << "Cerinta 1: CMMDC(a,n) = ";
	std::cout << CMMDC(a, n) << "\n\n";
	std::cout << "Cerinta 2: a*k + n*l = CMMMDC(a,n) => ";
	std::cout << K_L(a, n, CMMDC(a, n)).first << "*" << a << " + " << K_L(a, n, CMMDC(a, n)).second << "*" << n << " = " << CMMDC(a, n) << "\n\n";
	std::cout << "Cerinta 3: U(Z " << n << ") = ";
	ElmInv(n);
	std::cout << "Cerinta 4: a * x = b in (Z " << n << ") => ";
	Inmultire(a, b, n);
}

int main()
{
	Rezolvare();
	return 0;
}