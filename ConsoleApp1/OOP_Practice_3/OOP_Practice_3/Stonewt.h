#pragma once
#include <iostream>

class Stonewt
{
private:
	enum {lbsPerStone = 14};		//pounds per stone
	int stone;						//whole stones
	double pdsLeft;					//fractional pounds
	double pounds;					//entire weight in pounds

public:
	Stonewt(double lbs);			//constructor for double lbs
	Stonewt(int stn, double lbs);	//constructor for stones and lbs
	Stonewt();						//default constructor
	~Stonewt();						//destructor
	void showLbs() const;			//show weight in pounds
	void showStn() const;			//show weight in stone
};

