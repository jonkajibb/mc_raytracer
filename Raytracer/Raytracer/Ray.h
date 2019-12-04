#ifndef RAY_HEADER
#define RAY_HEADER

//triangle class. Defined by three objects from class Vertex.
//Has color represented by instance of ColorDbl.
//Has normal stored as an instance of Direction.

#include "Direction.h"
#include <glm.hpp>

class Ray
{
public:
	Ray();
	//Constructor
    Ray(glm::vec4 x, glm::vec3 d) {
      start = x;
      dir = glm::normalize(d);
    };

	//ColorDbl shadowRay(Triangle &hitTri, Ray &importance, Vertex light);

	glm::vec4 start;
	glm::vec4 end;
	glm::vec3 dir;
	ColorDbl color;

private:
};

#endif
