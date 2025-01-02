#include <iostream>
using namespace std;

int CMMDC(int x, int y)
{
	while( y )
	{
		int rest = x % y;
		x = y;
		y = rest;
	}
	return x;
}

void Rezolvare(int &nm1, int &nm2)
{
	int n, nr1, nr2;
	int maxCMMDC = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> nr1 >> nr2;
		cout << CMMDC(nr1, nr2) << "\n";
		if (CMMDC(nr1, nr2) > maxCMMDC)
		{
			maxCMMDC = CMMDC(nr1, nr2);
			nm1 = nr1;
			nm2 = nr2;
		}
	}
}
int main()
{
	int nm1, nm2;
	Rezolvare(nm1,nm2);
	cout << nm1 << " " << nm2;
}
