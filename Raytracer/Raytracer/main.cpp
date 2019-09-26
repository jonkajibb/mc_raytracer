//using namespace std;

#include <vector>
#include <fstream>

//#include "SDL.h";
//#include <stdio.h>

#include "Triangle.h"
#include "Scene.h"
#include "Camera.h"

int main() {

	//cool variables declarations
	std::vector<Triangle> triangles;

	Vertex eye(-2, 0, 0, 1);

	Camera cam(eye);

	ColorDbl white(255, 255, 255);
	ColorDbl red(255, 0, 0);
	ColorDbl green (0, 255, 0);
	ColorDbl blue(0, 0, 255);

	//Pixel pixel_col[H][W];

	//FLOOR
	Vertex fv1 = Vertex(0, 6, -5, 1);
	Vertex fv2 = Vertex(10, 6, -5, 1);
	Vertex fv3 = Vertex(13, 0, -5, 1);
	Vertex fv4 = Vertex(10, -6, -5, 1);
	Vertex fv5 = Vertex(0, -6, -5, 1);
	Vertex fv6 = Vertex(-5, 0, -5, 1);

	//ROOF
	Vertex rv1 = Vertex(0, 6, 5, 1);
	Vertex rv2 = Vertex(10, 6, 5, 1);
	Vertex rv3 = Vertex(13, 0, 5, 1);
	Vertex rv4 = Vertex(10, -6, 5, 1);
	Vertex rv5 = Vertex(0, -6, 5, 1);
	Vertex rv6 = Vertex(-5, 0, 5, 1);

	//CENTER
	Vertex fc = Vertex(5, 0, -5, 1);
	Vertex rc = Vertex(5, 0, 5, 1);

	//Triangles for scene
	/*//FLOOR
	Triangle ft1 = Triangle(fc, fv1, fv6, red);
	Triangle ft2 = Triangle(fc, fv1, fv2, red);
	Triangle ft3 = Triangle(fc, fv3, fv2, red);
	Triangle ft4 = Triangle(fc, fv4, fv3, red);
	Triangle ft5 = Triangle(fc, fv5, fv4, red);
	Triangle ft6 = Triangle(fc, fv6, fv5, red);

	//ROOF
	Triangle rt1 = Triangle(fc, rv6, rv1, blue);
	Triangle rt2 = Triangle(fc, rv1, rv2, blue);
	Triangle rt3 = Triangle(fc, rv2, rv3, blue);
	Triangle rt4 = Triangle(fc, rv3, rv4, blue);
	Triangle rt5 = Triangle(fc, rv4, rv5, blue);
	Triangle rt6 = Triangle(fc, rv5, rv6, blue);*/

	//WALLS
	//north west
	Triangle wt1 = Triangle(fv6, fv1, rv6, blue);
	Triangle wt2 = Triangle(fv1, rv1, rv6, green);
	//north
	Triangle wt3 = Triangle(fv1, fv2, rv1, green);
	Triangle wt4 = Triangle(fv2, rv2, rv1, green);
	//north east
	Triangle wt5 = Triangle(fv2, fv3, rv2, green);
	Triangle wt6 = Triangle(fv3, rv3, rv2, green);
	//south east
	Triangle wt7 = Triangle(fv3, fv4, rv3, green);
	Triangle wt8 = Triangle(fv4, rv4, rv3, green);
	//south
	Triangle wt9 = Triangle(fv4, fv5, rv4, green);
	Triangle wt10 = Triangle(fv5, rv5, rv4, green);
	//south west
	Triangle wt11 = Triangle(fv5, fv6, rv5, blue);
	Triangle wt12 = Triangle(fv6, rv6, rv5, green);

	//THE ROOM REPRESENTED AS A VECTOR
	/*triangles.push_back(ft1);
	triangles.push_back(ft2);
	triangles.push_back(ft3);
	triangles.push_back(ft4);
	triangles.push_back(ft5);
	triangles.push_back(ft6);
	triangles.push_back(rt1);
	triangles.push_back(rt2);
	triangles.push_back(rt3);
	triangles.push_back(rt4);
	triangles.push_back(rt5);
	triangles.push_back(rt6);*/
	triangles.push_back(wt1);
	triangles.push_back(wt2);
	triangles.push_back(wt3);
	triangles.push_back(wt4);
	triangles.push_back(wt5);
	triangles.push_back(wt6);
	triangles.push_back(wt7);
	triangles.push_back(wt8);
	triangles.push_back(wt9);
	triangles.push_back(wt10);
	triangles.push_back(wt11);
	triangles.push_back(wt12);

	//Fill scene with triangles
	Scene s = Scene(triangles);

	//Render "scene"
	cam.render(s);

	return 0;
}