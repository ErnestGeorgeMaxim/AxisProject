#include "Person.h"

Person::Person(const std::string& ln, const char* fn){
	lname = ln;
	int i;
	for (i = 0; i < LIMIT; i++) 
		fname[i] = fn[i];
	fname[i] = '\0';
}

void Person::Show() const{
	using std::cout;
	cout << fname << " " << lname << "\n";
}

void Person::FormalShow() const{
	using std::cout;
	cout << lname << " " << fname << "\n";
}
