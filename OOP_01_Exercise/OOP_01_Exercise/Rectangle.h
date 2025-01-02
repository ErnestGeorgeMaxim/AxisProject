#pragma once
#include <iostream>

class Rectangle {
private:
	float length = 1.0;
	float width = 1.0;
public:
	Rectangle() = default;
	Rectangle(const float& length, const float& width) : length(length), width(width) {}
	float getLength() const { return this->length; }
	void setLength(const float& length) { this->length = length; }
	float getWidth() const { return this->width; }
	void setWidth(const float& width) { this->width = width; }
	float getArea() const { return length * width; }
	float getPerimeter() const { return 2.0 * (length + width); }
	friend std::ostream& operator<<(std::ostream& os, const Rectangle& r);
};

std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
	os << "length : " << r.getLength() << "\n";
	os << "width  : " << r.getWidth() << "\n\n";
	return os;
}

