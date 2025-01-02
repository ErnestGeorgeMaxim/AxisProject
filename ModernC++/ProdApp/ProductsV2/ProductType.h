#pragma once
#include <cstdint>
#include<string>

enum class ProductType : uint8_t
{
	Clothing,
	SmallAppliances,
	PersonalHygiene
};

ProductType StringToProductType(const std::string& sType);
