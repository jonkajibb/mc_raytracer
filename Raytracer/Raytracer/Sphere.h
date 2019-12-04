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

	Sphere(glm::vec4 c, float r, Materials m, ColorDbl col) : center(c), radius(r), material(m), color(col) {};
	Sphere(glm::vec4 c, float r, Materials m) : center(c), radius(r), material(m) {};

	bool sphereIntersection(Ray &r, float &d) {

		float d0, d1;

		glm::vec3 L = r.start - center;
		float a = dot(r.dir, r.dir);
		float b = 2 * dot(r.dir, L);
		float c = dot(L, L) - (radius*radius);

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
		float discr = b * b - 4.0f * a * c;
		if (discr < 0) return false;
		else if (discr == 0) x0 = x1 = -0.5f * b / a;
		else {
			float q = (b > 0.0f) ?
				-0.5f * (b + sqrt(discr)) :
				-0.5f * (b - sqrt(discr));
			x0 = q / a;
			x1 = c / q;
		}
		if (x0 > x1) std::swap(x0, x1);

		return true;
	}

	glm::vec4 center;
	float radius;
	ColorDbl color;
	Materials material;

private:
};
#endif
