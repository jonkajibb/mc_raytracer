#include "ColorDbl.h"

/*
ColorDbl ColorDbl::shading(Ray &importance, Triangle hitTri, Scene s) {
	bool intersected;
	double t;
	double angle;
	ColorDbl col;
	Direction d(s.light.pos.X - importance.end.X, s.light.pos.Y - importance.end.Y, s.light.pos.Z - importance.end.Z);

	ColorDbl light_i = s.light.color * s.light.intensity; //Light color*intenisty

	Ray sRay(importance.end, d);
	d = d.normalize();
	//Angle between importance ray endpoint normal and sRay's direction
	angle = std::max(0.0, d.dot(hitTri.normal));
	//std::cout << angle << std::endl;

	for (int i = 0; i < s.tris.size(); i++)
	{
		if (s.tris[i].rayIntersection(sRay, t))
		{
			intersected = true;
		}
	}

	if (angle < 0) {
		col = hitTri.color;
	}
	else {
		col = hitTri.color * angle * light_i * intersected;
	}
	/*else if (angle > 1) {
	col = this->color * 0;
	}
	//std::cout << angle << std::endl;

	//Check if sRay intersects something

	return col;
};*/