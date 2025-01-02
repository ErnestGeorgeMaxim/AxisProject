#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include <unordered_map>

void dijkstra(std::vector<std::vector<int>>& graph, int source) {
    std::vector<int> distance(graph.size(), std::numeric_limits<int>::max());
    std::vector<bool> visited(graph.size());
    distance[source] = 0;

    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
    pq.push({0, source });

    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (dist > distance[node])
            continue;

        for (int i = 0; i < graph.size(); i++) {
            int weight = graph[node][i];
            if (weight != 0 ){
                int d = distance[node] + weight;
                if (d < distance[i]) {
                    distance[i] = d;
                    pq.push({ dist,i });
                }
            }
        }
    }

    std::cout << "Shortest distances from node " << source << ":\n";
    for (int i = 0; i < graph.size(); ++i) {
        std::cout << "Node " << i << ": " << distance[i] << "\n";
    }
}

void readGraph(std::vector<std::vector<int>>& graph, std::string pathToFile) {
    int n;
    std::ifstream in(pathToFile);
    if (!in) {
        std::cerr << "Error! File can't be opened!\n";
        in.close();
        return;
    }
    in >> n;
    graph.resize(n);
    for (int i = 0; i < graph.size(); i++) {
        graph[i].resize(n);
        for (int j = 0; j < graph[i].size(); j++)
            in >> graph[i][j];
    }
    in.close();
}

int main() {
    std::vector<std::vector<int>> graph;
    readGraph(graph, "dijkstra.txt");
    dijkstra(graph, 0);
    return 0;
}
