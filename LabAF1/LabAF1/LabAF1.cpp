#include <iostream>
#include <cmath>
using namespace std;

int Reverse(int n)
{
	int ogl = 0;
	while (n)
	{
		ogl = ogl * 10 + n % 10;
		n /= 10;
	}
	return ogl;
}

int Similar(int n)
{
	int x, i = 2, nr, cnt = 0;
	cin >> x;
	x = Reverse(x);
	while (i <= n)
	{
		cin >> nr;
		if (nr == x)
			cnt++;
		i++;
	}
	return cnt;
}

bool EPalindrom(int n)
{
	return n == Reverse(n);
}

void Palindroame(int a, int b)
{
	for (int i = a; i <= b; i++)
		if (EPalindrom(i))
			cout << i << " ";
}

int CelMaiMicNr(int n)
{
	int f[10] = {};

	while (n)
	{
		f[n % 10]++;
		n /= 10;
	}

	for( int i = 1; i < 10; i++)
		if(f[i])
			while (f[i])
			{
				n = n * 10 + i;
				f[i]--;
			}
	return n;
}

bool ProgresieA(int n)
{
	int ratie = n % 10 - (n / 10 % 10);
	if (n < 100)
		return false;
	while (n > 9)
	{
		if (n % 10 - (n / 10 % 10) != ratie)
			return false;
		n /= 10;
	}
	return true;
}

int NrZero(int n)
{
	int cnt = 0;
	while (n % 10 == 0)
	{
		cnt++;
		n /= 10;
	}
	return cnt;
}

int NrCif(int n)
{
	int cnt = 1;
	n /= 10;
	while (n)
	{
		cnt++;
		n /= 10;
	}
	return cnt;
}

int Pozitie(int n)
{
	
	int nrCifre = NrCif(n);
	int poz = -1;
	while (nrCifre > 1)
	{
		int prima = n / (int)pow(10, nrCifre - 1);
		int aDoua = n / (int)pow(10, nrCifre - 2) % 10;
		if (prima < aDoua)
			return nrCifre - 1;
		n = n % (int)pow(10, nrCifre - 1);
		nrCifre--;
	}
	return poz;

}

int CelMaiMareNumar(int n)
{
	int ind = 0;
	int pozitie = Pozitie(n) + 1;
	int p = 1, nrNou = 0;
	while (n)
	{
		if (ind != pozitie - 1)
		{
			nrNou = nrNou + p * (n % 10);
			p *= 10;
		}
		ind++;
		n /= 10;
	}

	return nrNou;
}

int main()
{
	cout << CelMaiMareNumar(1111);
	return 0;
}
