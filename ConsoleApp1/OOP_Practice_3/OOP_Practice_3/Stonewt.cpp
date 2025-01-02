#include "Stonewt.h"

Stonewt::Stonewt(double lbs){
	stone = int(lbs) / lbsPerStone;
	pdsLeft = int(lbs) % lbsPerStone + lbs - int(lbs);
	pounds = lbs;
}

Stonewt::Stonewt(int stn, double lbs){
	stone = stn;
	pdsLeft = lbs;
	pounds = stn * lbsPerStone + lbs;
}

Stonewt::Stonewt(){
	stone = pounds = pdsLeft = 0;
}

Stonewt::~Stonewt(){
}

void Stonewt::showLbs() const{
	std::cout << stone << " stone, " << pdsLeft << " pounds\n";
}

void Stonewt::showStn() const{
	std::cout << pounds << " pounds\n";
}
