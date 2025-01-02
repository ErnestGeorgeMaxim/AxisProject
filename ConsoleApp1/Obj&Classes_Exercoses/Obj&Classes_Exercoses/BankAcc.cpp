#include "BankAcc.h"

BankAcc::BankAcc() {
	d_name = "unknown";
	accNumber = "unknown";
	balance = 0.0;
}
BankAcc::BankAcc(const std::string& dn, const std::string& accN, double bnc) {
	d_name = dn;
	accNumber = accN;
	balance = bnc;
}
BankAcc::~BankAcc(){
}

void BankAcc::display(){
	using std::cout;

	cout << "Depositor's Name: " << d_name << "\n"
		 << "Account Number:   " << accNumber << "\n"
		 << "Balance:          $" << balance << "\n\n";
}

void BankAcc::deposit(double amount){
	if (amount < 0) {
		std::cout << "The amount of money is less than 0!\n"
			      << "Transaction of " << d_name
			      << " has been suspended!\n";
	}
	else {
		balance += amount;
		std::cout << "New balance of " << d_name << " account is:" << balance << "\n";
	}
}

void BankAcc::withdraw(double amount){
	if (amount < 0 || amount > balance ) {
		std::cout << "The amount of money is less than 0 or bigger than the balance!\n"
			      << "Transaction of " << d_name
		 	      << " has been suspended!\n";
	}
	else {
		balance -= amount;
		std::cout << "New balance of " << d_name << " account is:" << balance << "\n";
	}
}
