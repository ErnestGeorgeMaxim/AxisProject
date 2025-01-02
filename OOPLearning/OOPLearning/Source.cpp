#include <iostream>
#include <vector>
/*
class - describes the structure
object - a specific example of that structure(instance)
instance - another name for object
instantiating - creatiing an object from a class
data memebers - variables
methods - functions
Parent class(base class) - inherited FROM
Child class(derived class) - iherited TO
*/

/*
abstraction => a concept where you make something easy by hiding the complicated stuff
encapsulation => granting acces to private data only through controlled public interfaces 
					-> practic facem o oarecare separare intre informatiile din clasa
					   la modul in care vom restrictiona accesul la o parte din informatii

inheritance => we can create derived classes that inherit properties from their parent classes
polymorphism => we can treat multiple different objects as their base object type
*/


class Person {
protected:
	std::string first;
	std::string last;
public:
	Person(std::string first, std::string last) : first(first), last(last) {}
	Person() = default;
	// setteri
	void setFirstName(std::string first) { this->first = first; }
	void setLastName(std::string last) { this->last = last; }

	//getteri
	std::string getName() { return first + " " + last; }
	void printFullName() { std::cout << first << " " << last << "\n"; }
	virtual void printInfo() {
		std::cout << "first name  :  " << first << "\n";
		std::cout << "last name   :  " << last << "\n";
	}

	static void printPeople(std::vector<Person*> people) {
		for (auto t : people)
			t->printInfo();
	}
};


// cand o clasa mosteneste de la alta clasa metodele si variabilele ei partea public a clasei de la care se mosteneste
// in cazul nostru Person va deveni in clasa Employee private asa ca trebuie sa specificam ca tipul mostenirii sa fie public
// pentru a putea utiliza metodele acesteia
class Employee : public Person {
private:

	std::string departament;
public:
	Employee(std::string firstName, std::string lastName, std::string departament) : Person(firstName, lastName), departament(departament) {}
	std::string getDepartament() { return departament; }
	void setDepartament(std::string departament) { this->departament = departament; }
	void printInfo() override {
		std::cout << "first name  :  " << first << "\n";
		std::cout << "last name   :  " << last << "\n";
		std::cout << "departament :  " << getDepartament() << "\n";
 	}
};

int main() {
	/*Person p("Caleb","Curry");
	p.printFullName();
	std::cout << p.getName() << "\n";

	Person p1("Simon","Says");
	p1.printFullName();*/

	//polimorfism
	std::vector<Person*> people;
	Person p("Ernest", "Maxim");    
	Employee e("first", "last", "sales");
	people.push_back(&p);
	people.push_back(&e);

	Person::printPeople(people);
	return 0;
}