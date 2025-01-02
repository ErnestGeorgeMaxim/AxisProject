#pragma once
#include <cstdint>
#include <string>
#include <string_view>

#include "IPriceable.h"


class Product : public IPriceable
{
public:
	Product(int32_t id, std::string_view name, float rawPrice);

	// Inherited via IPriceable
	float GetPrice() const override;

	// Getters
	int32_t GetID() const;
	const std::string& GetName() const;

protected:
	int32_t m_id;
	std::string m_name;
	float m_price;
};
