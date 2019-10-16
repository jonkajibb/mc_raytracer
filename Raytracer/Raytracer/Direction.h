#ifndef DIRECTION_HEADER
#define DIRECTION_HEADER

//triangle class. Defined by three objects from class Vertex.
//Has color represented by instance of ColorDbl.
//Has normal stored as an instance of Direction.

#include "Vertex.h"
#include "ColorDbl.h"
#include <math.h>
#include <iostream>

class Direction
{
public:
	Direction()
		: X(0), Y(0), Z(0) { };
	//Constructor
	Direction(double x, double y, double z)
		: X(x), Y(y), Z(z) { };

	double dot(Direction& d1)// , Direction& d2)
	{
		double result = (X * d1.X) + (Y * d1.Y) + (Z * d1.Z);
		//std::cout << result << std::endl;
		return result;
	};

	Direction operator*(double const num) {
		return Direction(X*num, Y*num, Z*num);
	};

	Direction normalize() {
		//dividing vector by its length/magnitude
		X = X / sqrt((X*X) + (Y * Y) + (Z * Z));
		Y = Y / sqrt((X*X) + (Y * Y) + (Z * Z));
		Z = Z / sqrt((X*X) + (Y * Y) + (Z * Z));

		return Direction(X, Y, Z);
	};

	Direction crossProduct(Direction d1)
	{
		double Nx = this->Y * d1.Z - this->Z * d1.Y;
		double Ny = this->Z * d1.X - this->X * d1.Z;
		double Nz = this->X * d1.Y - this->Y * d1.X;

		return Direction(Nx, Ny, Nz);
	}

	double getScalar() {
		double s;
		s = sqrt(this->X*this->X + this->Y*this->Y + this->Z*this->Z);
		return s;
	};

	//DATA MEMBERS
	double X;
	double Y;
	double Z;

private:

};

#endif