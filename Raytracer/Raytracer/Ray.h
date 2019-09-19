#ifndef RAY_HEADER
#define RAY_HEADER

//triangle class. Defined by three objects from class Vertex.
//Has color represented by instance of ColorDbl.
//Has normal stored as an instance of Direction.

#include "Vertex.h"
#include "ColorDbl.h"

class Ray
{
public:
	//Constructor
	Ray(Vertex x, Direction d) : start(x), dir(d) { };

	Vertex start;
	Vertex end;
	Direction dir;
	ColorDbl color;

private:
};

#endif