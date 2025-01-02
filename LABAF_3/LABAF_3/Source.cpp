#include<iostream>

void ElimEl(int &n, int v[], int p)
{
	if (p < 0 || p == 0)
		return;
	for (int i = p; i < n - 1; i++)
		v[i] = v[i + 1];
	n--;
}

bool VerifS(int v[], int p)
{
	return v[p] == (v[p + 1] + v[p - 1]);
}

void ModificareVect(int v[], int& n)
{
	int poz[101], j = 0;
	for (int i = 1; i < n - 1; i++)
		if (VerifS(v, i) == true)
			poz[j++] = i;
	for (int i = j-1; i >= 0; i--)
		ElimEl(n, v, poz[i]);
}

void CitVect(int& n, int v[])
{
	std::cin >> n;
	for (int i = 0; i < n; i++)
		std::cin >> v[i];
}

void AfisVect(int n, int v[])
{
	for (int i = 0; i < n; i++)
		std::cout << v[i] << " ";
}

int main()
{
	int v[101] = {};
	int n;
	CitVect(n, v);
	ModificareVect(v, n);
	AfisVect(n, v);
	
	return 0;
}