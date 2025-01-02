#pragma once
#include <iostream>

namespace VECTOR {
	class Vector
	{
	public:
		enum Mode : int { RECT, POL };
		// RECT - rectangular, POL - polar modes	
	private:
		double x;		//horizontal value
		double y;		//vertical value
		double mag;		//length of vector
		double ang;		//direction of vector in degrees
		Mode mode;		//RECT or POL

		// privare methods for setting values
		void setMag();
		void setAng();
		void setX();
		void setY();

	public:
		Vector();
		Vector(double n1, double n2, Mode form = RECT);
		void reset(double n1, double n2, Mode form = RECT);
		~Vector();
		double xval() const { return x; }		// x value
		double yval() const { return y; }		// y value
		double magval() const { return mag; }	// magnitude value
		double angval() const { return ang; }	// angle value
		void polarMode();						//set mode to POL;
		void rectMode();						//set mode to RECT;

	//operator overloading
		Vector operator + (const Vector & v) const;
		Vector operator - (const Vector& v) const;
		Vector operator - () const;
		Vector operator * (double n) const;
	//friends
		friend Vector operator* (double n, const Vector& v);
		friend std::ostream& operator <<(std::ostream& os, const Vector& v);
	}; 
}//end namespace VECTOR
