
#include "Triangle.h"

const double EPS = 1e-4;

Triangle::Triangle()
{
	/*
    v1;
	v2;
	v3;
	color;
	normal;
     */
}

//Constructor for diffuse surfaces
Triangle::Triangle(Vertex i1, Vertex i2, Vertex i3, Materials m, ColorDbl c) {
	v1 = i1;
	v2 = i2;
	v3 = i3;
	material = m;
	color = c;

	normal = findNormal(v1, v2, v3);
};

//Constructor for mirror surfaces
Triangle::Triangle(Vertex i1, Vertex i2, Vertex i3, Materials m) {
	v1 = i1;
	v2 = i2;
	v3 = i3;
	material = m;

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
	Ny = -(U.X * V.Z - U.Z * V.X);
	Nz = U.X * V.Y - U.Y * V.X;

	return Direction(Nx, Ny, Nz).normalize();
};

bool Triangle::rayIntersection(Ray &r, double &t)
{
	Direction edge1(this->v2.X - this->v1.X, this->v2.Y - this->v1.Y, this->v2.Z - this->v1.Z);
	Direction edge2(this->v3.X - this->v1.X, this->v3.Y - this->v1.Y, this->v3.Z - this->v1.Z);
	Direction P = r.dir.crossProduct(edge2);
	double det = edge1.dot(P);

	//if culling (triangle is backfacing)
	if (det < EPS) {
		return false;
	}
	else if (fabs(det) < EPS) { //if parallell with triangle
		return false;
	}

	double invDet = 1 / det;

	Direction T(r.start.X - this->v1.X, r.start.Y - this->v1.Y, r.start.Z - this->v1.Z); //orig - v1
	double u = T.dot(P) * invDet;
	if (u < 0 || u > 1) return false;

	Direction Q = T.crossProduct(edge1);
	double v = r.dir.dot(Q) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = edge2.dot(Q) * invDet;

    
    //Är det här verkligen rätt?
	r.end = Vertex(r.start.X + r.dir.X*t,
		r.start.Y + r.dir.Y*t,
		r.start.Z + r.dir.Z*t, 1);

	return true;
}

Direction Triangle::crossProduct(Direction d1, Direction d2)
{
	double Nx = d1.Y * d2.Z - d1.Z * d2.Y;
	double Ny = d1.Z * d2.X - d1.X * d2.Z;
	double Nz = d1.X * d2.Y - d1.Y * d2.X;

	return Direction(Nx, Ny, Nz);
}

/*
std::vector<Triangle> Triangle::createTetrahedron(Vertex origo, ColorDbl clr)
{
	Vertex a, b, c, d;
	ColorDbl col(255, 200, 200);

	std::vector<Triangle> tetra;

	//closest
	a.X = origo.X - 1.5;
	a.Y = origo.Y;
	a.Z = origo.Z - 1.5;

	//back left
	b.X = origo.X + 1;
	b.Y = origo.Y + 1.5;
	b.Z = origo.Z - 1.5;

	//back right
	c.X = origo.X + 1.5;
	c.Y = origo.Y - 1.5;
	c.Z = origo.Z - 1.5;

	//top
	d.X = origo.X;
	d.Y = origo.Y;
	d.Z = origo.Z + 1;

	Triangle t1(a, d, b, clr);
	Triangle t2(b, d, c, clr);
	Triangle t3(a, c, d, clr);
	Triangle t4(a, b, c, clr);

	tetra.push_back(t1);
	tetra.push_back(t2);
	tetra.push_back(t3);
	tetra.push_back(t4);

	return tetra;
}*/

double Triangle::dot(Direction d1, Direction d2)
{
	double result = d1.X*d2.X + d1.Y*d2.Y + d1.Z*d2.Z;

	return result;
};
