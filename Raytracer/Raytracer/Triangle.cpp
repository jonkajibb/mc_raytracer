
#include "Triangle.h"

const float EPS = 1e-4f;

Triangle::Triangle() {};

//Constructor for diffuse surfaces
Triangle::Triangle(glm::vec4 i1, glm::vec4 i2, glm::vec4 i3, Materials m, ColorDbl c) {
	v1 = i1;
	v2 = i2;
	v3 = i3;
	material = m;
	color = c;
	normal = glm::normalize(cross(glm::vec3(i2 - i1), glm::vec3(i3 - i1)));
};

//Constructor for mirror surfaces
Triangle::Triangle(glm::vec4 i1, glm::vec4 i2, glm::vec4 i3, Materials m) {
	v1 = i1;
	v2 = i2;
	v3 = i3;
	material = m;
	normal = glm::normalize(cross(glm::vec3(i2 - i1), glm::vec3(i3 - i1)));
	//normal = findNormal(v1, v2, v3);
};

//glm::vec3 Triangle::findNormal(glm::vec4 a, glm::vec4 b, glm::vec4 c) {
//	//FUCKING CROSS PRODUCT
//	// Vector b - a
//	// Vector c - a
//	glm::vec3 U = b - a;
//	glm::vec3 V = c - a;
//	glm::vec3 out = cross(U, V);
//
//	return glm::normalize(out);
//};

bool Triangle::rayIntersection(Ray &r, float &t)
{
	glm::vec3 edge1 = this->v2 - this->v1;
	glm::vec3 edge2 = this->v3 - this->v1;
	glm::vec3 P = cross(r.dir, edge2);
	float det = dot(edge1, P);

	//if culling (triangle is backfacing)
	if (det < EPS) {
		return false;
	}
	else if (fabs(det) < EPS) { //if parallell with triangle
		return false;
	}

	float invDet = 1 / det;

	glm::vec3 T = r.start - this->v1; // Origin - v1
	float u = dot(T, P) * invDet;
	if (u < 0 || u > 1) return false;

	glm::vec3 Q = cross(T, edge1);
	float v = dot(r.dir, Q) * invDet;
	if (v < 0 || u + v > 1) return false;

    t = dot(edge2, Q) * invDet;
    
    if(t > EPS && t < 1000) {
        //Är det här verkligen rätt?
            return true;
    }

    return false;
}