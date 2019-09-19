//triangle class. Defined by three objects from class Vertex.
//Has color represented by instance of ColorDbl.
//Has normal stored as an instance of Direction.

#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"	
#include "Pixel.h"
#include "Ray.h"

const int H = 800;
const int W = 800;

class Camera
{
public:

	//Positions of eyes
	Vertex eye1;
	Vertex eye2;
	int switchEye = 0;

	//Image in the room
	Vertex image[H][W];
	
	//Constructor
	Camera(Vertex e1, Vertex e2) : eye1(e1), eye2(e2) { };


	void render();

	void createImage();

private:
};