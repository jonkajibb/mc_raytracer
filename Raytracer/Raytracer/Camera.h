#ifndef CAMERA_HEADER
#define CAMERA_HEADER

//triangle class. Defined by three objects from class Vertex.
//Has color represented by instance of ColorDbl.
//Has normal stored as an instance of Direction.

#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"	
#include "Pixel.h"
#include "Ray.h"
#include "Scene.h"
#include <fstream> 

const int H = 800;
const int W = 800;

class Camera
{
public:

	Camera() {
		pixelPlane.resize(800, std::vector<Pixel>(800, ColorDbl()));
	};

	void render(Scene s);

	void createImage(ColorDbl c, int w, int h);


	//Positions of eyes
	Vertex eye1 = Vertex(-1, 0, 0, 1);

	//Vertex eye2;
	//int switchEye = 0;

	//Image in the room
	//Vertex **image = new Vertex*[H];

	//Pixel **pixels = new Pixel*[H];

	std::vector<std::vector<Pixel>> pixelPlane;

private:

};

#endif