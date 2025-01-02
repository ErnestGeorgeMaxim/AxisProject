#include <iostream>
#include <vector>

// Vectori:
//		-alocati static
//		-alocati dinamic
//		-STL (Standard Template Library)

void CitireV(int v[], int &length)
{
	std::cin >> length;
	for (int i = 0; i < length; i++)
	{
		std::cin >> v[i];
	}
}

void AfisV(int v[], int length)
{
	for (int i = 0; i < length; i++)
		std::cout << v[i] << " ";
}

void CitireVD(int* v, int &length)
{
	std::cin >> length;
	if (v != nullptr)
	{
		delete[] v;
	}
	v = new int[length];
	for (int i = 0; i < length; i++)
	{
		std::cin >> v[i];
	}
}	

int* CitireV(int& length)
{
	std::cin >> length;
	int* v = new int[length];
	for (int i = 0; i < length; i++)
		std::cin >> v[i];
	return v;
}

int main()
{
	int v[10], length;

	int* adr = new int;
	std::cout << adr << std::endl;

	std::cout << sizeof(int) << "\n";
	std::cout << adr + 1 << "\n";
	std::cout << adr + 2 << "\n";
	std::cout << adr + 3 << "\n";

	adr = &length;
	std::cout << adr << "\n";

	std::vector<int> vect;

	//adaugare in vector 
	vect.push_back(12);
	vect.push_back(13);
	vect.push_back(5);

	//dimensiunea 
	std::cout << vect.size() << "\n";

	//redimensionare
	vect.resize(5, -1); // initializeaza tot ce apare dupa resize cu -1
	vect.resize(5);

	// inserare
	vect.insert(vect.begin()+3,6);

	//stergere
	vect.erase(vect.begin()+3);

	for (int i = 0; i < vect.size(); i++)
		std::cout << vect[i] << " ";


}
