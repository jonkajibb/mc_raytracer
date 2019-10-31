#pragma once

#include "Vertex.h"
#include "ColorDbl.h"

class Light {
public:
	Light() {
	//	pos;
		intensity = 0;
	//	color;
	}

	Light(Vertex p, double i, ColorDbl c) : pos(p), intensity(i), color(c) {};
	
	Vertex pos;
	double intensity;
	ColorDbl color;
private:

};
