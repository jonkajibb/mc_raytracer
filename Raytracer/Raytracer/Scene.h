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
		float t = 1000;
		//float angle;
		float minDistance = 10000;
		float d; //Distance to sphere intersection

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

					sRay.end = Vertex(
						sRay.start.X + sRay.dir.X*minDistance,
						sRay.start.Y + sRay.dir.Y*minDistance,
						sRay.start.Z + sRay.dir.Z*minDistance,
						1);
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
			if (spheres[j].sphereIntersection(sRay, d)) {
				//minSphere = spheres[j];
				//intersected = true;

				sRay.end = Vertex(sRay.start.X + d * sRay.dir.X,
					sRay.start.Y + d * sRay.dir.Y,
					sRay.start.Z + d * sRay.dir.Z,
					1);
				//normal
				sphereNormal = Direction(sRay.end.X - spheres[j].center.X,
					sRay.end.Y - spheres[j].center.Y,
					sRay.end.Z - spheres[j].center.Z);
				sphereNormal = sphereNormal.normalize();
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
