#include <iostream>
#include <vector>
#include <algorithm>

/*
6
-3 2
-2 3
-1 0
0 3
-5 -4
1 2

*/

struct Proiect
{
	int id, profit, deadline;
};

int comparator_profit(Proiect a, Proiect b)
{
	return a.profit > b.profit;
}

int main()
{
	int n;
	Proiect x;
	std::vector<Proiect> p;
	std::cin >> n;
	p.resize(n);
	for (int i = 0; i < p.size(); i++)
		std::cin >> p[i].id >> p[i].profit >> p[i].deadline;
	int paux[101], cnt = 0;
	std::sort(p.begin(), p.end(), comparator_profit);
	int fr[101] = {};
	for (int i = 0; i < p.size(); i++)
	{
		if (fr[p[i].deadline] == 0)
		{
			paux[p[i].deadline] = p[i].id;
			cnt++;
			fr[p[i].deadline] = 1;
		}
		else
		{
			for (int j = 0; j < p[i].deadline; j++)
			{
				if (fr[j] == 0)
				{
					paux[j] = p[i].deadline;
					fr[j] = 1;
					cnt++;
					j = p[i].deadline+1;
				}
			}
		}
	}
	for (int i = 0; i < cnt; i++)
		std::cout << paux[i] << " ";

	return 0;
}