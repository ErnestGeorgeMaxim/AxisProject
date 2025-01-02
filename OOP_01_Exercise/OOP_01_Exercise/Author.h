#pragma once
#include <iostream>

class Author{
private:
	std::string name;
	std::string email;
	char gender;
public:
	Author(const std::string& name = "", const std::string& email = "", const char& gender = 'x') {
		this->name = name;
		this->email = email;
		this->gender = gender;
	}
	std::string getName() const { return this->name; }
	std::string getEmail() const { return this->email; }
	void getEmail(const std::string& email) { this->email = email; }
	char getGender() const { return this->gender; }
	friend std::ostream& operator<<(std::ostream& os, const Author& a);
};

std::ostream& operator<<(std::ostream& os, const Author& a) {
	os << "Author[name=" << a.name << ",email=" << a.email << ",gender=" << a.gender << "]\n";
	return os;
}

