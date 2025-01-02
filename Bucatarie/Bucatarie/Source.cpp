#include<iostream>
#include<vector>
#include<fstream>
#include <algorithm>

/*
5
132 1000
5
1 430
2 300
3 500 
5 332
10 2332

104 3024
3
2 300
2 300
3 500

134 323
1
7 100

432 4002
2
10 2332
43 223

593 2330
5
1 430
2 300
3 500
6 120
10 2332


*/

struct Ingredient
{
	int calorii;
	int id_ingredient;
};

struct Reteta
{
	Ingredient ing[100];
	int pret;
	int id_reteta;
	int nr_ingrediente;
	int valoare_calorica;
};

void citireRetete(std::vector<Reteta>& r, int& n)
{
	std::cin >> n;
	if (n < 5 || n > 10)
	{
		std::cerr << "Numarul de retete este in afara intervalului [5,10]" << "\n";
		return;
	}
	r.resize(n);
	for (int i = 0; i < r.size(); i++)
	{
		std::cin >> r[i].id_reteta >> r[i].pret;
		if(r[i].id_reteta < 100 || r[i].id_reteta > 1000)
		{
			std::cerr << "Id-ul retetei " << r[i].id_reteta << " este in afara intervalului [100,1000]" << "\n";
			return;
		}
		std::cin >> r[i].nr_ingrediente;
		for (int j = 0; j < r[i].nr_ingrediente; j++)
		{
			std::cin >> r[i].ing[j].id_ingredient >> r[i].ing[j].calorii;
			if( r[i].ing[j].id_ingredient < 1 || r[i].ing[j].id_ingredient > 99)
			{
				std::cerr << "Id-ul ingredientului " << r[i].ing[j].id_ingredient << " este in afara intervalului [1,99]" << "\n";
				return;
			}
		} 
	}
}

void afisareRetete(std::vector<Reteta> r)
{
	std::cout << r.size() << "\n";
	for (int i = 0; i < r.size(); i++)
	{
		std::cout << r[i].id_reteta << " " << r[i].pret << "\n";
		for (int j = 0; j < r[i].nr_ingrediente; j++)
		{
			std::cout << r[i].ing[j].id_ingredient << " " << r[i].ing[j].calorii << "\n";
		}
		std::cout << r[i].valoare_calorica << "\n\n";
	}
}

void ingredientPopular(std::vector<Reteta> r)
{
	std::fstream fout("ingPopular.txt");
	std::vector<int> apariti;
	apariti.resize(100);
	for (int i = 0; i < r.size(); i++)
	{
		for (int j = 0; j < r[i].nr_ingrediente; j++)
			apariti[r[i].ing[j].id_ingredient]++;
	}
	int aparitieMaxima = -1, id_ing = 1;
	for (int i = 1; i < apariti.size(); i++)
	{
		if (apariti[i] > aparitieMaxima)
			aparitieMaxima = apariti[i], id_ing = i;
	}
	apariti.clear();
	fout << id_ing << "\n";
	for (int i = 0; i < r.size(); i++)
	{
		int ok = 0;
		for (int j = 0; j < r[i].nr_ingrediente; j++)
			if (r[i].ing[j].id_ingredient == id_ing && ok == 0)
			{
				fout << r[i].id_reteta << " ";
				ok = 1;
			}
	}
	fout << "\n";
	fout.close();
}

int comparatorCaloriiDescrescator(Reteta a, Reteta b)
{
	return a.valoare_calorica > b.valoare_calorica;
}

void verificareCaloriiRetete(std::vector<Reteta>& r)
{
	for (int i = 0; i < r.size(); i++)
	{
		for (int j = 0; j < r[i].nr_ingrediente; j++)
			r[i].valoare_calorica += r[i].ing[j].calorii;
	}
	int ok = 0;
	for (int i = 0; i < r.size() - 1; i++)
		if (r[i].valoare_calorica < r[i + 1].valoare_calorica)
			ok = 1;
	if (ok == 1)
		std::sort(r.begin(),r.end(), comparatorCaloriiDescrescator );
}

int binarySearchX(std::vector<Reteta> r, int st, int dr, int x)
{
	if (st < dr)
	{
		int mij = (st + dr) / 2;
		if (r[mij].valoare_calorica == x)
			return 1;
		else if (r[mij].valoare_calorica > x)
			return binarySearchX(r, st, mij, x);
		else
			return binarySearchX(r, mij + 1, dr, x);
	}
	return -1;
}

int binarySearchY(std::vector<Reteta> r, int st, int dr, int y)
{
	if (st < dr)
	{
		int mij = (st + dr) / 2;
		if (r[mij].nr_ingrediente == y)
			return 1;
		else if (r[mij].nr_ingrediente > y)
			return binarySearchY(r, st, mij, y);
		else
			return binarySearchY(r, mij + 1, dr, y);
	}
	return -1;
}

void verificareExistentaXY(std::vector<Reteta> r, int &X, int &Y)
{
	std::cin >> X >> Y;
	int ok = 0;
	if (binarySearchX(r, 0, r.size() - 1, X) && binarySearchY(r, 0, r.size() - 1, Y))
	{
		ok = 1;
		std::cout << "Exista numar care sa indeplineasca conditia!\n";
	}
	if (ok == 0)
		std::cout << "Nu exista retete care sa satisfaca conditia!";
	std::cout << "\n";
}


/*
Am utilizat tehnica de programare greedy pentru ca problema data este una de optimizare
(minim/maxim).Am multimea preturilor retetelor(care reprezinta candidatii) din care la fiecare 
pas optimul local (minimul din punct de vedere al preturilor), astfel incat pretul total obtinut sa
fie mai mic decat un numar M dat.De asemenea, solutia generata de un algoritm tip Greedy nu este neaparat
cea optima si la nivel local.Am obtinut complexitatea O(NlogN) deoarece complexitatea functie predefinite sort este
aceeasi.

*/

int comparatorBugetMeniuCrescator(Reteta a, Reteta b)
{
	return a.pret < b.pret;
}

void meniuRestaurant(std::vector<Reteta> r, int &M)
{
	std::cin >> M;
	std::sort(r.begin(), r.end(), comparatorBugetMeniuCrescator);
	int i = 0;
	int pret_total = 0;
	while (i < r.size())
	{
		if (pret_total + r[i].pret <= M)
		{
			pret_total += r[i].pret;
			std::cout << r[i].id_reteta << " ";
		}
		i++;
	}
	std::cout << "\n" << pret_total << "\n";
}


int main()
{
	int nr_retete,x,y,M;
	std::vector<Reteta> r;
	citireRetete(r, nr_retete);
	std::cout << "\n";
	ingredientPopular(r);
	verificareCaloriiRetete(r);
	afisareRetete(r);
	verificareExistentaXY(r, x, y);
	meniuRestaurant(r, M);
	return 0;    

}