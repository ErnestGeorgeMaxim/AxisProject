#pragma once
#include <iostream>

class Account{
private:
	std::string id;
	std::string name;
	int balance = 0;

public:
	Account(const std::string& id, const std::string& name) {
		this->id = id;
		this->name = name;
	}
	Account(const std::string& id, const std::string& name, const int& balance) {
		this->id = id;
		this->name = name;
		this->balance = balance;
	}
	std::string getId() const { return this->id; }
	std::string getName() const { return this->name; }
	int getBalance() const { return this->balance; }
	int credit(const int& amount) {
		this->balance += amount;
		return balance;
	}
	int debit(const int& amount) {
		if (amount <= balance)
			this->balance -= amount;
		else
			std::cout << "Amount exceeded balance";
		return balance;
	}
	int transferTo(Account& another,const int& amount) {
		if (amount <= balance) {
			this->balance -= amount;
			another.balance += amount;
		}
		else
			std::cout << "Amount exceeded balance";
		return balance;
	}
	friend std::ostream& operator<<(std::ostream& os, const Account& a);

};

std::ostream& operator<<(std::ostream& os, const Account& a) {
	os << "Id       : " << a.id << "\nName     : " << a.name << "\nBalance  : " << a.balance << "\n";
	return os;
}

