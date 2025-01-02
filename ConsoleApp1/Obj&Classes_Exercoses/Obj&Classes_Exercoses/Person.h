#pragma once
#include <iostream>

class Person{
private:
	static const int LIMIT = 25;
	std::string lname; //last name
	char fname[LIMIT]; //first name
public:
	Person() { lname = ""; fname[0] = '\0'; }
	Person(const std::string& ln, const char* fn = "Heyyou");

	void Show() const; // firstname lastname
	void FormalShow() const; // lastname firstname
};

