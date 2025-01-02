#pragma once
#include "Author.h"

class Book : public Author{
private:
	std::string name;
	Author author;
	double price;
	int qty = 0;
public:
	Book() = default;
	Book(const std::string& name, const Author& author, const double& price) {
		this->name = name;
		this->author = author;
		this->price = price;
	}
	Book(const std::string& name, const Author& author, const double& price, const int& qty) {
		this->name = name;
		this->author = author;
		this->price = price;
		this->qty = qty;
	}
	std::string getName() const { return this->name; }
	Author getAuthor() const { return this->author; }
	double getPrice() const { return this->price; }
	void setPrice(const double& price) { this->price = price; }
	int getQty() const { return this->qty; }
	void setQty(const int& qty) { this->qty = qty; }
	friend std::ostream& operator<<(std::ostream& os, const Book& b);
};

std::ostream& operator<<(std::ostream& os, const Book& b) {
	os << "Bool[name=" << b.name << "," << b.author << ",price=" << b.price << ",qty=" << b.qty << "]\n";
	return os;
}
