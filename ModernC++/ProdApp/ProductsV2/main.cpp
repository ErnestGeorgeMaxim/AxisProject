#include <algorithm>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "IPriceable.h"
#include "Product.h"
#include "NonperishableProduct.h"
#include "PerishableProduct.h"


bool isDate(const std::string& sDate)
{
	return std::regex_match(sDate, std::regex{ R"(\d\d\d\d-\d\d-\d\d)" });
}


int main()
{
	std::vector<IPriceable*> priceables;

	int32_t id{};
	std::string name;
	float rawPrice{};
	int32_t vat{};
	std::string dateOrType;

	for (std::ifstream in{ "../product.prodb" }; !in.eof(); /*EMPTY*/)
	{
		// read line
		in >> id >> name >> rawPrice >> vat >> dateOrType;

		// construct object based on date or type
		if (isDate(dateOrType))
		{
			priceables.push_back(new PerishableProduct(id, name, rawPrice, dateOrType));
		}
		else
		{
			priceables.push_back(new NonperishableProduct(id, name, rawPrice, StringToProductType(dateOrType)));
		}
	}
	for (const auto product : priceables) {

	}
	return 0;
}