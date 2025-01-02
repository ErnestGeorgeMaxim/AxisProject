#include "Product.h"
#include "IPriceable.h"
#include "PerishableProduct.h"
#include "NonperishableProduct.h"
#include<vector>
#include<regex>
#include<fstream>

bool IsDate(const std::string& str) {
	return std::regex_match(str, std::regex{ R"(\d\d\d\d-\d\d-\d\d)"});
}

int main() {
	std::vector<IPriceable*> products;

	for (std::ifstream file("product.txt"); !file.eof(); /*empty*/ ) {

		uint16_t id;
		std::string name;
		float price;
		uint16_t VAT;
		std::string exprDateOrProductType;

		if (!file) {
			std::cout << "Error\n";
			exit(1);
		}

		file >> id >> name >> price >> VAT >> exprDateOrProductType;
		if (IsDate(exprDateOrProductType)) {
			IPriceable* product = new PerishableProduct(id, name, price, exprDateOrProductType);	
			products.push_back(product);
		}
		//else 
		//  
		//products.emplace_back(id, name, price, VAT, exprDateOrProductType);
	}

	for (const auto& prod : products) {
		std::cout << prod->GetPrice() << " " << prod->GetVAT() << "\n";
	}
	return 0; 
}