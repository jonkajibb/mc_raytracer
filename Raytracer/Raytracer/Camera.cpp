#include "Camera.h"
#include <iostream>
#include <algorithm>

void Camera::render(Scene s)
{
	//side length of pixels: 0.0025
	//center: y+0.00125, z-0.00125
	double length = 0.0025;
	double hLength = 0.00125; //half length
	Direction sphereNormal;

	std::ofstream out("out.ppm");

	out << "P3\n" << H << '\n' << W << '\n' << "255\n";

	Vertex currentP(0, 1 - hLength, 1 - hLength, 1);


	//Build image plane, 800x800 vertices
	for (int h = 0; h < H; h++)
	{
		for (int w = 799; w >= 0; w--)
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
	double t = 0;
	double d = 1000;
	double minDistance = 1000;
	Triangle minTriangle;
	Sphere minSphere;
	Direction sphereNormal;
	Direction lightDir;
	double angle;
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
				//Determine endpoint of ray, used in shading
				//ray.endTri = minTriangle;
			}
		}
	}
	//Check if a sphere was also intersected, to set d
	for (int j = 0; j < s.spheres.size(); j++)
	{
		if (s.spheres[j].sphereIntersection(ray, d, sphereNormal)) {
			minSphere = s.spheres[j];
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

            Direction myNormal = minTriangle.normal;
            Direction myIncoming = ray.dir;
            //myNormal = myNormal*(-1);
            //myIncoming = myIncoming*(-1);
            
            
			//Reflection -> find new direction
			//reflection = ray.dir - myNormal * (2 * (ray.dir.dot(myNormal)));
            
            
            //Direction myNormal = minTriangle.normal;
            //Direction myIncoming = ray.dir*(-1);
            reflection = myIncoming - myNormal*(myNormal.dot(myIncoming))*2;
            
            //Tror det är fel på ray.end här... Den startar liksom på väggen bakom tetraheden iställer för tetraheden.
			Ray rRay = Ray(ray.end, reflection);
            return castRay(rRay, s);
		}
		else if (minTriangle.material == Diffuse) {
			//finalColor = minTriangle.color;
			lightDir = Direction(s.light.pos.X - ray.end.X, s.light.pos.Y - ray.end.Y, s.light.pos.Z - ray.end.Z);

			lightDir.normalize();
            Direction myNormal = minTriangle.normal;

			angle = 1 - cos(myNormal.dot(lightDir));
			//std::cout << minTriangle.normal.X << ", " << minTriangle.normal.Y << ", " << minTriangle.normal.Z << std::endl;
			//std::cout << dotProduct << std::endl;
			//std::cout << minTriangle.normal.getScalar() << std::endl;
			if (angle < 0) {
				finalColor = minTriangle.color * 0;
			}
			else {
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

