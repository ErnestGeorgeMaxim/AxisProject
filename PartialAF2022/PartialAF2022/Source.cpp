#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::vector<int>> CitireMat(std::string cale)
{
	std::fstream f(cale);
	int n, m;
	f >> n >> m;
	std::vector<std::vector<int>> matrix;
	matrix.resize(n);
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix[i].resize(m);
		for (int j = 0; j < matrix[i].size(); j++)
		{
			f >> matrix[i][j];
		}
	}
	f.close();
	return matrix;
}

bool Validation(std::vector<std::vector<int>> m)
{
	if (m.size() <= 0 || m[0].size() <= 0)
	{
		std::cerr << "Matricea este goala";
		return false;
	}

	for (int i = 0; i < m.size() - 1; i++)
	{
		for (int j = 0; j < m[i].size() - 1; j++)
		{
			if (m[i][j] != 0)
			{
				if (m[i][j] != m[i][j + 1] && m[i][j + 1] != 0)
				{
					return false;
				}
				if (m[i][j] != m[i + 1][j] && m[i + 1][j] != 0)
				{
					return false;
				}
				if (m[i][j] != m[i + 1][j + 1] && m[i + 1][j + 1] != 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

struct Forest
{
	int tip, dimensiune;
};

int CountForests(std::vector<std::vector<int>> m)
{
	std::vector<int> v;
	v.resize(m.size() * m[0].size());
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
		{
			v[m[i][j]] = 1;
		}
	}
	int cnt = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == 1)
		{
			cnt++;
		}
	}
	return cnt - 1;
}

bool comparator_dimensiune_crescator(Forest f1, Forest f2)
{
	return f1.dimensiune <= f2.dimensiune;
}

int partitionare(std::vector<Forest>& v, int st, int dr, bool comparator(Forest, Forest))
{
	Forest pivot = v[dr];
	int i = st - 1;
	for (int j = st; j < dr; j++)
	{
		if (comparator(v[j], pivot))
			i++, std::swap(v[i], v[j]);
	}
	i++;
	std::swap(v[i], v[dr]);
	return i;
}

void quicksort(std::vector<Forest>& v, int st, int dr, bool comparator(Forest, Forest))
{
	if (st < dr)
	{
		int poz_pivot = partitionare(v, st, dr, comparator);
		quicksort(v, st, poz_pivot - 1, comparator);
		quicksort(v, poz_pivot + 1, dr, comparator);
	}
}

void Sort(std::vector<Forest>& v)
{
	quicksort(v, 0, v.size() - 1, comparator_dimensiune_crescator);
}


void LeForest(std::vector<std::vector<int>> m)
{
	std::vector<Forest> forest;
	forest.resize(CountForests(m));
	for (int i = 0; i < forest.size(); i++)
	{
		forest[i].tip = i + 1;
		forest[i].dimensiune = 0;
	}
	for (int i = 0; i < forest.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			for (int k = 0; k < m[j].size(); k++)
			{
				if (m[j][k] == forest[i].tip)
				{
					forest[i].dimensiune++;
				}
			}
		}

	}
	Sort(forest);
	std::cout << "Cerinta 2: ";
	for (int i = forest.size() - 1; i >= 0; i--)
	{
		std::cout << forest[i].tip << " ";
	}
	std::cout << std::endl;
}

struct Coordonate
{
	int x, y;
};

void Pasuni(std::vector<std::vector<int>> m, std::vector<Coordonate> &pasuni)
{
	int k = 0;
	
	pasuni.resize(10);
	for(int i = 1; i < m.size()-1;i++)
		for (int j = 1; j < m.size() - 1; j++)
		{
			if (m[i][j] == 0)
			{
				if (m[i][j + 1] != 0 && m[i][j + 1] == m[i][j - 1])
				{
					pasuni[k].x = i;
					pasuni[k].y = j;
					k++;
				}
				if (m[i+1][j] != 0 && m[i+1][j] == m[i-1][j])
				{
					pasuni[k].x = i;
					pasuni[k].y = j;
					k++;
				}
			}
		}
	pasuni.resize(k);
	for(Coordonate i : pasuni)
		std::cout << i.x << " " << i.y << std::endl;

}

int main()
{
	std::vector<std::vector<int>> m = CitireMat("Forest.txt");
	std::cout << "Cerinta 1: ";
	if (Validation(m) == true)
		std::cout << "true";
	else
		std::cout << "false";
	std::cout << std::endl;
	LeForest(m);
	std::vector<Coordonate> pasuni;
	Pasuni(m, pasuni);
	return 0;
}