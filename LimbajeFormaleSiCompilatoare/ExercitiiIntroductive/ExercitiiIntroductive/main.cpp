#include <iostream>
#include <regex>
void evaluateExpression(const std::string& str) {
	if (std::regex_match(str, std::regex("[-+]?\\d+"))) {
		std::cout << "Intreg\n";
	}
	else if (std::regex_match(str, std::regex("\\d+"))) {
		std::cout << "Natural\n";
	}
	else if (std::regex_match(str, std::regex("\\d+\\.\\d+([eE][-+]?\\d+)?"))) {
		std::cout << "Real\n";
	}
	else {
		std::cout << "NU e numar\n";
	}
}
int main() {
	std::string str;
	std::cin >> str;
	evaluateExpression(str);
	return 0;
}