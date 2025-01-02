#include <iostream>
#include <vector>
/*
Instrument is the base class with a virtual function makeSound
Accordion inherits the functions of the base class and has it s own makeSound function
Violin also inherits the funtions of the base class.

When we want to display the makeSound function which is virtual in the base class 
we will have the next cases:
	1. For the fact that Accordion class has already a function that overrides the virtual one
	   it will display "Accordion is playing..."
	2. However, the second class Violion has no function in it so it will inherit 
	   the makeSound function from the base class and display "Instrument is playing..."

At the end of the day, the virtual function is changed if the inheriter class has an override version of it,
if not the class will actually use the base virtual function.

class Instrument {
public:
	virtual void makeSound() {
		std::cout << "Instrument is playing...\n";
	}
};
*/

//it become an abstract class
class Instrument {
public:
	//pure virtual function
	virtual void makeSound() = 0;
};

class Accordion : public Instrument {
public:
	void makeSound() override{
		std::cout << "Accordion is playing...\n";
	}
};

class Violin : public Instrument {
public:
	void makeSound() override{
		std::cout << "Violin is playing...\n";
	}
};

int main() {
	Instrument *i1 = new Accordion();
	//i1->makeSound();
	Instrument *i2 = new Violin();
	//i2->makeSound();

	std::vector<Instrument*> instruments;
	instruments.push_back(i1);
	instruments.push_back(i2);
	for (int i = 0; i < instruments.size(); i++)
		instruments[i]->makeSound();
	return 0;
}