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
	Direction(float x, float y, float z)
		: X(x), Y(y), Z(z) { };

	float dot(Direction& d1)// , Direction& d2)
	{
		float result = (X * d1.X) + (Y * d1.Y) + (Z * d1.Z);
		//std::cout << result << std::endl;
		return result;
	};

	Direction operator*(float num) {
		return Direction(X*num, Y*num, Z*num);
	};

	Direction operator-(Direction const &d) {
		return Direction(X-d.X, Y-d.Y, Z-d.Z);
	};

	Direction normalize() {
      float x1 = X;
      float y1 = Y;
      float z1 = Z;

      //dividing vector by its length/magnitude
      X = x1 / sqrt((x1*x1) + (y1 * y1) + (z1 * z1));
      Y = y1 / sqrt((x1*x1) + (y1 * y1) + (z1 * z1));
      Z = z1 / sqrt((x1*x1) + (y1 * y1) + (z1 * z1));

      return Direction(X, Y, Z);
    };

	const Direction crossProduct(Direction &d1)
	{
		float Nx = this->Y * d1.Z - this->Z * d1.Y;
		float Ny = this->Z * d1.X - this->X * d1.Z;
		float Nz = this->X * d1.Y - this->Y * d1.X;

		return Direction(Nx, Ny, Nz);
	}

	float getScalar() {
		float s;
		s = sqrt(this->X*this->X + this->Y*this->Y + this->Z*this->Z);
		return s;
	};

	//DATA MEMBERS
	float X;
	float Y;
	float Z;

private:

};

#endif
