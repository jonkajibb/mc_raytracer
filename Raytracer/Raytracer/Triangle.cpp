#include "Triangle.h"
#include "Direction.h"
#include "math.h"

const double EPS = 1e-4;

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

	double t = dot(edge2, Q) * invDet;

	return true;

	/*
	double D = this->v1.X*r.start.X + this->v1.Y*r.start.Y + this->v1.Z*r.start.Z; //v1 * ray start
	Direction orig(r.start.X, r.start.Y, r.start.Z);

	//normal*origin
	double NO = dot(this->normal, orig);
	//normal*ray direction
	double NR = dot(this->normal, r.dir);

	double t = -((NO + D) / NR);

	//Check if the triangle is behind the ray (?)
	if (t < 0) return false;

	Vertex Phit(orig.X + t * r.dir.X, orig.Y + t * r.dir.Y, orig.Z + t * r.dir.Z, 1);  //P = orig + t * r.dir;

	//STEP 2 LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOL
	Direction C;

	//edge 1 (v2 - v1)
	Direction edge1(this->v2.X - this->v1.X, this->v2.Y - this->v1.Y, this->v2.Z - this->v1.Z);
	//sdasdasmkd
	Direction vp1(Phit.X - this->v1.X, Phit.Y - this->v1.Y, Phit.Z - this->v1.Z);

	C = crossProduct(edge1, vp1);

	if (dot(this->normal, C) < 0) return false; // P is on the right side 

	//edge 2 (v2 - v3)
	Direction edge2(this->v3.X - this->v2.X, this->v3.Y - this->v2.Y, this->v3.Z - this->v2.Z);
	//mkdmkmkdmvkv
	Direction vp2(Phit.X - this->v2.X, Phit.Y - this->v2.Y, Phit.Z - this->v2.Z);

	C = crossProduct(edge2, vp2);

	if (dot(this->normal, C) < 0) return false; // P is on the right side 

	//edge 3 (v1 - v3)
	Direction edge3(this->v1.X - this->v3.X, this->v1.Y - this->v3.Y, this->v1.Z - this->v3.Z);
	//mkdmkmkdmvkv
	Direction vp3(Phit.X - this->v3.X, Phit.Y - this->v3.Y, Phit.Z - this->v3.Z);

	C = crossProduct(edge3, vp3);

	if (dot(this->normal, C) < 0) return false; // P is on the right side

	return true; //the ray hits the triangles.*/
}

Direction Triangle::crossProduct(Direction d1, Direction d2)
{
	double Nx = d1.Y * d2.Z - d1.Z * d2.Y;
	double Ny = d1.Z * d2.X - d1.X * d2.Z;
	double Nz = d1.X * d2.Y - d1.Y * d2.X;

	return Direction(Nx, Ny, Nz);
}

double Triangle::dot(Direction d1, Direction d2)
{
	double result = d1.X*d2.X + d1.Y*d2.Y + d1.Z*d2.Z;

	return result;
};
