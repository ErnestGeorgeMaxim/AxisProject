#include <iostream>
#include <string>
#include "Rectangle.h"
#include "Employee.h"
#include "InvoiceItem.h"
#include "Account.h"
#include "Date.h"
#include "Time.h"
#include "Ball.h"
#include "Author.h"
#include "Book.h"

int main() {
	/*Rectangle r1(1.2,3.4);
	std::cout << r1;
	Rectangle r2;
	std::cout << r2;

	r1.setLength(5.6);
	r1.setWidth(7.8);
	std::cout << r1;
	std::cout <<"Area : " << r1.getArea() << " Perimeter : " << r1.getPerimeter() << "\n";*/
	
	/*Employee e1(1023,"Eliot","Jhon",4023);
	std::cout << e1;
	std::cout << e1.getAnnualSalary() << "\n";
	e1.raiseSalary(30);
	std::cout << e1.getSalary() << "\n";*/

	/*InvoiceItem i("A101", "Pen Red", 888, 0.08);
	std::cout << i;*/

	/*Account a("A101", "Tan Ah Teck", 88);
	Account a1("A102", "Kumar");
	a.debit(12);
	std::cout << a;
	a.transferTo(a1, 12);
	std::cout << a;
	std::cout << a1;*/

	/*Date d(10, 2, 2014);
	std::cout << d;*/

	/*Time t1(1, 2, 3);
	std::cout << t1;
	t1.setTime(0, 0, 0);
	std::cout << t1;
	t1.nextSecond();
	std::cout << t1;
	t1.nextSecond();
	std::cout << t1;
	t1.previousSecond();
	t1.previousSecond();
	t1.previousSecond();
	std::cout << t1;*/

	Author a("Tan Ah Teck", "ahteck@nowhere.com", 'm');
	std::cout << a;
	Book b("Java for dummy", a, 19.95, 99);
	std::cout << b;
	std::cout << b.getAuthor().getEmail() << "\n";
	std::cout << b.getAuthor().getName();

	return 0;
}