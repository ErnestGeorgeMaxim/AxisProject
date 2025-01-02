#include <iostream>
#include "BankAcc.h"
#include "Person.h"
#include "Move.h"	

int main() {
	//EX1
	/*BankAcc customer1("Olly Alexander", "119202", 120000.12);
	BankAcc customer2("Lica Insarcinatul", "192145", 1.42);
	customer1.display();
	customer2.display();
	
	customer1.deposit(1233.0);
	customer2.deposit(0.60);
	customer1.withdraw(12.0);
	customer2.withdraw(3.0);*/

	//EX2
	/*Person one;
	Person two("Smythecraft");
	Person three("Dimwiddy", "Sam");
	one.Show();
	one.FormalShow();
	two.Show();
	two.FormalShow();
	three.Show();
	three.FormalShow();*/

	//EX3
	Move first;
	Move second(3);
	Move third(3, 5);
	first.showmove();
	second.showmove();
	third.showmove();
	Move fourth = first.add(second);
	fourth.showmove();
	first.showmove();
	first.reset();
	first.showmove();
	return 0;
}