#ifndef SPHERE_HEADER
#define SPHERE_HEADER

#include "Triangle.h"
#include "Direction.h"

class Sphere
{
public:

	Sphere() {
		center;
		radius = 0;
		color;
	}

	Sphere(Vertex c, double r, Materials m, ColorDbl col) : center(c), radius(r), material(m), color(col) {};
	Sphere(Vertex c, double r, Materials m) : center(c), radius(r), material(m) {};

	bool sphereIntersection(Ray &r, double &d, Direction &n) {

		double d0, d1;

		Direction L(r.start.X - center.X, r.start.Y - center.Y, r.start.Z - center.Z);
		double a = r.dir.dot(r.dir);
		double b = 2 * r.dir.dot(L);
		double c = L.dot(L) - (radius*radius);

		if (!solveQuadratic(a, b, c, d0, d1)) return false;

		if (d0 > d1) std::swap(d0, d1);

		if (d0 < 0) {
			d0 = d1;
			if (d0 < 0) return false;
		}

		Vertex Phit(r.start.X - d0 * r.dir.X, r.start.Y - d0 * r.dir.Y, r.start.Z - d0 * r.dir.Z, 1);
		//normal
		n = Direction(Phit.X - center.X, Phit.Y - center.Y, Phit.Z - center.Z).normalize();

		d = d0;
	};

	bool solveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1)
	{
		double discr = b * b - 4 * a * c;
		if (discr < 0) return false;
		else if (discr == 0) x0 = x1 = -0.5 * b / a;
		else {
			double q = (b > 0) ?
				-0.5 * (b + sqrt(discr)) :
				-0.5 * (b - sqrt(discr));
			x0 = q / a;
			x1 = c / q;
		}
		if (x0 > x1) std::swap(x0, x1);

		return true;
	}

	Vertex center;
	double radius;
	ColorDbl color;
	Materials material;

private:
};
#endif