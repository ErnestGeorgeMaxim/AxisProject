#include "Product.h"

Product::Product(uint16_t id,std::string_view name, float price)
	: m_id{ id }, m_name{ name }, m_price{ price } {}

float Product::GetPrice() const {
	return m_price;
}
