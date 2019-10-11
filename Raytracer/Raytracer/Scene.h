#ifndef SCENE_HEADER
#define SCENE_HEADER

//class scene. contains instances of class triangle.
//scene objects are closed 

#include "Triangle.h"
#include "Sphere.h"
#include <vector>

class Scene
{
public:

	//Scene(std::vector<Triangle> triangles) : object(triangles) { };

	//std::vector<Triangle> object;

	std::vector<Triangle> tris;
	std::vector<Sphere> spheres;
	Vertex light;

private:
};
#endif