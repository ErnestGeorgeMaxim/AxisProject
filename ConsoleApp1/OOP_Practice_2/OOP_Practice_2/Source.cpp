#include <iostream>
#include "TIme.h"
#include "vect.h"
#include <ctime>
#include <cstdlib>

int main() {
	//using std::cout;
	//using std::endl;
	//TIme aida(3, 35);
	//TIme tosca(2, 48);
	//TIme temp;
	//cout << "Aida and Tosca:\n";
	//cout << aida << "; " << tosca << endl;
	//temp = aida + tosca; // operator+()
	//cout << "Aida + Tosca: " << temp << endl;
	//temp = aida * 1.17; // member operator*()
	//cout << "Aida * 1.17: " << temp << endl;
	//cout << "10.0 * Tosca: " << 10.0 * tosca << endl;
	
	using namespace std;
	using VECTOR::Vector;
	srand(time(0));//seed random-number generator
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;
	cout << "Enter target distance (q to quit): ";
	while (cin >> target) {
		cout << "Enter step length: ";
		if (!(cin >> dstep))
			break;
		while (result.magval() < target) {
			direction = rand() % 360;
			step.reset(dstep, direction, Vector::POL);
			result = result + step;
			steps++;
		}
		cout << "After " << steps << " steps, the subject "
			"has the following location:\n";
		cout << result << "\n";
		result.polarMode();
		cout << " or\n" << result << "\n";
		cout << "Average outward distance per step = "
			<< result.magval() / steps << "\n";
		steps = 0;
		result.reset(0.0, 0.0);
		cout << "Enter target distance (q to quit): ";
	} 
	cout << "Bye!\n";
	cin.clear();
	while (cin.get() != '\n')
		continue;

	return 0;
}