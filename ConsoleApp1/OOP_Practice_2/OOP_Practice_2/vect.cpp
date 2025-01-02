#include "vect.h"
#include <cmath>

using std::sqrt;
using std::cout;
using std::sin;
using std::cos;
using std::atan;
using std::atan2;

namespace VECTOR {
// compute degrees in one radian
	const double radToDegree = 45.0 / atan(1.0); // about 57.2957795130823

//privare methods
	void Vector::setMag(){ //sets magnitude
		mag = sqrt(x * x + y * y);
	}

	void Vector::setAng(){
		if (x == 0.0 && y == 0.0)
			ang = 0.0;
		else
			ang = atan2(y, x);
	}

	void Vector::setX(){
		x = mag * cos(ang);
	}

	void Vector::setY(){
		y = mag * sin(ang);
	}

//public methods
	Vector::Vector(){ //default constructor
		x = y = mag = ang = 0.0;
		mode = RECT;
	}

//construc vector from rectangular coordinates if form is RECT( the default) or else
//from polar coordinates if is POL
	Vector::Vector(double n1, double n2, Mode form){
		mode = form;
		if (form == RECT) {
			x = n1;
			y = n2;
			setMag();
			setAng();
		}
		else if (form == POL) {
			mag = n1;
			ang = n2 / radToDegree;
			setX();
			setY();
		}
		else {
			cout << "Incorrect 3rd argument to Vector() -- ";
			cout << "vector set to 0\n";
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}

// reset vector from rectangular coordinates if form is
// RECT (the default) or else from polar coordinates if
// form is POL
	void Vector::reset(double n1, double n2, Mode form){
		mode = form;
		if (form == RECT) {
			x = n1;
			y = n2;
			setMag();
			setAng();
		}
		else if (form == POL) {
			mag = n1;
			ang = n2 / radToDegree;
			setX();
			setY();
		}
		else {
			cout << "Incorrect 3rd argument to Vector() -- ";
			cout << "vector set to 0\n";
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}

	Vector::~Vector(){ //destructor
	}

	void Vector::polarMode(){
		mode = POL;
	}

	void Vector::rectMode(){
		mode = RECT;
	}

//operator overloading
//addition
	Vector Vector::operator+(const Vector& v) const{
		return Vector(x + v.x, y + v.y);
	}
	Vector Vector::operator-(const Vector& v) const
	{
		return Vector(x - v.x, y - v.y);
	}
	Vector Vector::operator-() const
	{
		return Vector(-x,-y);
	}
	Vector Vector::operator*(double n) const
	{
		return Vector(n * x, n * y);
	}
	Vector operator*(double n, const Vector& v)
	{
		return v * n;
	}
	std::ostream& operator<<(std::ostream& os, const Vector& v)
	{
		if( v.mode == Vector::RECT)
			os << "(x,y) = (" << v.x << ", " << v.y << ")";
		else if( v.mode == Vector::POL)
			os << "(m,a) = (" << v.mag << ", " << v.ang * radToDegree << ")";
		else 
			os << "Vector object mode is invalid";
		return os;
	}
}