#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <fstream>

/*
*               A* from the top-left corner to down-right corner
*/

class Node {
public:
    int x, y, height;
    Node() {}
    Node(int a, int b, int h) : x(a), y(b), height(h) {}
};

bool operator<(Node a, Node b) {
    return a.height > b.height;
}

bool isValid(Node a, int n, int m) {
    return (0 <= a.x && a.x < n && 0 <= a.y && a.y < m);
}

void Astar(std::vector<std::vector<int>>& map) {
    int s = 0;
    std::vector<int> dx = { 0,1,0,-1 };
    std::vector<int> dy = { 1,0,-1,0 };

    int threshold = std::numeric_limits<int>::max();

    std::vector<std::vector<int>> cost(map.size(), std::vector<int>(map[0].size(), 0));

    std::priority_queue<Node> pq;
    Node temp(0, 0, map[0][0]);
    pq.push(temp);

    while (!pq.empty()) {
        Node parent = pq.top();
        pq.pop();

        if (threshold < parent.height)
            continue;

        if (parent.x == map.size() - 1 && parent.y == map[0].size() - 1) {
            if (threshold > parent.height)
                threshold = parent.height;
            s = cost[parent.x][parent.y];
            break;
        }

        for (int i = 0; i < 4; i++) {
            Node child;
            child.x = parent.x + dx[i];
            child.y = parent.y + dy[i];

            if (isValid(child, map.size(), map[0].size()) && cost[child.x][child.y] == 0 && map[child.x][child.y] != -1) {
                cost[child.x][child.y] = cost[parent.x][parent.y] + 1;
                child.height = cost[child.x][child.y] + map[child.x][child.y];
                pq.push(child);
            }
        }
    }
    std::cout << s;
}

void readMap(std::vector<std::vector<int>>& map, std::string pathToFile) {
    int n, m;
    std::ifstream in(pathToFile);
    if (!in) {
        std::cerr << "File can't be opened!\n";
        in.close();
        return;
    }
    in >> n >> m;
    map.resize(n, std::vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            in >> map[i][j];
    }
    in.close();
}

int main() {
    std::vector<std::vector<int>> map;
    readMap(map, "Astar.txt");
    Astar(map);
    return 0;
}
