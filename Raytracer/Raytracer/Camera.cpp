#include "Camera.h"
#include <iostream>
#include "BMP.h"
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

	/*for (int i = 0; i < W; i++)
	{
		image[i] = new Vertex[W];
		pixels[i] = new Pixel[W];
	}*/

	Vertex currentP(0, 1 - hLength, 1 - hLength, 1);
	//Vertex startingPos = currentP;
	//std::cout << image[0][0].X << std::endl;

	//Build image plane, 800x800 vertices
	for (int h = 0; h < H; h++)
	{
		for (int w = 799; w >= 0; w--)
		{

			//pixelPlane[h][w] = currentP;
			//std::cout << image[w][h].X << std::endl;

			Direction dir(currentP.X - eye1.X, currentP.Y - eye1.Y, currentP.Z - eye1.Z);

			Ray ray = Ray(eye1, dir);

			//Check if this ray hits a triangle
			//if yes, then call createImage()
			double t;
			double d = 1000;
			double minDistance = 1000;
			Triangle minTriangle;
			Sphere minSphere;
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

			//Check if sphere is in front of the triangle
			if (d < t) {
				pixelPlane[w][h] = minSphere.color;
			}
			else {
				Direction lightDir = Direction(s.light.pos.X - ray.end.X, s.light.pos.Y - ray.end.Y, s.light.pos.Z - ray.end.Z);

				lightDir.normalize();
				/*std::cout << "Light Direction:\t"
					<< lightDir.X 
					<< ", " << lightDir.Y 
					<< ", " << lightDir.Z 
					<< std::endl;
				std::cout << "Importance ray endpoint\t"
					<< ray.end.X
					<< ", " << ray.end.Y
					<< ", " << ray.end.Z
					<< std::endl;*/

				double dotProduct = lightDir.dot(minTriangle.normal);
				//std::cout << minTriangle.normal.X << ", " << minTriangle.normal.Y << ", " << minTriangle.normal.Z << std::endl;
				//std::cout << dotProduct << std::endl;
				//std::cout << minTriangle.normal.getScalar() << std::endl;
				if (dotProduct < 0) {
					pixelPlane[w][h] = minTriangle.color * 0;
				}
				else {
					pixelPlane[w][h] = minTriangle.color * dotProduct;
				}
			}
			//std::cout << "(" << currentP.Y << ", " << currentP.Z << ")\t"
			
			out << pixelPlane[w][h].color.R 
				<< ", " << pixelPlane[w][h].color.G 
				<< ", " << pixelPlane[w][h].color.B 
				<< std::endl;

			currentP.Y = currentP.Y - length;
		}

		currentP.Z = currentP.Z - length; //step down
		currentP.Y = 1 - hLength; //start from first position again
	}
}

void Camera::createImage(ColorDbl c, int wCoor, int hCoor)
{
	//Window size
	//const int H = 800;
	//const int W = 800;

	//Output of a .ppm file (what is ppm?)
	
	//std::ofstream out("out.ppm");

	//out << "P3\n" << W << '\n' << H << '\n' << "255\n";
	
	//out << 

	/*
	//printf("aboo");
	BMP bmp2(H, W, false);

	int channels = bmp2.bmp_info_header.bit_count / 8;

	//Modify pixels

	bmp2.data[channels * (hCoor * bmp2.bmp_info_header.width + wCoor) + 0] = 0;   // B
	bmp2.data[channels * (hCoor * bmp2.bmp_info_header.width + wCoor) + 1] = 0;   // G
	bmp2.data[channels * (hCoor * bmp2.bmp_info_header.width + wCoor) + 2] = 255; // R

	bmp2.write("coolbild.bmp");
	*/
}