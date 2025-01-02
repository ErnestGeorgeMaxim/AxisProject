#pragma once
#include <iostream>

class Date{
private:
	int day;
	int month;
	int year;
public:
	Date(const int& day, const int& month, const int& year) {
		this->day = day;
		this->month = month;
		this->year = year;
	}
	int getDay() const { return this->day; }
	int getMonth() const { return this->month; }
	int getYear() const { return this->year; }
	void setDay(const int& day) { this->day = day; }
	void setMonth(const int& month) { this->month = month; }
	void setYear(const int& year) { this->year = year; }
	friend std::ostream& operator<<(std::ostream& os, const Date& d);
};

std::ostream& operator<<(std::ostream& os, const Date& d) {
	if (d.day < 10)
		os << "0";
	os << d.day << "/";
	if (d.month < 10)
		os << "0";
	os << d.month << "/";
	os << d.year << "\n";
	return os;
}

