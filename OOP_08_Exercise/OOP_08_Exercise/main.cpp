#include <iostream>
#include <string>
#define PI 3.14


class CutiePraline {
private:
	std::string aroma;
	std::string origine;
public:
	CutiePraline() = default;
	CutiePraline(const std::string& aroma, const std::string& origine) {
		this->aroma = aroma;
		this->origine = origine;
	}
	virtual float getVolume() = 0;
	std::string toString() {
		return "Cutia " + origine + " are aroma " + aroma + " si volumul " + std::to_string(getVolume());
	}
};

class Lindt : public CutiePraline{
private:
	float length;
	float width;
	float height;
public:
	Lindt() = default;
	Lindt(const std::string& aroma, const std::string& origine, const float& length, const float& width, const float& height) : CutiePraline(aroma, origine), length(length), width(width), height(height) {}
	float getVolume() override{
		return length * width * height;
	}
};

class Baravelli : public CutiePraline{
private:
	float radius;
	float height;
public:
	Baravelli() = default;
	Baravelli(const std::string& aroma, const std::string& origine, const float& radius, const float& height) : CutiePraline(aroma, origine), radius(radius), height(height) {}
	float getVolume() override {
		return PI*radius*radius*height;
	}
};

class Raffaello : public CutiePraline{
private:
	float length;
public:
	Raffaello() = default;
	Raffaello(const std::string& aroma, const std::string& origine, const float& length) : CutiePraline(aroma, origine), length(length) {}
	float getVolume() override {
		return length*length*length;
	}
};

int main() {
	Lindt lindtBox("Ciocolată neagra", "Elvetia", 10.0f, 5.0f, 3.0f);
	Baravelli baravelliBox("Caramel", "Italia", 4.0f, 6.0f);
	Raffaello raffaelloBox("Cocos", "Italia", 5.0f);

	std::cout << lindtBox.toString() << std::endl;
	std::cout << baravelliBox.toString() << std::endl;
	std::cout << raffaelloBox.toString() << std::endl;
	return 0;
}