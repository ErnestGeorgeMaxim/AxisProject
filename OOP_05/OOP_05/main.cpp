#include <iostream>

class Employee {
private:
	std::string name;
	std::string company;
	int age;
public:
	Employee(const std::string& name = "unknown", const std::string& company = "unknown", const int& age = 0) {
		this->name = name;
		this->company = company;
		this->age = age;
	}

	std::string getName() const {
		return this->name;
	}
	std::string getCompany() const {
		return this->company;
	}
	int getAge() const {
		return this->age;
	}
	void setName(const std::string& name) {
		this->name = name;
	}
	void setCompany(const std::string& company) {
		this->company = company;
	}
	void setAge(const int& age) {
		this->age = age;
	}

	friend std::ostream& operator<<(std::ostream& os, Employee e);
};

std::ostream& operator<<(std::ostream& os, Employee e) {
	os << "Name    : " << e.name << "\n";
	os << "Company : " << e.company << "\n";
	os << "Age     : " << e.age << "\n";
	return os;
}

int main() {
	Employee e1("Maxim Ernest","Waters",20);
	Employee e2;
	std::cout << e1 << "\n" << e2;
	return 0;
}