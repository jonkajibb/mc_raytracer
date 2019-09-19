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

	//Destructor
	//~Direction();

	//DATA MEMBERS
	double X;
	double Y;
	double Z;

private:
	
};

#endif