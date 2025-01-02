#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>

struct Rucsac
{
	std::string marca;
	int volum;
	double pret;
};

int partitionare(std::vector<Rucsac>& v, int st, int dr, bool comparator(Rucsac,Rucsac))
{
	Rucsac pivot = v[dr];
	int i = st - 1;
	for (int j = st; j < dr; j++)
	{
		if (comparator(v[j],pivot))
			i++, std::swap(v[i], v[j]);
	}
	i++;
	std::swap(v[i], v[dr]);
	return i;
}

void quicksort(std::vector<Rucsac> &v, int st, int dr, bool comparator(Rucsac,Rucsac))
{
	if (st < dr)
	{
		int poz_pivot = partitionare(v, st, dr, comparator);
		quicksort(v, st, poz_pivot - 1, comparator);
		quicksort(v, poz_pivot + 1, dr, comparator);
	}
}

bool comparator_volum_descrescator(Rucsac r1, Rucsac r2)
{
	return r1.volum >= r2.volum;
}

int main()
{
	std::vector<Rucsac> v;
	std::fstream f("Text.txt");
	int dim;
	f >> dim;
	v.resize(dim);

	for (int i = 0; i < v.size(); i++)
		f >> v[i].marca >> v[i].volum >> v[i].pret;
	quicksort(v, 0, v.size() - 1, comparator_volum_descrescator);
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i].marca << " " << v[i].volum << " " << v[i].pret << "\n";
	return 0;
}