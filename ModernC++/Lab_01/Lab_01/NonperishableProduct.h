#pragma once
#include "Product.h"

class NonperishableProduct :public Product{
public:
	NonperishableProduct(uint16_t id, std::string_view name, float price,const ProductType& productType);
	uint16_t GetVAT() const override;

private:
	static const uint16_t kVAT{ 19 };

private:
	ProductType m_productType;
};

