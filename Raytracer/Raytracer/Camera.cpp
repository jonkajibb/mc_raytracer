#include "Camera.h"

void Camera::render()
{
	//side length of pixels: 0.0025
	//center: y+0.00125, z-0.00125
	double length = 0.0025;
	double hLength = 0.00125; //half length

	Vertex currentP(0, -1+hLength, 1-hLength, 0);

	//Build image plane, 800x800 vertices
	for (int h = 0; h < H; h++)
	{
		for (int w = 0; w < W; w++)
		{
			
			image[w][h] = currentP;

			Direction dir(currentP.X - eye1.X, currentP.Y - eye1.Y, currentP.Z - eye1.Z);

			Ray ray(eye1, dir);

			currentP.Y = currentP.Y + length;
		}

		currentP.Z = currentP.Z - length;
	}


}