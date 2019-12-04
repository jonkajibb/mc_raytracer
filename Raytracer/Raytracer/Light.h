#pragma once

#include <glm.hpp>

#include "Vertex.h"
#include "ColorDbl.h"

class Light {
public:
	Light() {
	//	pos;
		intensity = 0;
	//	color;
	}

	Light(glm::vec4 p, double i, ColorDbl c) : pos(p), intensity(i), color(c) {};
	
	glm::vec4 pos;
	double intensity;
	ColorDbl color;
private:

};
