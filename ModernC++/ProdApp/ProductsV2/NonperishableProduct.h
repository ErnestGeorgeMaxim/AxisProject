#pragma once
#include <cstdint>
#include <iostream>
#include <string_view>

#include "Product.h"
#include "ProductType.h"


class NonperishableProduct : public Product
{
public:
	NonperishableProduct(int32_t id, std::string_view name, float rawPrice, ProductType type);

	// Inherited via Product
	int32_t GetVat() const override;

	// Getters
	ProductType GetType() const;

	friend std::ostream& operator<<(std::ostream& os, const NonperishableProduct& prod);

private:
	static const int32_t kVat{ 19 };

private:
	ProductType m_type;
};
