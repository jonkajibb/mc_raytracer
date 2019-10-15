#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

//triangle class. Defined by three objects from class Vertex.
//Has color represented by instance of ColorDbl.
//Has normal stored as an instance of Direction.

#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "Light.h"
#include "Ray.h"
#include "math.h"
#include "ColorDbl.h"

class Triangle
{
public:
	Triangle();

	//Constructor
	Triangle(Vertex v1, Vertex v2, Vertex v3, ColorDbl c);

	bool rayIntersection(Ray &r, double &t);

	Direction findNormal(Vertex a, Vertex b, Vertex c);

	double dot(Direction d1, Direction d2);

	Direction crossProduct(Direction d1, Direction d2);

	std::vector<Triangle> createTetrahedron(Vertex origo, ColorDbl clr);

	//ColorDbl shading(Ray &importance, Light l, std::vector<Triangle> triangles);

	Vertex v1;
	Vertex v2;
	Vertex v3;
	ColorDbl color;
	Direction normal;
private:

};

#endif