#include <iostream>
#include <vector>
#include <algorithm>

/*
5
garoafa
1 4
trandafir
3 7
lacramioara
1 8
narcisa
4 5
toporas
6 9

*/


struct Flower
{
	char name[35];
	int price;
	int colour;
};

void readFlowers(std::vector<Flower>& flower, int& n)
{
	std::cin >> n;
	flower.resize(n);
	for (int i = 0; i < flower.size(); i++)
	{
		std::cin >> flower[i].name;
		std::cin >> flower[i].colour >> flower[i].price;
	}
	int ok = 0;
	for (int i = 0; i < flower.size()-1; i++)
	{
		for (int j = i; j < flower.size(); j++)
			if (flower[i].name == flower[j].name)
				if (flower[i].colour == flower[i].colour)
					ok = 1;
	}
	if (ok == 0)
	{
		std::cout << "Nu exista flori de aceeasi culoare!\n\n";
	}
	else
		std::cout << "Exista flori de aceeasi culoare!\n\n";
}

void writeFlowers(std::vector<Flower> flower)
{
	for (int i = 0; i < flower.size(); i++)
	{
		std::cout << flower[i].name << "\n";
		std::cout << flower[i].colour << " " << flower[i].price <<"\n";
	}
}

void identifyDominantColour(std::vector<Flower> flower)
{
	std::vector<int> colours(10);
	for (int i = 0; i < flower.size(); i++)
		colours[flower[i].colour]++;

	int max = -1, number_flowers = 0;
	for (int i = 0; i < 9; i++)
	{
		if (colours[i] > max)
			max = i, number_flowers = colours[i];
	}
	std::cout << "Culoarea: " << max << " ,Numarul de flori: " << number_flowers << "\n\n";
}

int comparatorBiggerPrice(Flower a, Flower b)
{
	return a.price > b.price;
}

int binarySearch(std::vector<Flower> flower, int left, int right, int x)
{
	if (left < right)
	{
		int middle = (left + right) / 2;
		if (flower[middle].price == x)
			return middle;
		else if (flower[middle].price > x)
			binarySearch(flower, left, middle, x);
		else
			binarySearch(flower, middle + 1, right, x);
	}
	return -1;
}

void sortIfNotBigger(std::vector<Flower> &flower, int &x)
{
	int ok = 0;
	for (int i = 1; i < flower.size(); i++)
	{
		if (flower[i - 1].price < flower[i].price)
			ok = 1;
	}
	if (ok)
		std:sort(flower.begin(), flower.end(), comparatorBiggerPrice);
	std::cin >> x;
	int pos = binarySearch(flower, 0, flower.size()-1, x);
	std::cout << flower[pos].name << " " << flower[pos].colour << " " << flower[pos].price << "\n";
}

int comparatorLowerPrice(Flower a, Flower b)
{
	return a.price < b.price;
}

void createbBouquetOfFlowers(std::vector<Flower> &flower, int &p, int &c)
{
	std::cin >> p >> c;
	std::vector<int> indexflowers(10);
	int newprice = 0;
	std::sort(flower.begin(), flower.end(), comparatorLowerPrice);
	std::cout << "Buchetul este format din urmatoarele flori: \n";
	for (int i = 0; i < flower.size(); i++)
	{
		if (flower[i].colour == c)
		{
			indexflowers[flower[i].colour] = 1;
			newprice += flower[i].price;
			std::cout << flower[i].name << " " << flower[i].colour << " " << flower[i].price << "\n";
			i = flower.size();
		}
	}
	for (int i = 0; i < flower.size(); i++)
	{
		if (flower[i].price + newprice <= p && indexflowers[flower[i].colour] == 0)
		{
			newprice += flower[i].price;
			indexflowers[flower[i].colour] = 1;
			std::cout << flower[i].name << " " << flower[i].colour << " " << flower[i].price << "\n";
		}
	}
	std::cout << "Pretul buchetului este: " << newprice << " lei.\n";
}

int main()
{
	int n;
	std::vector<Flower> flower;
	readFlowers(flower, n);
	writeFlowers(flower);
	identifyDominantColour(flower);
	int x;
	sortIfNotBigger(flower,x);
	int c, p;
	createbBouquetOfFlowers(flower, p, c);
	writeFlowers(flower);
	return 0;
}