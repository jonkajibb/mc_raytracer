#include "Triangle.h"

/* Constructor: initialize a TriangleSoup object to an empty object */
Triangle::Triangle(Vertex i1, Vertex i2, Vertex i3, ColorDbl c) {
	v1 = i1;
	v2 = i2;
	v3 = i3;
	color = c;

	normal = findNormal(v1, v2, v3);
};


/* Destructor: clean up allocated data in a TriangleSoup object */
Triangle::~Triangle() {

};

Direction Triangle::findNormal(Vertex a, Vertex b, Vertex c) {
	//FUCKING CROSS PRODUCT

	double Nx;
	double Ny;
	double Nz;

	// Vector b - a
	// Vector c - a
	Direction U = Direction(b.X - a.X, b.Y - a.Y, b.Z - a.Z);
	Direction V = Direction(c.X - a.X, c.Y - a.Y, c.Z - a.Z);

	Nx = U.Y * V.Z - U.Z * V.Y;
	Ny = U.Z * V.X - U.X * V.Z;
	Nz = U.X * V.Y - U.Y * V.X;

	return Direction(Nx, Ny, Nz);
};
