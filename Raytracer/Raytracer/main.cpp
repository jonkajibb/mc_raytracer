//using namespace std;

#include <vector>
#include <fstream>

//#include "SDL.h";
//#include <stdio.h>

#include "Triangle.h"
#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"

int main() {

	//cool variables declarations
	std::vector<Triangle> triangles;
	std::vector<Triangle> tetrahedron;

	Vertex eye(-1, 0, 0, 1);

	Camera cam;

	ColorDbl white(255, 255, 255);
	ColorDbl gray(100, 100, 100);
	ColorDbl offwhite(230, 230, 230);
	ColorDbl lightblue(210, 210, 255);
	ColorDbl lightgreen(30, 255, 30);
	ColorDbl red(255, 0, 0);
	ColorDbl green(0, 255, 0);
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
	Triangle ft1 = Triangle(fc, fv1, fv6, offwhite);
	Triangle ft2 = Triangle(fc, fv2, fv1, offwhite);
	Triangle ft3 = Triangle(fc, fv3, fv2, offwhite);
	Triangle ft4 = Triangle(fc, fv4, fv3, offwhite);
	Triangle ft5 = Triangle(fc, fv5, fv4, offwhite);
	Triangle ft6 = Triangle(fc, fv6, fv5, offwhite);

	//ROOF
	Triangle rt1 = Triangle(rc, rv6, rv1, lightblue);
	Triangle rt2 = Triangle(rc, rv1, rv2, lightblue);
	Triangle rt3 = Triangle(rc, rv2, rv3, lightblue);
	Triangle rt4 = Triangle(rc, rv3, rv4, lightblue);
	Triangle rt5 = Triangle(rc, rv4, rv5, lightblue);
	Triangle rt6 = Triangle(rc, rv5, rv6, lightblue);

	//WALLS
	//north west
	Triangle wt1 = Triangle(fv6, fv1, rv6, orange);
	Triangle wt2 = Triangle(fv1, rv1, rv6, orange);
	//north
	Triangle wt3 = Triangle(fv1, fv2, rv1, orange);
	Triangle wt4 = Triangle(fv2, rv2, rv1, orange);
	//std::cout << wt4.normal.X << ", " << wt4.normal.Y << ", " << wt4.normal.Z << std::endl;
	//north east
	Triangle wt5 = Triangle(rv2, fv2, fv3, lightblue);// fv2, fv3, rv2, lightgreen);
	//std::cout << wt5.normal.X << ", " << wt5.normal.Y << ", " << wt5.normal.Z << std::endl;
	Triangle wt6 = Triangle(fv3, rv3, rv2, lightgreen);
	//south east
	Triangle wt7 = Triangle(fv3, fv4, rv3, lightgreen);
	Triangle wt8 = Triangle(fv4, rv4, rv3, lightgreen);
	//south
	Triangle wt9 = Triangle(fv4, fv5, rv4, orange);
	Triangle wt10 = Triangle(fv5, rv5, rv4, orange);
	//south west
	Triangle wt11 = Triangle(fv5, fv6, rv5, orange);
	Triangle wt12 = Triangle(fv6, rv6, rv5, orange);

	//CREATE TETRAHEDRON IN ORIGO (9, 1, 0)
	//std::vector<Triangle> tetra1;
	//Triangle asd; //skittriangel
	//tetra1 = asd.createTetrahedron(Vertex(8, -1, 0, 1), blue);

	Vertex origo = Vertex(8, -1, 0, 1);
	Vertex a, b, c, d;
	ColorDbl col(255, 200, 200);

	std::vector<Triangle> tetra;

	//closest
	a.X = origo.X - 1.5;
	a.Y = origo.Y;
	a.Z = origo.Z - 1.5;

	//back left
	b.X = origo.X + 1;
	b.Y = origo.Y + 1.5;
	b.Z = origo.Z - 1.5;

	//back right
	c.X = origo.X + 1.5;
	c.Y = origo.Y - 1.5;
	c.Z = origo.Z - 1.5;

	//top
	d.X = origo.X;
	d.Y = origo.Y;
	d.Z = origo.Z + 1;

	Triangle t1(a, d, b, blue);
	std::cout << t1.normal.X << ", " << t1.normal.Y << ", " << t1.normal.Z << std::endl;
	Triangle t2(b, d, c, blue);
	std::cout << t2.normal.X << ", " << t2.normal.Y << ", " << t2.normal.Z << std::endl;
	Triangle t3(a, c, d, blue);
	std::cout << t3.normal.X << ", " << t3.normal.Y << ", " << t3.normal.Z << std::endl;
	Triangle t4(a, b, c, blue);
	std::cout << t4.normal.X << ", " << t4.normal.Y << ", " << t4.normal.Z << std::endl;

	triangles.push_back(t1);
	triangles.push_back(t2);
	triangles.push_back(t3);
	triangles.push_back(t4);
	/*
	Vertex a(8, 1, 0, 1);
	Vertex b(8.5, -1, 0, 1);
	Vertex c(9, 0, 2, 1);
	Triangle bajs = Triangle(a, b, c, green);*/

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
	//triangles.push_back(tetra1[0]);
	//triangles.push_back(tetra1[1]);
	//triangles.push_back(tetra1[2]);
	//triangles.push_back(tetra1[3]);

	//SKAPA SFÄÄÄÄÄÄÄR
	Vertex asdf(10, 3, -0.5, 1);
	std::vector<Sphere> spheres;
	spheres.push_back(Sphere(asdf, 1.0, white));

	//Fill scene with triangles, spheres and lights
	Scene s;
	s.tris = triangles;
	s.spheres = spheres;
	Light light(Vertex(5.0, 0.0, 4.5, 1), 0.9, white);
	s.light = light;

	//Render "scene"
	cam.render(s);
	return 0;
}
