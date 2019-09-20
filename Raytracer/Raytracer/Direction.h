#ifndef DIRECTION_HEADER
#define DIRECTION_HEADER

//triangle class. Defined by three objects from class Vertex.
//Has color represented by instance of ColorDbl.
//Has normal stored as an instance of Direction.

#include "Vertex.h"
#include "ColorDbl.h"

class Direction
{
public:
	Direction()
		: X(0), Y(0), Z(0) { };
	//Constructor
	Direction(double x, double y, double z)
		: X(x), Y(y), Z(z) { };
	
	/*
	double Direction::operator*(Direction d1, Direction d2) {

	};

	double dot(Direction& d1, Direction& d2)
	{
		double result = d1.X * d2.X + d1.Y * d2.Y + d1.Z * d2.Z;
		return result;
	};*/

	//DATA MEMBERS
	double X;
	double Y;
	double Z;

private:
	
};

#endif