#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<int> a = { 11, 11,17, 30, 37,40, 40, 11, 29 };
	auto x = std::unique(a.begin(), a.end());// elimina duplicatele
	a.resize(std::distance(a.begin(), x));// resize la vect pt ca pune duplicatele la finalul sirului
	for (int i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	return 0;
}