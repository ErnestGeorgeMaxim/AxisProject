#pragma once
#include "Product.h"

class PerishableProduct  :public Product{
public:
	PerishableProduct(uint16_t id, std::string_view name, float price, std::string_view expirationDate);
	uint16_t GetVAT() const override;
private:
	static const uint16_t kVAT{ 9 };

private:
	std::string m_expirationDate;
};

