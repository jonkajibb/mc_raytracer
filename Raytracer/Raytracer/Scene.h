#ifndef SCENE_HEADER
#define SCENE_HEADER

//class scene. contains instances of class triangle.
//scene objects are closed 

#include "Triangle.h"
#include "Sphere.h"
#include "Light.h"
#include "Ray.h"
#include <vector>


class Scene
{
public:

	//Scene(std::vector<Triangle> triangles) : tris(triangles) { };
	//Scene(std::vector<Sphere> sph) : spheres(sph) { };

	bool shading(Ray &importance) {
		//bool intersected = false;
		double t = 1000;
		double angle;
		double minDistance = 10000;
		double d; //Distance to sphere intersection

		Sphere minSphere;
		Direction sphereNormal;
		Triangle minTriangle;
		Direction lDir(light.pos.X - importance.end.X, light.pos.Y - importance.end.Y, light.pos.Z - importance.end.Z);
		Direction isec;


		//ColorDbl light_i = l.color * l.intensity; //Light color*intenisty

		//Creating the shadowray
		Ray sRay(importance.end, lDir);

		//Check if shadowray intersects a surface -> shadow
		//has to check if the intersected surface is between
		//the light source and the shadowray origin point
		for (int i = 0; i < tris.size(); i++)
		{
			if (tris[i].rayIntersection(sRay, t))
			{
				if (t < minDistance) {
					minDistance = t;
					//minTriangle = tris[i];
					//intersected = true;
				}
				isec = Direction(sRay.end.X - sRay.start.X, sRay.end.Y - sRay.start.Y, sRay.end.Z - sRay.start.Z);

				if (isec.getScalar() < lDir.getScalar()) {
					return true;
				}

				
			}
		}

		//Check if a sphere was also intersected, to set d
		for (int j = 0; j < spheres.size(); j++)
		{
			if (spheres[j].sphereIntersection(sRay, d, sphereNormal)) {
				//minSphere = spheres[j];
				//intersected = true;
			}

			isec = Direction(sRay.end.X - sRay.start.X, sRay.end.Y - sRay.start.Y, sRay.end.Z - sRay.start.Z);

			if (isec.getScalar() < lDir.getScalar()) {
				return true;
			}
		}

		return false;
	};

	std::vector<Triangle> tris;
	std::vector<Sphere> spheres;
	Light light;

private:
};
#endif