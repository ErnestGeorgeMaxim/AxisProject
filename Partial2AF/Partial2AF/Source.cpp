#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

/*
6 7
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 1 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0

6 7
0 0 1 0 0 0 0
0 1 0 0 1 0 0
0 0 0 1 0 1 0
0 0 0 0 0 0 0
0 0 1 0 1 0 0
0 0 0 0 0 0 1

6 7
0 0 1 0 0 0 0
0 1 0 0 1 0 0
0 0 0 1 1 1 0
0 0 0 0 0 0 0
0 0 1 0 1 0 0
0 0 0 0 0 0 1

6 7
0 0 1 0 0 0 3
0 1 0 0 1 0 0
0 0 0 1 0 1 0
0 2 0 0 0 0 0
0 0 1 0 1 0 0
0 0 0 3 0 0 1
*/


int validationOfMap(std::vector<std::vector<int>> map)
{
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 1)
                if (j < map[i].size() - 1 && map[i][j + 1] == 1 || i < map.size() - 1 && map[i + 1][j] == 1)
                    return 0;
        }
    }
    return 1;
}

void readMap(std::vector<std::vector<int>>& map, int& n, int& m, int &ok)
{
    std::cin >> n >> m;
    map.resize(n);
    int count = 0;
    ok = 1;
    for (int i = 0; i < map.size(); i++)
    {
        map[i].resize(m);
        for (int j = 0; j < map[i].size(); j++)
        {
            std::cin >> map[i][j];
            if (map[i][j] != 0 && map[i][j] != 1)
            {
                std::cerr << "Elementele trebuie sa fie binare!\n";
                ok = 0;
                return;
            }
            if (map[i][j] == 1)
                count++;
        }
    }
    if (validationOfMap(map) == 0)
    {
        std::cerr << "S-au identificat elemente adiacente!\n";
        ok = 0;
        return;
    }
    if (count < 2)
    {
        std::cerr << "Nu au fost citite destul orase!\n";
        ok = 0;
        return;
    }
}

void writeMap(std::vector<std::vector<int>> map)
{
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
            std::cout << map[i][j] << " ";
        std::cout << "\n";
    }
}

bool isAValidMove(const std::vector<std::vector<int>>& map, int row, int col) {
    return row >= 0 && row < map.size() &&
        col >= 0 && col < map[0].size() &&
        map[row][col] == 0;
}

int verifyToBuildANewCity(std::vector<std::vector<int>> map, int x, int y)
{
    if (isAValidMove(map, x, y))
    {
        if (map[x][y - 1] == 0 && map[x][y + 1] == 0 && map[x - 1][y] == 0 && map[x + 1][y] == 0)
            return 1;
    }
    return 0;
}

/*
Metoda de mai jos se bazeaza algoritmul de cautare dinamica ce in cazul de mai jos
consta in crearea unei matrici de sume partial astfel incat sa retinem la fiecare pozitie
suma elementelor pana la acel punct. Algoritmul are o complexitatea O(n^2) din prisma faptului
ca utilizeaza doua structuri repetitive cu ajutorul carora se retine suma[i][j].
*/

int numberOfCities(std::vector<std::vector<int>> map, int x)
{
    std::vector<std::vector<int>> sum;
    sum.resize(x);
    for (int i = 0; i < sum.size(); i++)
        sum[i].resize(map.size());
    for (int i = 1; i < x; i++)
    {
        for (int j = 1; j < map[i].size(); j++)
            sum[i][j] = map[i][j - 1] + map[i - 1][j] - sum[i - 1][j - 1];
    }
    return sum[x][map[x].size()];
}

void turnDegrees(std::vector<std::vector<int>>& map, int n, int m)
{
    std::vector<std::vector<int>> a;
    a.resize(m);
    for (int i = 0; i < a.size(); i++)
        a[i].resize(n);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
            a[i][j] = map[a[i].size() - j-1][i];
    }
    std::ofstream f("rotire.txt");
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
            f << a[i][j] << " ";
        f << "\n";
    }
    f.close();
}

struct Coordinates
{
    int x, y;

    Coordinates(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

double distanceFromATOB(std::vector<std::vector<int>> map, Coordinates a, Coordinates b)
{
    if (map[a.x][a.y] == 1 && map[b.x][b.y] == 1)
    {
         return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
}

bool DFS(std::vector<std::vector<int>>& map, Coordinates start, Coordinates end, std::vector<Coordinates>& path,std::vector<std::vector<bool>>& visited) 
{
    if (start.x == end.x && start.y == end.y)
    {
        path.push_back(start);
        return true;
    }
    visited[start.x][start.y] = true;
    int moves[][2] = { {-1, 0},{1, 0},{0, -1},{0, 1} };

    for (auto& move : moves) 
    {
        int newRow = start.x + move[0];
        int newCol = start.y + move[1];

        if (isAValidMove(map, newRow, newCol) && !visited[newRow][newCol])
        {
            if (DFS(map, Coordinates(newRow, newCol), end, path, visited)) 
            {
                path.push_back(start);
                return true;
            }
        }
    }

    return false;
}

std::vector<Coordinates> findShortestPath(std::vector<std::vector<int>>& map, Coordinates start, Coordinates end) 
{
    std::vector<Coordinates> path;
    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));
    if (!isAValidMove(map, start.x, start.y) || !isAValidMove(map, end.x, end.y))
    {
        std::cout << "Puncte sunt invalide!";
        return path;
    }
    DFS(map, start, end, path, visited);
    std::reverse(path.begin(), path.end());

    return path;
}

int main()
{
    int n, m;
    int ok;
    std::vector<std::vector<int>> map;
    readMap(map, n, m, ok);
    while (ok == 0)
        readMap(map, n, m, ok);
    int x, y;
    std::cin >> x >> y;
    if( verifyToBuildANewCity(map, x, y) == 1)
        std::cout << "Pozitia (" << x << ", " << y << ") valida pentru introducerea unui oras!\n";
    else 
        std::cout << "Pozitia (" << x << ", " << y << ") nu este valida pentru introducerea unui oras!\n";
    std::cout << "\n";
    int poz;
    std::cin >> poz;
    std::cout << numberOfCities(map, poz);
    turnDegrees(map, n, m);
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    distanceFromATOB(map, Coordinates(x1, y1), Coordinates(x2, y2));
    std::cin >> x1 >> y1 >> x2 >> y2;
    findShortestPath(map,Coordinates(x1,y1), Coordinates(x2,y2));


    return 0;
}
