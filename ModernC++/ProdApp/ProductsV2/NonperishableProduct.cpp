#include "NonperishableProduct.h"


NonperishableProduct::NonperishableProduct(int32_t id, std::string_view name, float rawPrice, ProductType type) :
	Product(id, name, rawPrice),
	m_type{ type }
{
	// empty
}

int32_t NonperishableProduct::GetVat() const
{
	return kVat;
}

ProductType NonperishableProduct::GetType() const
{
	return m_type;
}

std::ostream& operator<<(std::ostream& os, const NonperishableProduct& prod)
{
	os << prod.GetID() << " " << prod.GetName() << " " << prod.GetPrice();
	return os;
}
