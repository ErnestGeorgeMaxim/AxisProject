#include<iostream>
#include <vector>
#include <fstream>

struct RGB
{
	int r, g, b;
};

std::vector<std::vector<RGB>> citireMatPixeli(std::string cale)
{
	std::ifstream f(cale);
	int n, m;
	f >> n >> m;
	std::vector<std::vector<RGB>> mat;
	mat.resize(n);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(m);
		for (int j = 0; j < mat[i].size(); j++)
			f >> mat[i][j].r >> mat[i][j].g >> mat[i][j].b;
	}
	f.close();
	return mat;
}

bool cautarePixel(std::vector<std::vector<RGB>> mat, std::string culoare)
{
	int ok = 0;
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			if (culoare == "red")
			{
				if (mat[i][j].r != 0 && mat[i][j].g == 0 && mat[i][j].b == 0)
					ok = 1;
			}
			else if (culoare == "green")
			{
				if (mat[i][j].r == 0 && mat[i][j].g != 0 && mat[i][j].b == 0)
					ok = 1;
			}
			else if (culoare == "blue")
			{
				if (mat[i][j].r == 0 && mat[i][j].g == 0 && mat[i][j].b != 0)
					ok = 1;
			}
		}
	}
	if (ok == 1)
		return true;
	return false;
}

std::vector<std::vector<RGB>> rotire90grade(const std::vector<std::vector<RGB>>& matrice) 
{
	int n = matrice.size();
	int m = matrice[0].size();

	// Transpunerea matricei
	std::vector<std::vector<RGB>> matTranspusa(m, std::vector<RGB>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matTranspusa[j][i] = matrice[i][j];

	// Inversarea ordinei elementelor pe fiecare linie
	for (int i = 0; i < m; i++)
		std::reverse(matTranspusa[i].begin(), matTranspusa[i].end());

	return matTranspusa;
}

void primPlan(std::vector<std::vector<RGB>> mat, int prag)
{
	int zpp = 0;
	std::vector<std::vector<int>> img;
	img.resize(mat.size());
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			img[i].resize(mat[i].size());
			if ((mat[i][j].r + mat[i][j].g + mat[i][j].b) / 3 >= prag)
			{
				img[i][j] = 1;
				zpp++;
			}
			else
				img[i][j] = 0;
		}
	}
	for (int i = 0; i < img.size(); i++)
	{
		for (int j = 0; j < img[i].size(); j++)
			std::cout << img[i][j] << " ";
		std::cout << "\n";	
	}
	std::cout << zpp;
}

int main()
{
	std::vector<std::vector<RGB>> mat = citireMatPixeli("Pixeli.txt");
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
			std::cout << mat[i][j].r << " " << mat[i][j].g << " " << mat[i][j].b << " ";
		std::cout << "\n";
	}
	std::cout << cautarePixel(mat, "green");
	std::cout << "\n";
	std::vector<std::vector<RGB>>matr = rotire90grade(mat);
	for (int i = 0; i < matr.size(); i++)
	{
		for (int j = 0; j < matr[i].size(); j++)
			std::cout << matr[i][j].r << " " << matr[i][j].g << " " << matr[i][j].b << " ";
		std::cout << "\n";
	}
	primPlan(mat, 2);
	return 0;
}