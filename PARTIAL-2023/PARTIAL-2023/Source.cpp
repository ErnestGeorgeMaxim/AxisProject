#include<iostream>
#include <vector>

struct Piesa
{
	int numar;
	std::string culoare;

};

struct Culoare
{
	int r, g, a, n;
};


/*
15
1 rosu 2 galben 4 albastru 4 albastru 5 negru 5 negru 13 rosu 12 verde 13 verde 6 galben 7 rosu 10 verde 3 albastru 2 rosu 6 verde
14
1 rosu 2 galben 4 albastru 4 albastru 5 negru 5 negru 13 rosu 12 albatru  13 albatru 6 galben 7 rosu 10 galben 3 albastru 2 rosu
*/

void citireMat(std::vector<Piesa> list)
{
	int n;
	std::cin >> n;
	list.resize(n);
	std::vector<Culoare> frecv = {};
	frecv.resize(n);
	for (int i = 0; i < list.size(); i++)
	{
		std::cin >> list[i].numar >> list[i].culoare;
		if (list[i].culoare == "rosu")
		{
			frecv[list[i].numar].r += 1;
		}
		if (list[i].culoare == "galben")
		{
			frecv[list[i].numar].g += 1;
		}
		if (list[i].culoare == "albastru")
		{
			frecv[list[i].numar].a += 1;
		}
		if (list[i].culoare == "negru")
		{
			frecv[list[i].numar].n += 1;
		}
	}
	if (n != 14)
	{
		std::cout << "Esuat, introduceti alt numar de piese: ";
		std::cin >> n;
	}
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].numar < 1 || list[i].numar > 13)
		{
			std::cout << "Esuat, introduceti alte piese: \n";
			for (int i = 0; i < list.size(); i++)
				std::cin >> list[i].numar >> list[i].culoare;

		}
		else if (list[i].culoare != "rosu" || list[i].culoare != "galben" || list[i].culoare != "albastru" || list[i].culoare != "negru")
		{
			std::cout << "Esuat, introduceti alte piese: \n";
			for (int i = 0; i < list.size(); i++)
				std::cin >> list[i].numar >> list[i].culoare;
		}
	}
	std::cout << "Succes\n";
}

int partitie(std::vector<Piesa>& vect, int st, int dr, int &cntpiese)
{
	int pivot = vect[dr].numar;
	int i = st;
	cntpiese = 0;
	for (int j = i; j < dr; ++j) {
		if (vect[j].numar < pivot) {
			std::swap(vect[i], vect[j]);
			i++;
			cntpiese++;
		}
	}

	std::swap(vect[i], vect[dr]);
	cntpiese++;
	return i;
}
void sortare(std::vector<Piesa>& vect, int st, int dr) 
{
	int cntpiese;
	if (st < dr) {
		int piv = partitie(vect, st, dr,cntpiese);
		sortare(vect, st, piv - 1);
		sortare(vect, piv + 1, dr);
	}
	std::cout << cntpiese;
}
int VerificareSort(std::vector<Piesa> vect)
{
	int ok = 0;
	for (int i = 0; i < vect.size(); i++)
	{
		if (vect[i].numar > vect[i + 1].numar)
			ok = 1;
	}
	if (ok == 1)
	{
		return 0;
		sortare(vect, 0, vect.size());
	}
	else
		return 1;
}

void afisareMat(std::vector<Piesa> list)
{
	for (int i = 0; i < list.size(); i++)
		std::cout << list[i].numar << " "<< list[i].culoare << " ";
	std::cout << "\n";
}

int main()
{
	std::vector<Piesa> list;
	citireMat(list);
	VerificareSort(list);
	return 0;
}