#include <iostream>
#include <vector>
#include <cstdarg>

void quicksort(std::vector<int>& vect, int st, int dr) 
{
    // 4 5 2 1 6 9 3
    /*
    p = 3 pozp = 6

    i = 0
    j = 2
    */
    if (st < dr) {
        int poz_pivot;

        int pivot = vect[dr];
        int i = st - 1;
        for (int j = st; j < dr; j++)
        {
            if (vect[j] < pivot)
            {
                i++;
                std::swap(vect[i], vect[j]);
            }
        }
        i++;
        std::swap(vect[i], vect[dr]);
        poz_pivot = i;

        quicksort(vect, st, poz_pivot - 1);
        quicksort(vect, poz_pivot + 1, dr);
    }
}

int max(int n, ...)
{
    va_list list;
    int max = -1E10, arg;
    va_start(list, n);
    for (int i = 0; i < n; i++)
    {
        arg = va_arg(list, int);
        if (arg > max)
            max = arg;
    }
    va_end(list);
    return max;
}

int main()
{
    std::vector<int> vect = { 4,5,2,1,6,9,3 };
    quicksort(vect, 0, 6);
    for (int i = 0; i < 6; i++)
        std::cout << vect[i] << " ";

    printf("%d", max(4, 1, 2, 3, 4));
    return 0;
}