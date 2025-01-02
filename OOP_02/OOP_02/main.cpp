#include <iostream>

class Smartphone {
public:
	virtual void takeSelfie() = 0;
	virtual void makeACall() = 0;
};

class Samsung : public Smartphone {
public:
	void takeSelfie() override {
		std::cout << "Samsung selfie\n";
	}
	void makeACall() override {
		std::cout << "Samsung calling\n";
	}
};

class IPhone : public Smartphone {
public:
	void takeSelfie() override {
		std::cout << "IPhone selfie\n";
	}
	void makeACall() override {
		std::cout << "IPhone calling\n";
	}
};

int main() {
	Smartphone* s1 = new Samsung();
	s1->takeSelfie();
	s1->makeACall();
	Smartphone* s2 = new IPhone();
	s2->takeSelfie();
	s2->makeACall();
	return 0;
}