#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

//triangle class. Defined by three objects from class Vertex.
//Has color represented by instance of ColorDbl.
//Has normal stored as an instance of Direction.

#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <glm.hpp>

//#include "pointLight.h"
//#include "areaLight.h"
#include "Ray.h"
#include "math.h"
#include "ColorDbl.h"

enum Materials {
	Diffuse,
	Mirror,
	Light
};

class Triangle
{
public:
	Triangle();

	//Constructor
	Triangle(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, Materials m, ColorDbl c);
	Triangle(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, Materials m);

	bool rayIntersection(Ray &r, float &t);

	//glm::vec3 findNormal(glm::vec4 a, glm::vec4 b, glm::vec4 c);

	//std::vector<Triangle> createTetrahedron(Vertex origo, ColorDbl clr);

	//ColorDbl shading(Ray &importance, Light l, std::vector<Triangle> triangles);

	glm::vec4 v1;
	glm::vec4 v2;
	glm::vec4 v3;
	Materials material;
	ColorDbl color;
	glm::vec3 normal;
private:

};

#endif