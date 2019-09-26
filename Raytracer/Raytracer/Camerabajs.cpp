#include "Camera.h"

void Camera::render(Scene& s)
{
	//side length of pixels: 0.0025
	//center: y+0.00125, z-0.00125
	double length = 0.0025;
	double hLength = 0.00125; //half length

	Vertex currentP(0, -1 + hLength, 1 - hLength, 0);

	//Build image plane, 800x800 vertices
	for (int h = 0; h < H; h++)
	{
		for (int w = 0; w < W; w++)
		{

			image[w][h] = currentP;

			Direction dir(currentP.X - eye1.X, currentP.Y - eye1.Y, currentP.Z - eye1.Z);

			Ray ray(eye1, dir);

			//Check if this ray hits a triangle
			//if yes, then call createImage()
			for (unsigned i = 0; i < s.object.size(); i++)
			{
				if (s.object[i].rayIntersection(ray))
				{
					createImage(s.object[i].color, w, h);
				}
			}


			currentP.Y = currentP.Y + length;
		}

		currentP.Z = currentP.Z - length;
	}
}

void Camera::createImage(ColorDbl c, int wCoor, int hCoor)
{
	//Window size
	//const int H = 800;
	//const int W = 800;

	//Output of a .ppm file (what is ppm?)
	printf("loool \n");
	//std::ofstream out("coolbild.ppm");

	//out << "P3\n" << W << '\n' << H << '\n' << "255\n";
}