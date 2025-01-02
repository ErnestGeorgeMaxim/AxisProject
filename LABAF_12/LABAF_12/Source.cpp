#include <iostream>
#include <vector>

/*
11
1 3 5 8 1 2 6 7 6 8 9
0 1 2 3 4 5 6 7 8 9 10
  k
k  
for( i = k; i <= a[k] + k; i++;
*/



void citireVector(std::vector<int>& a, int& n)
{
    std::cin >> n;
    a.resize(n);
    for (int i = 0; i < a.size(); i++)
        std::cin >> a[i];
}

int salturi(std::vector<int> a)
{
    int pasi = 0;
    std::vector<int> pasim;
    pasim.resize(a.size());
    int k = 0;
    while (k < a.size())
    {
        if (a[k] == 0)
            return -1;
        if (a[k] + k < a.size())
        {
            for (int i = k + 1; i <= a[k] + k; i++)
            {
                int maxloc = -1;
                if (a[i] > maxloc)
                    maxloc = a[i], k = i;
            }
        }
        else
            k = a.size() - 1;
        pasi++;
    }
    return pasi;
}

int main()
{
    std::vector<int> a;
    int n;
    citireVector(a, n);
    salturi(a);
    return 0;
}
