#include "PerishableProduct.h"


PerishableProduct::PerishableProduct(int32_t id, std::string_view name, float rawPrice, std::string_view expirationDate) :
	Product(id, name, rawPrice),
	m_expirationDate{ expirationDate }
{
	// empty
}

int32_t PerishableProduct::GetVat() const
{
	return kVAT;
}

const std::string& PerishableProduct::GetExpirationDate() const
{
	return m_expirationDate;
}
