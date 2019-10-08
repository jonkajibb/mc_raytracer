#include "Triangle.h"
#include "Direction.h"
#include "math.h"

const double EPS = 1e-4;

Triangle::Triangle()
{
	v1;
	v2;
	v3;
	color;
	normal;
}

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

bool Triangle::rayIntersection(Ray &r, double &t)
{
	Direction edge1(this->v2.X - this->v1.X, this->v2.Y - this->v1.Y, this->v2.Z - this->v1.Z);
	Direction edge2(this->v3.X - this->v1.X, this->v3.Y - this->v1.Y, this->v3.Z - this->v1.Z);
	Direction P = crossProduct(r.dir, edge2);
	double det = dot(edge1, P);

	//if culling (triangle is backfacing)
	if (det < EPS) {
		return false;
	}
	else if (fabs(det) < EPS) { //if parallell with triangle
		return false;
	}

	double invDet = 1 / det;

	Direction T(r.start.X - this->v1.X, r.start.Y - this->v1.Y, r.start.Z - this->v1.Z); //orig - v1
	double u = dot(T, P) * invDet;
	if (u < 0 || u > 1) return false;

	Direction Q = crossProduct(T, edge1);
	double v = dot(r.dir, Q) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = dot(edge2, Q) * invDet;

	return true;
}

Direction Triangle::crossProduct(Direction d1, Direction d2)
{
	double Nx = d1.Y * d2.Z - d1.Z * d2.Y;
	double Ny = d1.Z * d2.X - d1.X * d2.Z;
	double Nz = d1.X * d2.Y - d1.Y * d2.X;

	return Direction(Nx, Ny, Nz);
}

std::vector<Triangle> Triangle::createTetrahedron(Vertex origo, ColorDbl clr)
{
	Vertex a, b, c, d;
	ColorDbl col(140, 10, 240);

	std::vector<Triangle> tetra;

	a.X = origo.X + 1;
	a.Y = origo.Y;
	a.Z = origo.Z - -1 / sqrt(2);

	b.X = origo.X - 1;
	b.Y = origo.Y;
	b.Z = origo.Z - (-1 / sqrt(2));

	c.X = origo.X;
	c.Y = origo.Y + 1;
	c.Z = origo.Z + (-1 / sqrt(2));

	d.X = origo.X;
	d.Y = origo.Y - 1;
	d.Z = origo.Z + (-1 / sqrt(2));

	Triangle t1(a, c, d, clr);
	Triangle t2(a, b, c, clr);
	Triangle t3(a, d, b, clr);
	Triangle t4(b, d, c, clr);

	tetra.push_back(t1);
	tetra.push_back(t2);
	tetra.push_back(t3);
	tetra.push_back(t4);

	return tetra;
}

double Triangle::dot(Direction d1, Direction d2)
{
	double result = d1.X*d2.X + d1.Y*d2.Y + d1.Z*d2.Z;

	return result;
};
