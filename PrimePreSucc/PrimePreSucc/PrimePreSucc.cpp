#include <iostream>
using namespace std;

int Prime(int nr)
{
	if (n < 2)
		return 0;
	if (n % 2 == 0 && n != 2)
		return 0;
	for (int d = 3; d * d <= n; d += 2)
		if (n % d == 0)
			return 0;
	return 1;
}

int 

int main()
{

}