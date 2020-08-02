//using namespace std;

#include <vector>
#include <fstream>

//#include "SDL.h";
//#include <stdio.h>

#include "Triangle.h"
#include "Camera.h"
#include "Sphere.h"
#include <glm.hpp>

int main() {

	//cool variables declarations
	std::vector<Triangle> triangles;
	std::vector<Triangle> tetrahedron;

	//glm::vec4 eye = glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f);

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
	glm::vec4 fv1 = glm::vec4(0, 6, -5, 1);
	glm::vec4 fv2 = glm::vec4(10, 6, -5, 1);
	glm::vec4 fv3 = glm::vec4(13, 0, -5, 1);
	glm::vec4 fv4 = glm::vec4(10, -6, -5, 1);
	glm::vec4 fv5 = glm::vec4(0, -6, -5, 1);
	glm::vec4 fv6 = glm::vec4(-5, 0, -5, 1);

	//ROOF
	glm::vec4 rv1 = glm::vec4(0, 6, 5, 1);
	glm::vec4 rv2 = glm::vec4(10, 6, 5, 1);
	glm::vec4 rv3 = glm::vec4(13, 0, 5, 1);
	glm::vec4 rv4 = glm::vec4(10, -6, 5, 1);
	glm::vec4 rv5 = glm::vec4(0, -6, 5, 1);
	glm::vec4 rv6 = glm::vec4(-5, 0, 5, 1);

	//CENTER
	glm::vec4 fc = glm::vec4(5, 0, -5, 1);
	glm::vec4 rc = glm::vec4(5, 0, 5, 1);

	//Triangles for scene
	//FLOOR
	Triangle ft1 = Triangle(fc, fv1, fv6, Diffuse, offwhite);
	Triangle ft2 = Triangle(fc, fv2, fv1, Diffuse, offwhite);
	Triangle ft3 = Triangle(fc, fv3, fv2, Diffuse, offwhite);
	Triangle ft4 = Triangle(fc, fv4, fv3, Diffuse, offwhite);
	Triangle ft5 = Triangle(fc, fv5, fv4, Diffuse, offwhite);
	Triangle ft6 = Triangle(fc, fv6, fv5, Diffuse, offwhite);

	//ROOF
	Triangle rt1 = Triangle(rc, rv6, rv1, Diffuse, lightblue);
	Triangle rt2 = Triangle(rc, rv1, rv2, Diffuse, lightblue);
	Triangle rt3 = Triangle(rc, rv2, rv3, Diffuse, lightblue);
	Triangle rt4 = Triangle(rc, rv3, rv4, Diffuse, lightblue);
	Triangle rt5 = Triangle(rc, rv4, rv5, Diffuse, lightblue);
	Triangle rt6 = Triangle(rc, rv5, rv6, Diffuse, lightblue);

	//WALLS
	//north west, normal wrong way (lazy fixed)
	Triangle wt1 = Triangle(fv6, fv1, rv6, Diffuse, blue);
    wt1.normal = -wt1.normal;
	Triangle wt2 = Triangle(fv1, rv1, rv6, Diffuse, blue);
    wt2.normal = -wt2.normal;
	//north
	Triangle wt3 = Triangle(fv1, fv2, rv1, Diffuse, orange);
	Triangle wt4 = Triangle(fv2, rv2, rv1, Diffuse, orange);
	//std::cout << "WT4: " << wt4.normal.X << ", " << wt4.normal.Y << ", " << wt4.normal.Z << std::endl;
	//north east
    Triangle wt5 = Triangle(rv2, fv2, fv3, Diffuse, lightblue);// fv2, fv3, rv2, lightgreen);
	//std::cout << wt5.normal.x << ", " << wt5.normal.y << ", " << wt5.normal.z << std::endl;
	wt5.normal = wt5.normal * -1.0f;
	Triangle wt6 = Triangle(fv3, rv3, rv2, Diffuse, lightblue);
	wt6.normal = wt6.normal * -1.0f;

	//south east
	Triangle wt7 = Triangle(fv3, fv4, rv3, Diffuse, lightgreen);
	Triangle wt8 = Triangle(fv4, rv4, rv3, Diffuse, lightgreen);
	//south
	Triangle wt9 = Triangle(fv4, fv5, rv4, Diffuse, red);
    //std::cout << "WT9: " << wt9.normal.X << ", " << wt9.normal.Y << ", " << wt9.normal.Z << std::endl;
	Triangle wt10 = Triangle(fv5, rv5, rv4, Diffuse, red);
	//south west
	Triangle wt11 = Triangle(fv5, fv6, rv5, Diffuse, blue);
	Triangle wt12 = Triangle(fv6, rv6, rv5, Diffuse, blue);

	//CREATE TETRAHEDRON IN ORIGO (9, 1, 0)
	//std::vector<Triangle> tetra1;
	//Triangle asd; //skittriangel
	//tetra1 = asd.createTetrahedron(glm::vec4(8, -1, 0, 1), blue);

	glm::vec4 origo = glm::vec4(7.5, -2, 0, 1);
	glm::vec4 a, b, c, d;
	ColorDbl col(255, 200, 200);

	std::vector<Triangle> tetra;

	//closest
	a.x = origo.x - 1.5f;
	a.y = origo.y;
	a.z = origo.z - 1.5f;

	//back left
	b.x = origo.x + 1.0f;
	b.y = origo.y + 1.5f;
	b.z = origo.z - 1.5f;

	//back right
	c.x = origo.x + 1.5f;
	c.y = origo.y - 1.5f;
	c.z = origo.z - 1.5f;

	//top
	d.x = origo.x;
	d.y = origo.y;
	d.z = origo.z + 1;

	Triangle t1(a, d, b, Mirror);
	//std::cout << t1.normal.x << ", " << t1.normal.y << ", " << t1.normal.z << std::endl;
	Triangle t2(b, d, c, Mirror);
	//std::cout << t2.normal.x << ", " << t2.normal.y << ", " << t2.normal.z << std::endl;
	Triangle t3(a, c, d, Mirror);
	//std::cout << t3.normal.x << ", " << t3.normal.y << ", " << t3.normal.z << std::endl;
	Triangle t4(a, b, c, Mirror);
	//std::cout << t4.normal.x << ", " << t4.normal.y << ", " << t4.normal.z << std::endl;

	//t2.normal = t2.normal * -1.0f;

	triangles.push_back(t1);
	triangles.push_back(t2);
	triangles.push_back(t3);
	triangles.push_back(t4);
	/*
	glm::vec4 a(8, 1, 0, 1);
	glm::vec4 b(8.5, -1, 0, 1);
	glm::vec4 c(9, 0, 2, 1);
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

	//SKAPA SFƒƒƒƒƒƒƒR
    
    //6, 3, -0.5, 1
	glm::vec4 asdf = glm::vec4(6, 1, 1, 1);
	std::vector<Sphere> spheres;
    //Artefakter i väggar beror inte på sfären!
	spheres.push_back(Sphere(asdf, 1.0, Diffuse, red));
    
	//Fill scene with triangles, spheres and lights
	Scene s;
	s.tris = triangles;
	s.spheres = spheres;
	//Light light(glm::vec4(5.0, 0.0, 4.5, 1), 0.9, white);

	//Area lights
	glm::vec4 lv1 = glm::vec4(6,-1, 4.95, 1);
	glm::vec4 lv2 = glm::vec4(6, 1, 4.95, 1);
	glm::vec4 lv3 = glm::vec4(7, 1, 4.95, 1);
	glm::vec4 lv4 = glm::vec4(7, -1, 4.95, 1);
	Triangle alight1 = Triangle(lv1, lv2, lv3, Light, white);
	Triangle alight2 = Triangle(lv1, lv3, lv4, Light, white);
	AreaLight areaLight1 = AreaLight(alight1, 1.0f, white);
	AreaLight areaLight2 = AreaLight(alight2, 1.0f, white);
	
	//Push lights into scene
	s.areaLights.push_back(areaLight1);
	s.areaLights.push_back(areaLight2);

	//Render "scene"
	cam.render(s);
	return 0;
}
