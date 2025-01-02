#pragma once
#include <iostream>

class TIme
{
private:
	int hours;
	int minutes;
public:
	TIme();
	TIme(int h, int m = 0);
	void addMin(int m);
	void addHr(int h);
	void Reset(int h = 0, int m = 0);
	// was initialy TIme Sum(const TIme& t) const;
	// became TIme operator +(const TIme& t) const;
	friend TIme operator +(const TIme& t1, const TIme& t2); // this form allows to sum in any way the objects
	TIme operator -(const TIme & t) const;
	TIme operator *(double n) const;
	friend TIme operator*(double m, const TIme& t);
	//friend void operator <<(std::ostream& os, const TIme& t);
	friend std::ostream& operator<<(std::ostream& os, const TIme& t); // better variant
};

