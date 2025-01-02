#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <limits>
#include <tuple>
#include <cmath>
#include <queue>

#define POST_X 5
#define POST_Y 7
#define MAX_WEIGHT 10.0

double dist(const int& x, const int& y) {
	return std::sqrt((x - POST_X) * (x - POST_X) + (y - POST_Y) * (y - POST_Y));
}

void readPostOffice(std::vector<std::tuple< double, std::string, int, int, double >>& office, const std::string& path) {
	std::ifstream in(path);
	if (!in) {
		std::cerr << "File can't be opened!\n";
		in.close();
		return;
	}
	int n;
	in >> n;
	office.resize(n);
	for (int i = 0; i < office.size(); i++) {
		std::string id;
		int x, y;
		double weight;
		in >> id;
		in >> x >> y >> weight;
		office[i] = std::make_tuple(dist(x, y), id, x, y, weight);
	}
	in.close();
}

//Complexitatea functiei este O(log n) deoarece in cadrul acesteaia se efectuiaza doar stergerea elementeleor din priority_queue
void turnIon(std::priority_queue<std::tuple< double, std::string, int, int, double >>& p_queue) {
	double weight = 0;
	if (!p_queue.empty()) {
		std::cout << "Pachete Ion:\n";
		while (!p_queue.empty() && weight < MAX_WEIGHT) {
			weight += std::get<4>(p_queue.top());
			std::cout << std::get<0>(p_queue.top()) << " " << std::get<1>(p_queue.top()) << " " << std::get<2>(p_queue.top()) << " " << std::get<3>(p_queue.top()) << " " << std::get<4>(p_queue.top()) << "\n";
			p_queue.pop();
		}
		std::cout << "\n";
	}
	else {
		std::cout << "In aceasta tura Ion nu a gasit pachete!\n";
	}
}

//Complexitatea functiei este O(log n) deoarece in cadrul acesteaia se efectuiaza doar stergerea elementeleor din priority_queue
void turnAndreea(std::priority_queue < std::tuple < double, std::string, int, int, double >>& p_queue) {
	double weight = 0;
	if (!p_queue.empty()) {
		std::cout << "Pachete Mihai:\n";
		while (!p_queue.empty() && weight < MAX_WEIGHT) {
			if (std::get<0>(p_queue.top()) < 10.0) {
				weight += std::get<4>(p_queue.top());
				std::cout << std::get<0>(p_queue.top()) << " " << std::get<1>(p_queue.top()) << " " << std::get<2>(p_queue.top()) << " " << std::get<3>(p_queue.top()) << " " << std::get<4>(p_queue.top()) << "\n";
			}
			p_queue.pop();
		}
		std::cout << "\n";
	}
	else {
		std::cout << "In aceasta tura Andreea nu a gasit pachete!\n";
	}
}

//Complexitatea functiei este O(log n) deoarece in cadrul acesteaia se efectuiaza doar stergerea elementeleor din priority_queue
void turnMihai(std::priority_queue<std::tuple< double, std::string, int, int, double >>& p_queue) {
	double weight = 0;
	if (!p_queue.empty()) {
		std::cout << "Pachete Mihai:\n";
		while (!p_queue.empty() && weight < MAX_WEIGHT) {
			if (std::get<0>(p_queue.top()) < 5.0) {
				weight += std::get<4>(p_queue.top());
				std::cout << std::get<0>(p_queue.top()) << " " << std::get<1>(p_queue.top()) << " " << std::get<2>(p_queue.top()) << " " << std::get<3>(p_queue.top()) << " " << std::get<4>(p_queue.top()) << "\n";
			}
			p_queue.pop();
		}
		std::cout << "\n";
	}
	else {
		std::cout << "In aceasta tura Mihai nu a gasit pachete!\n";
	}
}

//Complextiatea functie este O(logn) + O(logn) + ... + O(log n) = O(mlogn) unde m reperezinta numarul de reapelari ale priority_queue ori prin 
void takePackets(const std::vector<std::tuple< double, std::string, int, int, double >>& office) {
	std::priority_queue<std::tuple<double, std::string, int, int, double>> p_queue;
	for (const auto& pack : office)
		p_queue.push(std::make_tuple(std::get<0>(pack), std::get<1>(pack), std::get<2>(pack), std::get<3>(pack), std::get<4>(pack)));
	/*while (!p_queue.empty()) {
		std::cout << std::get<0>(p_queue.top()) << " " << std::get<1>(p_queue.top()) << " " << std::get<2>(p_queue.top()) << " " << std::get<4>(p_queue.top()) << "\n";
		p_queue.pop();
	}*/
	while (!p_queue.empty()) {
		turnIon(p_queue);
		turnAndreea(p_queue);
		turnMihai(p_queue);
	}
}

void printOffice(const std::vector<std::tuple< double, std::string, int, int, double >>& office) {
	for (int i = 0; i < office.size(); i++)
		std::cout << std::get<0>(office[i]) << " " << std::get<1>(office[i]) << " " << std::get<2>(office[i]) << " " << std::get<3>(office[i]) << " " << std::get<4>(office[i]) << "\n";
}



int main() {
	std::vector<std::tuple< double, std::string, int, int, double>> office;
	readPostOffice(office, "Pachete.txt");
	printOffice(office);
	std::cout << "\n\n";
	takePackets(office);
	return 0;
}