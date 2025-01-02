#include "PerishableProduct.h"

PerishableProduct::PerishableProduct(uint16_t id, std::string_view name, float price, std::string_view expirationDate)
	: Product(id, name, price), m_expirationDate{expirationDate} {}

uint16_t PerishableProduct::GetVAT() const
{
	return PerishableProduct::kVAT;
}
