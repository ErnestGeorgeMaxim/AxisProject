#include <iostream>
#include <vector>

void CitVect(std::vector<int>& v)
{
	int n;
	std::cin >> n;
	int x;
	for (int i = 0; i < n; i++)
	{
		std::cin >> x;
		v.push_back(x);
	}
}

void ModifVect(std::vector<int>& v)
{
	bool antsters = false;
	int aux;
	for(int i = 1; i < v.size()-1; i++)
		if (antsters)
		{
			if (v[i] == aux + v[i + 1])
			{
				aux = v[i];
				antsters = true;
				v.erase(v.begin() + i);
				i--;
			}
			else
				antsters = false;
		}
		else
		{
			if (v[i] == v[i - 1] + v[i + 1])
			{
				aux = v[i];
				antsters = true;
				v.erase(v.begin() + i);
				i--;
			}
			else 
				antsters = false;
		}
}

void AfisVect(std::vector<int>& v)
{
	for (int x : v)
		std::cout << x << " ";
}

int main()
{
	std::vector<int> v;
	CitVect(v);
	ModifVect(v);
	AfisVect(v);

	return 0;
}