#include <iostream>
#include "Product.h"
#include <vector>
#include <fstream>

int main() {
    std::vector<Product> products;
    std::ifstream file("Products.txt");

    if (!file) {
        std::cerr << "File can't be opened!";
        file.close();
        return 0;
    }

    Product prod;
    while (file >> prod) {
        products.push_back(prod);
    }

    file.close();

    for(auto& pd : products) {
        if (std::isalpha(pd.getInfo()[0]))
            std::cout << pd.getProductName() << " " << pd.vatPrice() << "\n";
    }
	return 0;
}