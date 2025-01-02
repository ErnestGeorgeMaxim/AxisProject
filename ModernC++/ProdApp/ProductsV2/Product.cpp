#include "Product.h"


Product::Product(int32_t id, std::string_view name, float rawPrice) :
	m_id{ id },
	m_name{ name },
	m_price{ rawPrice }
{
	// empty
}

float Product::GetPrice() const
{
	return m_price;
}

int32_t Product::GetID() const
{
	return m_id;
}

const std::string& Product::GetName() const
{
	return m_name;
}
