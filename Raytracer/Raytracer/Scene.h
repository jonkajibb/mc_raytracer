#ifndef SCENE_HEADER
#define SCENE_HEADER

//class scene. contains instances of class triangle.
//scene objects are closed 

#include "Triangle.h"
#include "Sphere.h"
#include "Light.h"
#include <vector>


class Scene
{
public:

	//Scene(std::vector<Triangle> triangles) : tris(triangles) { };
	//Scene(std::vector<Sphere> sph) : spheres(sph) { };

	/*
	ColorDbl shading(Ray &importance, Light l, Triangle tHit) {
		bool intersected = false;
		double t = 1000;
		double angle;
		double minDistance = 10000;

		Triangle minTriangle;
		ColorDbl col;
		Direction d(l.pos.X - importance.end.X, l.pos.Y - importance.end.Y, l.pos.Z - importance.end.Z);

		ColorDbl light_i = l.color * l.intensity; //Light color*intenisty

		Ray sRay(importance.end, d);
		d = d.normalize();

		//Angle between importance ray endpoint normal and sRay's direction
		angle = std::max(0.0, d.dot(tHit.normal));
		//std::cout << angle << std::endl;

		//Check if shadowray intersects a surface -> shadow
		//has to check if the intersected surface is between
		//the light source and the shadowray origin point
		for (int i = 0; i < this->tris.size(); i++)
		{
			if (this->tris[i].rayIntersection(sRay, t))
			{
				if (t < minDistance) {
					minDistance = t;
					minTriangle = this->tris[i];
					//Determine endpoint of ray, used in shading
					//ray.endTri = minTriangle;
				}
			}
		}

		Direction newD(l.pos.X - importance.end.X, l.pos.Y - importance.end.Y, l.pos.Z - importance.end.Z);
		Direction isec(sRay.end.X - importance.end.X, sRay.end.Y - importance.end.Y, sRay.end.Z - importance.end.Z);
		if (isec.getScalar() < newD.getScalar()) {
			intersected = true;
		}

		if (angle < 0) {
			col = tHit.color;
		}
		else if (!intersected) {
			col = tHit.color * angle; //* light_i;
		}
		else if (intersected) {
			col = tHit.color * 0.4;
		}

		//Check if sRay intersects something
		return col;
	};*/

	std::vector<Triangle> tris;
	std::vector<Sphere> spheres;
	Light light;

private:
};
#endif