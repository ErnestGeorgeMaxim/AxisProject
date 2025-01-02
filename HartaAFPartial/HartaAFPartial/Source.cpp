#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

void readMap(std::vector<std::vector<int>>& map, int& n, int& m)
{
    std::ifstream f("harta.txt");
    if (!f)
    {
        std::cerr << "Fisierul nu a putut fi deschis!\n";
        exit(1);
    }
    f >> n >> m;
    map.resize(n);
    int count = 0;
    for (int i = 0; i < map.size(); i++)
    {
        map[i].resize(m);
        for (int j = 0; j < map[i].size(); j++)
        {
            f >> map[i][j];
            if (map[i][j] != 0 && map[i][j] != 1)
            {
                std::cerr << "Elementele trebuie sa fie binare!\n";
                exit(1);
            }
            if (map[i][j] == 1)
                count++;
        }
    }
    if (validationOfMap(map) == 0)
    {
        std::cerr << "S-au identificat elemente adiacente!\n";
        exit(1);
    }
    if (count < 2)
    {
        std::cerr << "Nu au fost citite destul orase!\n";
        exit(1);
    }
    f.close();
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

/**
 * Complexitatea algoritmului DFS în implementarea de mai jos este în mare m?sur? determinat? de dimensiunile matricei ?i de forma acesteia.
 * Vom evalua complexitatea pentru o matrice de dimensiuni n ?i m, unde n este num?rul de rânduri ?i m este num?rul de coloane.
 * Timpul de parcurgere cu DFS este O(V + E), unde V este num?rul de noduri (în cazul nostru, n * m), iar E este num?rul de muchii
 * (corespunz?tor vecinilor pentru fiecare celul?).
 * În cazul unei matrice, fiecare celul? poate avea maxim patru vecini (sus, jos, stânga, dreapta), a?adar num?rul total de muchii,
 * E, este propor?ional cu 4 * n * m.
 * Astfel, timpul total va fi în O(n * m).
 * Complexitatea spa?ial? este determinat? de dimensiunea matricei ?i de stiva utilizat? pentru DFS. Stiva poate avea o dimensiune
 * maxim? de O(n * m) în cel mai r?u caz (când matricea are o singur? cale de la start la end, iar stiva con?ine toate pozi?iile).
 * În general, complexitatea depinde de configura?ia matricei ?i de calea exact? pe care DFS o parcurge, dar pentru o matrice tipic?,
 * complexitatea timpului este O(n * m).

 */
struct Point
{
    int x, y;

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

bool isValidMove(const std::vector<std::vector<int>>& matrix, int row, int col) {
    return row >= 0 && row < matrix.size() &&
        col >= 0 && col < matrix[0].size() &&
        matrix[row][col] == 0;
}

bool depthFirstSearch(const std::vector<std::vector<int>>& matrix, Point start, Point end, std::vector<Point>& path,
    std::vector<std::vector<bool>>& visited) {

    // reach destination?
    if (start.x == end.x && start.y == end.y) {
        path.push_back(start);
        return true;
    }

    //mark as visited
    visited[start.x][start.y] = true;

    int moves[][2] = { {-1, 0}, // sus
                      {1,  0}, // jos
                      {0,  -1}, // stanga
                      {0,  1} }; // dreapta

    for (auto& move : moves) {
        int newRow = start.x + move[0];
        int newCol = start.y + move[1];

        if (isValidMove(matrix, newRow, newCol) && !visited[newRow][newCol]) {
            // Dac? urm?toarea pozi?ie este valid? ?i nevizitat?, continu?m c?utarea
            if (depthFirstSearch(matrix, Point(newRow, newCol), end, path, visited)) {
                // Ad?ug?m pozi?ia curent? la drumul g?sit
                path.push_back(start);
                return true;
            }
        }
    }

    return false;
}

std::vector<Point> findShortestPath(const std::vector<std::vector<int>>& matrix, Point start, Point end) {
    std::vector<Point> path;
    std::vector<std::vector<bool>> visited(matrix.size(), std::vector<bool>(matrix[0].size(), false));

    // Verific?m dac? punctele de start ?i end sunt valide
    if (!isValidMove(matrix, start.x, start.y) || !isValidMove(matrix, end.x, end.y)) {
        std::cout << "Puncte invalide!";
        return path;
    }

    // find path
    depthFirstSearch(matrix, start, end, path, visited);

    // Revers?m drumul pentru a ob?ine ordinea corect?
    std::reverse(path.begin(), path.end());

    return path;
}

int main()
{
    int n, m;
    std::vector<std::vector<int>> map;
    readMap(map, n, m);
    writeMap(map);

	std::vector<int> a = { 1, 3, 7, 9, 10, 11, 17, 24, 36 };
	int index = std::distance(a.begin(), std::lower_bound(a.begin(), a.end(), 11));
	std::cout << index << "\n";

    std::vector<int> b = { 3, 23, 43,3, 5, 43, 55,55,234 };
    std::sort(b.begin(), b.end(), [](int x, int y)
            {
                return x < y;
            });
    auto x = std::unique(b.begin(), b.end());// elimina duplicatele
    b.resize(std::distance(b.begin(), x));// resize la vect pt ca pune duplicatele la finalul sirului
    for (int i = 0; i < b.size(); i++)
        std::cout << b[i] << " ";
    std::cout << "\n";
    return 0;
}
