#pragma once

#include "Vertex.h"
#include "ColorDbl.h"

class Light {
public:
	Light() {
		intensity = 0;
	}

	Light(Vertex p, double i, ColorDbl c) : pos(p), intensity(i), color(c) {};
	
	Vertex pos;
	double intensity;
	ColorDbl color;
private:

};