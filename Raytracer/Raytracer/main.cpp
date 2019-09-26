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
	ColorDbl orange(255, 191, 0);

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
	//FLOOR
	Triangle ft1 = Triangle(fc, fv1, fv6, red);
	Triangle ft2 = Triangle(fc, fv2, fv1, red);
	Triangle ft3 = Triangle(fc, fv3, fv2, red);
	Triangle ft4 = Triangle(fc, fv4, fv3, red);
	Triangle ft5 = Triangle(fc, fv5, fv4, red);
	Triangle ft6 = Triangle(fc, fv6, fv5, red);

	//ROOF
	Triangle rt1 = Triangle(rc, rv1, rv6, blue);
	Triangle rt2 = Triangle(rc, rv1, rv2, blue);
	Triangle rt3 = Triangle(rc, rv2, rv3, blue);
	Triangle rt4 = Triangle(rc, rv3, rv4, blue);
	Triangle rt5 = Triangle(rc, rv4, rv5, blue);
	Triangle rt6 = Triangle(rc, rv6, rv5, blue);

	//WALLS
	//north west
	Triangle wt1 = Triangle(fv6, fv1, rv6, orange);
	Triangle wt2 = Triangle(fv1, rv1, rv6, orange);
	//north
	Triangle wt3 = Triangle(fv1, fv2, rv1, orange);
	Triangle wt4 = Triangle(fv2, rv2, rv1, orange);
	//north east
	Triangle wt5 = Triangle(fv2, fv3, rv2, orange);
	Triangle wt6 = Triangle(fv3, rv3, rv2, orange);
	//south east
	Triangle wt7 = Triangle(fv3, fv4, rv3, orange);
	Triangle wt8 = Triangle(fv4, rv4, rv3, orange);
	//south
	Triangle wt9 = Triangle(fv4, fv5, rv4, orange);
	Triangle wt10 = Triangle(fv5, rv5, rv4, orange);
	//south west
	Triangle wt11 = Triangle(fv5, fv6, rv5, orange);
	Triangle wt12 = Triangle(fv6, rv6, rv5, orange);

	//Tetrahedron
	Vertex tv1(9, 2, 0, 1);
	Vertex tv2(10, 2, 0, 1);
	Vertex tv3(10, 0, 0, 1);
	Vertex tv4(9.5, 1.5, 4, 1);

	Triangle tt1 = Triangle(tv1, tv2, tv3, white);
	Triangle tt2 = Triangle(tv2, tv1, tv4, white);
	Triangle tt3 = Triangle(tv3, tv2, tv4, white);
	Triangle tt4 = Triangle(tv1, tv3, tv4, white);

	//THE ROOM REPRESENTED AS A VECTOR
	triangles.push_back(ft1);
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
	triangles.push_back(rt6);
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
	triangles.push_back(tt1);
	triangles.push_back(tt2);
	triangles.push_back(tt3);
	triangles.push_back(tt4);

	//Fill scene with triangles
	Scene s = Scene(triangles);

	//Render "scene"
	cam.render(s);

	return 0;
}