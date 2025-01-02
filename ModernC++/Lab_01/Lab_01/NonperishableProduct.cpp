#include "NonperishableProduct.h"

NonperishableProduct::NonperishableProduct(uint16_t id, std::string_view name, float price, const ProductType& productType)
	: Product(id, name, price), m_productType{productType} {}

uint16_t NonperishableProduct::GetVAT() const
{
	return NonperishableProduct::kVAT;
}
