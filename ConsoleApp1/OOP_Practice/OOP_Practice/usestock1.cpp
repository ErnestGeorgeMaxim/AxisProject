#include <iostream>
#include "stock20.h"

const int STKS = 4;

int main() {
	{
		using std::cout;
		cout << "Using constructors to create new objects\n";
		Stock stock1("NanoSmart", 12, 20.0);
		stock1.show();
		Stock stock2 = Stock("Boffo Objects", 2, 2.0);
		stock2.show();

		cout << "Assigning stock1 to stock2:\n";
		stock2 = stock1;
		cout << "Listing stock1 and stock2:\n";
		stock1.show();
		stock2.show();

		cout << "Using a constructor to reset an object\n";
		stock1 = Stock("Nifty Foods", 10, 50.0);
		cout << "Revised stock1:\n";
		stock1.show();
		cout << "Done\n";
	}

	//list initialization 
	Stock hot_tip = { "Derivatives Plus Plus", 100, 45.0 };
	Stock temp{};

	const Stock land = Stock("Kludgehorn Properties");
	land.show();

	std::cout << "\n\n\n\n";

	Stock stocks[STKS] = {
		Stock("NanoSmart", 12.5, 20),
		Stock("Boffo Objects", 200, 2.0),
		Stock("Monolithic Obelisks", 130, 3.250),
		Stock("Fleep Enterprises", 60, 6.5)
	};
	std::cout << "Stock holdings:\n";
	for (const auto & st : stocks)
		st.show();

	const Stock* top = &stocks[0];
	for (int st = 1; st < STKS; st++)
		top = &top->topval(stocks[st]);
	std::cout << "\nMost valuable holding:\n";
	top->show();


	//enum class egg {Small, Medium, Large, Jumbo};
	//enum class t_shirt {Small, Medium, Large, Jumbo};
	//egg choice = egg::Large;
	//t_shirt Floyd = t_shirt::Large;

	//enum egg_old { Small, Medium, Large, Jumbo }; // unscoped
	//enum class t_shirt { Small, Medium, Large, Xlarge }; // scoped
	//egg_old one = Medium; // unscoped
	//t_shirt rolf = t_shirt::Large; // scoped
	//int king = one; // implicit type conversion for unscoped
	////int ring = rolf; // not allowed, no implicit type conversion
	//if (king < Jumbo) // allowed
	//	std::cout << "Jumbo converted to int before comparison.\n";
	////if (king < t_shirt::Medium) // not allowed
	////	std::cout << "Not allowed: < not defined for scoped enum.\n";

	////explicit conversion
	//int Frodo = int(t_shirt::Small);



	return 0;
}