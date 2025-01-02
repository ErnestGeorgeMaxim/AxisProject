#pragma once
#include <iostream>

class Move{
private:
	double x;
	double y;
public:
	Move(double a = 0, double b = 0);// sets x, y to a, b;
	void showmove() const; //shows the current x,y values
	Move add(const Move& m) const;
	void reset(double a = 0, double b = 0);
};

