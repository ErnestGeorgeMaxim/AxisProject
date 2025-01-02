#include <iostream>

class Movie {
public:
	std::string name;
	std::string genre;
	float rating;

	Movie(const std::string& name = "", const std::string& genre ="", const float& rating = 0) {
		this->name = name;
		this->genre = genre;
		this->rating = rating;
	}
	Movie(const Movie& original) {
		this->name = original.name;
		this->genre = original.genre;
		this->rating = original.rating;
	}

	Movie& operator=(const Movie& original) {
		this->name = original.name;
		this->genre = original.genre;
		this->rating = original.rating;

		return *this;
	}

};

int main() {
	Movie m1("The Dark Knight", "Action", 9.5);
	Movie m2("The Lion King", "Animated", 8);

	Movie m3;
	Movie m4(m1);
	m4 = m2;

	Movie m5 = m1;
	return 0;
}