#pragma once
#include <iostream>

class InvoiceItem{
private:
	std::string id;
	std::string desc;
	int qty;
	double unitPrice;
public:
	InvoiceItem(const std::string& id, const std::string& desc, const int& qty, const double& unitPrice) {
		this->id = id;
		this->desc = desc;
		this->qty = qty;
		this->unitPrice = unitPrice;
	}
	std::string getId() const { return this->id; }
	std::string getDesc() const { return this->desc; }
	int getQty() const { return this->qty; }
	void setQty(const int& qty) { this->qty = qty; }
	double getUnitPrice() const { return this->unitPrice; }
	void setUnitPrice(const double& unitPrice) { this->unitPrice = unitPrice; }
	double getTotal() const { return qty * unitPrice; }
	friend std::ostream& operator<<(std::ostream& os, const InvoiceItem& i);

};

std::ostream& operator<<(std::ostream& os, const InvoiceItem& i) {
	os << "Id        : " << i.id << "\nDesc      : " << i.desc << "\nQty       : " << i.qty << "\nUnitPrice : " << i.unitPrice << "\n";
	return os;
}

