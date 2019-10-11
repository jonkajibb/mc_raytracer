#ifndef SCENE_HEADER
#define SCENE_HEADER

//class scene. contains instances of class triangle.
//scene objects are closed 

#include "Triangle.h"
#include <vector>
#include "Sphere.h"

class Scene
{
public:

	//Scene(std::vector<Triangle> triangles) : tris(triangles) { };
	//Scene(std::vector<Sphere> sph) : spheres(sph) { };

	std::vector<Triangle> tris;
	std::vector<Sphere> spheres;
	Vertex light;

private:
};
#endif