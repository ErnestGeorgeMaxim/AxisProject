#include<iostream>
#include<vector>
#include<fstream>

std::vector<std::vector<int>> CitMat(std::string cale)
{
	std::ifstream f(cale);
	int nr_linii, nr_coloane;

	f >> nr_linii >> nr_coloane;

	std::vector<std::vector<int>>mat;
	mat.resize(nr_linii);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(nr_coloane);
		for (int j = 0; j < mat[i].size(); j++)
			f >> mat[i][j];
	}
	return mat;
}

void SumeZone(std::vector<std::vector<int>>  mat)
{
	int z1, z2, z3, z4;
	z1 = z2 = z3 = z4 = 0;
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[i].size(); j++)
        {
                if (i < j && i + j < mat[i].size() + 1)
                    z1 += mat[i][j];
                if (i < j && i + j > mat[i].size() + 1)
                    z2 += mat[i][j];
                if (i > j && i + j > mat[i].size() + 1)
                    z3 += mat[i][j];
                if (i > j && i + j < mat[i].size() + 1)
                    z4 += mat[i][j];
		}

	std::cout << z1 << " " << z2 << " " << z3 << " " << z4;

}

int main()
{
	std::vector<std::vector<int>> mat = CitMat("Text.txt");
	SumeZone(mat);
	return 0;
}