#include <iostream>
#include <cmath>
/*
l = 4
16 = 4 + 12
*/

class EquilateralTriangle {
private:
	float a;
	float circumference;
	float area;
public:
	void setA(const float& length) {
		this->a = length;
		circumference = a * 3;
		float hpower2 = (a * a - (a / 2)*(a / 2));
		area = a * std::sqrt(hpower2) / 2;
	}

	//friend void printResults(EquilateralTriangle et);
	friend class Homework;
};

class Homework {
public:
	void printResults(EquilateralTriangle et) {
		std::cout << "circumference = " << et.circumference << "\n";
		std::cout << "area = " << et.area << "\n";
	}
};

int main() {
	EquilateralTriangle et;
	et.setA(3);
	Homework h;
	h.printResults(et);
	return 0;
}