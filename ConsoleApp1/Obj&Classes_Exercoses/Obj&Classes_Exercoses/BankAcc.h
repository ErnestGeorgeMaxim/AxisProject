#pragma once
#include <iostream>

class BankAcc
{
private:
	std::string d_name;
	std::string accNumber;
	double balance;

public:
	//constructors
	BankAcc();
	BankAcc(const std::string& dn, const std::string& accN, double bnc = 0);

	//destructor
	~BankAcc();

	void display();
	void deposit(double amount);
	void withdraw(double amount);
};

