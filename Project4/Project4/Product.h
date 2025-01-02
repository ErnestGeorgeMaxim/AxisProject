#pragma once
#include <iostream>

class Product{
public:
	Product();
    int getId() const;
    std::string getProductName() const;
    float getPrice() const;
    int getQuantity() const;
    std::string getInfo() const;
	float vatPrice();
	friend std::istream& operator>>(std::istream& is,Product& product);
	friend std::ostream& operator<<(std::ostream& os,const Product& product);

private:
	int id;
	std::string productName;
	float price;
	int quantity;
	std::string info;
};

