#include<iostream>
#include<vector>
#include<algorithm>
/*
5
1002 2
4
2 4 3 3
3324 5
2
4 3
4332 10
6
2 5 1 3 2 5
6643 8
3
4 9 3 
3001 4
1
3

{1001, 5, {2, 4, 8}} --- 14 ore
{1002, 7, {1, 3, 5, 4}} --- 13 ore
{1003, 8, {5, 2, 1, 4, 3}} --- 15 ore
{1004, 6, {3, 1, 5}} --- 9 ore
{1005, 9, {4, 2, 1, 3}} --- 10 ore


5
1001 5
3
2 4 8
1002 7
4
1 3 5 4
1003 8
5
5 2 1 4 3
1004 6
3
3 1 5
1005 9
4
4 2 1 3


*/

struct Comanda
{
	int id_comanda;
	int prioriate;
	int nr_produse;
	int timpi[101];
	int timp_comanda;
};

void citireComenzi(std::vector<Comanda>& c, int& N)
{
	std::cin >> N;
	if (N < 5 || N > 10)
	{
		std::cerr << "Numarul de comenzi se afla in afara intervalului [5,10]";
		return;
	}
	c.resize(N);
	for (int i = 0; i < c.size(); i++)
	{
		std::cin >> c[i].id_comanda >> c[i].prioriate;
		if( c[i].id_comanda < 1000 || c[i].id_comanda > 9999 )
		{
			std::cerr << "Id-ul comenzii " << c[i].id_comanda <<" se afla in afara intervalului [1000,9999]";
			return;
		}
		if (c[i].prioriate < 0)
		{
			std::cerr << "Prioritatea comenzii se afla in afara intervalului [0,inf)";
			return;
		}
		std::cin >> c[i].nr_produse;
		for (int j = 0; j < c[i].nr_produse; j++)
		{
			std::cin >> c[i].timpi[j];
			c[i].timp_comanda += c[i].timpi[j];
		}
	}
}

void determinareComandaUrgenta(std::vector<Comanda> c)
{
	int maxi = -1;
	for (int i = 0; i < c.size(); i++)
	{
		if (c[i].timp_comanda > maxi)
			maxi = c[i].timp_comanda;
	}
	for (int i = 0; i < c.size(); i++)
	{
		if (c[i].timp_comanda == maxi)
		{
			std::cout << c[i].id_comanda << " " << maxi;
			break;
		}
	}
}

int comparatorPrioritate(Comanda a, Comanda b)
{
	if (a.prioriate == b.prioriate)
		return a.nr_produse > b.nr_produse;
	return a.prioriate > b.prioriate;
}

void afisareComenzi(std::vector<Comanda> c)
{
	for (int i = 0; i < c.size(); i++)
	{
		std::cout << c[i].id_comanda << " " << c[i].prioriate << " " << c[i].nr_produse << " " << c[i].timp_comanda << "\n";
	}
}

int mediumDeliveryTime(std::vector<Comanda> c, int p)
{
	int sum = 0, delivers = 0;
	for (int i = 0; i < c.size(); i++)
	{
		if (c[i].prioriate < p)
			return (double)sum / delivers;

		sum += c[i].timp_comanda;
		delivers++;
	}
	return  (double)sum / delivers;
}

void maximizeDeliveryTime(std::vector<Comanda> c, int t)
{
	int timp_tot = 0, prioritate_tot = 0;
	for (int i = 0; i < c.size(); i++)
	{
		if (timp_tot + c[i].timp_comanda <= t)
		{
			timp_tot += c[i].timp_comanda;
			std::cout << c[i].id_comanda << " ";
			prioritate_tot += c[i].prioriate;
		}
	}
	std::cout << "\n" << prioritate_tot;
}

int comparatorPrioritateTimp(Comanda a, Comanda b)
{
	return a.timp_comanda * b.prioriate < b.timp_comanda * a.prioriate;
}
 
int main()
{
	int n;
	std::vector<Comanda> c;
	citireComenzi(c, n);
	determinareComandaUrgenta(c);
	std::cout << "\n";
	std::sort(c.begin(), c.end(), comparatorPrioritate);
	afisareComenzi(c);
	int p;
	std::cin >> p;
	std::cout << mediumDeliveryTime(c, p);
	std::cout << "\n";
	std::sort(c.begin(), c.end(), comparatorPrioritateTimp);
	int t;
	std::cin >> t;
	maximizeDeliveryTime(c, t);
	return 0;
}