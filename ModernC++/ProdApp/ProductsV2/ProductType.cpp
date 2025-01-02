#include "ProductType.h"

ProductType StringToProductType(const std::string& sType)
{
	if (sType == "PersonalHygiene")
		return ProductType::PersonalHygiene;
	else if (sType == "SmallAppliences")
		return ProductType::SmallAppliances;
	else if (sType == "Clothing")
		return ProductType::Clothing;

	throw std::exception{ "Error: Could not convert from string to NonperishableProduct::Type!" };
}
