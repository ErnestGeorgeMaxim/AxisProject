#pragma once
#include <iostream>

class Ball{
private:
	float x;
	float y;
	int radius;
	float xDelta;
	float yDelta;
public:
	Ball(const float& x, const float& y, const int& radius, const float& xDelta, const float& yDelta) {
		this->x = x;
		this->y = y;
		this->radius = radius;
		this->xDelta = xDelta;
		this->yDelta = yDelta;
	}
	float getX() const { return this->x; }
	void setX(const float& x) { this->x = x; }
	float getY() const { return this->y; }
	void setY(const float& y) { this->y = y; }
	int getRadius() const { return this->radius; }
	void setRadius(const int& radius) { this->radius = radius; }
	float getXDelta() const { return this->xDelta; }
	void setXDelta(const float& xDelta) { this->xDelta = xDelta; }
	float getYDelta() const { return this->yDelta; }
	void setYDelta(const float& yDelta) { this->yDelta = yDelta; }
	void move() {
		this->x += this->xDelta;
		this->y += this->yDelta;
	}
	void reflectHorizontal() {
		this->xDelta = -this->xDelta;
	}
	void reflectVertical() {
		this->yDelta = -this->yDelta;
	}
	friend std::ostream& operator<<(std::ostream& os, const Ball& b);
};

std::ostream& operator<<(std::ostream& os, const Ball& b) {
	os << "X     : " << b.x << "\nY     : " << b.y << "\nRadius : " << b.radius << "\nxDelta : " << b.xDelta << "\nyDelta : " << b.yDelta << "\n";
	return os;
}

