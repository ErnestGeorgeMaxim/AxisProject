#include<iostream>

int partitionare(int v[], int n, int st, int dr)
{
	int pivot = v[dr];
	int i = st;
	for (int j = i; j < dr; ++j) {
		if (v[j] < pivot) {
			std::swap(v[i], v[j]);
			i++;
		}
	}
	std::swap(v[i], v[dr]);
	return i;
}

int CautareC(int a[][101], int st, int dr, int x, int &poz)
{
	int mij = (st + dr)/2;
	if (a[0][mij] == x)
	{
		poz = mij;
		return a[0][mij];
	}
	if (a[0][mij] < x)
		return CautareC(a, mij + 1, dr, x, poz);
	return CautareC(a, st, mij, x, poz);
}

void Citire(int a[][101], int& n, int& m, int &x)
{
	std::cin >> n >> m;
	std::cin >> x;
	for (int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			std::cin >> a[i][j];
}

int main()
{
	//20 1 7 10 3 5
	int n, m, v[101][101], x;
	Citire(v, n, m, x);
	std::cout << CautareC(v, n, m, 0, n - 1);
	return 0;
}