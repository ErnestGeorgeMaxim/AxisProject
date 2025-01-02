#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <cmath>
#include <queue>
#include <string>

#define OFFICE_X 5
#define OFFICE_Y 7

using post = std::tuple<double, std::string, int, int, double>;
using deliver = std::vector < std::tuple<std::string, int, int, double>>;

double calculateDistance(int x, int y) {
    return sqrt((x - OFFICE_X) * (x - OFFICE_X) + (y - OFFICE_Y) * (y - OFFICE_Y));
}

void readPackages(std::vector<std::tuple<std::string, int, int, double>>& packs, const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "File can't be opened!\n";
        return;
    }
    int n;
    in >> n;
    packs.resize(n);
    for (int i = 0; i < n; ++i) {
        std::string code;
        int x, y;
        double weight;
        in >> code >> x >> y >> weight;
        packs[i] = std::make_tuple(code, x, y, weight);
    }
    in.close();
}

void assignPackages(const deliver& packages, deliver& ion, deliver& andreea, deliver& mihai) {
    std::priority_queue<post> pq;

    for (const auto& pack : packages) {
        double distance = calculateDistance(std::get<1>(pack), std::get<2>(pack));
        pq.push(std::make_tuple(-distance, std::get<0>(pack), std::get<1>(pack), std::get<2>(pack), std::get<3>(pack)));
    }

    while (!pq.empty()) {
        auto pack = pq.top();
        pq.pop();

        double distance = -std::get<0>(pack);
        if (distance <= 5 && std::get<4>(pack) <= 10) {
            if (mihai.size() < 3) {
                mihai.push_back(std::make_tuple(std::get<1>(pack), std::get<2>(pack), std::get<3>(pack), std::get<4>(pack)));
            }
        }
        else if (distance <= 10 && std::get<4>(pack) <= 10) {
            if (andreea.size() < 3) {
                andreea.push_back(std::make_tuple(std::get<1>(pack), std::get<2>(pack), std::get<3>(pack), std::get<4>(pack)));
            }
        }
        else if (std::get<4>(pack) <= 10) {
            if (ion.size() < 3) {
                ion.push_back(std::make_tuple(std::get<1>(pack), std::get<2>(pack), std::get<3>(pack), std::get<4>(pack)));
            }
        }
    }
}

void printAssignments(const std::string& name, const std::vector<std::tuple<std::string, int, int, double>>& assignments) {
    std::cout << name << " delivered:\n";
    for (const auto& pack : assignments) {
        std::cout << "Code: " << std::get<0>(pack) << ", Distance: " << calculateDistance(std::get<1>(pack), std::get<2>(pack))
            << " km, Weight: " << std::get<3>(pack) << " kg\n";
    }
}

int main() {
    deliver packages;
    readPackages(packages, "Pachete.txt");

    deliver ion, andreea, mihai;

    for (int i = 0; i < 3; ++i) {
        assignPackages(packages, ion, andreea, mihai);

        std::cout << "Delivery round " << (i + 1) << ":\n";
        printAssignments("Ion", ion);
        printAssignments("Andreea", andreea);
        printAssignments("Mihai", mihai);

        // Clear the deliveries for the next round
        ion.clear();
        andreea.clear();
        mihai.clear();
    }

    return 0;
}

