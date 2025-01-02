#include <iostream>
using namespace std;

int Rezolvare(int n)
{
	int f[10] = {};
	while (n)
	{
		f[n % 10]++;
		n /= 10;
	}
	for (int i = 0; i <= 9; i++)
	{
		while (f[i])
		{
			n = n * 10 + i;
			f[i]--;
		}
	}
	return n;
}

int main()
{
	cout << Rezolvare(1204192);
}


