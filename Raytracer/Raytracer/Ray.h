#ifndef RAY_HEADER
#define RAY_HEADER

//triangle class. Defined by three objects from class Vertex.
//Has color represented by instance of ColorDbl.
//Has normal stored as an instance of Direction.

#include "Vertex.h"
#include "Direction.h"

class Ray
{
public:
	Ray();
	//Constructor
    Ray(Vertex x, Direction d) {
      start = x;
      dir = d;
      dir.normalize();
    };

	//ColorDbl shadowRay(Triangle &hitTri, Ray &importance, Vertex light);

	Vertex start;
	Vertex end;
	Direction dir;
	ColorDbl color;

private:
};

#endif
