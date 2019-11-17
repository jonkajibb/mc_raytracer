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
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <math.h>

const int H = 800;
const int W = 800;

class Camera
{
public:

	Camera() {
		pixelPlane.resize(800, std::vector<Pixel>(800, ColorDbl()));
	};

	void render(Scene s);

	ColorDbl castRay(Ray ray, Scene s, int &depth);

	void createCoordinateSystem(Direction &N, Direction &Nt, Direction &Nb);

	Direction hemisphere(const float &r1, const float &r2);


	//Positions of eyes
	Vertex eye1 = Vertex(-1, 0, 0, 1);

	std::vector<std::vector<Pixel>> pixelPlane;

private:

};

#endif
