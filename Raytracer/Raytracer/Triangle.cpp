#include "Triangle.h"
#include "Direction.h";

/* Constructor: initialize a TriangleSoup object to an empty object */
Triangle::Triangle(Vertex i1, Vertex i2, Vertex i3, ColorDbl c) {
	v1 = i1;
	v2 = i2;
	v3 = i3;
	color = c;

	normal = findNormal(v1, v2, v3);
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

bool Triangle::rayIntersection(Ray r)
{
	//if intersection, return true
	
	Direction T(r.start.X - this->v1.X, r.start.Y - this->v1.Y, r.start.Z - this->v1.Z);
	/*
	Direction E1(this->v2.X - this->v1.X, this->v2.Y - this->v1.Y, this->v2.Z - this->v1.Z);
	Direction E2(this->v3.X - this->v1.X, this->v3.Y - this->v1.Y, this->v3.Z - this->v1.Z);
	Direction D(r.start.X - r.end.X, r.start.Y - r.end.Y, r.start.Z - r.end.Z);

	//Cross product
	double Px = D.Y * E2.Z - D.Z * E2.Y;
	double Py = D.Z * E2.X - D.X * E2.Z;
	double Pz = D.X * E2.Y - D.Y * E2.X;

	Direction P(Px, Py, Pz);

	double Qx = T.Y * E1.Z - T.Z * E1.Y;
	double Qy = T.Z * E1.X - T.X * E1.Z;
	double Qz = T.X * E1.Y - T.Y * E1.X;

	Direction Q(Qx, Qy, Qz);

	// t = Q*E2 / P*E1
	double t;

	t = (Q.X*E2.X + Q.Y*E2.Y + Q.Z*E2.Z) / (P.X*E1.X + P.Y*E1.Y + P.Z*E1.Z);
	*/

	double D = this->v1.X*r.start.X + this->v1.Y*r.start.Y + this->v1.Z*r.start.Z;

	//normal*origin
	Direction orig(r.start.X, r.start.Y, r.start.Z);
	double NO = dot(this->normal, orig);//this->normal.X*r.start.X + this->normal.Y*r.start.Y + this->normal.Z*r.start.Z;
	//normal*ray direction
	double NR = dot(this->normal, r.dir);//this->normal.X*r.dir.X + this->normal.Y*r.dir.Y + this->normal.Z*r.dir.Z;

	double t = -((NO + D) / NR);

	// Phit = orig + t*r.dir

	return false;
}

double Triangle::dot(Direction d1, Direction d2)
{
	double result = d1.X*d2.X + d1.Y*d2.Y + d1.Z*d2.Z;

	return result;
};
