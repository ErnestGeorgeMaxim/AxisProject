#pragma once
#include <iostream>

class Employee{
private:
	int id;
	std::string firstName;
	std::string lastName;
	int salary;

public:
	Employee(const int& id = 0, const std::string& firstName = "unknown", const std::string& lastName = "unknown", const int& salary = 0) {
		this->id = id;
		this->firstName = firstName;
		this->lastName = lastName;
		this->salary = salary;
	}
	int getId() const { return this->id; }
	std::string getFirstName() const { return this->firstName; }
	std::string getLastName() const { return this->lastName; }
	std::string getName() const { return firstName + " " + lastName; }
	int getSalary() const { return this->salary; }
	void setSalary(const int& salary) { this->salary = salary; }
	int getAnnualSalary() {
		return this->salary * 12;
	}
	template <typename T>
	void operator+=(T value) {
		this->salary += value;
		return (*this);
	}

	int raiseSalary(const int& percent) {
		int sum = this->salary * percent / 100;
		salary += sum;
		return salary;
	}

	friend std::ostream& operator<<(std::ostream& os, const Employee& e);
};

std::ostream& operator<<(std::ostream& os, const Employee& e) {
	os << "Id      : " << e.getId() << "\nName    : " << e.getName() << "\nSalary  : " << e.getSalary() << "\n";
	return os;
}

