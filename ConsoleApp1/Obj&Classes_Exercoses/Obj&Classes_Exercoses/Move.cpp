#include "Move.h"

Move::Move(double a, double b){
	x = a;
	y = b;
}

void Move::showmove() const{
	using std::cout;
	std::cout << x << " " << y << "\n";
}

Move Move::add(const Move& m) const{
	double y_m = y + m.y;
	double x_m = x + m.x;
	return Move(x_m,y_m);
}

void Move::reset(double a, double b){
	x = a;
	y = b;
}
