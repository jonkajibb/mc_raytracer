#include "Camera.h"
#include <iostream>
#include <algorithm>

const float EPS = 1e-4;

void Camera::render(Scene s)
{
	//side length of pixels: 0.0025
	//center: y+0.00125, z-0.00125
	float length = 0.0025;
	float hLength = 0.00125; //half length
	Direction sphereNormal;

	std::ofstream out("out.ppm");

	out << "P3\n" << H << '\n' << W << '\n' << "255\n";

	Vertex currentP(0, 1 - hLength, 1 - hLength, 1);


	//Build image plane, 800x800 vertices
	for (int h = 0; h < H; h++)
	{
		for (int w = 0; w < W; w++)
		{

			//pixelPlane[h][w] = currentP;
			//std::cout << image[w][h].X << std::endl;

			Direction dir(currentP.X - eye1.X, currentP.Y - eye1.Y, currentP.Z - eye1.Z);

			Ray ray = Ray(eye1, dir);
			ColorDbl finalCol;
			//Check if this ray hits a triangle
			//if yes, then call createImage()
			
			finalCol = castRay(ray, s);
			
			pixelPlane[w][h] = finalCol;

			out << pixelPlane[w][h].color.R
				<< ", " << pixelPlane[w][h].color.G
				<< ", " << pixelPlane[w][h].color.B
				<< std::endl;

			currentP.Y = currentP.Y - length;

		}
		currentP.Z = currentP.Z - length; //step down
		currentP.Y = 1 - hLength; //start from first position again

		if (h == 200) std::cout << "25% rendered..." << std::endl;
		if (h == 400) std::cout << "50% rendered..." << std::endl;
		if (h == 600) std::cout << "75% rendered..." << std::endl;
		if (h == 799) std::cout << "100% rendered!"  << std::endl;
	}
}

ColorDbl Camera::castRay(Ray ray, Scene s) {
	float t = 0;
	float d = 1000;
	float minDistance = 10000;
	Triangle minTriangle;
	Sphere minSphere;
	Direction sphereNormal;
	Direction lightDir;
	float angle;
	Direction reflection;
	ColorDbl finalColor;
	//Ray rRay; //reflected ray

	//Ray ray = this;

	for (unsigned i = 0; i < s.tris.size(); i++)
	{
		if (s.tris[i].rayIntersection(ray, t))
		{
			//A triangle has been intersected, save t (distance between camera and triangle)
			if (t < minDistance) {
				minDistance = t;
				minTriangle = s.tris[i];
                //std::cout << "Minimum distance: " << minDistance << std::endl;
				//ray.endTri = minTriangle;

				//Determine endpoint of ray
				//Before the rays endpoint was changed each time in the intersection func.
				//even though that triangle could be behind something.
				ray.end = Vertex(
					ray.start.X + ray.dir.X*minDistance,
					ray.start.Y + ray.dir.Y*minDistance,
					ray.start.Z + ray.dir.Z*minDistance,
					1);
			}
		}
	}
	//Check if a sphere was also intersected, to set d
	for (int j = 0; j < s.spheres.size(); j++)
	{
		if (s.spheres[j].sphereIntersection(ray, d)) {
			minSphere = s.spheres[j];
			//std::cout << d << std::endl;
			ray.end = Vertex(ray.start.X + d * ray.dir.X,
				ray.start.Y + d * ray.dir.Y,
				ray.start.Z + d * ray.dir.Z,
				1);
			//normal
			sphereNormal = Direction(ray.end.X - s.spheres[j].center.X,
				ray.end.Y - s.spheres[j].center.Y,
				ray.end.Z - s.spheres[j].center.Z);
			sphereNormal = sphereNormal.normalize();

			
			//MOve ray hit point outside sphere, else the ray is stuck inside
			ray.end.X += sphereNormal.X*EPS;
			ray.end.Y += sphereNormal.Y*EPS;
			ray.end.Z += sphereNormal.Z*EPS;

			//break;
		}
	}

	if (d < t) //If sphere
	{
		if (minSphere.material == Mirror) {
			//Reflection -> find new direction

			reflection = ray.dir - sphereNormal*(2 * (ray.dir.dot(sphereNormal)));
			Ray rRay = Ray(ray.end, reflection);
            return castRay(rRay, s);
		}
		else if (minSphere.material == Diffuse) {
			finalColor = minSphere.color;
			/*lightDir = Direction(s.light.pos.X - ray.end.X, s.light.pos.Y - ray.end.Y, s.light.pos.Z - ray.end.Z);
			lightDir.normalize();
			sphereNormal.normalize();
			//std::cout << sphereNormal.X << ", " << sphereNormal.Y << ", " << sphereNormal.Z << std::endl;
			angle = 1 - cos(lightDir.dot(sphereNormal));

			return minSphere.color * angle;*/
		}
	}
	else //If triangle
	{
		if (minTriangle.material == Mirror) {
			//Skapa lokalt koordinatsystem

            Direction myNormal = minTriangle.normal;
            Direction myIncoming = ray.dir;
            myIncoming.normalize();
            
            reflection = myIncoming - myNormal*(myNormal.dot(myIncoming))*2;

			//Tror det är fel på ray.end här... Den startar liksom på väggen bakom tetraheden iställer för tetraheden.
			Ray rRay = Ray(ray.end, reflection);
			//rRay.start.X = 10;
            //return ColorDbl(0, 0, 0);
            finalColor = castRay(rRay, s);
		}
		else if (minTriangle.material == Diffuse) {
			//finalColor = minTriangle.color;
			lightDir = Direction(s.light.pos.X - ray.end.X, s.light.pos.Y - ray.end.Y, s.light.pos.Z - ray.end.Z);

			lightDir.normalize();
            Direction myNormal = minTriangle.normal;

			angle = 1 - cos(myNormal.dot(lightDir));

			if (angle < 0) {
				finalColor = minTriangle.color * 0;
                //finalColor = ColorDbl(255,255,255);
			}
			else {
                //finalColor = ColorDbl(255,255,255);
				finalColor = minTriangle.color * angle;
			}
		}
	}

	/*
	//skit h�r nere
	if (s.shading(ray)) {
		return minTriangle.color * 0.2;
	}*/

	return finalColor;

};

