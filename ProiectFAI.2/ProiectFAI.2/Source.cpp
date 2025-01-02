#include <iostream>
#include <vector>

void afisareMatrice(std::vector<std::vector<float>> a)
{
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a[i].size(); j++)
			std::cout << a[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
}

void swapLinii(std::vector < std::vector < float >> mat, int L1, int L2)
{
	for (int i = 0; i < mat[0].size(); i++)
	{
		float a = mat[L1][i];
		mat[L1][i] = mat[L2][i];
		mat[L2][i] = a;
	}
}

void swapColoane(std::vector < std::vector < float >> mat, int C1, int C2)
{
	for (int i = 0; i < mat.size(); i++)
	{
		float a = mat[i][C1];
		mat[i][C1] = mat[i][C2];
		mat[i][C2] = a;
	}
}

void atribuireValori(std::vector<std::vector<float>> &a, int i)
{
	for (int j = 0; j < a.size(); j++)
	{
		if (j != i)
		{
			float val = -1.0 * (a[j][i] / a[i][i]);
			for (int k = 0; k < a[j].size(); k++)
			{
				a[j][k] += (val * a[i][k]);
			}
		}afisareMatrice(a);
		
	}
}

void solutieMatrice(std::vector<std::vector<float>> &a)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i][i] == 1)
			atribuireValori(a, i);
		else if (a[i][i] != 0 && a[i][i] != 1) 
		{
			float val = 1.0 * a[i][i];
			for (int j = 0; j < a[0].size(); j++)
				a[i][j] /= val;
			atribuireValori(a, i);
		}
		else if (a[i][i] == 0)
		{
			int ok = 0;
			for (int j = i+1; j < a.size(); j++)
				if (a[j][i] > 0 || a[j][i] < 0)
				{
					swapLinii(a, i, j);
					ok = 1;
					j = a.size();
				}
			if (ok == 0)
			{
				for (int j = i+1; j < a[i].size(); j++)
				{
					for(int k = i; k < a.size(); k++)
						if (a[k][j] != 0)
						{
							swapColoane(a, i, j);
							j = a[i].size();
						}
				}
			}
			if (a[i][i] != 0 && a[i][i] != 1)
			{
				float val = 1.0 * a[i][i];
				for (int j = 0; j < a[0].size(); j++)
				a[i][j] /= val;					
				atribuireValori(a, i);
			}
			else if (a[i][i] == 1)
				atribuireValori(a, i);
		}
	}
}

int main()
{
	std::vector<std::vector<float>> mat;
	int n, m;
	std::cin >> n >> m;
	mat.resize(n);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(m);
		for (int j = 0; j < mat[i].size(); j++)
			std::cin >> mat[i][j];
	}
	std::cout << "\n";
	solutieMatrice(mat);
	return 0;
}