#ifndef SCENE_HEADER
#define SCENE_HEADER

//class scene. contains instances of class triangle.
//scene objects are closed 

#include "Triangle.h"
#include "Sphere.h"
#include "AreaLight.h" // kanske ger errors xdd
#include "PointLight.h" // kanske ger errors xdd
#include "Ray.h"
#include <vector>


class Scene
{
public:

	//Scene(std::vector<Triangle> triangles) : tris(triangles) { };
	//Scene(std::vector<Sphere> sph) : spheres(sph) { };

	float random_float(float min, float max) {

		return ((float)rand() / RAND_MAX) * (max - min) + min;

	};

	bool shading(Ray &importance) {
		//bool intersected = false;
		float t = 1000;
		//float angle;
		float minDistance = 10000;
		float d; //Distance to sphere intersection

		Sphere minSphere;
		glm::vec3 sphereNormal;
		Triangle minTriangle;
		//glm::vec3 lDir = light.pos - importance.end;
		glm::vec3 isec;

		//If area light, sample random point as SHADOW ray end point
		float randX = random_float(6, 7);
		float randY = random_float(-1, 1);
		glm::vec4 lightSample = glm::vec4(randX, randY, areaLights[0].area.v1.z, 1.0);

		glm::vec3 lDir = lightSample - importance.end;

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

					sRay.end = sRay.start + glm::vec4(sRay.dir * minDistance, 1.0f);
				}
				isec = sRay.end - sRay.start;

				if (glm::length(isec) < glm::length(lDir)) {
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
				sRay.end = sRay.start + glm::vec4(sRay.dir * d, 1.0f);

				//normal

				sphereNormal = sRay.end - spheres[j].center;
				sphereNormal = glm::normalize(sphereNormal);
			}

			isec = sRay.end - sRay.start;

			if (glm::length(isec) < glm::length(lDir)) return true;
		}
		return false;
	};

	std::vector<Triangle> tris;
	std::vector<Sphere> spheres;
	std::vector<AreaLight> areaLights;
	std::vector<PointLight> pointLights;

private:
};
#endif
