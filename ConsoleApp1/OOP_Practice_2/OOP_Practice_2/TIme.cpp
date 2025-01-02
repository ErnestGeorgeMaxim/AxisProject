#include "TIme.h"

TIme::TIme(){
	hours = minutes = 0;
}

TIme::TIme(int h, int m){
	hours = h;
	minutes = m;
}

void TIme::addMin(int m){
	minutes += m;
	hours += minutes / 60;
	minutes %= 60;
}

void TIme::addHr(int h){
	hours += h;
}

void TIme::Reset(int h, int m){
	hours = h;
	minutes = m;
}

TIme operator+(const TIme& t1, const TIme& t2) {
	TIme sum;
	sum.minutes = t1.minutes + t2.minutes;
	sum.hours = t1.hours + t2.hours + sum.minutes/60;
	sum.minutes %= 60;
	return sum;
}

TIme TIme::operator-(const TIme& t) const
{
	TIme result;
	int tot1,tot2;
	tot1 = t.minutes + 60 * t.hours;
	tot2 = minutes + 60 * hours;
	result.minutes = (tot2 - tot1) % 60;
	result.hours = (tot2 - tot1) / 60;
	return result;
}

TIme TIme::operator*(double n) const
{
	TIme result;
	int totalmins = hours * n * 60 + minutes * n;
	result.minutes = totalmins % 60;
	result.hours = totalmins / 60;
	return result;
}

TIme operator*(double m, const TIme& t){
	TIme result;
	long totalmins = t.hours * m * 60 + t.minutes * m;
	result.hours = totalmins / 60;
	result.minutes = totalmins % 60;
	return result;
}

std::ostream& operator<<(std::ostream& os, const TIme& t) {
	os << t.hours << ":" << t.minutes;
	return os;
} 

