#include "Product.h"

Product::Product(){
	this->id = 0;
	this->productName = "unknown";
	this->price = 0.0;
	this->quantity = 0;
	this->info = "unknown";
}

int Product::getId() const {
	return this->id;
}

std::string Product::getProductName() const {
	return this->productName;
}

float Product::getPrice() const {
	return this->price;
}

int Product::getQuantity() const {
	return this->quantity;
}

std::string Product::getInfo() const {
	return this->info;
}

float Product::vatPrice()
{
	return (this->price * 10 / 100) + this->price;
}

std::istream& operator>>(std::istream& is, Product& product){
	is >> product.id >> product.productName >> product.price >> product.quantity >> product.info;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Product& product){
	os << product.getId() << " " << product.getProductName() << " " << product.getPrice() << " " << product.getQuantity() << " " << product.getInfo() << "\n";
	return os;
}
