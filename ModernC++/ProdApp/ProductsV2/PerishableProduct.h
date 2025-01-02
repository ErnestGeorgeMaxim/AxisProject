#pragma once
#include <cstdint>
#include <string>
#include <string_view>

#include "Product.h"


class PerishableProduct : public Product
{
public:
	PerishableProduct(int32_t id, std::string_view name, float rawPrice, std::string_view expirationDate);

	// Inherited via Product
	int32_t GetVat() const override;

	// Getters
	const std::string& GetExpirationDate() const;

private:
	static const int32_t kVAT{ 9 };

private:
	std::string m_expirationDate;
};