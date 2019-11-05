#ifndef SPHERE_HEADER
#define SPHERE_HEADER

#include "Triangle.h"
#include "Direction.h"

class Sphere
{
public:

	Sphere() {
		//center;
		radius = 0;
		//color;
	}

	Sphere(Vertex c, float r, Materials m, ColorDbl col) : center(c), radius(r), material(m), color(col) {};
	Sphere(Vertex c, float r, Materials m) : center(c), radius(r), material(m) {};

	bool sphereIntersection(Ray &r, float &d) {

		float d0, d1;

		Direction L(r.start.X - center.X, r.start.Y - center.Y, r.start.Z - center.Z);
		float a = r.dir.dot(r.dir);
		float b = 2 * r.dir.dot(L);
		float c = L.dot(L) - (radius*radius);

		if (!solveQuadratic(a, b, c, d0, d1)) return false;

		if (d0 > d1) std::swap(d0, d1);

		if (d0 < 0) {
			d0 = d1;
			if (d0 < 0) return false;
		}

		

		d = d0;
        
        return true;
	};

	bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
	{
		float discr = b * b - 4 * a * c;
		if (discr < 0) return false;
		else if (discr == 0) x0 = x1 = -0.5 * b / a;
		else {
			float q = (b > 0) ?
				-0.5 * (b + sqrt(discr)) :
				-0.5 * (b - sqrt(discr));
			x0 = q / a;
			x1 = c / q;
		}
		if (x0 > x1) std::swap(x0, x1);

		return true;
	}

	Vertex center;
	float radius;
	ColorDbl color;
	Materials material;

private:
};
#endif
