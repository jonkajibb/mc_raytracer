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

	double dot(Direction& d1)// , Direction& d2)
	{
		double result = X * d1.X + Y * d1.Y + Z * d1.Z;
		return result;
	};

	Direction operator*(double const num) {
		return Direction(X*num, Y*num, Z*num);
	};

	/*Direction operator-(Vertex const &v1, Vertex const &v2) {
		return Direction(this.X - v2.X, v1.Y - v2.Y, v1.Z - v2.Z);
	};*/

	//DATA MEMBERS
	double X;
	double Y;
	double Z;

private:

};

#endif