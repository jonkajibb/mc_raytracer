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

	std::ofstream out("out.ppm");

	out << "P3\n" << W << '\n' << H << '\n' << "255\n";

	for (int i = 0; i < W; i++)
	{
		image[i] = new Vertex[W];
		pixels[i] = new Pixel[W];
	}

	Vertex currentP(0, -1 + hLength, 1 - hLength, 1);

	std::cout << image[0][0].X << std::endl;

	//Build image plane, 800x800 vertices
	for (int h = 0; h < H; h++)
	{
		for (int w = 0; w < W; w++)
		{

			image[w][h] = currentP;
			//std::cout << image[w][h].X << std::endl;

			Direction dir(currentP.X - eye1.X, currentP.Y - eye1.Y, currentP.Z - eye1.Z);

			Ray ray(eye1, dir);

			//Check if this ray hits a triangle
			//if yes, then call createImage()
			for (unsigned i = 0; i < s.object.size(); i++)
			{
				if (s.object[i].rayIntersection(ray))
				{
					pixels[w][h] = s.object[i].color;

					//createImage(s.object[i].color, w, h);
					break;
				}
			}
			//std::cout << "(" << currentP.Y << ", " << currentP.Z << ")\t"
			
			out << pixels[w][h].color.R << ", " << pixels[w][h].color.G << ", " << pixels[w][h].color.B << std::endl;

			currentP.Y = currentP.Y + 0.0025;
		}

		currentP.Z = currentP.Z - length; //step down
		currentP.Y = -1 + hLength; //start from first position again
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