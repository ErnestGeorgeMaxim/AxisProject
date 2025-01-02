#pragma once
#include<iostream>
#include<cstdint>
#include<string_view>              
#include "ProductType.h"
#include "IPriceable.h"

class Product : public IPriceable {
public:
	Product(uint16_t id,std::string_view name, float price);
	float GetPrice() const override;

private:
	uint16_t m_id;
	std::string m_name;
	float m_price;
};

