#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // for strlen and strcpy

class Employee {
private:
    char* firstName;
    char* lastName;
    float salary;

public:
    // Constructor
    Employee(const char* firstName = "", const char* lastName = "", float salary = 0.0) : salary(salary) {
        this->firstName = new char[strlen(firstName) + 1];
        strcpy(this->firstName, firstName);
        this->lastName = new char[strlen(lastName) + 1];
        strcpy(this->lastName, lastName);
    }

    // Destructor
    ~Employee() {
        delete[] firstName;
        delete[] lastName;
    }

    // Copy constructor
    Employee(const Employee& other) : salary(other.salary) {
        firstName = new char[strlen(other.firstName) + 1];
        strcpy(firstName, other.firstName);
        lastName = new char[strlen(other.lastName) + 1];
        strcpy(lastName, other.lastName);
    }

    // Assignment operator
    Employee& operator=(const Employee& other) {
        if (this != &other) {
            delete[] firstName;
            delete[] lastName;

            firstName = new char[strlen(other.firstName) + 1];
            strcpy(firstName, other.firstName);
            lastName = new char[strlen(other.lastName) + 1];
            strcpy(lastName, other.lastName);
            salary = other.salary;
        }
        return *this;
    }

    // Comparison operator
    bool operator<(const Employee& a) const {
        int firstNameCmp = strcmp(firstName, a.firstName);
        if (firstNameCmp != 0) {
            return firstNameCmp < 0;
        }
        return strcmp(lastName, a.lastName) < 0;
    }

    // Salary increase operator
    Employee operator+(int percent) const {
        Employee temp(*this);
        temp.salary += temp.salary * percent / 100;
        return temp;
    }

    Employee operator-(int value) const {
        if (value > salary)
            throw std::invalid_argument("Amount is greater than the salary");
        Employee temp(*this);
        temp.salary -= value;
        return temp;
    }

    // Friend function for output
    friend std::ostream& operator<<(std::ostream& os, const Employee& a);
};

// Output operator
std::ostream& operator<<(std::ostream& os, const Employee& a) {
    os << a.firstName << " " << a.lastName << " " << a.salary << "\n";
    return os;
}

int main() {
    std::vector<Employee> emp;
    for (int i = 0; i < 2; i++) {
        char firstName[35];
        char lastName[35];
        float salary;

        std::cout << "Enter first name: ";
        std::cin.get(firstName, 35);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character left in the buffer

        std::cout << "Enter last name: ";
        std::cin.get(lastName, 35);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character left in the buffer

        std::cout << "Enter salary: ";
        std::cin >> salary;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character left in the buffer

        emp.emplace_back(firstName, lastName, salary);
    }

    std::sort(emp.begin(), emp.end());

    // Increase the salary of the first employee by 20%
    emp[0] = emp[0] + 20;

    // Decrease the salary of the last employee by 10 units
    if (emp.size() > 1) {
        emp[1] = emp[1] - 10;
    }

    for (const auto& e : emp) {
        std::cout << e;
    }

    return 0;
}
