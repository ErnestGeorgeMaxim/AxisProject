#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>

std::vector<std::vector<int>> CitireM(std::string cale)
{
	std::ifstream f(cale);
	int n_linii, n_coloane;
	f >> n_linii >> n_coloane;
	std::vector<std::vector<int>> matrix;
	matrix.resize(n_linii);
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix[i].resize(n_coloane);
		for (int j = 0; j < matrix[i].size(); j++)
			f >> matrix[i][j];
	}
	f.close();
	return matrix;
}

void Stack(std::vector<std::vector<int>> matrix)
{
	int k = 0;
	double *v = new double[matrix.size()];
	for (int i = 0; i < matrix.size(); i++)
	{
		double val = ((matrix[i][matrix[i].size() - 1] - matrix[i][0]) * 100.0 / matrix[i][0] * 100) / 100.0;
		v[k++] = val;
	}
	double max = v[0];
	int poz = 0;
	for(int i = 1; i < k; i++)
	{
		if (v[i] > max)
		{
			max = v[i];
			poz = i;
		} 
	}
	delete[]v;
	std::cout << "Criptomoneda " << poz << " cu ";
	std::cout << std::fixed << std::setprecision(2) << max << "% profit";
}

struct Valuta
{
	int z1, z2, diferenta;
};

void CursValutar(std::vector<std::vector<int>> m)
{
	std::vector<Valuta> v;
	v.resize(m.size());
	for (int i = 0; i < m.size(); i++)
	{
		int difmax = -1;
		for (int j = 0; j < m[i].size()-1; j++)
		{
			if (m[i][j] - m[i][j + 1] > difmax)
			{
				difmax = m[i][j] - m[i][j + 1];
				v[i].z1 = j;
				v[i].z2 = j + 1;
				v[i].diferenta = difmax;
			}
		}

	}
	for(int i = 0; i < v.size(); i++)
		std::cout << "De la ziua cu indexul " << v[i].z1 << " la ziua cu indexul " << v[i].z2 << " am fi avut pierderea de " << v[i].diferenta << "\n";
}

struct Evolutie
{
	int dif;
};

int partitionare(std::vector<Evolutie> &v, int st, int dr, std::vector<std::vector<int>> &m)
{
	int i = st;
	for (int j = st; j <= dr; j++)
	{
		if (v[j].dif < v[dr].dif)
		{
			std::swap(v[i], v[j]);
			std::swap(m[i], m[j]);
			i++;
		}
	}
	std::swap(v[i], v[dr]);
	std::swap(m[i], m[dr]);
	
	return i;
}

void quicksort(std::vector<Evolutie> &v, int st, int dr, std::vector<std::vector<int>> &m)
{
	if (st < dr)
	{
		int poz_pivot = partitionare(v, st, dr, m);
		quicksort(v, st, poz_pivot - 1, m);
		quicksort(v, poz_pivot + 1, dr,m);
	}
}

void SortareCrypto(std::vector<std::vector<int>> &m)
{
	std::vector<Evolutie> v;
	v.resize(m.size());
	for (int i = 0; i < m.size(); i++)
	{
		int tcrescator = 0, tdescrescator = 0;
		for (int j = 0; j < m[i].size() - 1; j++)
		{
			if (m[i][j] > m[i][j + 1])
				tdescrescator++;
			else
				tcrescator++;
		}
		v[i].dif = tcrescator - tdescrescator;
	}
	quicksort(v, 0, m.size()-1, m);
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
			std::cout << m[i][j] << " ";
		std::cout << std::endl;
	}
}

int main()
{
	std::vector<std::vector<int>> crypto = CitireM("CryptoMatrix.txt");
	std::cout << "Cerinta 1: \n";
	Stack(crypto);
	std::cout << "\n\nCerinta 2: \n";
	CursValutar(crypto);
	std::cout << "\n\nCerinta 3: \n";
	SortareCrypto(crypto);
	return 0;
}