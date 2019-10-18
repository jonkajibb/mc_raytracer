
#include "Triangle.h"

const double EPS = 1e-4;

Triangle::Triangle()
{
	//v1;
	//v2;
	//v3;
	//color;
	//normal;
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
}

double Triangle::dot(Direction d1, Direction d2)
{
	double result = d1.X*d2.X + d1.Y*d2.Y + d1.Z*d2.Z;

	return result;
};

/*
ColorDbl Triangle::shading(Ray &importance, Light l, std::vector<Triangle> triangles) {
	bool intersected = false;
	double t = 1000;
	double angle;
	double minDistance = 10000;

	Triangle minTriangle;
	ColorDbl col;
	Direction d(l.pos.X - importance.end.X, l.pos.Y - importance.end.Y, l.pos.Z - importance.end.Z);

	ColorDbl light_i = l.color * l.intensity; //Light color*intenisty

	Ray sRay(importance.end, d);
	d = d.normalize();

	//Angle between importance ray endpoint normal and sRay's direction
	angle = std::max(0.0, d.dot(this->normal));
	//std::cout << angle << std::endl;

	//Check if shadowray intersects a surface -> shadow
	//has to check if the intersected surface is between
	//the light source and the shadowray origin point
	for (int i = 0; i < triangles.size(); i++)
	{
		if (triangles[i].rayIntersection(sRay, t))
		{
			if (t < minDistance) {
				minDistance = t;
				minTriangle = triangles[i];
				//Determine endpoint of ray, used in shading
				//ray.endTri = minTriangle;
			}
		}
	}

	Direction newD(l.pos.X - importance.end.X, l.pos.Y - importance.end.Y, l.pos.Z - importance.end.Z);
	Direction isec(sRay.end.X - importance.end.X, sRay.end.Y - importance.end.Y, sRay.end.Z - importance.end.Z);
	if (isec.getScalar() < newD.getScalar()) {
		intersected = true;
	}

	if (angle < 0) {
		col = this->color;
	}
	else if(!intersected){
		col = this->color * angle; //light_i;
	}
	else if (intersected) {
		col = this->color * 0.4;
	}

	//Check if sRay intersects something
	return col;
};*/
