#include <iostream>

void CitireVect(int& n, int*& v)
{
	std::cin >> n;
	v = new int[n];
	for (int i = 0; i < n; i++)
		std::cin >> v[i];
}

void ModifVect(int*& v, int& n)
{
	int nrelm = 2;
	for (int i = 1; i < n - 1; i++)
		if (v[i] != v[i - 1] + v[i + 1])
			nrelm++;

	int* rezultat = new int[nrelm];
	rezultat[0] = v[0];
	rezultat[nrelm - 1] = v[n - 1];
	int cnt = 1;
	for (int i = 1; i < n-1; i++)
		if (v[i] != v[i - 1] + v[i + 1])
			rezultat[cnt++] = v[i];
	rezultat[cnt] = v[n - 1];

	delete[] v;
	v = rezultat;
	n = cnt + 1;
}

void AfisVect(int n, int* v)
{
	for (int i = 0; i < n; i++)
		std::cout << v[i] << " ";
}

int main()
{
	int n;
	int* v;
	CitireVect(n, v);
	ModifVect(v, n);
	AfisVect(n, v);
	return 0;
}