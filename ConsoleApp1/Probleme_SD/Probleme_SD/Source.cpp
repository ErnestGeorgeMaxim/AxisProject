#include <iostream>
#include <vector>
#include <queue>

int main() {
	std::vector<int> a, b;
	std::priority_queue<int, std::vector<int>, std::greater<int>> c;
	int n, m;
	std::cin >> n;
	a.resize(n);
	for (int i = 0; i < a.size(); i++)
		std::cin >> a[i];
	std::cin >> m;
	b.resize(m);
	for (int i = 0; i < b.size(); i++)
		std::cin >> b[i];

	for (int i = 0; i < a.size(); i++)
		c.push(a[i]);
	for (int i = 0; i < b.size(); i++)
		c.push(b[i]);

	while (!c.empty()) {
		std::cout << c.top() << " ";
		c.pop();
	}
	return 0;
}