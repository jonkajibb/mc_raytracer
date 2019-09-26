#ifndef SCENE_HEADER
#define SCENE_HEADER

//class scene. contains instances of class triangle.
//scene objects are closed 

#include "Triangle.h"
#include <vector>

class Scene
{
public:

	Scene(std::vector<Triangle> triangles) : object(triangles) { };

	std::vector<Triangle> object;

private:
};
#endif